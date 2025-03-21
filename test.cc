#include <iostream>
#include <math.h>
#include "Quat.hh"

using namespace std;

#define D2R(d) (M_PI * (d)/180.0)
#define R2D(r) (180.0 * (r)/M_PI)

int
main ()
{
  Quat t;
  
  cout << "\nConstructors:\n";
  Quat r (1, 2, 3, 4);
  cout << "r = " << r << endl;
  
  Quat s (2, 3, 4, 5);
  cout << "s = " << s << endl;

  cout << "\nSimple math:\n";
  cout << "r + s = " << r + s << endl;
  t = r;  t += s;
  cout << "r += s = " << t << endl;
  
  t = r;  t -= s;
  cout << "r -= s = " << t << endl;

  cout << "r * s = " << r * s << endl;
  cout << "s * r = " << s * r << endl;
  {
    Quat rs = r * s;
    Quat sr = s * r;
    cout << "(r * s == s * r) = " << (rs == sr)  << endl;
    cout << "(r * s != s * r) = " << (rs != sr)  << endl;
  }
  
  cout << "r / s = " << r/s << endl;

  cout << "\nConjugate:\n";
  cout << "*(r*s) = " << *(r*s) << endl;
  cout << "*r * *s = " << *r * *s << endl;
  cout << "*s * *r = " << *s * *r << endl;

  cout << "\nNorm:\n";
  cout << "+r = " << +r << endl;

  cout << "\nNegate:\n";
  cout << "-r = " << -r << endl;
  
  cout << "\nInvert:\n";
  cout << "~r" << ~r << endl;
  Quat ri = ~r;
  cout << "r * ri = " << r * ri << endl;
  
  cout << "\nMulitply/divide by double:\n";
  cout << "r * 7 = " <<  r * 7 << endl;
  cout << "r / 7 = " <<  r / 7 << endl;

  cout << "\nMulitply-assign:\n";
  {
    Quat x = r;
    cout << "r *= s = " << (x *= s) << endl;
  }

  cout << "\nDivide-assign:\n";
  {
    Quat x = r;
    cout << "r /= s = " << (x /= s) << endl;
  }
  
  cout << "\nDots and crosses:\n";
#if 0
  cout << "r qdot s = " << Quat::qdot (r,s) << endl;
  cout << "r qdot r = " << Quat::qdot (r,r) << endl;
  cout << "r qcross s = " << Quat::qcross (r,s) << endl;
  cout << "r qcross r = " << Quat::qcross (r,r) << endl;
#endif
  
  cout << "r.qdot (s) = " << r.qdot (s) << endl;
  cout << "r.qdot (r) = " << r.qdot (r) << endl;
  cout << "r.qcross (s) = " << r.qcross (s) << endl;
  cout << "r.qcross (r) = " << r.qcross (r) << endl;
  cout << "r.qang (s) = " << R2D (r.qang (s)) << " degrees" << endl;
  cout << "r.qang (r) = " << R2D (r.qang (r)) << " degrees" << endl;

  cout << "\nStringify:\n";
#if 0
  cout << "sring " << Quat::qstr (r) << endl;
#endif
  cout << "sring " << r.qstr () << endl;
  
  return 0;
}
