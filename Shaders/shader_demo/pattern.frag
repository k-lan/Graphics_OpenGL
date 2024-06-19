// make this 120 for the mac:
// #version 120 compatibility

// lighting uniform variables -- these can be set once and left alone:
uniform float   uKa, uKd, uKs;	 // coefficients of each type of lighting -- make sum to 1.0
uniform vec3    uColor;		 // object color
uniform vec3    uSpecularColor;	 // light color
uniform float   uShininess;	 // specular exponent

// square-equation uniform variables -- these should be set every time Display( ) is called:

//uniform float   uS0, uT0, uD;

// ellipse-equation uniform variables - Set everytime display is called.
uniform float	uSc, uTc, uRs, uRt;

// in variables from the vertex shader and interpolated in the rasterizer:

varying  vec3  vN;		   // normal vector
varying  vec3  vL;		   // vector from point to light
varying  vec3  vE;		   // vector from point to eye
varying  vec2  vST;		   // (s,t) texture coordinates


void
main( )
{
	float s = vST.s;
	float t = vST.t;

	// determine the color using the square-boundary equations:

	vec3 myColor = uColor;
	//if( uS0-uD/2. <= s  &&  s <= uS0+uD/2.  &&  uT0-uD/2. <= t  &&  t <= uT0+uD/2. )
	//{
	//	myColor = vec3( 1., 1., 1. );
	//}
	//if (((s - uS0) * (s - uS0)) / (uD * uD) + ((s - uT0) * (s - uT0)) / (uD * uD) <= 1.)  {

	if( (( ( (s - uSc) * (s - uSc) ) / (uRs * uRs)) ) + ( ( ( (t - uTc) * (t - uTc) ) / (uRt * uRt)) ) <= 1. ) {
		myColor = vec3( 1., 1., 1. );
	}

	// apply the per-fragmewnt lighting to myColor:

	vec3 Normal = normalize(vN);
	vec3 Light  = normalize(vL);
	vec3 Eye    = normalize(vE);

	vec3 ambient = uKa * myColor;

	float dd = max( dot(Normal,Light), 0. );       // only do diffuse if the light can see the point
	vec3 diffuse = uKd * dd * myColor;

	float ss = 0.;
	if( dot(Normal,Light) > 0. )	      // only do specular if the light can see the point
	{
		vec3 ref = normalize(  reflect( -Light, Normal )  );
		ss = pow( max( dot(Eye,ref),0. ), uShininess );
	}
	vec3 specular = uKs * ss * uSpecularColor;
	gl_FragColor = vec4( ambient + diffuse + specular,  1. );
}

