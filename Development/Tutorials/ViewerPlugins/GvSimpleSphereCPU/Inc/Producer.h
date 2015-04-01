/*
 * GigaVoxels is a ray-guided streaming library used for efficient
 * 3D real-time rendering of highly detailed volumetric scenes.
 *
 * Copyright (C) 2011-2013 INRIA <http://www.inria.fr/>
 *
 * Authors : GigaVoxels Team
 *
 * GigaVoxels is distributed under a dual-license scheme.
 * You can obtain a specific license from Inria at gigavoxels-licensing@inria.fr.
 * Otherwise the default license is the GPL version 3.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/** 
 * @version 1.0
 */

#ifndef _PRODUCER_H_
#define _PRODUCER_H_

/******************************************************************************
 ******************************* INCLUDE SECTION ******************************
 ******************************************************************************/

// GigaVoxels
#include <GvUtils/GvSimpleHostProducer.h>

// Project
#include "ProducerKernel.h"

/******************************************************************************
 ************************* DEFINE AND CONSTANT SECTION ************************
 ******************************************************************************/

/******************************************************************************
 ***************************** TYPE DEFINITION ********************************
 ******************************************************************************/

/******************************************************************************
 ******************************** CLASS USED **********************************
 ******************************************************************************/

/******************************************************************************
 ****************************** CLASS DEFINITION ******************************
 ******************************************************************************/

/** 
 * @class Producer
 *
 * @brief The Producer class provides the mecanisms to produce data
 * following data requests emitted during N-tree traversal (rendering).
 *
 * It is the main user entry point to produce data from CPU, for instance,
 * loading data from disk or procedurally generating data.
 *
 * This class is implements the mandatory functions of the GvIProvider base class.
 */
template< typename TDataStructureType, typename TDataProductionManager >
class Producer : public GvUtils::GvSimpleHostProducer< ProducerKernel< TDataStructureType >, TDataStructureType, TDataProductionManager >
{

	/**************************************************************************
	 ***************************** PUBLIC SECTION *****************************
	 **************************************************************************/

public:

	/****************************** INNER TYPES *******************************/

	/**
	 * Type definition of the inherited parent class
	 */
	typedef GvUtils::GvSimpleHostProducer< ProducerKernel< TDataStructureType >, TDataStructureType, TDataProductionManager > ParentClassType;

	/**
	 * Type definition of the node tile resolution
	 */
	typedef typename TDataStructureType::NodeTileResolution NodeRes;

	/**
	 * Type definition of the brick resolution
	 */
	typedef typename TDataStructureType::BrickResolution BrickRes;

	/**
	 * Enumeration to define the brick border size
	 */
	enum
	{
		BorderSize = TDataStructureType::BrickBorderSize
	};

	/**
	 * Linear representation of a node tile
	 */
	//typedef typename TDataProductionManager::NodeTileResLinear NodeTileResLinear;
	typedef typename ParentClassType::NodeTileResLinear NodeTileResLinear;

	/**
	 * Type definition of the full brick resolution (i.e. with border)
	 */
	typedef typename TDataProductionManager::BrickFullRes BrickFullRes;
	//typedef typename ParentClassType::BrickFullRes BrickFullRes;
	
	/**
	 * Defines the data type list
	 */
	typedef typename TDataStructureType::DataTypeList DataTList;
	
	/**
	 * Typedef the kernel part of the producer
	 */
	typedef ProducerKernel< TDataStructureType > KernelProducerType;
	//typedef typename ParentClassType::KernelProducer KernelProducerType;

	/**
	 * This pool will contains an array for each voxel's field
	 */
	typedef GvCore::GPUPoolHost< GvCore::Array3D, DataTList > BricksPool;
		
	/******************************* ATTRIBUTES *******************************/
	
	/**
	 * Defines the maximum number of requests we can handle in one pass
	 */
	static const uint nbMaxRequests = 128;

	/******************************** METHODS *********************************/

	/**
	 * Constructor.
	 * Initialize all buffers.
	 */
	Producer();

	/**
	 * Destructor
	 */
	virtual ~Producer();

	/**
	 * Initialize
	 *
	 * @param pDataStructure data structure
	 * @param pDataProductionManager data production manager
	 */
	virtual void initialize( TDataStructureType* pDataStructure, TDataProductionManager* pDataProductionManager );

	/**
	 * Finalize
	 */
	virtual void finalize();
	
