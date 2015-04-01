////////////////////////////////////////////////////////////////////////////////
//
// VERTEX SHADER
//
// Front to back peeling
// - This shader program is used render a mesh
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// VERSION
////////////////////////////////////////////////////////////////////////////////

#version 400

////////////////////////////////////////////////////////////////////////////////
// INPUT
////////////////////////////////////////////////////////////////////////////////

// Model space vertex position (i.e object space)
layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec3 iNormal;
//layout (location = 2) in vec2 iTexCoords;

////////////////////////////////////////////////////////////////////////////////
// UNIFORM
////////////////////////////////////////////////////////////////////////////////

// Model-View matrix
uniform mat4 uModelViewMatrix;

// Projection matrix
uniform mat4 uProjectionMatrix;

// Model-View Projection matrix
//uniform mat4 uModelViewProjectionMatrix;

// Normal matrix
uniform mat3 uNormalMatrix;

////////////////////////////////////////////////////////////////////////////////
// OUTPUT
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PROGRAM
////////////////////////////////////////////////////////////////////////////////
void main()
{
	// Transform model space position to clip space
	gl_Position = uProjectionMatrix * uModelViewMatrix * vec4( iPosition, 1.0 );
	//gl_Position = uModelViewProjectionMatrix * vec4( iPosition, 1.0 );
}
