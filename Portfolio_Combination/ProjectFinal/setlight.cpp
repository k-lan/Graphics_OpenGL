// void
// SetPointLight( int ilight, float x, float y, float z,  float r, float g, float b )
// {
// 	GLfloat ambient[] = {1.0f, 0.5f, 0.0f, 1.0f};   // Warm ambient color
// 	GLfloat diffuse[] = {1.0f, 0.2f, 0.0f, 1.0f};   // Intense and warm diffuse color
// 	GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};  // Standard white specular highlight

// 	glLightfv( ilight, GL_POSITION,  Array3( x, y, z ) );
// 	glLightf(  ilight, GL_SPOT_CUTOFF, 180.f );
// 	// glLightfv( ilight, GL_AMBIENT,   MulArray3( 0.1f,  1.f, 1.f, 1.f ) );
// 	// glLightfv( ilight, GL_DIFFUSE,   MulArray3( 0.6f, r, g, b ) );
// 	// glLightfv( ilight, GL_SPECULAR,  MulArray3( 0.4f, 1.f, 1.f, 1.f ) );
// 	// Set light properties
// 	glLightfv(ilight, GL_AMBIENT, ambient);
// 	glLightfv(ilight, GL_DIFFUSE, diffuse);
// 	glLightfv(ilight, GL_SPECULAR, specular);
// 	glLightf ( ilight, GL_CONSTANT_ATTENUATION, 1. );
// 	glLightf ( ilight, GL_LINEAR_ATTENUATION, 0. );
// 	glLightf ( ilight, GL_QUADRATIC_ATTENUATION, 0. );
// 	glEnable( ilight );
// }

void SetPointLight(int ilight, float x, float y, float z, float r, float g, float b) {
    GLfloat ambient[] = {0.5f, 0.1f, 0.0f, 1.0f};   // Dim and warm ambient color
    GLfloat diffuse[] = {1.0f, 0.5f, 0.0f, 1.0f};   // Intense and warm diffuse color
    GLfloat specular[] = {1.0f, 0.8f, 0.5f, 1.0f};  // Warm specular highlight

    glLightfv(ilight, GL_POSITION, Array3(x, y, z));
    glLightf(ilight, GL_SPOT_CUTOFF, 180.f);

    // Set light properties
    glLightfv(ilight, GL_AMBIENT, ambient);
    glLightfv(ilight, GL_DIFFUSE, diffuse);
    glLightfv(ilight, GL_SPECULAR, specular);

    // Attenuation
    glLightf(ilight, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(ilight, GL_LINEAR_ATTENUATION, 0.1f);
    glLightf(ilight, GL_QUADRATIC_ATTENUATION, 0.01f);

    glEnable(ilight);
}

// void SetPointLightCustom(int ilight, float x, float y, float z, float intensityR, float intensityG, float intensityB) {
//     // Set ambient color (dim and warm)
//     GLfloat ambient[] = {0.5f, 0.1f, 0.0f, 1.0f};

//     // Set diffuse color with intensity control
//     GLfloat diffuse[] = {intensityR, intensityG, intensityB, 1.0f};

//     // Set specular color (warm specular highlight)
//     GLfloat specular[] = {1.0f, 0.8f, 0.5f, 1.0f};

//     glLightfv(ilight, GL_POSITION, Array3(x, y, z));
//     glLightf(ilight, GL_SPOT_CUTOFF, 180.f);

//     // Set light properties
//     glLightfv(ilight, GL_AMBIENT, ambient);
//     glLightfv(ilight, GL_DIFFUSE, diffuse);
//     glLightfv(ilight, GL_SPECULAR, specular);

//     // Attenuation
//     glLightf(ilight, GL_CONSTANT_ATTENUATION, 1.0f);
//     glLightf(ilight, GL_LINEAR_ATTENUATION, 0.1f);
//     glLightf(ilight, GL_QUADRATIC_ATTENUATION, 0.01f);

//     glEnable(ilight);
// }

void SetPointLightCustom(int ilight, float x, float y, float z, float intensityR, float intensityG, float intensityB, float brightness) {
    // Set ambient color (dim and warm)
    GLfloat ambient[] = {0.5f, 0.1f, 0.0f, 1.0f};
    // Set ambient color (dim and warm)
    // GLfloat ambient[] = {0.1f, 0.05f, 0.0f, 1.0f};


    // Adjust diffuse color based on brightness
    GLfloat diffuse[] = {intensityR * brightness, intensityG * brightness, intensityB * brightness, 1.0f};


    // Set specular color (warm specular highlight)
    GLfloat specular[] = {1.0f, 0.8f, 0.5f, 1.0f};

    glLightfv(ilight, GL_POSITION, Array3(x, y, z));
    glLightf(ilight, GL_SPOT_CUTOFF, 180.f);

    // Set light properties
    glLightfv(ilight, GL_AMBIENT, ambient);
    glLightfv(ilight, GL_DIFFUSE, diffuse);
    glLightfv(ilight, GL_SPECULAR, specular);

    // Attenuation
    glLightf(ilight, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(ilight, GL_LINEAR_ATTENUATION, 0.1f);
    glLightf(ilight, GL_QUADRATIC_ATTENUATION, 0.01f);

    // glLightf(ilight, GL_CONSTANT_ATTENUATION, 0.5f); // Adjust the value as needed
    // glLightf(ilight, GL_LINEAR_ATTENUATION, 0.05f); // Adjust the value as needed
    // glLightf(ilight, GL_QUADRATIC_ATTENUATION, 0.005f); // Adjust the value as needed


    glEnable(ilight);
}




void
SetSpotLight( int ilight, float x, float y, float z,  float xdir, float ydir, float zdir, float r, float g, float b )
{
	glLightfv( ilight, GL_POSITION,  Array3( x, y, z ) );
	glLightfv( ilight, GL_SPOT_DIRECTION,  Array3(xdir,ydir,zdir) );
	glLightf(  ilight, GL_SPOT_EXPONENT, 1.f );
	glLightf(  ilight, GL_SPOT_CUTOFF, 45.f );
	glLightfv( ilight, GL_AMBIENT,   Array3( 0., 0., 0. ) );
	glLightfv( ilight, GL_DIFFUSE,   Array3( r, g, b ) );
	glLightfv( ilight, GL_SPECULAR,  Array3( r, g, b ) );
	glLightf ( ilight, GL_CONSTANT_ATTENUATION, 1. );
	glLightf ( ilight, GL_LINEAR_ATTENUATION, 0. );
	glLightf ( ilight, GL_QUADRATIC_ATTENUATION, 0. );
	glEnable( ilight );
}

