/*
 * GigaVoxels is a ray-guided streaming library used for efficient
 * 3D real-time rendering of highly detailed volumetric scenes.
 *
 * Copyright (C) 2011-2012 INRIA <http://www.inria.fr/>
 *
 * Authors : GigaVoxels Team
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

#ifndef _SAMPLE_CORE_H_
#define _SAMPLE_CORE_H_

/******************************************************************************
 ******************************* INCLUDE SECTION ******************************
 ******************************************************************************/

// Cuda
#include <cuda_runtime.h>
#include <vector_types.h>

// Loki
#include <loki/Typelist.h>

// OpenGL
#include <GL/glew.h>

// GigaVoxels
#include <GvCore/vector_types_ext.h>
//#include <GvUtils/GvPipeline.h>

// GigaVoxels - TEST
#include <GvUtils/GvTransferFunction.h>

// GvViewer
#include <GvvPipelineInterface.h>

// STL
#include <string>

/******************************************************************************
 ************************* DEFINE AND CONSTANT SECTION ************************
 ******************************************************************************/

/******************************************************************************
 ***************************** TYPE DEFINITION ********************************
 ******************************************************************************/

/******************************************************************************
 ******************************** CLASS USED **********************************
 ******************************************************************************/

// Forward references
namespace GvCore
{
	template< uint r >
	struct StaticRes1D;
}

namespace GvStructure
{
	template<
		class DataTList, class NodeTileRes,
		class BrickRes, uint BorderSize >
	struct GvVolumeTree;

	template <
		typename VolumeTreeType, typename ProducerType,
		typename NodeTileRes, typename BrickFullRes >
	class GvVolumeTreeCache;
}

namespace GvRenderer
{	
	template<
		typename VolumeTreeType, typename VolumeTreeCacheType,
		typename ProducerType, typename SampleShader >
	class GvVolumeTreeRendererCUDA;
}

// Producers
template< typename DataTList, typename NodeRes, typename BrickRes, uint BorderSize >
class ProducerLoad;

// Shaders
class ShaderLoad;

// Defines the type list representing the content of one voxel
typedef Loki::TL::MakeTypelist< uchar4 >::Result DataType;

// Defines the size of a node tile
typedef GvCore::StaticRes1D< 2 > NodeRes;

// Defines the size of a brick
typedef GvCore::StaticRes1D< 8 > BrickRes;

// Defines the size of the border around a brick
enum { BrickBorderSize = 1 };

// Defines the total size of a brick
typedef GvCore::StaticRes1D< 8 + 2 * BrickBorderSize > RealBrickRes;

// Defines the type of the producer
typedef ShaderLoad ShaderType;

// Defines the type of the shader
typedef ProducerLoad< DataType,
	NodeRes, BrickRes, BrickBorderSize > ProducerType;

namespace GvUtils
{	
	template< class DataTList, uint NodeTileRes, uint BrickRes, typename ProducerType, typename SampleShader >
	class GvPipeline;
}

enum { NodeTileSize = 2 };
enum { BrickTileSize = 8 };
// Defines the type of the GigaVoxels pipeine we want to use
//typedef GvUtils::GvPipeline< DataType, 2, 8, ProducerType, ShaderType > PipelineType;
typedef GvUtils::GvPipeline< DataType, NodeTileSize, BrickTileSize, ProducerType, ShaderType > PipelineType;

/******************************************************************************
 ****************************** CLASS DEFINITION ******************************
 ******************************************************************************/

/** 
 * @class SampleCore
 *
 * @brief The SampleCore class provides...
 *
 * ...
 */
class SampleCore : public GvViewerCore::GvvPipelineInterface
{

	/**************************************************************************
	 ***************************** PUBLIC SECTION *****************************
	 **************************************************************************/

public:

	/******************************* ATTRIBUTES *******************************/

	/******************************** METHODS *********************************/

	/**
	 * Constructor
	 */
	SampleCore();

	/**
	 * Destructor
	 */
	virtual ~SampleCore();

