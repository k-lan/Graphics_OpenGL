#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cstdlib>
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <vector>

#ifndef F_PI
#define F_PI		((float)(M_PI))
#define F_2_PI		((float)(2.f*F_PI))
#define F_PI_2		((float)(F_PI/2.f))
#endif


#include "glew.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "glut.h"

// PARTICLE CODE
// Structure to represent a particle
struct Particle {
    float x, y, z;  // Position
    float size;     // Size of the particle
    float speed;    // Vertical speed
    float alpha;    // Opacity
    float red, green, blue; // Color components

    Particle() : x(0.0f), y(0.0f), z(0.0f), size(0.02f), speed(0.0f), alpha(1.0f) {
        // Use a predefined array of colors (shades of orange, red, and yellow)
        static const float colors[][3] = {
            {1.0f, 0.5f, 0.0f},  // Orange
            {1.0f, 0.0f, 0.0f},  // Red
            {0.8f, 0.2f, 0.0f},  // Darker Orange
            {0.9f, 0.4f, 0.0f},  // Darker Orange
            {0.7f, 0.1f, 0.0f},  // Dark Red
            {1.0f, 0.7f, 0.0f},  // Yellow-Orange
            {1.0f, 0.8f, 0.2f},  // Light Orange
            {1.0f, 0.3f, 0.0f},  // Dark Orange
            {1.0f, 0.6f, 0.0f},  // Orange-Yellow
            {0.9f, 0.2f, 0.0f}   // Darker Red
        };

        // Select a random color from the predefined array
        int index = rand() % (sizeof(colors) / sizeof(colors[0]));
        red = colors[index][0];
        green = colors[index][1];
        blue = colors[index][2];
    }
};

// Number of particles in the fire
const int numParticles = 80;

// Vector to store the particles
std::vector<Particle> particles;

// Predefined array of colors (shades of orange, red, and yellow)
static const float colors[][3] = {
    {1.0f, 0.5f, 0.0f},  // Orange
    {1.0f, 0.0f, 0.0f},  // Red
    {0.8f, 0.2f, 0.0f},  // Darker Orange
    {0.9f, 0.4f, 0.0f},  // Darker Orange
    {0.7f, 0.1f, 0.0f},  // Dark Red
    {1.0f, 0.7f, 0.0f},  // Yellow-Orange
    {1.0f, 0.8f, 0.2f},  // Light Orange
    {1.0f, 0.3f, 0.0f},  // Dark Orange
    {1.0f, 0.6f, 0.0f},  // Orange-Yellow
    {0.9f, 0.2f, 0.0f}   // Darker Red
};

// Function to initialize particles
// void initializeParticles() {
//     particles.clear();
//     particles.resize(numParticles);

//     for (int i = 0; i < numParticles; ++i) {
//         particles[i].x = (rand() % 2000 - 1000) / 1000.0f; // Random initial x position
//         particles[i].y = 0.0f;
//         particles[i].z = (rand() % 2000 - 1000) / 1000.0f; // Random initial z position
//         particles[i].size = 0.02f;
//         particles[i].speed = static_cast<float>(rand() % 100) / 10000.0f + 0.005f; // Random speed between 0.005 and 0.015
//         particles[i].alpha = 1.0f;
//     }
// }
void initializeParticles() {
    particles.clear();
    particles.resize(numParticles);

    for (int i = 0; i < numParticles; ++i) {
        float angle = static_cast<float>(rand()) / RAND_MAX * F_2_PI; // Random angle between 0 and 2*pi
        float radius = static_cast<float>(rand()) / RAND_MAX * 0.2f; // Random radius between 0 and 0.5

        particles[i].x = radius * cos(angle);
        particles[i].y = 0.0f;
        particles[i].z = radius * sin(angle);
        particles[i].size = 0.02f;
        particles[i].speed = static_cast<float>(rand() % 100) / 10000.0f + 0.005f; // Random speed between 0.005 and 0.015
        particles[i].alpha = 1.0f;
    }
}

void updateParticles() {
    for (int i = 0; i < numParticles; ++i) {
        particles[i].y += particles[i].speed;
        particles[i].alpha -= 0.005f;

        // Disappear randomly between y values of 0.5 and 1
        if ((particles[i].y > 0.5f && rand() % 100 < 5) || particles[i].alpha <= 0.0f) {
            particles[i].y = 0.0f;
            particles[i].alpha = 1.0f;

            // Use polar coordinates to reset particle position within the circular area
            float angle = static_cast<float>(rand()) / RAND_MAX * F_2_PI; // Random angle between 0 and 2*pi
            float radius = static_cast<float>(rand()) / RAND_MAX * 0.2f; // Random radius between 0 and 0.5

            particles[i].x = radius * cos(angle);
            particles[i].z = radius * sin(angle);

            // Randomize color again when particles reset
            int index = rand() % (sizeof(colors) / sizeof(colors[0]));
            particles[i].red = colors[index][0];
            particles[i].green = colors[index][1];
            particles[i].blue = colors[index][2];
        }
    }
}

// Function to handle updates
void update(int value) {
    updateParticles();
    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // 60 FPS
}

// Particles continues in Display() from here



//	This is a sample OpenGL / GLUT program
//
//	The objective is to draw a 3d object and change the color of the axes
//		with a glut menu
//
//	The left mouse button does rotation
//	The middle mouse button does scaling
//	The user interface allows:
//		1. The axes to be turned on and off
//		2. The color of the axes to be changed
//		3. Debugging to be turned on and off
//		4. Depth cueing to be turned on and off
//		5. The projection to be changed
//		6. The transformations to be reset
//		7. The program to quit
//
//	Author:			Kaelan Trowbridge

// title of these windows:

const char *WINDOWTITLE = "OpenGL / GLUT Sample -- Kaelan Trowbridge";
const char *GLUITITLE   = "User Interface Window";

// what the glui package defines as true and false:

const int GLUITRUE  = true;
const int GLUIFALSE = false;

// the escape key:

const int ESCAPE = 0x1b;

// initial window size:

const int INIT_WINDOW_SIZE = 1000;

// size of the 3d box to be drawn:

const float BOXSIZE = 2.f;

// multiplication factors for input interaction:
//  (these are known from previous experience)

const float ANGFACT = 1.f;
const float SCLFACT = 0.005f;

// minimum allowable scale factor:

const float MINSCALE = 0.05f;

// scroll wheel button values:

const int SCROLL_WHEEL_UP   = 3;
const int SCROLL_WHEEL_DOWN = 4;

