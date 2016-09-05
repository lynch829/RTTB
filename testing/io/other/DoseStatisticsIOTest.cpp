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
#include <boost/lexical_cast.hpp>
#include <map>

#include "litCheckMacros.h"

#include "rttbBaseType.h"
#include "rttbDoseStatistics.h"
#include "rttbDoseStatisticsCalculator.h"
#include "rttbDoseStatisticsXMLWriter.h"
#include "rttbDoseStatisticsXMLReader.h"
#include "rttbGenericDoseIterator.h"
#include "rttbDoseIteratorInterface.h"
#include "rttbInvalidParameterException.h"
#include "rttbNullPointerException.h"

#include "../../core/DummyDoseAccessor.h"

#include "CompareDoseStatistic.h"


namespace rttb
{

	namespace testing
	{

		/*! @brief OtherIOTest - test the IO for dose statistics
		1) test exception
		2) test writing statistics to xml file
		*/

		int DoseStatisticsIOTest(int argc, char* argv[])
		{
			typedef core::GenericDoseIterator::DoseAccessorPointer DoseAccessorPointer;
			typedef core::DoseIteratorInterface::DoseIteratorPointer DoseIteratorPointer;
			typedef boost::shared_ptr<rttb::algorithms::DoseStatisticsCalculator> DoseStatisticsCalculatorPtr;

			PREPARE_DEFAULT_TEST_REPORTING;

			/* generate dummy dose */
			boost::shared_ptr<DummyDoseAccessor> spTestDoseAccessor = boost::make_shared<DummyDoseAccessor>();
			DoseAccessorPointer spDoseAccessor(spTestDoseAccessor);

			boost::shared_ptr<core::GenericDoseIterator> spTestDoseIterator =
			    boost::make_shared<core::GenericDoseIterator>(spDoseAccessor);
			DoseIteratorPointer spDoseIterator(spTestDoseIterator);

			rttb::algorithms::DoseStatisticsCalculator myDoseStatsCalculator(spDoseIterator);
			auto myDoseStatsSimple = myDoseStatsCalculator.calculateDoseStatistics();
			auto myDoseStatsComplex = myDoseStatsCalculator.calculateDoseStatistics(true);

			/* test writing statistics to xml file */
			FileNameString filenameSimple = "testStatisticsSimple.xml";
			CHECK_NO_THROW(io::other::writeDoseStatistics(myDoseStatsSimple, filenameSimple));
			io::other::DoseStatisticsXMLReader readerSimple= io::other::DoseStatisticsXMLReader(filenameSimple);
			boost::shared_ptr<rttb::algorithms::DoseStatistics> rereadSimplyDose;
			CHECK_NO_THROW(rereadSimplyDose = readerSimple.generateDoseStatistic());
			CHECK(checkEqualDoseStatistic(myDoseStatsSimple, rereadSimplyDose));

			FileNameString filenameComplex = "testStatisticsComplex.xml";
			CHECK_NO_THROW(io::other::writeDoseStatistics(myDoseStatsComplex, filenameComplex));

			io::other::DoseStatisticsXMLReader readerComplex = io::other::DoseStatisticsXMLReader(filenameComplex);
			boost::shared_ptr<rttb::algorithms::DoseStatistics> rereadComplexDose;
			
			CHECK_NO_THROW(rereadComplexDose = readerComplex.generateDoseStatistic());
			CHECK(checkEqualDoseStatistic(myDoseStatsComplex, rereadComplexDose));



			/* test writing statistics to string */
			boost::property_tree::ptree ptSimple = io::other::writeDoseStatistics(myDoseStatsSimple);
			XMLString strSimple = io::other::writerDoseStatisticsToString(myDoseStatsSimple);

			boost::property_tree::ptree ptComplex = io::other::writeDoseStatistics(myDoseStatsComplex);
			XMLString strComplex = io::other::writerDoseStatisticsToString(myDoseStatsComplex);

			std::stringstream sstrSimple;
			boost::property_tree::xml_parser::write_xml(sstrSimple, ptSimple,
			        boost::property_tree::xml_writer_make_settings<std::string>('\t',
			                1));
			CHECK_EQUAL(strSimple, sstrSimple.str());

			std::stringstream sstrComplex;
			boost::property_tree::xml_parser::write_xml(sstrComplex, ptComplex,
			        boost::property_tree::xml_writer_make_settings<std::string>('\t',
			                1));
			CHECK_EQUAL(strComplex, sstrComplex.str());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}

	}//testing
}//rttb



