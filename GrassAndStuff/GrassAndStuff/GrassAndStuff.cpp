// This is the main DLL file.

#include "stdafx.h"

#include "GrassAndStuff.h"

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