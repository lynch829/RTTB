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

#include "rttbConformityIndex.h"
#include "rttbNullPointerException.h"
#include "rttbInvalidParameterException.h"
#include "rttbExceptionMacros.h"

namespace rttb
{

	namespace indices
	{

		ConformityIndex::ConformityIndex(core::DVHSet::Pointer dvhSet, DoseTypeGy aDoseReference)
			: DvhBasedDoseIndex(dvhSet, aDoseReference)
		{
			init();
		}

		bool ConformityIndex::calcIndex()
		{
			VolumeType TV = _dvhSet->getTargetVolume(0);
			VolumeType Vref = _dvhSet->getWholeVolume(_doseReference);

			if (TV != 0 && Vref != 0)
			{
				_value = (_dvhSet->getTargetVolume(this->_doseReference) / TV) * (1 -
				         _dvhSet->getHealthyTissueVolume(_doseReference) / Vref);
			}
			else if (TV == 0)
			{
				throw core::InvalidParameterException("DVH Set invalid: Target volume should not be 0!");
			}
			else
			{
				rttbExceptionMacro(core::InvalidParameterException,
				                   << "Reference dose " << this->getDoseReference() <<
				                   " invalid: Volume of reference dose should not be 0!");
			}

			return true;
		}

		IndexValueType ConformityIndex::getValueAt(core::DVHSet::IndexType tvIndex)
		{
			std::vector<core::DVH> dvhTVSet = this->_dvhSet->getTargetVolumeSet();
			VolumeType Vref = _dvhSet->getWholeVolume(_doseReference);

			if (tvIndex >= dvhTVSet.size())
			{
				rttbExceptionMacro(core::InvalidParameterException,
				                   << "tvIndex invalid: it should be <" << dvhTVSet.size() << "!");
			}
			else
			{
				core::DVH dvh = dvhTVSet.at(tvIndex);
				VolumeType TV = dvh.getVx(0);

				if (TV == 0)
				{
					throw core::InvalidParameterException("DVH invalid: Volume of tvIndex should not be 0!");
				}
				else if (Vref == 0)
				{
					rttbExceptionMacro(core::InvalidParameterException,
					                   << "Reference dose " << this->getDoseReference() <<
					                   " invalid: Volume of reference dose should not be 0!");
				}

				double value = dvh.getVx(_doseReference) / TV; //the irradiation factor of i-th treated volume
				value = value * (1 - _dvhSet->getHealthyTissueVolume(_doseReference) / Vref);
				return value;
			}
		}

	}//end namespace indices
}//end namespace rttb
