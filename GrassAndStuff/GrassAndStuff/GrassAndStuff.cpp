// This is the main DLL file.

#include "stdafx.h"

#include "GrassAndStuff.h"

static int win(0); //The gl window
static double win_width(750.0); //Width and Height
static double win_length(750.0);
static int menu_id; //Menu Attached to Right Click
//Flag to set whether a vertex has been chosen to deform or not
static int deformflag(0);

const float PI = 3.14159265359;
const float DEG_TO_RAD = PI / 180.0;
const float MAX = 10000.0;

const float K_R = 0.166;
const float K_M = 0.0025;
const float E = 14.3; 						// intensity
const glm::vec3  C_R = glm::vec3( 0.3, 0.7, 1.0 ); 	// 1 / wavelength ^ 4
const float G_M = -0.85;					// Mie g

const GLdouble Skydomeradius = 0.75;

double intensity(){
	return 0.0;
}

void Display(){
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity(); 

	GLUquadricObj* qobj; 
	qobj = gluNewQuadric();

	GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat model_ambient[] = { 0.5, 0.5, 0.5, 1.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient); 

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluSphere(qobj, Skydomeradius, 50, 10);

	glFlush();

}

int main(int argc, char* argv[]){

	//Init and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowSize(win_width,win_length);
	glutInitWindowPosition(100,100);

	win = glutCreateWindow("GrassAndStuff");
	glClearColor(0.0,0.0,0.0,0.0);

	
	//Display, Mouse, and Menu
	glutDisplayFunc(Display);
	//glutMouseFunc(Mouse);
	//glutKeyboardFunc(Keyboard);
	//CreateMenu(); 

	glutMainLoop();
}