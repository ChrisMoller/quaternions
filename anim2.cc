#include <iostream>

#include <error.h>
#include <getopt.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <GL/glut.h>

#include "Quat.hh"

using namespace std;

GLdouble ang = 0.0;
#define FAST D2R (5.0)
#define SLOW D2R (30.0)
GLdouble inc = FAST;

#define DEFAULT_WIDTH  500
int width  = DEFAULT_WIDTH;
#define DEFAULT_HEIGHT 500
int height = DEFAULT_HEIGHT;

GLdouble axes[][3] = {
  {0, 0, 1},
  {0, 1, 1},
  {0, 1, 0},
  {1, 1, 0},
  {1, 1, 1},
  {1, 0, 1},
  {1, 0, 0}
};

const char* cmd = "ffmpeg -r 10 -f rawvideo -pix_fmt rgba -s %dx%d \
 -i - -threads 0 -preset fast -y -pix_fmt yuv420p -crf 21 -vf vflip %s";
char *vidout = nullptr;
FILE* ffmpeg = nullptr;

//GLdouble axis[3] = {0, 1.0, 1.0};		// rotate around y-z
int axisIndex = 0;
#define TIMERSECS 100

#define OFFSET 0.0

Quat p0 (0, -0.4,  0.4, OFFSET-0.4);	// left  lower rear
Quat p1 (0,  0.4,  0.4, OFFSET-0.4);	// right lower rear
Quat p2 (0,  0.4, -0.4, OFFSET-0.4);	// right upper rear
Quat p3 (0, -0.4, -0.4, OFFSET-0.4);	// left  upper rear

Quat p4 (0, -0.4,  0.4, OFFSET+0.4);  // left  lower front
Quat p5 (0,  0.4,  0.4, OFFSET+0.4);  // right lower front
Quat p6 (0,  0.4, -0.4, OFFSET+0.4);  // right upper front
Quat p7 (0, -0.4, -0.4, OFFSET+0.4);  // left  upper front

void animate(int value) {
  glutTimerFunc(TIMERSECS, animate, 1); // Re-register timer
  ang += inc;
  if (ang > 2.0 * M_PI) {
    ang = 0.0;
    // if (++axisIndex > 6) axisIndex = 0;
    if (++axisIndex > 6) {
      if (ffmpeg) {
	pclose(ffmpeg);
	exit (0);
      }
      else axisIndex = 0;
    }
  }
  glutPostRedisplay(); // Request a redraw
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Quat rotator (ang, axes[axisIndex]);
    Quat r0 = rotator.qrot (p0);
    Quat r1 = rotator.qrot (p1);
    Quat r2 = rotator.qrot (p2);
    Quat r3 = rotator.qrot (p3);
    Quat r4 = rotator.qrot (p4);
    Quat r5 = rotator.qrot (p5);
    Quat r6 = rotator.qrot (p6);
    Quat r7 = rotator.qrot (p7);

#define LEFT__LOWER_REAR  r0.X (),  r0.Y (), r0.Z ()
#define RIGHT_LOWER_REAR  r1.X (),  r1.Y (), r0.Z ()
#define RIGHT_UPPER_REAR  r2.X (),  r2.Y (), r0.Z ()
#define LEFT__UPPER_REAR  r3.X (),  r3.Y (), r0.Z ()
#define LEFT__LOWER_FRONT r4.X (),  r4.Y (), r4.Z ()
#define RIGHT_LOWER_FRONT r5.X (),  r5.Y (), r5.Z ()  
#define RIGHT_UPPER_FRONT r6.X (),  r6.Y (), r6.Z ()
#define LEFT__UPPER_FRONT r7.X (),  r7.Y (), r7.Z ()

  glBegin(GL_QUADS);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3d(LEFT__LOWER_REAR);
  glVertex3d(RIGHT_LOWER_REAR);
  glVertex3d(RIGHT_UPPER_REAR);
  glVertex3d(LEFT__UPPER_REAR);
  glEnd();

  glBegin(GL_QUADS);
  glColor3f(0.0f, 1.0f, 1.0f);
  glVertex3d(LEFT__LOWER_FRONT);
  glVertex3d(RIGHT_LOWER_FRONT);
  glVertex3d(RIGHT_UPPER_FRONT);
  glVertex3d(LEFT__UPPER_FRONT);
  glEnd();

  glBegin(GL_QUADS);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3d(LEFT__LOWER_REAR);
  glVertex3d(RIGHT_LOWER_REAR);
  glVertex3d(RIGHT_LOWER_FRONT);
  glVertex3d(LEFT__LOWER_FRONT);
  glEnd();

  glBegin(GL_QUADS);
  glColor3f(1.0f, 0.0f, 1.0f);
  glVertex3d(LEFT__UPPER_REAR);
  glVertex3d(RIGHT_UPPER_REAR);
  glVertex3d(RIGHT_UPPER_FRONT);
  glVertex3d(LEFT__UPPER_FRONT);
  glEnd();

  glBegin(GL_QUADS);
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3d(LEFT__LOWER_REAR);
  glVertex3d(LEFT__UPPER_REAR);
  glVertex3d(LEFT__UPPER_FRONT);
  glVertex3d(LEFT__LOWER_FRONT);
  glEnd();

  glBegin(GL_QUADS);
  glColor3f(1.0f, 1.0f, 0.0f);
  glVertex3d(RIGHT_LOWER_REAR);
  glVertex3d(RIGHT_UPPER_REAR);
  glVertex3d(RIGHT_UPPER_FRONT);
  glVertex3d(RIGHT_LOWER_FRONT);
  glEnd();

  if (ffmpeg) {
    void *buffer = malloc (sizeof(int) * width * height);
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    fwrite(buffer, sizeof(int) * width * height, 1, ffmpeg);
    free (buffer);
  }

  glutSwapBuffers();
}

int main(int ac, char *av[]) {
  {
    static struct option long_options[] = {
      {"width",     required_argument, 0,  'w' },
      {"height",    required_argument, 0,  'h' },
      {"video",     required_argument, 0,  'v' },
      {0,           0,                 0,   0 }
    };

    int c;
    int option_index = 0;
    while (-1 != (c = getopt_long (ac, av, "w:h:v:",
				   long_options, &option_index))) {
      switch (c) {
      case 'w': width  = atoi (optarg); break;
      case 'h': height = atoi (optarg); break;
      case 'v': vidout = strdup (optarg); break;
      }
    }
    if (vidout) {
      char *cmdstring = nullptr;
      asprintf (&cmdstring, cmd, width, height, vidout);
      fprintf (stderr, "vid = \"%s\"\n", cmdstring);
      ffmpeg = popen(cmdstring, "w");
      free (cmdstring);
      inc = SLOW;
    }
  }

  glutInit (&ac, av);
  glutInitWindowSize (width, height);
  glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glEnable (GL_DEPTH_TEST);
  glDepthMask (GL_TRUE);
  glDepthFunc (GL_LESS);
  glutCreateWindow ("Quat Animation");
  glutDisplayFunc (display);

#if 0
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective (40.f, 1.f, 1.f, 10.f);
#endif
    
  glutTimerFunc (TIMERSECS, animate, 0); // Start the timer
  glutMainLoop ();
  return 0;
}   