	///**
	// * Returns the type of this browsable. The type is used for retrieving
	// * the context menu or when requested or assigning an icon to the
	// * corresponding item
	// *
	// * @return the type name of this browsable
	// */
	//virtual const char* getTypeName() const;
		
	/**
     * Gets the name of this browsable
     *
     * @return the name of this browsable
     */
	virtual const char* getName() const;

	/**
	 * Initialize the GigaVoxels pipeline
	 */
	virtual void init();

	/**
	 * Draw function called of frame
	 */
	virtual void draw();

	/**
	 * Resize the frame
	 *
	 * @param width the new width
	 * @param height the new height
	 */
	virtual void resize( int width, int height );

	/**
	 * Clear the GigaVoxels cache
	 */
	virtual void clearCache();

	/**
	 * Toggle the display of the N-tree (octree) of the data structure
	 */
	virtual void toggleDisplayOctree();

	/**
	 * Toggle the GigaVoxels dynamic update mode
	 */
	virtual void toggleDynamicUpdate();

	/**
	 * Toggle the display of the performance monitor utility if
	 * GigaVoxels has been compiled with the Performance Monitor option
	 *
	 * @param mode The performance monitor mode (1 for CPU, 2 for DEVICE)
	 */
	virtual void togglePerfmonDisplay( uint mode );

	/**
	 * Increment the max resolution of the data structure
	 */
	virtual void incMaxVolTreeDepth();

	/**
	 * Decrement the max resolution of the data structure
	 */
	virtual void decMaxVolTreeDepth();

	/**
	 * Get the node tile resolution of the data structure.
	 *
	 * @param pX the X node tile resolution
	 * @param pY the Y node tile resolution
	 * @param pZ the Z node tile resolution
	 */
	virtual void getDataStructureNodeTileResolution( unsigned int& pX, unsigned int& pY, unsigned int& pZ ) const;

		/**
	 * Get the brick resolution of the data structure (voxels).
	 *
	 * @param pX the X brick resolution
	 * @param pY the Y brick resolution
	 * @param pZ the Z brick resolution
	 */
	virtual void getDataStructureBrickResolution( unsigned int& pX, unsigned int& pY, unsigned int& pZ ) const;
	
	/**
	 * Get the max depth.
	 *
	 * @return the max depth
	 */
	virtual unsigned int getRendererMaxDepth() const;
	
	/**
	 * Set the max depth.
	 *
	 * @param pValue the max depth
	 */
	virtual void setRendererMaxDepth( unsigned int pValue );

	/**
	 * Get the max number of requests of node subdivisions the cache has to handle.
	 *
	 * @return the max number of requests
	 */
	virtual unsigned int getCacheMaxNbNodeSubdivisions() const;

	/**
	 * Set the max number of requests of node subdivisions.
	 *
	 * @param pValue the max number of requests
	 */
	virtual void setCacheMaxNbNodeSubdivisions( unsigned int pValue );

	/**
	 * Get the max number of requests of brick of voxel loads.
	 *
	 * @return the max number of requests
	 */
	virtual unsigned int getCacheMaxNbBrickLoads() const;
	
	/**
	 * Set the max number of requests of brick of voxel loads.
	 *
	 * @param pValue the max number of requests
	 */
	virtual void setCacheMaxNbBrickLoads( unsigned int pValue );
	
	/**
	 * Set the request strategy indicating if, during data structure traversal,
	 * priority of requests is set on brick loads or on node subdivisions first.
	 *
	 * @param pFlag the flag indicating the request strategy
	 */
	virtual void setRendererPriorityOnBricks( bool pFlag );

	/**
	 * Specify color to clear the color buffer
	 *
	 * @param pRed red component
	 * @param pGreen green component
	 * @param pBlue blue component
	 * @param pAlpha alpha component
	 */
	virtual void setClearColor( unsigned char pRed, unsigned char pGreen, unsigned char pBlue, unsigned char pAlpha );

	/**
	 * Tell wheter or not the pipeline has a transfer function.
	 *
	 * @return the flag telling wheter or not the pipeline has a transfer function
	 */
	virtual bool hasTransferFunction() const;

