#include <GL/glut.h>
#include <vector>
#include "Quat.hh"

vector<Quat> cube = {
  Quat (0, -0.4,  0.4, -0.4),	// left  lower rear
  Quat (0,  0.4,  0.4, -0.4),	// right lower rear
  Quat (0,  0.4, -0.4, -0.4),	// right upper rear
  Quat (0, -0.4, -0.4, -0.4),	// left  upper rear
  Quat (0, -0.4,  0.4,  0.4),    // left  lower front
  Quat (0,  0.4,  0.4,  0.4),    // right lower front
  Quat (0,  0.4, -0.4,  0.4),    // right upper front
  Quat (0, -0.4, -0.4,  0.4)     // left  upper front
};

extern GLdouble axes[][3];

void
draw_cube (GLdouble ang, int axisIndex)
{
  Quat rotator (ang, axes[axisIndex]);
  vector<Quat> rr = rotator.qrot (cube);

#define LEFT__LOWER_REAR  rr[0].X (),  rr[0].Y (), rr[0].Z ()
#define RIGHT_LOWER_REAR  rr[1].X (),  rr[1].Y (), rr[0].Z ()
#define RIGHT_UPPER_REAR  rr[2].X (),  rr[2].Y (), rr[0].Z ()
#define LEFT__UPPER_REAR  rr[3].X (),  rr[3].Y (), rr[0].Z ()
#define LEFT__LOWER_FRONT rr[4].X (),  rr[4].Y (), rr[4].Z ()
#define RIGHT_LOWER_FRONT rr[5].X (),  rr[5].Y (), rr[5].Z ()  
#define RIGHT_UPPER_FRONT rr[6].X (),  rr[6].Y (), rr[6].Z ()
#define LEFT__UPPER_FRONT rr[7].X (),  rr[7].Y (), rr[7].Z ()

  glBegin (GL_QUADS);
  glColor3f (1.0f, 0.0f, 0.0f);
  glVertex3d (LEFT__LOWER_REAR);
  glVertex3d (RIGHT_LOWER_REAR);
  glVertex3d (RIGHT_UPPER_REAR);
  glVertex3d (LEFT__UPPER_REAR);
  glEnd ();

  glBegin (GL_QUADS);
  glColor3f (0.0f, 1.0f, 0.0f);
  glVertex3d (LEFT__LOWER_REAR);
  glVertex3d (RIGHT_LOWER_REAR);
  glVertex3d (RIGHT_LOWER_FRONT);
  glVertex3d (LEFT__LOWER_FRONT);
  glEnd ();

  glBegin (GL_QUADS);
  glColor3f (1.0f, 0.0f, 1.0f);
  glVertex3d (LEFT__UPPER_REAR);
  glVertex3d (RIGHT_UPPER_REAR);
  glVertex3d (RIGHT_UPPER_FRONT);
  glVertex3d (LEFT__UPPER_FRONT);
  glEnd ();

  glBegin (GL_QUADS);
  glColor3f (0.0f, 0.0f, 1.0f);
  glVertex3d (LEFT__LOWER_REAR);
  glVertex3d (LEFT__UPPER_REAR);
  glVertex3d (LEFT__UPPER_FRONT);
  glVertex3d (LEFT__LOWER_FRONT);
  glEnd ();

  glBegin (GL_QUADS);
  glColor3f (1.0f, 1.0f, 0.0f);
  glVertex3d (RIGHT_LOWER_REAR);
  glVertex3d (RIGHT_UPPER_REAR);
  glVertex3d (RIGHT_UPPER_FRONT);
  glVertex3d (RIGHT_LOWER_FRONT);
  glEnd();
};
