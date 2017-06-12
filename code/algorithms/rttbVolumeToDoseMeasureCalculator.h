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
// @version $Revision: 1674 $ (last changed revision)
// @date    $Date: 2017-01-27 10:34:46 +0100 (Fr, 27 Jan 2017) $ (last change date)
// @author  $Author: hentsch $ (last changed by)
*/

#ifndef __VOLUME_TO_DOSE_MEASURE_CALCULATOR_H
#define __VOLUME_TO_DOSE_MEASURE_CALCULATOR_H

#include "rttbVolumeToDoseMeasure.h"

namespace rttb
{

	namespace algorithms
	{
		class RTTBAlgorithms_EXPORT VolumeToDoseMeasureCalculator {

		public:
			typedef std::map<VolumeType, DoseTypeGy> VolumeToDoseFunctionType;

		protected:
			std::vector<DoseTypeGy> _doseVector;
			DoseVoxelVolumeType _currentVoxelVolume;
			std::vector<double> _voxelProportionVector;

		private:
			VolumeType _volume;
			VolumeToDoseMeasure measure;
			std::vector<double> _precomputeVolumeValues;

		public:
			/*!  @brief Computes the measure. Algorithm for the specific complex Statistic has to be implemented in the corresponding subclass.
			*/
			void compute();
			VolumeToDoseMeasure getMeasure();

		protected:
			VolumeToDoseMeasureCalculator(const std::vector<double>& precomputeVolumeValues, const VolumeType volume,
				const std::vector<DoseTypeGy>& doseVector, const std::vector<double>& voxelProportionVector,
				const DoseVoxelVolumeType currentVoxelVolume, VolumeToDoseMeasure::complexStatistics name);
			void insertIntoMeasure(VolumeType xAbsolute, DoseTypeGy resultDose);
			virtual DoseTypeGy computeSpecificValue(double xAbsolute) const = 0;
		};

	}
}


#endif
