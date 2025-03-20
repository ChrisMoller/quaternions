#include <iostream>
#include <iomanip>
#include <ios>
#include <math.h>

#include "Quat.hh"

using namespace std;

#define D2R(d) (M_PI * (d)/180.0)
#define R2D(r) (180.0 * (r)/M_PI)

int
main ()
{
  // initial vectors to be rotated from p0 to p1
  Quat p0 (0, 1, 0, 0);
  Quat p1 (0, 0, 1, 0);

  // the angle between those vectors
  double theta = Quat::qang (p0, p1);

  // the normal of those vectors, the rotation vector
  Quat u =  Quat::qcross (p0, p1);
  
  double tp;

  // arbitrary 20 steps in the rotation
  double ti = theta / 20.0;

  for (tp = 0; tp < theta + ti; tp += ti) {
    // create a quat with a scalar component consisting of the rotation angle
    // and a vector component consisting of the rotation axis
    Quat q = Quat (cos (tp/2.0), 0, 0, 0) + (u * sin (tp/2.0));

    // do the rotation
    Quat r = q * p0 * ~q;

    cout << Quat::qstr (r) << "   " << +r << "   " 
	 <<  R2D (Quat::qang (p1, r)) << endl;
  }
  cout << "p1 =" << p1 << endl;

  return 0;
}

