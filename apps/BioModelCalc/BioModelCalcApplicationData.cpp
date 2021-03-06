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

#include "BioModelCalcApplicationData.h"

#include "BioModelCmdLineParser.h"

namespace rttb
{
	namespace apps
	{
		namespace bioModelCalc
		{
			ApplicationData::
			ApplicationData()
			{
				this->reset();
			}

			void
			ApplicationData::
			reset()
			{
				_doseFileName = "";
				_outputFileName = "";
				_doseScaling = 1.0;
                _nFractions = 1;
                _modelParameters.clear();
                _modelParameterMapsFilename.clear();
                _modelParameterMaps.clear();
			}

			void populateAppData(boost::shared_ptr<BioModelCmdLineParser> argParser, ApplicationData& appData)
			{
				appData._doseFileName = argParser->get<std::string>(argParser->OPTION_DOSE_FILE);
				appData._doseLoadStyle = argParser->get<std::string>(argParser->OPTION_LOAD_STYLE);
				appData._doseScaling = argParser->get<double>(argParser->OPTION_DOSE_SCALING);
				appData._outputFileName = argParser->get<std::string>(argParser->OPTION_OUTPUT_FILE);
				appData._model = argParser->get<std::string>(argParser->OPTION_MODEL);
                if (argParser->isSet(argParser->OPTION_MODEL_PARAMETERS)){
                    appData._modelParameters = argParser->get<std::vector<double> >(argParser->OPTION_MODEL_PARAMETERS);
                }
                else {
                    appData._modelParameterMapsFilename = argParser->get<std::vector<std::string> >(argParser->OPTION_MODEL_PARAMETER_MAPS);
                    appData._parameterMapsLoadStyle = argParser->get<std::string>(argParser->OPTION_LOAD_STYLE_PARAMETER_MAPS);
                }
                if (argParser->isSet(argParser->OPTION_N_FRACTIONS)){
                    appData._nFractions = argParser->get<unsigned int>(argParser->OPTION_N_FRACTIONS);
                }
			}

		}
	}
}
