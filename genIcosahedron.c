#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int
main ()
{
#define SCALE 3.0
  double phi = ((1 + sqrt (5.0)) / 2.0)/5.0;
  double icosahedron[][3] = {
#if 1
    {0, +1, +phi}, // 0
    {0, +1, -phi}, // 1
    {0, -1, -phi}, // 2
    {0, -1, +phi}, // 3

    {+phi, 0, +1}, // 4
    {+phi, 0, -1}, // 5
    {-phi, 0, -1}, // 6
    {-phi, 0, +1}, // 7

    {+1, +phi, 0}, // 8
    {+1, -phi, 0}, // 9
    {-1, -phi, 0}, // 10
    {-1, +phi, 0}  // 11
#endif
#if 0
    { 0.0,  1.0,  phi},
    { 0.0, -1.0,  phi},
    { 0.0,  1.0, -phi},
    { 0.0, -1.0, -phi},
    { 1.0,  phi,  0.0},
    {-1.0,  phi,  0.0},
    { 1.0, -phi,  0.0},
    {-1.0, -phi,  0.0},
    { phi,  0.0,  1.0},
    {-phi,  0.0,  1.0},
    { phi,  0.0, -1.0},
    {-phi,  0.0, -1.0}
#endif
  };
  int nr_verts = sizeof(icosahedron) / (3 * sizeof(double));
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
  
    int icosafaces[][3] = {
        {3,0,4},
        {3,4,9},
        {3,9,10},
        {3,10,7},
        {3,7,0},
        {0,8,4},
        {0,7,11},
        {0,11,8},
        {4,8,5},
        {4,5,9},
        {7,10,6},
        {7,6,11},
        {9,5,2},
        {9,2,10},
        {2,6,10},
        {1,5,8},
        {1,8,11},
        {1,11,6},
        {5,1,2},
        {2,1,6}
        };
  int nr_faces = sizeof(icosafaces) / (3 * sizeof(int));
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
