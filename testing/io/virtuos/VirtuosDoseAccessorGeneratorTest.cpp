// -----------------------------------------------------------------------
// RTToolbox - DKFZ radiotherapy quantitative evaluation library
//
// Copyright (c) German Cancer Research Center (DKFZ),
// Software development for Integrated Diagnostics and Therapy (SIDT).
// ALL RIGHTS RESERVED.
// See rttbCopyright.txt or
// http://www.dkfz.de/en/sidt/projects/rttb/copyright.html [^]
//
// This software is distributed WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE. See the above copyright notices for more information.
//
//------------------------------------------------------------------------
/*!
// @file
// @version $Revision$ (last changed revision)
// @date $Date$ (last change date)
// @author $Author$ (last changed by)
*/

// this file defines the rttbCoreTests for the test driver
// and all it expects is that you have a function called RegisterTests

#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

#include "litCheckMacros.h"

#include "rttbBaseType.h"
#include "rttbVirtuosCubeinfoDoseAccessorGenerator.h"
#include "rttbVirtuosDoseFileDoseAccessorGenerator.h"
#include "rttbVirtuosPlanFileDoseAccessorGenerator.h"
#include "rttbVirtuosDoseAccessor.h"
#include "rttbInvalidDoseException.h"
#include "rttbInvalidParameterException.h"
#include "../rttbDoseAccessorTester.h"


namespace rttb
{

	namespace testing
	{

		/*! @brief VirtuosDoseAccessorGeneratorTest - test the accessor generator generateDoseAccessor() of virtuos data
				1) test virtuos accessor generator with only dose file
				2) test virtuos accessor generator with dose and plan file
				3) test virtuos accessor generator with cubeinfo
		*/

		int VirtuosDoseAccessorGeneratorTest(int argc, char* argv[])
		{

			PREPARE_DEFAULT_TEST_REPORTING;
			//           1: plan  file name (virtuos)		.../testing/data/Virtuos/prostate_ac/prostate_ac101.pln
			//           2: dose1 file name (virtuos)		.../testing/data/Virtuos/prostate_ac/prostate_ac101.dos.gz

			std::string RTPLAN_FILENAME;
			std::string RTDOSE_FILENAME;

			if (argc > 2)
			{
				RTPLAN_FILENAME = argv[1];
				RTDOSE_FILENAME = argv[2];
			}

			//1) test virtuos accessor generator with only dose file
			CHECK_NO_THROW(io::virtuos::VirtuosDoseFileDoseAccessorGenerator(RTDOSE_FILENAME.c_str(), 0,
			               0).generateDoseAccessor());
			CHECK_THROW_EXPLICIT(
			    io::virtuos::VirtuosDoseFileDoseAccessorGenerator("test.dos.gz", 0, 0).generateDoseAccessor(),
			    core::InvalidParameterException);



			//2) test virtuos accessor generator with dose and plan file
			CHECK_NO_THROW(io::virtuos::VirtuosPlanFileDoseAccessorGenerator(RTDOSE_FILENAME.c_str(), ""));
			CHECK_NO_THROW(io::virtuos::VirtuosPlanFileDoseAccessorGenerator("myDose.dos.gz",
			               RTPLAN_FILENAME.c_str()));

			CHECK_THROW_EXPLICIT(io::virtuos::VirtuosPlanFileDoseAccessorGenerator(RTDOSE_FILENAME.c_str(),
			                     "").generateDoseAccessor(), core::InvalidParameterException);
			CHECK_THROW_EXPLICIT(io::virtuos::VirtuosPlanFileDoseAccessorGenerator("",
			                     RTPLAN_FILENAME.c_str()).generateDoseAccessor(), core::InvalidParameterException);
			CHECK_THROW_EXPLICIT(io::virtuos::VirtuosPlanFileDoseAccessorGenerator(RTDOSE_FILENAME.c_str(),
			                     "myPlanfile.pln").generateDoseAccessor(), core::InvalidParameterException);
			CHECK_THROW_EXPLICIT(io::virtuos::VirtuosPlanFileDoseAccessorGenerator("myDose.dos.gz",
			                     RTPLAN_FILENAME.c_str()).generateDoseAccessor(), core::InvalidParameterException);

			CHECK_NO_THROW(io::virtuos::VirtuosPlanFileDoseAccessorGenerator(RTDOSE_FILENAME.c_str(),
			               RTPLAN_FILENAME.c_str()).generateDoseAccessor());


			std::string testFileName = RTPLAN_FILENAME;
			size_t gzPosition = testFileName.find(".pln");

			if (gzPosition != std::string::npos)
			{
				testFileName.erase(gzPosition, testFileName.length());
			}

			CHECK_THROW_EXPLICIT(io::virtuos::VirtuosPlanFileDoseAccessorGenerator(RTDOSE_FILENAME.c_str(),
			                     testFileName).generateDoseAccessor(), core::InvalidParameterException);

			testFileName = RTDOSE_FILENAME;
			gzPosition = testFileName.find(".dos");

			if (gzPosition != std::string::npos)
			{
				testFileName.erase(gzPosition, testFileName.length());
			}

			CHECK_THROW_EXPLICIT(io::virtuos::VirtuosPlanFileDoseAccessorGenerator(testFileName,
			                     RTPLAN_FILENAME.c_str()).generateDoseAccessor(), core::InvalidParameterException);

			//3) test virtuos accessor generator with cubeinfo
			Cubeinfo** pPointerOnVirtuosCube = new Cubeinfo*;
			*pPointerOnVirtuosCube = create_cubeinfo(0);
			CHECK_NO_THROW(io::virtuos::VirtuosCubeinfoDoseAccessorGenerator(*pPointerOnVirtuosCube));
			CHECK_THROW_EXPLICIT(io::virtuos::VirtuosCubeinfoDoseAccessorGenerator(
			                         *pPointerOnVirtuosCube).generateDoseAccessor(), core::InvalidDoseException);

			nc_init_cubeinfo(*pPointerOnVirtuosCube);
			CHECK_THROW_EXPLICIT(io::virtuos::VirtuosCubeinfoDoseAccessorGenerator(
			                         *pPointerOnVirtuosCube).generateDoseAccessor(), core::InvalidDoseException);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}

	}//testing
}//rttb

