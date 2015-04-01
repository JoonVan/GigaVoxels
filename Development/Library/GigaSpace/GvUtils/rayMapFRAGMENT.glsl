////////////////////////////////////////////////////////////////////////////////
//
// Fragment Shader
//
// Ray Map
//
////////////////////////////////////////////////////////////////////////////////

// Sreen resolution (width x height)
// It has been inverted to optimize code
uniform vec2 uScreenResolutionInverse;

////////////////////////////////////////////////////////////////////////////////
// Program
////////////////////////////////////////////////////////////////////////////////
void main()
{
	// Retrieve pixel coordinates between [ 0.0 ; 1.0 ]
	vec2 uv = gl_FragCoord.xy * uScreenResolutionInverse;

	// Compute ray direction
	vec3 rayDirection = vec3( 2.0f * uv - 1.0f, 1.0f );

	// Write output
	gl_FragColor = vec4( rayDirection, 0.0f );
}