// equivalent mouse movement when we click the scroll wheel:

const float SCROLL_WHEEL_CLICK_FACTOR = 5.f;

// active mouse buttons (or them together):

const int LEFT   = 4;
const int MIDDLE = 2;
const int RIGHT  = 1;

// which projection:

enum Projections
{
	ORTHO,
	PERSP
};

// which button:

enum ButtonVals
{
	RESET,
	QUIT
};

// window background color (rgba):

const GLfloat BACKCOLOR[ ] = { 0., 0., 0., 1. };

// line width for the axes:

const GLfloat AXES_WIDTH   = 3.;

// the color numbers:
// this order must match the radio button order, which must match the order of the color names,
// 	which must match the order of the color RGB values

enum Colors
{
	RED,
	YELLOW,
	GREEN,
	CYAN,
	BLUE,
	MAGENTA
};

char * ColorNames[ ] =
{
	(char *)"Red",
	(char*)"Yellow",
	(char*)"Green",
	(char*)"Cyan",
	(char*)"Blue",
	(char*)"Magenta"
};

// the color definitions:
// this order must match the menu order

const GLfloat Colors[ ][3] = 
{
	{ 1., 0., 0. },		// red
	{ 1., 1., 0. },		// yellow
	{ 0., 1., 0. },		// green
	{ 0., 1., 1. },		// cyan
	{ 0., 0., 1. },		// blue
	{ 1., 0., 1. },		// magenta
};

// fog parameters:

const GLfloat FOGCOLOR[4] = { .0f, .0f, .0f, 1.f };
const GLenum  FOGMODE     = GL_LINEAR;
const GLfloat FOGDENSITY  = 0.30f;
const GLfloat FOGSTART    = 1.5f;
const GLfloat FOGEND      = 4.f;

// for lighting:

const float	WHITE[ ] = { 1.,1.,1.,1. };

// for animation:

const int MS_PER_CYCLE = 500000;		//very long cycle to make sure that the planet spins very slow
// const int MS_PER_CYCLE_2 = 10000  // 10 seconds, this is for keytiming
const int MSEC = 10000;


// what options should we compile-in?
// in general, you don't need to worry about these
// i compile these in to show class examples of things going wrong
//#define DEMO_Z_FIGHTING
//#define DEMO_DEPTH_BUFFER


// non-constant global variables:

int		ActiveButton;			// current button that is down
GLuint	AxesList;				// list to hold the axes
int		AxesOn;					// != 0 means to draw the axes
GLuint	BoxList;				// object display list
int		DebugOn;				// != 0 means to print debugging info
int		DepthCueOn;				// != 0 means to use intensity depth cueing
int		DepthBufferOn;			// != 0 means to use the z-buffer
int		DepthFightingOn;		// != 0 means to force the creation of z-fighting
int		MainWindow;				// window id for main graphics window
int		NowColor;				// index into Colors[ ]
int		NowProjection;		// ORTHO or PERSP
float	Scale;					// scaling factor
int		ShadowsOn;				// != 0 means to turn shadows on
float	Time;					// used for animation, this has a value between 0. and 1.
int		Xmouse, Ymouse;			// mouse values
float	Xrot, Yrot;				// rotation angles in degrees

// Project 5 gobal variables
int SpaceDL, SphereDL;
int part_1, part_2, part_3, part_4, part_5; // every part of the island, split up so that I can color it.
int fire_log, fire_rock, fire_ground; // elements of the fire
int moai; // moai object
int Lookposition = 0;
float LookX, LookY, LookZ;

int SpaceTextureID = 0;
int IslandTextureID = 0;



// int TextureIDs[3] = {
// 	0, // Base sphere
// 	1, // Space
// };
// GLuint	SphereList, VenusList, EarthList, MarsList, JupiterList, SaturnList, UranusList, NeptuneList;

// function prototypes:

void	Animate( );
void	Display( );
void	DoAxesMenu( int );
void	DoColorMenu( int );
void	DoDepthBufferMenu( int );
void	DoDepthFightingMenu( int );
void	DoDepthMenu( int );
void	DoDebugMenu( int );
void	DoMainMenu( int );
void	DoProjectMenu( int );
void	DoRasterString( float, float, float, char * );
void	DoStrokeString( float, float, float, float, char * );
float	ElapsedSeconds( );
void	InitGraphics( );
void	InitLists( );
void	InitMenus( );
void	Keyboard( unsigned char, int, int );
void	MouseButton( int, int, int, int );
void	MouseMotion( int, int );
void	Reset( );
void	Resize( int, int );
void	Visibility( int );

void			Axes( float );
void			HsvRgb( float[3], float [3] );
void			Cross(float[3], float[3], float[3]);
float			Dot(float [3], float [3]);
float			Unit(float [3], float [3]);
float			Unit(float [3]);


// utility to create an array from 3 separate values:

float *
Array3( float a, float b, float c )
{
	static float array[4];

	array[0] = a;
	array[1] = b;
	array[2] = c;
	array[3] = 1.;
	return array;
}

// utility to create an array from a multiplier and an array:

float *
MulArray3( float factor, float array0[ ] )
{
	static float array[4];

	array[0] = factor * array0[0];
	array[1] = factor * array0[1];
	array[2] = factor * array0[2];
	array[3] = 1.;
	return array;
}


float *
MulArray3(float factor, float a, float b, float c )
{
	static float array[4];

	float* abc = Array3(a, b, c);
	array[0] = factor * abc[0];
	array[1] = factor * abc[1];
	array[2] = factor * abc[2];
	array[3] = 1.;
	return array;
}

// these are here for when you need them -- just uncomment the ones you need:

#include "setmaterial.cpp"
#include "setlight.cpp"
#include "osusphere.cpp"
//#include "osucone.cpp"
//#include "osutorus.cpp"
#include "bmptotexture.cpp"
#include "loadobjfile.cpp"
#include "keytime.cpp"
//#include "glslprogram.cpp"
Keytimes IntensityR, IntensityG, IntensityB, Brightness; 

// main program:

