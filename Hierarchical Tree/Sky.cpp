/* this draw skey above the tree and this the same with the ground but it has teh sky texture insted of the gorund
This code uses smaples by Dr. Araz Yusubov*/

#include <GL/glut.h>
#include <windows.h>
#include <objidl.h>
#define NOMINMAX 
#include <algorithm>
namespace Gdiplus {
	using std::min;  // this was the problem for loading the image
	using std::max;
}
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;
class Sky {
public:
	float height;
	GLuint TexSky;
public:
	Sky(float height): height(height) {
	}
	void textSky() {
		GLubyte image[256][256][3];
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &TexSky);
		glBindTexture(GL_TEXTURE_2D, TexSky);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 

		Bitmap bmp(L"sky.jpg", true);  // this is created by Dr. Araz Yusubov
		Color pixelcolor;
		for (int i = 0; i < 256; i++) {
			for (int j = 0; j < 256; j++) {
				bmp.GetPixel(j, i, &pixelcolor);
				image[i][j][0] = pixelcolor.GetR();
				image[i][j][1] = pixelcolor.GetG();
				image[i][j][2] = pixelcolor.GetB();
			}
		}
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glBindTexture(GL_TEXTURE_2D, TexSky);
		glBegin(GL_QUADS);        // add a sky
		glTexCoord2f(0.0, 0.0);  // these are the coordinates  for the sky texture
		glVertex3f(-20.0, height, -20.0); // here we chnage the y coordinate to the height of teh scene
		glTexCoord2f(10.0, 0.0);
		glVertex3f(-20.0, height, 20.0);
		glTexCoord2f(10.0, 10.0);
		glVertex3f(+20.0,height, 20.0);
		glTexCoord2f(0.0, 10.0);
		glVertex3f(+20.0,height, -20.0);
		glEnd();
	}
	GLuint getTextSky() {
		return TexSky;
	}
};