	/**
	 * Update the associated transfer function
	 *
	 * @param the new transfer function data
	 * @param the size of the transfer function
	 */
	virtual void updateTransferFunction( float* pData, unsigned int pSize );

	/**
	 * Get the light position
	 *
	 * @param pX the X light position
	 * @param pY the Y light position
	 * @param pZ the Z light position
	 */
	virtual void getLightPosition( float& pX, float& pY, float& pZ ) const;

	/**
	 * Set the light position
	 *
	 * @param pX the X light position
	 * @param pY the Y light position
	 * @param pZ the Z light position
	 */
	virtual void setLightPosition( float pX, float pY, float pZ );

	/**
	 * Tell wheter or not the pipeline has a 3D model to load.
	 *
	 * @return the flag telling wheter or not the pipeline has a 3D model to load
	 */
	virtual bool has3DModel() const;

	/**
	 * Get the 3D model filename to load
	 *
	 * @return the 3D model filename to load
	 */
	virtual std::string get3DModelFilename() const;

	/**
	 * Set the 3D model filename to load
	 *
	 * @param pFilename the 3D model filename to load
	 */
	virtual void set3DModelFilename( const std::string& pFilename );

	/**
	 * Get the 3D model resolution
	 *
	 * @return the 3D model resolution
	 */
	unsigned int get3DModelResolution() const;

	/**
	 * Set the 3D model resolution
	 *
	 * @param pValue the 3D model resolution
	 */
	void set3DModelResolution( unsigned int pValue );

	/**
	 * Get the threshold
	 *
	 * @return the threshold
	 */
	float getThreshold() const;

	/**
	 * Set the threshold
	 *
	 * @param pValue the threshold
	 */
	void setThreshold( float pValue );

	/**
	 * Get the full opacity distance
	 *
	 * @return the full opacity distance
	 */
	float getFullOpacityDistance() const;

	/**
	 * Set the full opacity distance
	 *
	 * @param pValue the full opacity distance
	 */
	void setFullOpacityDistance( float pValue );

	/**
	 * Get the gradient step
	 *
	 * @return the gradient step
	  */
	float getGradientStep() const;

	/**
	 * Set the gradient step
	 *
	 * @param pValue the gradient step
	 */
	void setGradientStep( float pValue );

	/**************************************************************************
	 **************************** PROTECTED SECTION ***************************
	 **************************************************************************/

protected:

	/******************************* ATTRIBUTES *******************************/

	/**
	 * Light position
	 */
	float3 _lightPosition;

	/**
	 * 3D model filename
	 */
	std::string _filename;

	/**
	 * 3D model resolution
	 */
	unsigned int _resolution;

	/**
	 * Threshold
	 */
	float _threshold;

	/**
	 * Full opacity distance
	 */
	float _fullOpacityDistance;

	/**
	 * Gradient step used to compute local normal with symetric gradient from data
	 */
	float _gradientStep;

	/**
	 * TEST
	 */
	GvUtils::GvTransferFunction* _myTransferFunction;

	/******************************** METHODS *********************************/

	/**************************************************************************
	 ***************************** PRIVATE SECTION ****************************
	 **************************************************************************/

private:

	/******************************* ATTRIBUTES *******************************/

	/**
	 * Producer
	 */
	ProducerType* mProducer;

	/**
	 * GigaVoxels pipeline
	 */
	PipelineType* _pipeline;
	
	/**
	 * ...
	 */
	GLuint mDepthBuffer;

	/**
	 * ...
	 */
	GLuint mColorTex;
	/**
	 * ...
	 */
	GLuint mDepthTex;

	/**
	 * ...
	 */
	GLuint mFrameBuffer;

	/**
	 * ...
	 */
	int mWidth;
	/**
	 * ...
	 */
	int mHeight;

	/**
	 * ...
	 */
	bool mDisplayOctree;
	/**
	 * ...
	 */
	uint mDisplayPerfmon;
	/**
	 * ...
	 */
	uint mMaxVolTreeDepth;

	/******************************** METHODS *********************************/

};

#endif // !_SAMPLE_CORE_H_
