// This is the main DLL file.

#include "stdafx.h"

#include "GrassAndStuff.h"

static int win(0); //The gl window
static double win_width(750.0); //Width and Height
static double win_length(750.0);
static int menu_id; //Menu Attached to Right Click
//Flag to set whether a vertex has been chosen to deform or not
static int deformflag(0);

double intensity(){

}

int main(int argc, char* argv[]){
	//Init and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowSize(win_width,win_length);
	glutInitWindowPosition(100,100);

	win = glutCreateWindow("GrassAndStuff");
	glClearColor(0.0,0.0,0.0,0.0);

	/*
	//Display, Mouse, and Menu
	glutDisplayFunc(Display);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	CreateMenu(); */

	glutMainLoop();
}