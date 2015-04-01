﻿////////////////////////////////////////////////////////////////////////////////
//
// TESSELATION CONTROL SHADER
//
// Terrain rendering
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// VERSION
////////////////////////////////////////////////////////////////////////////////

#version 400

////////////////////////////////////////////////////////////////////////////////
// INPUT
////////////////////////////////////////////////////////////////////////////////

in vec3 vPosition[];
in vec3 vNormal[];

////////////////////////////////////////////////////////////////////////////////
// UNIFORM
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// OUTPUT
////////////////////////////////////////////////////////////////////////////////

// Number of vertices in output patch
layout( vertices = 3 ) out;

out vec3 tcPosition[];
out vec3 tcNormal[];

////////////////////////////////////////////////////////////////////////////////
// PROGRAM
////////////////////////////////////////////////////////////////////////////////
void main()
{
	// ...
	gl_out[ gl_InvocationID ].gl_Position = gl_in[ gl_InvocationID ].gl_Position;

	// Define the tesselation levels
	gl_TessLevelOuter[ 0 ] = 4.0;
	gl_TessLevelOuter[ 1 ] = 4.0;
	gl_TessLevelOuter[ 2 ] = 4.0;
	gl_TessLevelInner[ 0 ] = 2.0;

	tcPosition[ gl_InvocationID ] = vPosition[ gl_InvocationID ];
	tcNormal[ gl_InvocationID ] = vNormal[ gl_InvocationID ];
}
