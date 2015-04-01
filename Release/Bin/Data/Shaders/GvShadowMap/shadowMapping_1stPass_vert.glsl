////////////////////////////////////////////////////////////////////////////////
//
// VERTEX SHADER
//
// Shadow Mapping
//
// - 1st pass
//
// The scene is rendered from the point of view of the light source.
// Depth is written automatically in the shadow map.
//
// Mandatory :
// - a FBO (frame buffer object) with a unique depth texture bound to its depth attachement
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// VERSION
////////////////////////////////////////////////////////////////////////////////

#version 400

////////////////////////////////////////////////////////////////////////////////
// INPUT
////////////////////////////////////////////////////////////////////////////////

// Vertex position
layout (location = 0) in vec3 iPosition;

////////////////////////////////////////////////////////////////////////////////
// UNIFORM
////////////////////////////////////////////////////////////////////////////////

// Model View Projection matrix
uniform mat4 uModelViewProjectionMatrix;

////////////////////////////////////////////////////////////////////////////////
// OUTPUT
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PROGRAM
////////////////////////////////////////////////////////////////////////////////
void main()
{
	// Transform position from Model space to Clip space
	gl_Position = uModelViewProjectionMatrix * vec4( iPosition, 1.0 );
}
