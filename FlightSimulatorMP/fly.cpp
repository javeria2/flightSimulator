/*
*@Author: Sanchay Javeria
*/

#include "fly.h"
#include "mountain.h"


camera view; /* instance of camera class */
float speed = 0.0; /* variable used to increase/decrease speed */
int FPS = 30; /* fps rating for score */
clock_t startClock = 0, curClock; /* to monitor clock time to disiplay score */
char buffer[1000] = { '\0' }; /* buffer used to store score */
int score = 0; /* score to be displayed on screen */

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	view.translate(speed - 0.0002);
	mdisplay();

	/*this part displays score on screen */
	curClock = clock();
	float elapsed = (curClock - startClock) / (float)CLOCKS_PER_SEC;
	if (elapsed>1.0f){
		score++; 
		_snprintf(buffer, sizeof(buffer), "Score: %d", score);
		view.output(8, -8, 0, 0, 0, GLUT_BITMAP_TIMES_ROMAN_24, buffer);
	}
	
	/* this part draws the sun */
	glTranslatef(2, -1, 4);
	GLfloat pass_mat[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pass_mat);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pass_mat);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pass_mat);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0);
	int i, x = 0, y = 0; /* to mark the centre (x,y) */
	double radius = 0.30; /* sun radius */
	double twicePi = 2.0 * 3.142;
	glBegin(GL_TRIANGLE_FAN); /* begin circle */
	glVertex2f(x, y); /* centre of circle */
	for (i = 0; i <= 20; i++)   {
		glVertex2f(
			(x + (radius * cos(i * twicePi / 20))), (y + (radius * sin(i * twicePi / 20)))
			);
	}
	glEnd();  
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();

	
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, 1.0, 0.01, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

/* keyboard and special key function for flying */
void keys(int key, int x, int y){
	/* rudder control */
	if (key == GLUT_KEY_RIGHT)
		view.roll(-0.1);

	/* pitch control */
	if (key == GLUT_KEY_DOWN)
		view.pitch(0.1);

	/* rudder control */
	if (key == GLUT_KEY_LEFT)
		view.roll(0.1);

	/*pitch control */
	if (key == GLUT_KEY_UP)
		view.pitch(-0.1);

	/* control rudder and pedals together */
	if (key == GLUT_KEY_DOWN + GLUT_KEY_LEFT){
		view.pitch(0.1);
		view.roll(0.1);
	}

	if (key == GLUT_KEY_DOWN + GLUT_KEY_RIGHT){
		view.pitch(0.1);
		view.roll(-0.1);
	}

	if (key == GLUT_KEY_UP + GLUT_KEY_LEFT){
		view.pitch(-0.1);
		view.roll(0.1);
	}

	if (key == GLUT_KEY_UP + GLUT_KEY_RIGHT){
		view.pitch(-0.1);
		view.roll(-0.1);
	}
	glutPostRedisplay();
}

/* keyboard controls for flying */
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 't':
		toggle(); 
		init();
		break;

	/* use rudders to move right */
	case 'd':
		view.yaw(0.1);
		break;

	/* use rudders to move left */
	case 'a':
		view.yaw(-0.1);
		break;

	/* pitch up */
	case 's':
		view.pitch(0.1);
		break;

	/*pitch down */
	case 'w':
		view.pitch(-0.1);
		break;

	/* hit SPACEBAR to increase speed */
	case ' ':
		speed -= 0.0001;
		break;

	/* hit 'b' to break/reverse */
	case 'b':
		speed += 0.0001;
		break;

	/* hit escape to quit app */
	case 27:
		exit(0);
		break;
	}
	/* keyboard controls for mountain */
	mkeyboard(key,x,y);
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	system("color 1A"); /* set the color of console window to cool BLUE in foreground and NEON in background */
	std::cout << "WELCOME TO FLIGHT SIMULATOR!" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "CONTROLS:" << std::endl;
	std::cout << "1. Press 'w' or 'up arrow key' a few times to see the SUN!" << std::endl;
	std::cout << "2. Press 'a' to yaw left" << std::endl;
	std::cout << "3. Press 'd' to yaw right" << std::endl;
	std::cout << "4. Press 'w' or 'up arrow key' to pitch up" << std::endl;
	std::cout << "5. Press 's' or 'down arrow key' to pitch down" << std::endl;
	std::cout << "6. Press 'left arrow key' to roll left" << std::endl;
	std::cout << "7. Press 'right arrow key' to roll right" << std::endl;
	std::cout << "8. Try a combination of controls 4, 5, 6, 7 to fly interactively" << std::endl;
	std::cout << "9. Press 't' to toggle between day/night mode" << std::endl;
	std::cout << "10. Press '-/+' to decrease/increase mud level around mountains" << std::endl;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("FLIGHT SIMULATOR");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keys);
	startClock = clock();
	glutMainLoop();
	return 0;
}
