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
#ifndef __GENERIC_DOSE_ITERATOR_INTERFACE_NEW_H
#define __GENERIC_DOSE_ITERATOR_INTERFACE_NEW_H


#include <string>
#include <vector>
#include <exception>

#include "rttbBaseType.h"
#include "rttbDoseIteratorInterface.h"

#include "RTTBCoreExports.h"

namespace rttb
{
	namespace core
	{

		/*! @class GenericDoseIterator
			@brief Standard implementation of the dose iterator interface.
		*/
		class RTTBCore_EXPORT GenericDoseIterator : public DoseIteratorInterface
		{
		public:
			typedef DoseIteratorInterface::DoseAccessorPointer DoseAccessorPointer;
			typedef DoseIteratorInterface::DoseIteratorPointer DoseIteratorPointer;

		private:

			VoxelGridID _currentDoseVoxelGridID;
			DoseVoxelVolumeType _currentVoxelVolume;

			GenericDoseIterator(const GenericDoseIterator&); //not implemented on purpose -> non-copyable
			GenericDoseIterator& operator=(const
			                               GenericDoseIterator&);//not implemented on purpose -> non-copyable

		public:

			/*! @brief Constructor
				@param aDoseAccessor contains the corresponding dose data
			*/
			GenericDoseIterator(DoseAccessorPointer aDoseAccessor);

			/*! @brief Set the itterator to the start of the Dose.
				@exception InvalidParameterException if a inhomogeneous grid is defined in the dose accessors, because
				these grids are currently not supported.
			*/
			bool reset();

			/*! @brief Test if next voxel position is still on the data grid, if so move to next position.
			*/
			void next();

			/*! @brief Determine if the current voxel position is valid.
			*/
			bool isPositionValid() const;

			/*! @brief Return volume of one voxel (in cm3)
			@exception InvalidParameterException if a inhomogeneous grid is defined in the dose accessors, because
			these grids are currently not supported.
			*/
			DoseVoxelVolumeType getCurrentVoxelVolume() const;

			DoseTypeGy getCurrentDoseValue() const;

			/*! @brief For DoseIterators this function returns 1, always, because no mask is applied.
			*/
			inline FractionType getCurrentRelevantVolumeFraction() const
			{
				return 1;
			};

			inline VoxelGridID getCurrentVoxelGridID() const
			{
				return _currentDoseVoxelGridID;
			};

		};
	}
}

#endif
