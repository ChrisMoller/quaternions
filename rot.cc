#include <iostream>
#include <math.h>

#include "Quat.hh"

using namespace std;

#define D2R(d) (M_PI * (d)/180.0)
#define R2D(r) (180.0 * (r)/M_PI)

int
main ()
{
  Quat p0 (0, 1, 0, 0);
  Quat p1 (0, 0, 1, 0);
#if 1
  double theta = Quat::qang (p0, p1);
#else
  double theta = acos (Quat::qdot (p0, p1) / (+p0 * +p1));
#endif
  Quat u =  Quat::qcross (p0, p1);
  
  double tp;
  double ti = theta / 20.0;
  for (tp = 0; tp < theta + ti; tp += ti) {

    Quat q = Quat (cos (tp/2.0), 0, 0, 0) + (u * sin (tp/2.0));

    Quat r = q * p0 * ~q;

    cout << "r = " << r << " mag = " << +r << endl;
  }
  cout << "p1 =" << p1 << endl;

  return 0;
}

