/* 
Here we create a tree object in order to make our code neat and OOP
some parts of this code is written by Dr. Araz Yusubov and we are using that samples
*/
#include <GL\freeglut.h>
#include <math.h>
#include <windows.h>
#include <ctime>
#include <objidl.h>
#define NOMINMay 
#include <algorithm>
namespace Gdiplus {
	using std::min;
	using std::max;
}
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;
class Branch {
private:
	int n;
	float l; // the length of the tree
	float k1; // the first coefficient for the first branch
	float k2; // the second coefficient for the second branch
	float k3; // the third coefficient for the third branch
	float ay; // the angle of the first branch along y
	float ax; // the angle of the first branch along x
	float bx; // the angle of the second branch along the y
	float by; // the angle of the second branch along the x
	float cx; // the angle of the third branch along the x
	float cy; // the angle of the third branch along the y
	float m2; // the start point of the second branch
	float m3; // the start point of the third branch
	float base; // the base (radius) of the tree
	GLuint TexTree; // texture reference for binding
public:
	Branch(int n, float l,float base) : // constructor 
		n(n), l(l), base(base){} // only three parameters needed because we made the tree random
	void makePrism(float height, float base) { // creates prisms for the branches and it has the length and the base for each branch
		glPushMatrix();
		float side_len = base*sqrt(2);
		// downside of the quad
		glBegin(GL_QUADS);
		glVertex3f(-side_len, 0, -side_len); 
		glVertex3f(-side_len, 0, +side_len);
		glVertex3f(+side_len, 0, +side_len);
		glVertex3f(+side_len, 0, -side_len);
		glEnd();
		//top side of the quad
		glBegin(GL_QUADS);
		glVertex3f(-side_len, height, -side_len);
		glVertex3f(-side_len, height, +side_len);
		glVertex3f(+side_len, height, +side_len);
		glVertex3f(+side_len, height, -side_len);
		glEnd();

		//side quads here wew have also the coordinates for the textures
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-side_len, 0, -side_len);
		glTexCoord2f(0.0, 0.25);
		glVertex3f(-side_len, 0, +side_len);
		glTexCoord2f(1.0, 0.25);
		glVertex3f(-side_len, height, +side_len);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(-side_len, height, -side_len);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.25);
		glVertex3f(-side_len, 0, +side_len);
		glTexCoord2f(0.0, 0.50);
		glVertex3f(+side_len, 0, +side_len);
		glTexCoord2f(1.0, 0.50);
		glVertex3f(+side_len, height, +side_len);
		glTexCoord2f(1.0, 0.25);
		glVertex3f(-side_len, height, +side_len);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.50);
		glVertex3f(+side_len, 0, +side_len);
		glTexCoord2f(0.0, 0.75);
		glVertex3f(+side_len, 0, -side_len);
		glTexCoord2f(1.0, 0.75);
		glVertex3f(+side_len, height, -side_len);
		glTexCoord2f(1.0, 0.50);
		glVertex3f(+side_len, height, +side_len);
		glEnd();
		
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.75); 
		glVertex3f(-side_len, 0, -side_len);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(+side_len, 0, -side_len);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(+side_len, height, -side_len);
		glTexCoord2f(1.0, 0.75);
		glVertex3f(-side_len, height, -side_len);
		glEnd();

		glPopMatrix();
		glutSwapBuffers();
	}
	void randomGen() {  // this generates random numbers for each run
		  // however, i commented the coeffiecents random generation, if you want you can chnage it, but belive me the tree will be ugly :d
           srand(time(NULL)); // makes different random numbers each run http://stackoverflow.com/questions/7748071/same-random-numbers-every-time-i-run-the-program 
        	k1 = 0.5; //(float)((rand() % 10)) / 10;
			k2 = 0.7; //(float)((rand() % 10)) / 10;
			k3 = 0.8; //(float)((rand() % 10)) / 10;
			m2 = 0.5; //(float)((rand() % 10)) / 10;
			m3 = 0.7; //(float)((rand() % 10)) / 10;
			ax = (float)((rand() % 90)); // this generates different angles
			ay = (float)((rand() % 90));
			bx = (float)((rand() % 90));
			by = (float)((rand() % 90));
			cx = (float)((rand() % 90))*-1;
			cy = (float)((rand() % 90))*-1;
	}
	void makeTree(int n, float height, float base) {  // this is the recursion part of the tree and this generates the tree 
		// the hierarchical part of teh recursion refers to Dr. Araz Yusubov and the book
	    makePrism(height, base); // this creates prism
		if (n == 0) { // this the end of the recursion , base statement
			return;
		} 
		// first branch   
		glPushMatrix();	// it take matrix
		glTranslatef(0.0,height, 0.0); // go to the top;
		glRotatef(ax, 1, 0, 0); // make rotation to x
		glRotatef(ay, 0, 1, 0); // make rotation to y
		makeTree(n - 1, height*k1, base *0.7); // recur my method
		glPopMatrix(); // restore my matrix
		// here drawing second branch here
		glPushMatrix(); // the things with the first branch
		glTranslatef(0.0, height*m2, 0.0);
		glRotatef(bx, 1, 0, 0);
		glRotatef(by, 0, 1, 0);
		makeTree(n - 1, height*k2, base * 0.7);
		glPopMatrix();
		// drawing the third branch here
		glPushMatrix();
		glTranslatef(0.0, height*m3, 0.0);
		glRotatef(cx, 1, 0, 0);
		glRotatef(cy, 0, 1, 0);
		makeTree(n - 1, height*k3, base *0.7);
		glPopMatrix();
	}
	
	void textTree() {  // this part is taken from the sample codes by Dr. Araz Yusubov
		Bitmap bmp(L"tree.jpg", true);
		Color pixelcolor;
		GLubyte tree_image[256][256][3];
		glGenTextures(1, &TexTree); 
		glBindTexture(GL_TEXTURE_2D, TexTree);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, // used when the pixel being textured maps to an area less than or equal to one texture element
			GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, // used whenever the pixel being textured maps to an area greater than one texture element
			GL_LINEAR);

		for (int i = 0; i < 256; i++) {
			for (int j = 0; j < 256; j++) {
				bmp.GetPixel(j, i, &pixelcolor);
				tree_image[i][j][0] = pixelcolor.GetR();
				tree_image[i][j][1] = pixelcolor.GetG();
				tree_image[i][j][2] = pixelcolor.GetB();
			}
		}
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, tree_image);
	}

	GLuint getTexture() {
		return TexTree; // this is used in the main class for binding the texture
	}
};