int
main( int argc, char *argv[ ] )
{
	// turn on the glut package:
	// (do this before checking argc and argv since glutInit might
	// pull some command line arguments out)

	glutInit( &argc, argv );

	// setup all the graphics stuff:

	InitGraphics( );


	// create the display lists that **will not change**:

	InitLists( );

	// FOR PARTICLES
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Set a seed for random number generation
    srand(static_cast<unsigned int>(time(nullptr)));

    initializeParticles();

    glutTimerFunc(25, update, 0); // Initial call to update function

	// init all the global variables used by Display( ):
	// this will also post a redisplay

	Reset( );

	// setup all the user interface stuff:



	InitMenus( );

	// draw the scene once and wait for some interaction:
	// (this will never return)

	glutSetWindow( MainWindow );
	glutMainLoop( );

	// glutMainLoop( ) never actually returns
	// the following line is here to make the compiler happy:

	return 0;
}


// this is where one would put code that is to be called
// everytime the glut main loop has nothing to do
//
// this is typically where animation parameters are set
//
// do not call Display( ) from here -- let glutPostRedisplay( ) do it

void
Animate( )
{
	// put animation stuff in here -- change some global variables for Display( ) to find:

	int ms = glutGet(GLUT_ELAPSED_TIME);
	ms %= MS_PER_CYCLE;							// makes the value of ms between 0 and MS_PER_CYCLE-1
	Time = (float)ms / (float)MS_PER_CYCLE;		// makes the value of Time between 0. and slightly less than 1.

	// for example, if you wanted to spin an object in Display( ), you might call: glRotatef( 360.f*Time,   0., 1., 0. );

	// force a call to Display( ) next time it is convenient:

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


// draw the complete scene:

void
Display( )
{
	if (DebugOn != 0)
		fprintf(stderr, "Starting Display.\n");

	// set which window we want to do the graphics into:
	glutSetWindow( MainWindow );

	// erase the background:
	glDrawBuffer( GL_BACK );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glEnable( GL_DEPTH_TEST );
#ifdef DEMO_DEPTH_BUFFER
	if( DepthBufferOn == 0 )
		glDisable( GL_DEPTH_TEST );
#endif


	// specify shading to be flat:

	glShadeModel( GL_FLAT );


	// set the viewport to be a square centered in the window:

	GLsizei vx = glutGet( GLUT_WINDOW_WIDTH );
	GLsizei vy = glutGet( GLUT_WINDOW_HEIGHT );
	GLsizei v = vx < vy ? vx : vy;			// minimum dimension
	GLint xl = ( vx - v ) / 2;
	GLint yb = ( vy - v ) / 2;
	glViewport( xl, yb,  v, v );


	// set the viewing volume:
	// remember that the Z clipping  values are given as DISTANCES IN FRONT OF THE EYE
	// USE gluOrtho2D( ) IF YOU ARE DOING 2D !

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	// if( NowProjection == ORTHO )
	// glOrtho( -2.f, 2.f,     -2.f, 2.f,     0.1f, 1000.f );
	// else
	gluPerspective( 70.f, 1.f,	0.1f, 1000.f );

	// place the objects into the scene:

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	// turn # msec into the cycle ( 0 - MSEC-1 ):
	int msec = glutGet( GLUT_ELAPSED_TIME )  %  MSEC; //MS_PER_CYCLE;

	// turn that into a time in seconds:
	float nowTime = (float)msec  / 1000.;

	// set the eye position, look-at position, and up-vector:

	if (Lookposition == 0) {
		gluLookAt( 1.f, 0.9f, 3.f,     0.f, .4f, 0.f,     0.f, 1.f, 0.f );
	} else if (Lookposition == 1) {
		gluLookAt( -0.8f, 0.4f, .6f,     0.f, 0.4f, 0.2f,     0.f, 1.f, 0.f );
	} else if (Lookposition == 2) {
		gluLookAt( 1.f, 0.3f, -0.3f,     0.f, 0.4f, 0.1f,     0.f, 1.f, 0.f );
	}  else if (Lookposition == 3) {
		gluLookAt( 10.f, 0.5f, 10.f,     0.f, 0.4f, 0.f,     0.f, 1.f, 0.f );

	}

	// rotate the scene:

	glRotatef( (GLfloat)Yrot, 0.f, 1.f, 0.f );
	glRotatef( (GLfloat)Xrot, 1.f, 0.f, 0.f );

	// uniformly scale the scene:

	if( Scale < MINSCALE )
		Scale = MINSCALE;
	glScalef( (GLfloat)Scale, (GLfloat)Scale, (GLfloat)Scale );

	// set the fog parameters:

	if( DepthCueOn != 0 )
	{
		glFogi( GL_FOG_MODE, FOGMODE );
		glFogfv( GL_FOG_COLOR, FOGCOLOR );
		glFogf( GL_FOG_DENSITY, FOGDENSITY );
		glFogf( GL_FOG_START, FOGSTART );
		glFogf( GL_FOG_END, FOGEND );
		glEnable( GL_FOG );
	}
	else
	{
		glDisable( GL_FOG );
	}

	// possibly draw the axes:

	// if( AxesOn != 0 )
	// {
	// 	glColor3fv( &Colors[NowColor][0] );
	// 	glCallList( AxesList );
	// }

	// since we are using glScalef( ), be sure the normals get unitized:
	// Draw particles
    glBegin(GL_QUADS);
    for (const auto& particle : particles) {
        glColor4f(particle.red, particle.green, particle.blue, particle.alpha);

        // Render particle as a cube
        glVertex3f(particle.x - particle.size, particle.y - particle.size, particle.z - particle.size);
        glVertex3f(particle.x + particle.size, particle.y - particle.size, particle.z - particle.size);
        glVertex3f(particle.x + particle.size, particle.y + particle.size, particle.z - particle.size);
        glVertex3f(particle.x - particle.size, particle.y + particle.size, particle.z - particle.size);

        glVertex3f(particle.x - particle.size, particle.y - particle.size, particle.z + particle.size);
        glVertex3f(particle.x + particle.size, particle.y - particle.size, particle.z + particle.size);
        glVertex3f(particle.x + particle.size, particle.y + particle.size, particle.z + particle.size);
        glVertex3f(particle.x - particle.size, particle.y + particle.size, particle.z + particle.size);

        glVertex3f(particle.x - particle.size, particle.y - particle.size, particle.z - particle.size);
        glVertex3f(particle.x + particle.size, particle.y - particle.size, particle.z - particle.size);
        glVertex3f(particle.x + particle.size, particle.y - particle.size, particle.z + particle.size);
        glVertex3f(particle.x - particle.size, particle.y - particle.size, particle.z + particle.size);

        glVertex3f(particle.x - particle.size, particle.y + particle.size, particle.z - particle.size);
        glVertex3f(particle.x + particle.size, particle.y + particle.size, particle.z - particle.size);
        glVertex3f(particle.x + particle.size, particle.y + particle.size, particle.z + particle.size);
        glVertex3f(particle.x - particle.size, particle.y + particle.size, particle.z + particle.size);

        glVertex3f(particle.x - particle.size, particle.y - particle.size, particle.z - particle.size);
        glVertex3f(particle.x - particle.size, particle.y + particle.size, particle.z - particle.size);
        glVertex3f(particle.x - particle.size, particle.y + particle.size, particle.z + particle.size);
        glVertex3f(particle.x - particle.size, particle.y - particle.size, particle.z + particle.size);

        glVertex3f(particle.x + particle.size, particle.y - particle.size, particle.z - particle.size);
        glVertex3f(particle.x + particle.size, particle.y + particle.size, particle.z - particle.size);
        glVertex3f(particle.x + particle.size, particle.y + particle.size, particle.z + particle.size);
        glVertex3f(particle.x + particle.size, particle.y - particle.size, particle.z + particle.size);
    }
    glEnd();

	glEnable( GL_NORMALIZE );


	// Light source sphere, no lighting here
	glPushMatrix();
	// spin in a circle
	// glRotatef( 360.f*Time,   0., 1., 0. );
	// start farther out, this is so its on the outside of all planets
	// glTranslatef(12., 0., 0.);
	// make small
	// glScalef(5., 5., 5.);

	// glColor3f(1., 1., 1.);
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0);

	// glCallList( SphereDL ); // put a sphere in the scene
	SetPointLightCustom( GL_LIGHT0, 0., 0.6, 0., IntensityR.GetValue( nowTime ), IntensityG.GetValue( nowTime ), IntensityB.GetValue( nowTime ), Brightness.GetValue( nowTime ) );
	// SetPointLightCustom( GL_LIGHT0, 0., 0.6, 0., 1., 1., 1.);

	// SetPointLight( GL_LIGHT1, 0., -2, 0., 1., .1, .1 );
	glPopMatrix();

	glEnable( GL_TEXTURE_2D );

	
	// glEnable( GL_LIGHT1);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	// glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// Put space in the background (Sphere wrapped with stars)
	glPushMatrix();
	glRotatef( 360.f * Time,   1., 0., 0. ); //360.f* 0.01 * Time
	glCallList(SpaceDL);
	glPopMatrix();

	glDisable( GL_TEXTURE_2D );


	glPushMatrix();
	glScalef(.2, .2, .2);
	glTranslatef(-1.f, 0.f, -2.f);
	// draw the rocks and island rock
	glPushMatrix();
	// glScalef(.3, .3, .3);
	SetMaterial(  0.1, 0.1, 0.1, 5.f );
	glColor3f(.7, .7, .7);
	glCallList( part_3 );
	// glCallList( part_5 );
	glPopMatrix();

	// Draw the tree stump
	glPushMatrix();
	// glScalef(.3, .3, .3);
	SetMaterial( 0.3f, 0.2f, 0.1f, 2.f );
	glColor3f(0.3f, 0.2f, 0.1f);
	glCallList( part_1 );
	glPopMatrix();

	// draw the leaves and grass
	glPushMatrix();
	// glScalef(.3, .3, .3);
	SetMaterial( 0.f, 0.2f, 0.f, 2.f );
	glColor3f(0., 0.2f, 0.f );
	glCallList( part_2 );
	glCallList( part_4 );
	glPopMatrix();

	glPopMatrix();

	// Draw the campfire
	glPushMatrix();
	glScalef(.35, .35, .35);
	glTranslatef(0., 0.4, 0.);

	glPushMatrix();
	SetMaterial(  0.3f, 0.2f, 0.1f, 2.f );
	glCallList( fire_ground );
	glCallList( fire_log );
	glPopMatrix();

	glPushMatrix();
	SetMaterial( 0., 0., 0., 2.f );
	glCallList( fire_rock);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	SetMaterial( 0.1f, 0.1f, 0.1f, 2.f );
	glTranslatef(0.8, 0.f, 0.0f);
	glRotatef(-90., 0., 1., 0.);
	glScalef(0.0002f, 0.0002f, 0.0002f);
	glCallList( moai );
	glPopMatrix();

	


	glDisable(GL_LIGHT0);
	// glDisable(GL_LIGHT1);
	glDisable( GL_LIGHTING );

	// Don't light the island rock underneath, doesn't need light source
	glPushMatrix();
	glScalef(.2, .2, .2);
	glTranslatef(-1.f, 0.f, -2.f);
	glColor3f(.1, .1, .1);
	// glCallList( part_3 );
	glCallList( part_5 );
	glPopMatrix();
	
	

#ifdef DEMO_Z_FIGHTING
	if( DepthFightingOn != 0 )
	{
		glPushMatrix( );
			glRotatef( 90.f,   0.f, 1.f, 0.f );
			glCallList( BoxList );
		glPopMatrix( );
	}
#endif


	// draw some gratuitous text that just rotates on top of the scene:
	// i commented out the actual text-drawing calls -- put them back in if you have a use for them
	// a good use for thefirst one might be to have your name on the screen
	// a good use for the second one might be to have vertex numbers on the screen alongside each vertex

	glDisable( GL_DEPTH_TEST );
	glColor3f( 0.f, 1.f, 1.f );
	//DoRasterString( 0.f, 1.f, 0.f, (char *)"Text That Moves" );


	// draw some gratuitous text that is fixed on the screen:
	//
	// the projection matrix is reset to define a scene whose
	// world coordinate system goes from 0-100 in each axis
	//
	// this is called "percent units", and is just a convenience
	//
	// the modelview matrix is reset to identity as we don't
	// want to transform these coordinates

	glDisable( GL_DEPTH_TEST );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	gluOrtho2D( 0.f, 100.f,     0.f, 100.f );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	glColor3f( 1.f, 1.f, 1.f );

	//DoRasterString( 5.f, 5.f, 0.f, (char *)"Text That Doesn't" );

	// swap the double-buffered framebuffers:

	glutSwapBuffers( );

	// be sure the graphics buffer has been sent:
	// note: be sure to use glFlush( ) here, not glFinish( ) !

	glFlush( );
}


