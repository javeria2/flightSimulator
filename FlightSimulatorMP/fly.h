/*
*@Author: Sanchay Javeria
*/
/* header file and class definitions for fly.cpp */

#ifndef FLY___H___
#define FLY___H___
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <ctime>

/* position class used to monitor the position vector */
class position{
public:
	float a;
	float b;
	float c;

	/* constructor */
	position(){ 
		a = b = c = 0;
	}

	/* parameterized constructor */
	position(float a, float b, float c){ 
		this->a = a;
		this->b = b;
		this->c = c;
	}
};

/* vector class which contains the <x,y,z> co-ordinates of the plane vector */
class vector{
public:
	float x;
	float y;
	float z;
public:

	/* constructor */
	vector(){ 
		x = y = z = 0;
	}

	/* parameterized constructor */
	vector(float x, float y, float z){ 
		this->x = x;
		this->y = y;
		this->z = z;
	}

	/* copy constructor */
	vector(const vector& obj){ 
		x = obj.x;
		y = obj.y;
		z = obj.z;
	}

	/* normalizes a vector, or creates a unit vector along the same direction of the vector w.r.t which the function is called */
	vector normalize(){ 
		float value = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
		vector ret_;
		ret_.x = (float)(x / value);
		ret_.y = (float)(y / value);
		ret_.z = (float)(z / value);
		return ret_;

	}

	/* function to add two vectors, co-ordintes wise */
	vector addition(vector pt){ 
		vector pt_;
		pt_.x = pt.x + x;
		pt_.y = pt.y + y;
		pt_.z = pt.z + z;
		return pt_;
	}

	/* multiply floating constant to vector to move forward */
	vector multiply(float speed){ 
		vector ret_;
		ret_.x = x * speed;
		ret_.y = y * speed;
		ret_.z = z * speed;
		return ret_;
	}

	/* function to find dot-product of two vectors */
	float dot(vector pt){ 
		vector pt_;
		pt_.x = x * pt.x;
		pt_.y = y * pt.y;
		pt_.z = z * pt.z;
		return (pt_.x + pt_.y + pt_.z);
	}

	/* current position vector */
	vector curPosition(position p){ 
		vector ret_(p.a, p.b, p.c);
		return ret_;
	}
};

/* Camera class which tracks the current location and direction of the airplane */
class camera{
public:
	position p1; /* position vector */
	vector x1, y1, z1, copy; /* each vector corresponds to x, y and z axis of the plane in the horizontal plain and copy is used as a dummy vector */
	
	/* constructor */
	camera(){
		p1 = position(0.5, 1, 0.5);
		x1 = vector(-1, 0, 0);
		y1 = vector(0, -0.7, 0.8);
		z1 = vector(0, 0.9, 0.6);
	}

	/* current direction where the plain is pointing at (more like an alternative to gluLookAt())*/
	void lookAt(){  
		copy = vector(p1.a, p1.b, p1.c);
		const GLfloat m[16] = {
			x1.x, y1.x, z1.x, 0,
			x1.y, y1.y, z1.y, 0,
			x1.z, y1.z, z1.z, 0,
			-copy.dot(x1), -copy.dot(y1), -copy.dot(z1), 1 };
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(m);
	}
	
	/* to rotate a point  about an axis (here, z axis), formula taken from slides */	
	void rotationMatrix(vector &x1, vector &y1, float theta){ 
		vector _1 = x1;
		vector _2 = y1;
		x1.x = cos(theta) * _1.x - sin(theta) * _2.x;
		x1.y = cos(theta) * _1.y - sin(theta) * _2.y;
		x1.z = cos(theta) * _1.z - sin(theta) * _2.z;

		y1.x = sin(theta) * _1.x + cos(theta) * _2.x;
		y1.y = sin(theta) * _1.y + cos(theta) * _2.y;
		y1.z = sin(theta) * _1.z + cos(theta) * _2.z;
		lookAt();	
	}

	/* function for movement of plane horizontally (front: z and horizontal: x axis) */
	void yaw(float theta){ 
		rotationMatrix(x1, z1, -theta);
	}

	/* function for movement of plane about up (y) and forward (z) axis */
	void pitch(float theta){
		rotationMatrix(z1, y1, -theta);
	}

	/* function for movement of plane about up (y) and horizontal (x) axis */
	void roll(float theta){
		rotationMatrix(x1, y1, theta);
	}

	/* to display text on screen */
	void output(int x, int y, float r, float g, float b, void* font, char* string){ 
		glColor3f(r, g, b);
		glRasterPos2f(x, y);
		for (int i = 0; i < strlen(string); i++)
		{
			glutBitmapCharacter(font, string[i]);
		}
	}

	/* keeps the plane moving forward w.r.t forward (z) axis */
	void translate(float speed){ 
		vector normal = z1.normalize(); /* normal in the direction of motion */
		/* current position vector is added to the unit normal multiplied by the speed of motion */
		p1.a = z1.curPosition(p1).addition(normal.multiply(speed)).x; 
		p1.b = z1.curPosition(p1).addition(normal.multiply(speed)).y;
		p1.c = z1.curPosition(p1).addition(normal.multiply(speed)).z;

		lookAt();
	}
};
#endif
