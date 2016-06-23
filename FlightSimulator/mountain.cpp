/*
*@Author: Sanchay Javeria
*/

#include "mountain.h"
/* mountain.cpp file (provided by professor):
* key points to note: improved efficiency in this version of the height-map. If you notice, there are very less jerks now between frames,
* in other words, transition between two frames is a lot more smoother than before,
* I did this by creating a list of vertices for the triangles so that they don't have to be stored again and again each time they are rendered,
* Also, I've changed the colour from dull brown to brigh green which gives a feel of flying over grass.
*/
float sealevel;
float polysize;
int mode = 0;

void toggle(){
	mode = !mode;
}

int seed(float x, float y) {
	static int a = 1588635695, b = 1117695901;
	int xi = *(int *)&x;
	int yi = *(int *)&y;
	return ((xi * a) % b) - ((yi * b) % a);
}

void mountain(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float s)
{
	float x01, y01, z01, x12, y12, z12, x20, y20, z20;

	if (s < polysize) {
		x01 = x1 - x0;
		y01 = y1 - y0;
		z01 = z1 - z0;

		x12 = x2 - x1;
		y12 = y2 - y1;
		z12 = z2 - z1;

		x20 = x0 - x2;
		y20 = y0 - y2;
		z20 = z0 - z2;

		float nx = y01*(-z20) - (-y20)*z01;
		float ny = z01*(-x20) - (-z20)*x01;
		float nz = x01*(-y20) - (-x20)*y01;

		float den = sqrt(nx*nx + ny*ny + nz*nz);

		if (den > 0.0) {
			nx /= den;
			ny /= den;
			nz /= den;
		}

		glBegin(GL_TRIANGLES);
		glNormal3f(nx, ny, nz);
		glVertex3f(x0, y0, z0);
		glNormal3f(nx, ny, nz);
		glVertex3f(x1, y1, z1);
		glNormal3f(nx, ny, nz);
		glVertex3f(x2, y2, z2);
		glEnd();

		return;
	}

	x01 = 0.5*(x0 + x1);
	y01 = 0.5*(y0 + y1);
	z01 = 0.5*(z0 + z1);

	x12 = 0.5*(x1 + x2);
	y12 = 0.5*(y1 + y2);
	z12 = 0.5*(z1 + z2);

	x20 = 0.5*(x2 + x0);
	y20 = 0.5*(y2 + y0);
	z20 = 0.5*(z2 + z0);

	s *= 0.5;

	srand(seed(x01, y01));
	z01 += 0.3*s*(2.0*((float)rand() / (float)RAND_MAX) - 1.0);
	srand(seed(x12, y12));
	z12 += 0.3*s*(2.0*((float)rand() / (float)RAND_MAX) - 1.0);
	srand(seed(x20, y20));
	z20 += 0.3*s*(2.0*((float)rand() / (float)RAND_MAX) - 1.0);

	mountain(x0, y0, z0, x01, y01, z01, x20, y20, z20, s);
	mountain(x1, y1, z1, x12, y12, z12, x01, y01, z01, s);
	mountain(x2, y2, z2, x20, y20, z20, x12, y12, z12, s);
	mountain(x01, y01, z01, x12, y12, z12, x20, y20, z20, s);
}

void init(void)
{
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lpos[] = { 0.0, 1.0, 0.0, 0.0 };
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);

	if (!mode) glClearColor(0.6, 0.5, 1.0, 0.0);
	else glClearColor(0.1,0.1,0.1,0.0);

	/* glShadeModel (GL_FLAT); */
	glEnable(GL_DEPTH_TEST);

	sealevel = 0.01;
	polysize = 0.06; /* change polygon size (increase) to decrease jerks */
	glNewList(1, GL_COMPILE); /* form new list to avoid rendering the coordinates every time display() is called */
	mountain(2.0, 0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 2.0, 0.0, 2.0);
	mountain(2.0, 2.0, 0.0, 0.0, 2.0, 0.0, 2.0, 0.0, 0.0, 2.0);
	mountain(1.0, 2.0, 0.0, 0.0, 1.0, 0.0, 2.0, 0.0, 0.0, 2.0);
	glEndList();
}
void mkeyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '-':
		sealevel -= 0.01;
		break;
	case '+':
	case '=':
		sealevel += 0.01;
		break;
	case 'f':
		polysize *= 0.5;
		break;
	case 'c':
		polysize *= 2.0;
		break;
	}
}

void mdisplay(void)
{

	GLfloat tanamb[] = { 0.2, 0.15, 0.1, 1.0 };
	GLfloat tandiff[] = { 0.0, 0.3, 0.2, 1.0 };
	GLfloat new_[] = { 0.1, 0.2, 0.0, 1.0 }; /* new co-ordinates added */

	GLfloat seaamb[] = { 0.647059, 0.2, 0.10, 1.0 };
	GLfloat seadiff[] = { 0.164706, 0.2, 0.10, 1.0 };
	GLfloat seaspec[] = { 0.164706, 0.15, 0.10, 1.0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tanamb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tandiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, new_);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0); 

	glTranslatef(-1, -1, 0); /* translate and draw mountains */
	glCallList(1); /* call our list of mountain co-ordinates to spit out triangles */

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, seaamb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, seadiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, seaspec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0); 

	glNormal3f(0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
	glVertex3f(0.0, 0.0, sealevel);
	glVertex3f(2.5, 0.0, sealevel);
	glVertex3f(2.5, 2.5, sealevel);
	glVertex3f(0.0, 2.5, sealevel);
	glEnd();
}