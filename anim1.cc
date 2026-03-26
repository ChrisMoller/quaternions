#include <iostream>
#include <GL/glut.h>

#include "Quat.hh"

using namespace std;

GLdouble ang = 0.0;
GLdouble inc = D2R (5.0);	// inc 5 degrees
double axis[3] = {0, 1.0, 1.0};		// rotate around y-z
#define TIMERSECS 100

Quat p0 (0, -0.4,  0.4, 0);
Quat p1 (0,  0.4,  0.4, 0);
Quat p2 (0,  0.4, -0.4, 0);
Quat p3 (0, -0.4, -0.4, 0);

void animate(int value) {
  glutTimerFunc(TIMERSECS, animate, 1); // Re-register timer
  ang += inc;
  if (ang > 2.0 * M_PI) ang = 0.0;
  glutPostRedisplay(); // Request a redraw
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    Quat rotator (ang, axis);
    Quat r0 = rotator.qrot (p0);
    Quat r1 = rotator.qrot (p1);
    Quat r2 = rotator.qrot (p2);
    Quat r3 = rotator.qrot (p3);

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2d(r0.X (),  r0.Y ());
    glVertex2d(r1.X (),  r1.Y ());
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2d(r2.X (),  r2.Y ());
    glVertex2d(r3.X (),  r3.Y ());
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("Quat Animation");
    glutDisplayFunc(display);
    glutTimerFunc(TIMERSECS, animate, 0); // Start the timer
    glutMainLoop();
    return 0;
}   
