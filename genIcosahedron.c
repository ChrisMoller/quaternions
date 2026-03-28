#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int
main ()
{
#define SCALE 3.0
  double phi = ((1 + sqrt (5.0)) / 2.0)/4.0;
  double icosahedron[][3] = {
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
  };
  int nr_verts = sizeof(icosahedron) / (3 * sizeof(double));
  fprintf (stdout, "#ifndef ICOSAHEDRON_H\n");
  fprintf (stdout, "#define ICOSAHEDRON_H\n");
  fprintf (stdout, "#include \"Quat.hh\"\n");
  fprintf (stdout, "vector<Quat> icosahedron = {\n");
  for (int i= 0; i < nr_verts; i++) {
    fprintf (stdout, "  Quat (0.0, %g, %g, %g),\n",
	     icosahedron[i][0],
	     icosahedron[i][1],
	     icosahedron[i][2]);
  }
  fprintf (stdout, "};\n");
  fprintf (stdout, "#endif // ICOSAHEDRON_H\n");
  return EXIT_SUCCESS;
}
