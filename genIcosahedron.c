#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define phi (((1 + sqrt (5.0)) / 2.0)/5.0)
double icosahedron[][3] = {
  {1, phi, 0}, 
  {-1, phi, 0}, 
  {1, -phi, 0}, 
  {-1, -phi, 0}, 
  {0, 1, phi}, 
  {0, -1, phi}, 
  {0, 1, -phi}, 
  {0, -1, -phi}, 
  {phi, 0, 1}, 
  {-phi, 0, 1}, 
  {phi, 0, -1}, 
  {-phi, 0, -1}
};
int nr_verts = sizeof(icosahedron) / (3 * sizeof(double));
  
int icosafaces[][3] = {
  {0,  4,  8},
  {0,  8,  2},
  {0,  2,  5},
  {0,  5,  9},
  {0,  9,  4},
  {1,  3, 11},
  {1, 11,  7},
  {1,  7,  6},
  {1,  6, 10},
  {1, 10,  3},
  {2,  8,  5},
  {5,  2, 10},
  {5, 10,  9},
  {5,  9,  8},
  {3, 11,  7},
  {3,  7,  6},
  {3,  6, 10},
  {3, 10, 11},
  {4,  8, 11},
  {4, 11,  7}
};
int nr_faces = sizeof(icosafaces) / (3 * sizeof(int));

double colours[][3] = {
  {230, 25, 75},
  {60, 180, 75},
  {255, 225, 25},
  {67, 99, 216},
  {245, 130, 49},
  {145, 30, 180},
  {66, 212, 244},
  {240, 50, 230},
  {191, 239, 69},
  {250, 190, 212},
  {70, 153, 144},
  {220, 190, 255},
  {154, 99, 36},
  {255, 250, 200},
  {128, 0, 0},
  {170, 255, 195},
  {128, 128, 0},
  {255, 216, 177},
  {0, 0, 117},
  {169, 169, 169}
};

double
getcross (double *cp, int i)
{
  double avg_y = 0.0;
  int ix0 = icosafaces[i][0];		// vtx 0
  int ix1 = icosafaces[i][1];		// vtx 1
  int ix2 = icosafaces[i][2];		// vtx 2
  double v1[3];
  double v2[3];
  for (int i = 0; i < 3; i++) {
    v1[i] =  icosahedron[ix1][i] - icosahedron[ix0][i];
    v2[i] =  icosahedron[ix2][i] - icosahedron[ix0][i];
  }

  cp[0] = v1[1] * v2[2] - v1[2] * v2[1];
  cp[1] = v1[2] * v2[0] - v1[0] * v2[2];
  cp[2] = v1[0] * v2[1] - v1[1] * v2[0];

  avg_y += icosahedron[ix0][1];		// y coords
  avg_y += icosahedron[ix1][1];
  avg_y += icosahedron[ix2][1];
  return avg_y / 3.0;
}
	  
int
main ()
{
  // fix faces to ccw
  for (int i = 0; i < nr_faces; i++) {
    double crossprod[3];
    double avg_y = getcross (crossprod, i);
    // assume eye at [0 0 1]: ([ 0 0 1] dot crossprod) = crossprod[2]
    double dot = crossprod[2];
    if (avg_y > 0.0) dot = -dot;	// if on back side, reflect
    if (dot < 0.0) {			// if not ccw, swap any two verts
      int t =  icosafaces[i][0];
      icosafaces[i][0] = icosafaces[i][1];
      icosafaces[i][1] = t;
    }
#if 0
    getcross (crossprod, i);			// verify
    fprintf (stderr, "%g\n", crossprod[2]);
#endif
  }

#define SCALE 3.0
  fprintf (stdout, "#include <GL/glut.h>\n");
  fprintf (stdout, "#include <vector>\n");
  fprintf (stdout, "#include \"Quat.hh\"\n");
  fprintf (stdout, "extern GLdouble axes[][3];\n");
  fprintf (stdout,
	   "void\ndraw_icosahedron (GLdouble ang, int axisIndex)\n{\n");

  fprintf (stdout, "vector<Quat> cube = {\n");
  for (int i= 0; i < nr_verts; i++) {
    fprintf (stdout, "  Quat (0.0, %g, %g, %g),\n",
	     icosahedron[i][0],
	     icosahedron[i][1],
	     icosahedron[i][2]);
  }
  fprintf (stdout, "};\n");
  
  fprintf (stdout, "  Quat rotator (ang, axes[axisIndex]);\n");
  fprintf (stdout, "  vector<Quat> rr = rotator.qrot (cube);\n");

  for (int i = 0; i < nr_verts; i++)
    fprintf (stdout,
     "#define VERT_%1$02d  rr[%1$d].X (),  rr[%1$d].Y (), rr[%1$d].Z ()\n", i);
  
  for (int i = 0; i < nr_faces; i++) {
    fprintf (stdout, "\n  glBegin (GL_TRIANGLES); // t %d\n", i);
    fprintf (stdout, "    glColor3d (%g, %g, %g);\n",
	     colours[i][0]/256.0, colours[i][1]/256.0, colours[i][2]/256.0);
    for (int j = 0; j < 3; j++)
      fprintf (stdout, "    glVertex3d (VERT_%02d);\n", icosafaces[i][j]);
    fprintf (stdout, "  glEnd ();\n");
  }
  fprintf (stdout, "}\n");
}
