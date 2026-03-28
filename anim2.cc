#include <iostream>
#include <vector>

#include <error.h>
#include <getopt.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <GL/glut.h>

#include "Quat.hh"

#define OFFSET 0.0

#include "cube.hh"
#include "icosahedron.h"

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
#define Z_AXIS 0
  {0, 1, 1},	
  {0, 1, 0},
#define Y_AXIS 2
  {1, 1, 0},
  {1, 1, 1},
#define MAIN_DIAG_AXIS 4
  {1, 0, 1},
  {1, 0, 0}
#define X_AXIS 6
};
int axisIndex = 0;
bool axisLocked = false;

const char* cmd = "ffmpeg -r 10 -f rawvideo -pix_fmt rgba -s %dx%d \
 -i - -threads 0 -preset fast -y -pix_fmt yuv420p -crf 21 -vf vflip %s";
char *vidout = nullptr;
FILE* ffmpeg = nullptr;

#define TIMERSECS 100

void animate(int value) {
  glutTimerFunc(TIMERSECS, animate, 1); // Re-register timer
  ang += inc;
  if (ang > 2.0 * M_PI) {
    ang = 0.0;
    if (!axisLocked) {
      if (++axisIndex > 6) {
	if (ffmpeg) {
	  pclose(ffmpeg);
	  exit (0);
	}
	else axisIndex = 0;
      }
    }
  }
  glutPostRedisplay(); // Request a redraw
}

void display(void) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  draw_cube (ang, axisIndex);

  if (ffmpeg) {
    void *buffer = malloc (sizeof(int) * width * height);
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    fwrite(buffer, sizeof(int) * width * height, 1, ffmpeg);
    free (buffer);
  }
  glutSwapBuffers ();
}

int main(int ac, char *av[]) {
  {
    static struct option long_options[] = {
      {"width",     required_argument, 0,  'w' },
      {"height",    required_argument, 0,  'h' },
      {"video",     required_argument, 0,  'v' },
      {"axis",      required_argument, 0,  'a' },
      {0,           0,                 0,   0 }
    };

    int c;
    int option_index = 0;
    while (-1 != (c = getopt_long (ac, av, "w:h:v:a:",
				   long_options, &option_index))) {
      switch (c) {
      case 'w': width  = atoi (optarg); break;
      case 'h': height = atoi (optarg); break;
      case 'v': vidout = strdup (optarg); break;
      case 'a':
	switch (*optarg) {
	case 'x':
	  axisIndex = X_AXIS;
	  axisLocked = true;
	  break;
	case 'y':
	  axisIndex = Y_AXIS;
	  axisLocked = true;
	  break;
	case 'z':
	  axisIndex = Z_AXIS;
	  axisLocked = true;
	  break;
	case 'm':
	  axisIndex = MAIN_DIAG_AXIS;
	  axisLocked = true;
	  break;
	}
	break;
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