	/**
	 * This method is called by the cache manager when you have to produce data for a given pool.
	 * Implement the produceData method for the channel 0 (nodes)
	 *
	 * @param pNumElems the number of elements you have to produce.
	 * @param pNodeAddressCompactList a list containing the addresses of the numElems nodes concerned.
	 * @param pElemAddressCompactList a list containing numElems addresses where you need to store the result.
	 * @param pGpuPool the pool for which we need to produce elements.
	 * @param pPageTable the page table associated to the pool
	 * @param Loki::Int2Type< 0 > corresponds to the index of the node pool
	 */
	inline virtual void produceData( uint pNumElems,
									thrust::device_vector< uint >* pNodesAddressCompactList,
									thrust::device_vector< uint >* pElemAddressCompactList,
									Loki::Int2Type< 0 > );
	
	/**
	 * This method is called by the cache manager when you have to produce data for a given pool.
	 * Implement the produceData method for the channel 1 (bricks)
	 *
	 * @param pNumElems the number of elements you have to produce.
	 * @param pNodeAddressCompactList a list containing the addresses of the numElems nodes concerned.
	 * @param pElemAddressCompactList a list containing numElems addresses where you need to store the result.
	 * @param pGpuPool the pool for which we need to produce elements.
	 * @param pPageTable the page table associated to the pool
	 * @param Loki::Int2Type< 1 > corresponds to the index of the brick pool
	 */
	inline virtual void produceData( uint pNumElems,
									thrust::device_vector< uint >* pNodesAddressCompactList,
									thrust::device_vector< uint >* pElemAddressCompactList,
									Loki::Int2Type< 1 > );

	/**************************************************************************
	 **************************** PROTECTED SECTION ***************************
	 **************************************************************************/

protected:

	/******************************* ATTRIBUTES *******************************/

	/******************************** METHODS *********************************/

	/**
	 * Test if a point is in the unit sphere centered at [0,0,0]
	 *
	 * @param pPoint the point to test
	 *
	 * @return a flag to tell wheter or not the point is in the sphere
	 */
	inline bool isInSphere( const float3& pPoint ) const;

	/**
	 * Produce nodes
	 *
	 * Node production is associated to node subdivision to refine data.
	 * With the help of an oracle, user has to tell what is inside each subregion
	 * of its children.
	 *
	 * @param pNbElements number of elements to process (i.e. nodes)
	 * @param pRequestListCodePtr localization code list on device
	 * @param pRequestListDepthPtr localization depth list on device
	 */
	inline void produceNodes( const uint pNbElements, const GvCore::GvLocalizationInfo::CodeType* pRequestListCodePtr, const GvCore::GvLocalizationInfo::DepthType* pRequestListDepthPtr );

	/**
	 * Produce bricks
	 *
	 * Brick production is associated to fill brick with voxels.
	 *
	 * @param pNbElements number of elements to process (i.e. bricks)
	 * @param pRequestListCodePtr localization code list on device
	 * @param pRequestListDepthPtr localization depth list on device
	 */
	inline void produceBricks( const uint pNbElements, const GvCore::GvLocalizationInfo::CodeType* pRequestListCodePtr, const GvCore::GvLocalizationInfo::DepthType* pRequestListDepthPtr );

	/**
	 * Helper function used to retrieve the number of voxels at a given level of resolution
	 *
	 * @param pLevel level of resolution
	 *
	 * @return the number of voxels at given level of resolution
	 */
	inline uint3 getLevelResolution( const uint pLevel ) const;

	/**************************************************************************
	 ***************************** PRIVATE SECTION ****************************
	 **************************************************************************/

private:

	/******************************* ATTRIBUTES *******************************/

	/**
	 * ...
	 */
	GvCore::GvLocalizationInfo::CodeType* requestListCode;

	/**
	 * ...
	 */
	GvCore::GvLocalizationInfo::DepthType* requestListDepth;

	/**
	 * Node pool
	 */
	GvCore::Array3D< uint >* nodesBuffer;

	/**
	 * Data pool
	 */
	BricksPool* bricksPool;

	/**
	 * ...
	 */
	thrust::device_vector< GvCore::GvLocalizationInfo::CodeType >* requestListCodeDevice;

	/**
	 * ...
	 */
	thrust::device_vector< GvCore::GvLocalizationInfo::DepthType >* requestListDepthDevice;

};

/**************************************************************************
 ***************************** INLINE SECTION *****************************
 **************************************************************************/

#include "Producer.inl"

#endif // !_PRODUCER_H_