void
DoAxesMenu( int id )
{
	AxesOn = id;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


void
DoColorMenu( int id )
{
	NowColor = id - RED;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


void
DoDebugMenu( int id )
{
	DebugOn = id;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


void
DoDepthBufferMenu( int id )
{
	DepthBufferOn = id;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


void
DoDepthFightingMenu( int id )
{
	DepthFightingOn = id;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


void
DoDepthMenu( int id )
{
	DepthCueOn = id;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


// main menu callback:

void
DoMainMenu( int id )
{
	switch( id )
	{
		case RESET:
			Reset( );
			break;

		case QUIT:
			// gracefully close out the graphics:
			// gracefully close the graphics window:
			// gracefully exit the program:
			glutSetWindow( MainWindow );
			glFinish( );
			glutDestroyWindow( MainWindow );
			exit( 0 );
			break;

		default:
			fprintf( stderr, "Don't know what to do with Main Menu ID %d\n", id );
	}

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


void
DoProjectMenu( int id )
{
	NowProjection = id;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


// use glut to display a string of characters using a raster font:

void
DoRasterString( float x, float y, float z, char *s )
{
	glRasterPos3f( (GLfloat)x, (GLfloat)y, (GLfloat)z );

	char c;			// one character to print
	for( ; ( c = *s ) != '\0'; s++ )
	{
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, c );
	}
}


// use glut to display a string of characters using a stroke font:

void
DoStrokeString( float x, float y, float z, float ht, char *s )
{
	glPushMatrix( );
		glTranslatef( (GLfloat)x, (GLfloat)y, (GLfloat)z );
		float sf = ht / ( 119.05f + 33.33f );
		glScalef( (GLfloat)sf, (GLfloat)sf, (GLfloat)sf );
		char c;			// one character to print
		for( ; ( c = *s ) != '\0'; s++ )
		{
			glutStrokeCharacter( GLUT_STROKE_ROMAN, c );
		}
	glPopMatrix( );
}


// return the number of seconds since the start of the program:

float
ElapsedSeconds( )
{
	// get # of milliseconds since the start of the program:

	int ms = glutGet( GLUT_ELAPSED_TIME );

	// convert it to seconds:

	return (float)ms / 1000.f;
}


// initialize the glui window:

void
InitMenus( )
{
	if (DebugOn != 0)
		fprintf(stderr, "Starting InitMenus.\n");

	glutSetWindow( MainWindow );

	int numColors = sizeof( Colors ) / ( 3*sizeof(float) );
	int colormenu = glutCreateMenu( DoColorMenu );
	for( int i = 0; i < numColors; i++ )
	{
		glutAddMenuEntry( ColorNames[i], i );
	}

	int axesmenu = glutCreateMenu( DoAxesMenu );
	glutAddMenuEntry( "Off",  0 );
	glutAddMenuEntry( "On",   1 );

	int depthcuemenu = glutCreateMenu( DoDepthMenu );
	glutAddMenuEntry( "Off",  0 );
	glutAddMenuEntry( "On",   1 );

	int depthbuffermenu = glutCreateMenu( DoDepthBufferMenu );
	glutAddMenuEntry( "Off",  0 );
	glutAddMenuEntry( "On",   1 );

	int depthfightingmenu = glutCreateMenu( DoDepthFightingMenu );
	glutAddMenuEntry( "Off",  0 );
	glutAddMenuEntry( "On",   1 );

	int debugmenu = glutCreateMenu( DoDebugMenu );
	glutAddMenuEntry( "Off",  0 );
	glutAddMenuEntry( "On",   1 );

	int projmenu = glutCreateMenu( DoProjectMenu );
	glutAddMenuEntry( "Orthographic",  ORTHO );
	glutAddMenuEntry( "Perspective",   PERSP );

	int mainmenu = glutCreateMenu( DoMainMenu );
	glutAddSubMenu(   "Axes",          axesmenu);
	glutAddSubMenu(   "Axis Colors",   colormenu);

#ifdef DEMO_DEPTH_BUFFER
	glutAddSubMenu(   "Depth Buffer",  depthbuffermenu);
#endif

#ifdef DEMO_Z_FIGHTING
	glutAddSubMenu(   "Depth Fighting",depthfightingmenu);
#endif

	glutAddSubMenu(   "Depth Cue",     depthcuemenu);
	glutAddSubMenu(   "Projection",    projmenu );
	glutAddMenuEntry( "Reset",         RESET );
	glutAddSubMenu(   "Debug",         debugmenu);
	glutAddMenuEntry( "Quit",          QUIT );

// attach the pop-up menu to the right mouse button:

	glutAttachMenu( GLUT_RIGHT_BUTTON );
}



// initialize the glut and OpenGL libraries:
//	also setup callback functions

void
InitGraphics( )
{
	if (DebugOn != 0)
		fprintf(stderr, "Starting InitGraphics.\n");

	// request the display modes:
	// ask for red-green-blue-alpha color, double-buffering, and z-buffering:

	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );


	// set the initial window configuration:

	glutInitWindowPosition( 0, 0 );
	glutInitWindowSize( INIT_WINDOW_SIZE, INIT_WINDOW_SIZE );

	// open the window and set its title:

	MainWindow = glutCreateWindow( WINDOWTITLE );
	glutSetWindowTitle( WINDOWTITLE );

	// set the framebuffer clear values:

	glClearColor( BACKCOLOR[0], BACKCOLOR[1], BACKCOLOR[2], BACKCOLOR[3] );

	// setup the callback functions:
	// DisplayFunc -- redraw the window
	// ReshapeFunc -- handle the user resizing the window
	// KeyboardFunc -- handle a keyboard input
	// MouseFunc -- handle the mouse button going down or up
	// MotionFunc -- handle the mouse moving with a button down
	// PassiveMotionFunc -- handle the mouse moving with a button up
	// VisibilityFunc -- handle a change in window visibility
	// EntryFunc	-- handle the cursor entering or leaving the window
	// SpecialFunc -- handle special keys on the keyboard
	// SpaceballMotionFunc -- handle spaceball translation
	// SpaceballRotateFunc -- handle spaceball rotation
	// SpaceballButtonFunc -- handle spaceball button hits
	// ButtonBoxFunc -- handle button box hits
	// DialsFunc -- handle dial rotations
	// TabletMotionFunc -- handle digitizing tablet motion
	// TabletButtonFunc -- handle digitizing tablet button hits
	// MenuStateFunc -- declare when a pop-up menu is in use
	// TimerFunc -- trigger something to happen a certain time from now
	// IdleFunc -- what to do when nothing else is going on

	glutSetWindow( MainWindow );
	glutDisplayFunc( Display );
	glutReshapeFunc( Resize );
	glutKeyboardFunc( Keyboard );
	glutMouseFunc( MouseButton );
	glutMotionFunc( MouseMotion );
	glutPassiveMotionFunc(MouseMotion);
	//glutPassiveMotionFunc( NULL );
	glutVisibilityFunc( Visibility );
	glutEntryFunc( NULL );
	glutSpecialFunc( NULL );
	glutSpaceballMotionFunc( NULL );
	glutSpaceballRotateFunc( NULL );
	glutSpaceballButtonFunc( NULL );
	glutButtonBoxFunc( NULL );
	glutDialsFunc( NULL );
	glutTabletMotionFunc( NULL );
	glutTabletButtonFunc( NULL );
	glutMenuStateFunc( NULL );
	glutTimerFunc( -1, NULL, 0 );

	// setup glut to call Animate( ) every time it has
	// 	nothing it needs to respond to (which is most of the time)
	// we don't need to do this for this program, and really should set the argument to NULL
	// but, this sets us up nicely for doing animation

	glutIdleFunc( Animate );

	// init the glew package (a window must be open to do this):

#ifdef WIN32
	GLenum err = glewInit( );
	if( err != GLEW_OK )
	{
		fprintf( stderr, "glewInit Error\n" );
	}
	else
		fprintf( stderr, "GLEW initialized OK\n" );
	fprintf( stderr, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
#endif

	// all other setups go here, such as GLSLProgram and KeyTime setups:
	// RGB Light intensity for lighting. This is for flickering.
	// IntensityR.Init( );
	// IntensityR.AddTimeValue(  0.0,  0.000 );
	// IntensityR.AddTimeValue(  0.5,  0. );
	// IntensityR.AddTimeValue(  2.0,  0. );
	// IntensityR.AddTimeValue(  5.0,  0. );
	// IntensityR.AddTimeValue(  8.0,  0. );
	// IntensityR.AddTimeValue( 10.0,  0.000 );

	// IntensityG.Init( );
	// IntensityG.AddTimeValue(  0.0,  0.000 );
	// IntensityG.AddTimeValue(  0.5,  0. );
	// IntensityG.AddTimeValue(  2.0,  0. );
	// IntensityG.AddTimeValue(  5.0,  0. );
	// IntensityG.AddTimeValue(  8.0,  0. );
	// IntensityG.AddTimeValue( 10.0,  0.000 );

	// IntensityB.Init( );
	// IntensityB.AddTimeValue(  0.0,  0.000 );
	// IntensityB.AddTimeValue(  0.5,  0. );
	// IntensityB.AddTimeValue(  2.0,  0. );
	// IntensityB.AddTimeValue(  5.0,  0. );
	// IntensityB.AddTimeValue(  8.0,  0. );
	// IntensityB.AddTimeValue( 10.0,  0.000 );
	IntensityR.Init( );
	IntensityR.AddTimeValue(  0.0,  0.0 );
	IntensityR.AddTimeValue(  0.5,  1.0 );
	IntensityR.AddTimeValue(  1.0,  0.2 );
	IntensityR.AddTimeValue(  1.5,  0.8 );
	IntensityR.AddTimeValue(  2.0,  0.3 );
	IntensityR.AddTimeValue(  3.0,  1.0 );
	IntensityR.AddTimeValue(  4.0,  0.6 );
	IntensityR.AddTimeValue(  5.0,  0.0 );
	IntensityR.AddTimeValue(  6.0,  0.9 );
	IntensityR.AddTimeValue(  8.0,  0.1 );
	IntensityR.AddTimeValue( 10.0,  0.0 );

	IntensityG.Init( );
	IntensityG.AddTimeValue(  0.0,  0.0 );
	IntensityG.AddTimeValue(  0.5,  0.5 );
	IntensityG.AddTimeValue(  1.0,  0.1 );
	IntensityG.AddTimeValue(  1.5,  0.4 );
	IntensityG.AddTimeValue(  2.0,  0.2 );
	IntensityG.AddTimeValue(  3.0,  0.8 );
	IntensityG.AddTimeValue(  4.0,  0.3 );
	IntensityG.AddTimeValue(  5.0,  0.0 );
	IntensityG.AddTimeValue(  6.0,  0.6 );
	IntensityG.AddTimeValue(  8.0,  0.2 );
	IntensityG.AddTimeValue( 10.0,  0.0 );

	IntensityB.Init( );
	IntensityB.AddTimeValue(  0.0,  0.0 );
	IntensityB.AddTimeValue(  0.5,  0.3 );
	IntensityB.AddTimeValue(  1.0,  0.0 );
	IntensityB.AddTimeValue(  1.5,  0.7 );
	IntensityB.AddTimeValue(  2.0,  0.1 );
	IntensityB.AddTimeValue(  3.0,  0.5 );
	IntensityB.AddTimeValue(  4.0,  0.2 );
	IntensityB.AddTimeValue(  5.0,  0.0 );
	IntensityB.AddTimeValue(  6.0,  0.4 );
	IntensityB.AddTimeValue(  8.0,  0.0 );
	IntensityB.AddTimeValue( 10.0,  0.0 );


	// Common Brightness keytimes for all Intensity channels
	Brightness.Init();
	Brightness.AddTimeValue(0.0, 1.0);
	Brightness.AddTimeValue(0.5, 0.3);
	Brightness.AddTimeValue(1.0, 0.5);
	Brightness.AddTimeValue(1.5, 0.8);
	Brightness.AddTimeValue(2.0, 0.4);
	Brightness.AddTimeValue(3.0, 1.0);
	Brightness.AddTimeValue(4.0, 0.7);
	Brightness.AddTimeValue(5.0, 0.0);
	Brightness.AddTimeValue(6.0, 0.9);
	Brightness.AddTimeValue(8.0, 0.2);
	Brightness.AddTimeValue(10.0, 0.0);


	// Define an array to store texture IDs

	char file[] = "space.bmp"; // milky way
	// char file[] = "space1.bmp"; // plain stars

	int width, height;

	// Loop through each texture
	// char* file = fileNames[i];

	unsigned char* texture = BmpToTexture(file, &width, &height);

	if (texture != NULL) {
		//fprintf(stderr, "Opened '%s': width = %d ; height = %d\n", file, width, height);
		// 
		// Generate a new texture ID for the space texture
		glGenTextures(1, (GLuint *) &SpaceTextureID);
		glBindTexture(GL_TEXTURE_2D, SpaceTextureID);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
		
		// Free memory for the texture
		free(texture);
	} else {
		fprintf(stderr, "Cannot open texture '%s'\n", file);
	}
}


// initialize the display lists that will not change:
// (a display list is a way to store opengl commands in
//  memory so that they can be played back efficiently at a later time
//  with a call to glCallList( )

void
InitLists( )
{
	if (DebugOn != 0)
		fprintf(stderr, "Starting InitLists.\n");

	// float dx = BOXSIZE / 2.f;
	// float dy = BOXSIZE / 2.f;
	// float dz = BOXSIZE / 2.f;
	glutSetWindow( MainWindow );

	// Part 1-5 are the elements of the island. (rocks, tree, island)
	part_1 = glGenLists( 1 );
	glNewList( part_1, GL_COMPILE );
		LoadObjFile( (char *) "part_1.obj");
	glEndList( );

	part_2 = glGenLists( 1 );
	glNewList( part_2, GL_COMPILE );
		LoadObjFile( (char *) "part_2.obj");
	glEndList( );

	part_3 = glGenLists( 1 );
	glNewList( part_3, GL_COMPILE );
		LoadObjFile( (char *) "part_3.obj");
	glEndList( );

	part_4 = glGenLists( 1 );
	glNewList( part_4, GL_COMPILE );
		LoadObjFile( (char *) "part_4.obj");
	glEndList( );

	part_5 = glGenLists( 1 );
	glNewList( part_5, GL_COMPILE );
		LoadObjFile( (char *) "part_5.obj");
	glEndList( );

	// Create the campfire
	fire_log = glGenLists( 1 );
	glNewList( fire_log, GL_COMPILE );
		LoadObjFile( (char *) "fire_log.obj");
	glEndList( );

	fire_rock = glGenLists( 1 );
	glNewList( fire_rock, GL_COMPILE );
		LoadObjFile( (char *) "fire_rock.obj");
	glEndList( );

	moai = glGenLists( 1 );
	glNewList( moai, GL_COMPILE );
		LoadObjFile( (char *) "moai.obj");
	glEndList( );

	// fire_ground = glGenLists( 1 );
	// glNewList( fire_ground, GL_COMPILE );
	// 	LoadObjFile( (char *) "fire_ground.obj");
	// glEndList( );

	// moai = glGenLists( 1 );
	// glNewList( moai, GL_COMPILE );
	// 	LoadObjFile( (char *) "Moai.obj");
	// glEndList( );

	SphereDL = glGenLists( 1 );
	glNewList( SphereDL, GL_COMPILE );
		OsuSphere( 1., 100., 100. );
	glEndList( );

	SpaceDL = glGenLists( 1 );
	glNewList( SpaceDL, GL_COMPILE );
		glBindTexture( GL_TEXTURE_2D, SpaceTextureID );	// venus Tex must have already been created when this is called
		glPushMatrix( );
			glScalef( 30.f, 30.f, 30.f );	// scale of venus  sphere, from the table
			glCallList( SphereDL );		// a dl can call another dl that has been previously created
		glPopMatrix( );
	glEndList( );

	AxesList = glGenLists( 1 );
	glNewList( AxesList, GL_COMPILE );
		glLineWidth( AXES_WIDTH );
			Axes( 1.5 );
		glLineWidth( 1. );
	glEndList( );
}


// the keyboard callback:

void
Keyboard( unsigned char c, int x, int y )
{
	if( DebugOn != 0 )
		fprintf( stderr, "Keyboard: '%c' (0x%0x)\n", c, c );

	switch( c )
	{
		case 'p':
		case 'P':
			break;

		case '1':
			Lookposition = 0;
			break;

		case '2':
			Lookposition = 1;
			break;

		case '3':
			Lookposition = 2;
			break;

		case '4':
			Lookposition = 3;
			break;

		case 'q':
		case 'Q':
		case ESCAPE:
			DoMainMenu( QUIT );	// will not return here
			break;				// happy compiler

		default:
			fprintf( stderr, "Don't know what to do with keyboard hit: '%c' (0x%0x)\n", c, c );
	}

	// force a call to Display( ):

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


// called when the mouse button transitions down or up:

void
MouseButton( int button, int state, int x, int y )
{
	int b = 0;			// LEFT, MIDDLE, or RIGHT

	if( DebugOn != 0 )
		fprintf( stderr, "MouseButton: %d, %d, %d, %d\n", button, state, x, y );


	// get the proper button bit mask:

	switch( button )
	{
		case GLUT_LEFT_BUTTON:
			b = LEFT;		break;

		case GLUT_MIDDLE_BUTTON:
			b = MIDDLE;		break;

		case GLUT_RIGHT_BUTTON:
			b = RIGHT;		break;

		case SCROLL_WHEEL_UP:
			Scale += SCLFACT * SCROLL_WHEEL_CLICK_FACTOR;
			// keep object from turning inside-out or disappearing:
			if (Scale < MINSCALE)
				Scale = MINSCALE;
			break;

		case SCROLL_WHEEL_DOWN:
			Scale -= SCLFACT * SCROLL_WHEEL_CLICK_FACTOR;
			// keep object from turning inside-out or disappearing:
			if (Scale < MINSCALE)
				Scale = MINSCALE;
			break;

		default:
			b = 0;
			fprintf( stderr, "Unknown mouse button: %d\n", button );
	}

	// button down sets the bit, up clears the bit:

	if( state == GLUT_DOWN )
	{
		Xmouse = x;
		Ymouse = y;
		ActiveButton |= b;		// set the proper bit
	}
	else
	{
		ActiveButton &= ~b;		// clear the proper bit
	}

	glutSetWindow(MainWindow);
	glutPostRedisplay();

}


// called when the mouse moves while a button is down:

void
MouseMotion( int x, int y )
{
	int dx = x - Xmouse;		// change in mouse coords
	int dy = y - Ymouse;

	if( ( ActiveButton & LEFT ) != 0 )
	{
		Xrot += ( ANGFACT*dy );
		Yrot += ( ANGFACT*dx );
	}

	if( ( ActiveButton & MIDDLE ) != 0 )
	{
		Scale += SCLFACT * (float) ( dx - dy );

		// keep object from turning inside-out or disappearing:

		if( Scale < MINSCALE )
			Scale = MINSCALE;
	}

	Xmouse = x;			// new current position
	Ymouse = y;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


// reset the transformations and the colors:
// this only sets the global variables --
// the glut main loop is responsible for redrawing the scene

void
Reset( )
{
	ActiveButton = 0;
	AxesOn = 1;
	DebugOn = 0;
	DepthBufferOn = 1;
	DepthFightingOn = 0;
	DepthCueOn = 0;
	Scale  = 1.0;
	ShadowsOn = 0;
	NowColor = YELLOW;
	NowProjection = PERSP;
	Xrot = Yrot = 0.;
}


// called when user resizes the window:

void
Resize( int width, int height )
{
	// don't really need to do anything since window size is
	// checked each time in Display( ):

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


// handle a change to the window's visibility:

void
Visibility ( int state )
{
	if( DebugOn != 0 )
		fprintf( stderr, "Visibility: %d\n", state );

	if( state == GLUT_VISIBLE )
	{
		glutSetWindow( MainWindow );
		glutPostRedisplay( );
	}
	else
	{
		// could optimize by keeping track of the fact
		// that the window is not visible and avoid
		// animating or redrawing it ...
	}
}



///////////////////////////////////////   HANDY UTILITIES:  //////////////////////////


// the stroke characters 'X' 'Y' 'Z' :

static float xx[ ] = { 0.f, 1.f, 0.f, 1.f };

static float xy[ ] = { -.5f, .5f, .5f, -.5f };

static int xorder[ ] = { 1, 2, -3, 4 };

static float yx[ ] = { 0.f, 0.f, -.5f, .5f };

static float yy[ ] = { 0.f, .6f, 1.f, 1.f };

static int yorder[ ] = { 1, 2, 3, -2, 4 };

static float zx[ ] = { 1.f, 0.f, 1.f, 0.f, .25f, .75f };

static float zy[ ] = { .5f, .5f, -.5f, -.5f, 0.f, 0.f };

static int zorder[ ] = { 1, 2, 3, 4, -5, 6 };

// fraction of the length to use as height of the characters:
const float LENFRAC = 0.10f;

// fraction of length to use as start location of the characters:
const float BASEFRAC = 1.10f;

//	Draw a set of 3D axes:
//	(length is the axis length in world coordinates)

void
Axes( float length )
{
	glBegin( GL_LINE_STRIP );
		glVertex3f( length, 0., 0. );
		glVertex3f( 0., 0., 0. );
		glVertex3f( 0., length, 0. );
	glEnd( );
	glBegin( GL_LINE_STRIP );
		glVertex3f( 0., 0., 0. );
		glVertex3f( 0., 0., length );
	glEnd( );

	float fact = LENFRAC * length;
	float base = BASEFRAC * length;

	glBegin( GL_LINE_STRIP );
		for( int i = 0; i < 4; i++ )
		{
			int j = xorder[i];
			if( j < 0 )
			{
				
				glEnd( );
				glBegin( GL_LINE_STRIP );
				j = -j;
			}
			j--;
			glVertex3f( base + fact*xx[j], fact*xy[j], 0.0 );
		}
	glEnd( );

	glBegin( GL_LINE_STRIP );
		for( int i = 0; i < 5; i++ )
		{
			int j = yorder[i];
			if( j < 0 )
			{
				
				glEnd( );
				glBegin( GL_LINE_STRIP );
				j = -j;
			}
			j--;
			glVertex3f( fact*yx[j], base + fact*yy[j], 0.0 );
		}
	glEnd( );

	glBegin( GL_LINE_STRIP );
		for( int i = 0; i < 6; i++ )
		{
			int j = zorder[i];
			if( j < 0 )
			{
				
				glEnd( );
				glBegin( GL_LINE_STRIP );
				j = -j;
			}
			j--;
			glVertex3f( 0.0, fact*zy[j], base + fact*zx[j] );
		}
	glEnd( );

}


// function to convert HSV to RGB
// 0.  <=  s, v, r, g, b  <=  1.
// 0.  <= h  <=  360.
// when this returns, call:
//		glColor3fv( rgb );

void
HsvRgb( float hsv[3], float rgb[3] )
{
	// guarantee valid input:

	float h = hsv[0] / 60.f;
	while( h >= 6. )	h -= 6.;
	while( h <  0. ) 	h += 6.;

	float s = hsv[1];
	if( s < 0. )
		s = 0.;
	if( s > 1. )
		s = 1.;

	float v = hsv[2];
	if( v < 0. )
		v = 0.;
	if( v > 1. )
		v = 1.;

	// if sat==0, then is a gray:

	if( s == 0.0 )
	{
		rgb[0] = rgb[1] = rgb[2] = v;
		return;
	}

	// get an rgb from the hue itself:
	
	float i = (float)floor( h );
	float f = h - i;
	float p = v * ( 1.f - s );
	float q = v * ( 1.f - s*f );
	float t = v * ( 1.f - ( s * (1.f-f) ) );

	float r=0., g=0., b=0.;			// red, green, blue
	switch( (int) i )
	{
		case 0:
			r = v;	g = t;	b = p;
			break;
	
		case 1:
			r = q;	g = v;	b = p;
			break;
	
		case 2:
			r = p;	g = v;	b = t;
			break;
	
		case 3:
			r = p;	g = q;	b = v;
			break;
	
		case 4:
			r = t;	g = p;	b = v;
			break;
	
		case 5:
			r = v;	g = p;	b = q;
			break;
	}


	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
}

void
Cross(float v1[3], float v2[3], float vout[3])
{
	float tmp[3];
	tmp[0] = v1[1] * v2[2] - v2[1] * v1[2];
	tmp[1] = v2[0] * v1[2] - v1[0] * v2[2];
	tmp[2] = v1[0] * v2[1] - v2[0] * v1[1];
	vout[0] = tmp[0];
	vout[1] = tmp[1];
	vout[2] = tmp[2];
}

float
Dot(float v1[3], float v2[3])
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}


float
Unit(float vin[3], float vout[3])
{
	float dist = vin[0] * vin[0] + vin[1] * vin[1] + vin[2] * vin[2];
	if (dist > 0.0)
	{
		dist = sqrtf(dist);
		vout[0] = vin[0] / dist;
		vout[1] = vin[1] / dist;
		vout[2] = vin[2] / dist;
	}
	else
	{
		vout[0] = vin[0];
		vout[1] = vin[1];
		vout[2] = vin[2];
	}
	return dist;
}


float
Unit( float v[3] )
{
	float dist = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
	if (dist > 0.0)
	{
		dist = sqrtf(dist);
		v[0] /= dist;
		v[1] /= dist;
		v[2] /= dist;
	}
	return dist;
}
