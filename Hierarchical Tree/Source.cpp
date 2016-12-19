	/**************************************************************************************************************
	# Hierarchical Tree by "Akula"s team.
	# Team Members: Orkhan Hsueynli, Tural Hamidov, ELgun Majidov and Tunjay Habibbayli
	# Contribution to the project: Tunjay 25%, Orkhan 25%, Tural 25%, Elgun 25%;
	# This file uses some templates from Dr. Araz Yusubov's samples (c)
	***************************************************************************************************************/
    #include "Branch.cpp"
    #include "Ground.cpp"
    #include "Sky.cpp"
	#include <math.h>
	#include <time.h>
	#include <GL/glut.h>
    #include <ctime>
	#include <windows.h>
	#include <objidl.h>
	#define NOMINMAX 
	#include <algorithm>
	namespace Gdiplus {
		using std::min;
		using std::max;
	}
	#include <gdiplus.h>
	#pragma comment(lib, "gdiplus.lib")
	using namespace Gdiplus;
	GLuint drawT;
	float x, y, z;
	int n = 5;
	GLfloat l = 10, base = 0.1;
	Branch b(n,l,base); // the tre object
	Ground g; // ground object
	Sky s(l+20); // sky object
	GLfloat lightPosition[] = { 0.0, l+20, 20}; // poition of the light, this comes from the sky, afternoon position :)
	unsigned int Delay = 50;	
	float w, h;
	GLfloat AngleX, AngleY, AngleZ, side;
	void init(void){
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		b.randomGen();
		GdiplusStartupInput gdiplusStartupInput;
		ULONG_PTR gdiplusToken;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
		glPopMatrix();
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		drawT = glGenLists(1);
		glNewList(drawT, GL_COMPILE);
		b.makeTree(6, 10, 0.2);
		glEndList();
	}	
	
	GLfloat scale = 0.1;
	void keyboard(unsigned char key, int x2, int y2) {
		if (key == 'x') {x += 10;} // this rotates around x
		if (key == 'y') {y += 10;} // this rotates around y
		if (key == 'z') {z += 10;} // this rotates around z 
		if (key == '+') {scale *= 1.1;}
		if (key == '-') {scale *= 0.9;}
		if (key == 'w') scale *= 1.05;
		if (key=='a') side += 0.05;
		if (key == 'd') side -= 0.05;
		if (key == 's') scale *= 0.98;
		//if (GetAsyncKeyState('W') & 0x8000) 
		glutPostRedisplay();
	}
	void display() {
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
		glRotatef(x, 1.0, 0.0, 0.0);
		glRotatef(y, 0.0, 1.0, 0.0);
		glRotatef(z, 0.0, 0.0, 1.0);

		glScalef(scale, scale, scale);
		gluLookAt( + side, 0, l / 4,
			0 + AngleX, 0 + AngleY, 5 + AngleZ,
			0, 1, 0);
		g.textGround();
		s.textSky();
		glBindTexture(GL_TEXTURE_2D, b.getTexture()); // this binds the texture of the tree after  drawing gorund and sky
		glCallList(drawT);
		b.textTree();
		glPopMatrix();
		glutSwapBuffers();
	}
	void reshape(int w, int h) {
		GLfloat aspect = (GLfloat)w / (GLfloat)h;
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if (w <= h)
			glOrtho(2.0, 2.0, -2.0 / aspect, 2.0 / aspect, -10.0, 10.0);
		else 
			glOrtho(-2.0*aspect, 2.0*aspect, -2.0, 2.0, -10.0, 10.0);
		    glMatrixMode(GL_MODELVIEW);
	}

	int main(int argc, char** argv) {
		glutInit(&argc, argv);
		glutInitWindowSize(1500, 1500);
		glutCreateWindow("Hierarchical Tree");
		init();
		glutDisplayFunc(display);
		glutReshapeFunc(reshape);
		glutKeyboardFunc(keyboard);
		glutMainLoop();
	}
