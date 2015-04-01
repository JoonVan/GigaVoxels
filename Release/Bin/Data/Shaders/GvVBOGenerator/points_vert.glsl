////////////////////////////////////////////////////////////////////////////////
//
// VERTEX SHADER
//
// Points
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// VERSION
////////////////////////////////////////////////////////////////////////////////

#version 400

////////////////////////////////////////////////////////////////////////////////
// INPUT
////////////////////////////////////////////////////////////////////////////////

layout (location = 0) in vec3 VertexPosition;

////////////////////////////////////////////////////////////////////////////////
// UNIFORM
////////////////////////////////////////////////////////////////////////////////

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;
uniform float PointSize;

////////////////////////////////////////////////////////////////////////////////
// OUTPUT
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PROGRAM
////////////////////////////////////////////////////////////////////////////////
void main()
{
	gl_PointSize = PointSize;

	gl_Position = ProjectionMatrix * ModelViewMatrix * vec4( VertexPosition, 1.0 );
}
