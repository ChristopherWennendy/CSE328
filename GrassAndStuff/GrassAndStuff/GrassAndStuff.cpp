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

const GLdouble Skydomeradius = 0.75;

static GLuint g_program;
static GLuint g_programCameraPositionLocation;
static GLuint g_programLightPositionLocation;
static GLuint g_programLightColorLocation;

static GLuint g_cylinderBufferId;
static unsigned int g_cylinderNumVertices;

static float g_cameraPosition[3];

#define NUM_LIGHTS 3
static float g_lightPosition[NUM_LIGHTS * 3];
static float g_lightColor[NUM_LIGHTS * 3];
static float g_lightRotation;

void Display(){
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity(); 

	glUseProgram(g_program);
	glUniform3fv(g_programCameraPositionLocation, 1, g_cameraPosition);
	glUniform3fv(g_programLightPositionLocation, NUM_LIGHTS, g_lightPosition);
	glUniform3fv(g_programLightColorLocation, NUM_LIGHTS, g_lightColor); 

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

	glUseProgram(0);

	/*for (int i = 0; i < NUM_LIGHTS; ++i) {
		glPushMatrix();
		glTranslatef(g_lightPosition[i * 3 + 0], g_lightPosition[i * 3 + 1], g_lightPosition[i * 3 + 2]);
		glColor3fv(g_lightColor + (i * 3));
		glutSolidSphere(0.04, 36, 36);
		glPopMatrix();
	} */

	glFlush();

}

static void setPerspective(float fov, float aspect, float near, float far){
	float f;
	float mat[16];

	f = 1.0f / tanf(fov / 2.0f);

	mat[0] = f / aspect;
	mat[1] = 0.0f;
	mat[2] = 0.0f;
	mat[3] = 0.0f;

	mat[4] = 0.0f;
	mat[5] = f;
	mat[6] = 0.0f;
	mat[7] = 0.0f;

	mat[8] = 0.0f;
	mat[9] = 0.0f;
	mat[10] = (far + near) / (near - far);
	mat[11] = -1.0f;

	mat[12] = 0.0f;
	mat[13] = 0.0f;
	mat[14] = (2.0f * far * near) / (near - far);
	mat[15] = 0.0f;

	glMultMatrixf(mat);
}

void sceneCycle(void){

	/* update the light positions */
	g_lightRotation += (PI / 4.0f) * 1;
	for (int i = 0; i < NUM_LIGHTS; ++i) {
		const float radius = 1.75f;
		float r = (((PI * 2.0f) / (float)NUM_LIGHTS) * (float)i) + g_lightRotation;

		g_lightPosition[i * 3 + 0] = cosf(r) * radius;
		g_lightPosition[i * 3 + 1] = cosf(r) * sinf(r);
		g_lightPosition[i * 3 + 2] = sinf(r) * radius;
	}

	glutPostRedisplay();
}


void sceneInit(void) {
	GLint result;

	/* create program object and attach shaders */
	g_program = glCreateProgram();
	GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
	glAttachShader(g_program, shader);

	/* link the program and make sure that there were no errors */
	glLinkProgram(g_program);
	glGetProgramiv(g_program, GL_LINK_STATUS, &result);

	/* get uniform locations */
	g_programCameraPositionLocation = glGetUniformLocation(g_program, "cameraPosition");
	g_programLightPositionLocation = glGetUniformLocation(g_program, "lightPosition");
	g_programLightColorLocation = glGetUniformLocation(g_program, "lightColor");

	/* set up red/green/blue lights */
	g_lightColor[0] = 1.0f; g_lightColor[1] = 0.0f; g_lightColor[2] = 0.0f;
	g_lightColor[3] = 0.0f; g_lightColor[4] = 1.0f; g_lightColor[5] = 0.0f;
	g_lightColor[6] = 0.0f; g_lightColor[7] = 0.0f; g_lightColor[8] = 1.0f;

	/* create sphere */
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

	/* do the first cycle to initialize positions */
	g_lightRotation = 0.0f;
	sceneCycle();

	/* setup camera */
	g_cameraPosition[0] = 0.0f;
	g_cameraPosition[1] = 0.0f;
	g_cameraPosition[2] = 4.0f;
	glLoadIdentity();
	glTranslatef(-g_cameraPosition[0], -g_cameraPosition[1], -g_cameraPosition[2]);
}

int main(int argc, char* argv[]){

	//Init and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowSize(win_width,win_length);
	glutInitWindowPosition(100,100);

	win = glutCreateWindow("GrassAndStuff");
	glewInit();
	glClearColor(0.0,0.0,0.0,0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//setPerspective(PI / 4.0, win_width / win_length, 0.1, 200);
	glMatrixMode(GL_MODELVIEW);
	
	//Display, Mouse, and Menu
	glutDisplayFunc(Display);
	//glutIdleFunc(sceneCycle);
	//glutMouseFunc(Mouse);
	//glutKeyboardFunc(Keyboard);
	//CreateMenu(); 

	//sceneInit();
	glutMainLoop();
}