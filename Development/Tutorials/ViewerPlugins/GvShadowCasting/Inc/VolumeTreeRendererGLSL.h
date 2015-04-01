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

#ifndef _RENDERER_GLSL_H_
#define _RENDERER_GLSL_H_

/******************************************************************************
 ******************************* INCLUDE SECTION ******************************
 ******************************************************************************/

// GigaVoxels
#include <GvRendering/GvRenderer.h>

/******************************************************************************
 ************************* DEFINE AND CONSTANT SECTION ************************
 ******************************************************************************/

/******************************************************************************
 ***************************** TYPE DEFINITION ********************************
 ******************************************************************************/

/******************************************************************************
 ******************************** CLASS USED **********************************
 ******************************************************************************/

// GigaVoxels
namespace GvUtils
{
	class GsShaderProgram;
}

/******************************************************************************
 ****************************** CLASS DEFINITION ******************************
 ******************************************************************************/

/** 
 * @class VolumeTreeRendererGLSL
 *
 * @brief The VolumeTreeRendererGLSL class provides an implementation of a renderer
 * specialized for GLSL.
 *
 * It implements the renderImpl() method from GvRenderer::GvIRenderer base class
 * and has access to the data structure, cache and producer through the inherited
 * VolumeTreeRenderer base class.
 */
template< typename TVolumeTreeType, typename TVolumeTreeCacheType, typename TSampleShader >
class VolumeTreeRendererGLSL : public GvRendering::GvRenderer< TVolumeTreeType, TVolumeTreeCacheType >
{

	/**************************************************************************
	 ***************************** PUBLIC SECTION *****************************
	 **************************************************************************/

public:

	/****************************** INNER TYPES *******************************/

	/******************************* ATTRIBUTES *******************************/

	/******************************** METHODS *********************************/

	/**
	 * Constructor
	 *
	 * It initializes all OpenGL-related stuff
	 *
	 * @param pVolumeTree data structure to render
	 * @param pVolumeTreeCache cache
	 * @param pProducer producer of data
	 */
	VolumeTreeRendererGLSL( TVolumeTreeType* pVolumeTree, TVolumeTreeCacheType* pVolumeTreeCache );

	/**
	 * Destructor
	 */
	virtual ~VolumeTreeRendererGLSL();

	/**
	 * This function is the specific implementation method called
	 * by the parent GvIRenderer::render() method during rendering.
	 *
	 * @param pModelMatrix the current model matrix
	 * @param pViewMatrix the current view matrix
	 * @param pProjectionMatrix the current projection matrix
	 * @param pViewport the viewport configuration
	 */
	virtual void render( const float4x4& pModelMatrix, const float4x4& pViewMatrix, const float4x4& pProjectionMatrix, const int4& pViewport );

	/**
	 * Get the associated shader program
	 *
	 * @return the associated shader program
	 */
	GsGraphics::GsShaderProgram* getShaderProgram()
	{
		return _shaderProgram;
	}

	/**
	 * Get the cone aperture scale
	 *
	 * @return the cone aperture scale
	 */
	float getConeApertureScale() const;

	/**
	 * Set the cone aperture scale
	 *
	 * @param pValue the cone aperture scale
	 */
	void setConeApertureScale( float pValue );

	/**
	 * Get the max number of loops during the main GigaSpace pipeline pass (GLSL shader)
	 *
	 * @return the max number of loops
	 */
	unsigned int getMaxNbLoops() const;

	/**
	 * Set the max number of loops during the main GigaSpace pipeline pass (GLSL shader)
	 *
	 * @param pValue the max number of loops
	 */
	void setMaxNbLoops( unsigned int pValue );

	/**
	 * ...
	 */
	void setLightPosition( float x, float y, float z );

	/**
	 * ...
	 */
	uint3 getBrickCacheSize();

	/**
	 * ...
	 */
	float3 getBrickPoolResInv();

	/**
	 * ...
	 */
	uint getMaxDepth();

	/**
	 * ...
	 */
	GvCore::Array3DGPULinear< uint >* getVolTreeChildArray();

	/**
	 * ...
	 */
	GvCore::Array3DGPULinear< uint >* getVolTreeDataArray();

	/**
	 * ...
	 */
	GLint getChildBufferName();

	/**
	 * ...
	 */
	GLint getDataBufferName();

	/**************************************************************************
	 **************************** PROTECTED SECTION ***************************
	 **************************************************************************/

protected:

	/****************************** INNER TYPES *******************************/

	/******************************* ATTRIBUTES *******************************/

	/******************************** METHODS *********************************/

	/**************************************************************************
	 ***************************** PRIVATE SECTION ****************************
	 **************************************************************************/

private:

	/****************************** INNER TYPES *******************************/

	/******************************* ATTRIBUTES *******************************/

	/**
	 * Light Position
	 */
	float3 _lightPos;

	/**
	 * Shader program
	 */
	GsGraphics::GsShaderProgram* _shaderProgram;

	/**
	 * Buffer of requests
	 */
	GLuint _updateBufferTBO;

	/**
	 * Node time stamps buffer
	 */
	GLuint _nodeTimeStampTBO;

	/**
	 * Brick time stamps buffer
	 */
	GLuint _brickTimeStampTBO;

	/**
	 * Node pool's child array (i.e. encoded data structure [octree, N3-Tree, etc...])
	 */
	GLuint _childArrayTBO;

	/**
	 * Node pool's data array (i.e. addresses of bricks associated to each node in cache)
	 */
	GLuint _dataArrayTBO;

	/**
	 * Cone aperture scale
	 */
	float _coneApertureScale;

	/**
	 * Max number of loops during the main GigaSpace pipeline pass (GLSL shader)
	 */
	unsigned int _maxNbLoops;
	
	/**
	 * ...
	 */
	uint3 _brickCacheSize;
	float3 brickPoolResInv;
	uint maxDepth;
	GvCore::Array3DGPULinear< uint >* volTreeChildArray;
	GvCore::Array3DGPULinear< uint >* volTreeDataArray;
	GLint childBufferName;
	GLint dataBufferName;

	/******************************** METHODS *********************************/

	/**
	 * Start the rendering process.
	 *
	 * @param pModelMatrix the current model matrix
	 * @param pViewMatrix the current view matrix
	 * @param pProjectionMatrix the current projection matrix
	 * @param pViewport the viewport configuration
	 */
	virtual void doRender( const float4x4& pModelMatrix, const float4x4& pViewMatrix, const float4x4& pProjectionMatrix, const int4& pViewport );

};

/**************************************************************************
 ***************************** INLINE SECTION *****************************
 **************************************************************************/

#include "VolumeTreeRendererGLSL.inl"

#endif // !_RENDERER_GLSL_H_
