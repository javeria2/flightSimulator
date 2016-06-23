/*
*@Author: Sanchay Javeria
*/
/* header file for mountain.cpp */
#ifndef MOUNTAIN___H___
#define MOUNTAIN___H___
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <iostream>

void toggle(); /* toggles day/night mode */
int seed(float x, float y);
void mountain(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float s);
void init(void);
void mdisplay(void);
void mkeyboard(unsigned char key, int x, int y);

#endif