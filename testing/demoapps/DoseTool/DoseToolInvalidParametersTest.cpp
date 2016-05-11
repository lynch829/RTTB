// -----------------------------------------------------------------------
// RTToolbox - DKFZ radiotherapy quantitative evaluation library
//
// Copyright (c) German Cancer Research Center (DKFZ),
// Software development for Integrated Diagnostics and Therapy (SIDT).
// ALL RIGHTS RESERVED.
// See rttbCopyright.txt or
// http://www.dkfz.de/en/sidt/projects/rttb/copyright.html
//
// This software is distributed WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the above copyright notices for more information.
//
//------------------------------------------------------------------------
/*!
// @file
// @version $Revision$ (last changed revision)
// @date    $Date$ (last change date)
// @author  $Author$ (last changed by)
*/

#include <iostream>

#include "litCheckMacros.h"

#include "boost/filesystem.hpp"

namespace rttb
{
	namespace testing
	{

		//path to the current running directory. DoseTool is in the same directory (Debug/Release)
		extern const char* _callingAppPath;

		int DoseToolInvalidParametersTest(int argc, char* argv[])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			std::string doseToolExecutable;

			if (argc > 1)
			{
				doseToolExecutable = argv[1];
			}

			boost::filesystem::path callingPath(_callingAppPath);
			std::string doseToolExeWithPath = callingPath.parent_path().string() + "/" + doseToolExecutable;

			//call with too few parameters
			std::string toofewParametersCommand = doseToolExeWithPath;
			toofewParametersCommand += " -d test";
			toofewParametersCommand += " -s test";
			std::cout << "Command line call: " + toofewParametersCommand << std::endl;
			CHECK_EQUAL(system(toofewParametersCommand.c_str()) != 0, true);

			toofewParametersCommand = doseToolExeWithPath;
			toofewParametersCommand += " -s test";
			toofewParametersCommand += " -n test";
			std::cout << "Command line call: " + toofewParametersCommand << std::endl;
			CHECK_EQUAL(system(toofewParametersCommand.c_str()) != 0, true);

			toofewParametersCommand = doseToolExeWithPath;
			toofewParametersCommand += " test";
			toofewParametersCommand += " test";
			std::cout << "Command line call: " + toofewParametersCommand << std::endl;
			CHECK_EQUAL(system(toofewParametersCommand.c_str()) != 0, true);

			toofewParametersCommand = doseToolExeWithPath;
			toofewParametersCommand += " -d test";
			toofewParametersCommand += " -s test";
			toofewParametersCommand += " -n test";
			std::cout << "Command line call: " + toofewParametersCommand << std::endl;
			CHECK_EQUAL(system(toofewParametersCommand.c_str()) != 0, true);

			//call with invalid dose load option
			std::string minimalCLI = doseToolExeWithPath + " test test test ";
			std::string invalidDoseLoadOption = minimalCLI;
			invalidDoseLoadOption += "-t wrongOption";
			std::cout << "Command line call: " + invalidDoseLoadOption << std::endl;
			CHECK_EQUAL(system(invalidDoseLoadOption.c_str()) != 0, true);

			//call with invalid struct load option
			std::string invalidStructLoadOption = minimalCLI;
			invalidStructLoadOption += "-u wrongOption";
			std::cout << "Command line call: " + invalidStructLoadOption << std::endl;
			CHECK_EQUAL(system(invalidStructLoadOption.c_str()) != 0, true);

			//call with virtuos dose load option, but without plan/ctx
			std::string invalidVirtuosDoseLoadOption = minimalCLI;
			invalidVirtuosDoseLoadOption += "-u virtuos";
			std::cout << "Command line call: " + invalidVirtuosDoseLoadOption << std::endl;
			CHECK_EQUAL(system(invalidVirtuosDoseLoadOption.c_str()) != 0, true);

			std::string invalidVirtuosStructLoadOption = minimalCLI;
			invalidVirtuosStructLoadOption += "-t virtuos";
			std::cout << "Command line call: " + invalidVirtuosStructLoadOption << std::endl;
			CHECK_EQUAL(system(invalidVirtuosStructLoadOption.c_str()) != 0, true);

			//call with complex dose statistics, but without prescribed dose
			std::string complexDoseWithoutPrescribedDoseCommand = minimalCLI;
			complexDoseWithoutPrescribedDoseCommand += "-x";
			std::cout << "Command line call: " + complexDoseWithoutPrescribedDoseCommand << std::endl;
			CHECK_EQUAL(system(complexDoseWithoutPrescribedDoseCommand.c_str()) != 0, true);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace rttb