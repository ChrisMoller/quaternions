#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
//#include <libquat/Quat.hh>
#include "Quat.hh"

using namespace std;

#define D2R(d) (M_PI * (d)/180.0)
#define R2D(r) (180.0 * (r)/M_PI)

/***
    pca =? least squares/linear regression
 ***/

Quat r (1, 2, 3, 4);
Quat s (2, 3, 4, 5);
double axis[3] = { 0, 1, 2};		// x axis
Quat x (M_PI/4.0, axis);

#if 1
#include "tests.h"
#else
#define TEST(n,f) void test##n () {f}

TEST (01, cout << r << endl;)
TEST (02, cout << s << endl;)

TEST (03, cout << r + s << endl;)
TEST (04, {Quat t = r; t += s; cout << t << endl;})

TEST (05, cout << r - s << endl;)
TEST (06, {Quat t = r; t -= s; cout << t << endl;})

TEST (07, cout << r * s << endl;)
TEST (08, cout << s * r << endl;)
TEST (09, cout << r * 2.0 << endl;)
TEST (10, {Quat t = r; t *= s; cout << t << endl;})
TEST (11, {Quat t = r; t *= 2.0; cout << t << endl;})

TEST (12, cout << r / s << endl;)
TEST (13, cout << r / 2.0 << endl;)
TEST (14, {Quat t = r; cout << (t /= s) << endl;})
TEST (15, {Quat t = r; cout << (t /= 2.0) << endl;})

TEST (16, cout << *r << endl;)

TEST (17, cout << (r*s == s*r)  << endl;)
TEST (18, cout << (r*s != s*r)  << endl;)

TEST (19, cout << *(r*s) << endl;)

TEST (20, cout << *r * *s << endl;)
TEST (21, cout << *s * *r << endl;)

TEST (22, cout << +r << endl;)		// norm
TEST (23, cout << -r << endl;)
TEST (24, cout << ~r << endl;)
TEST (25, cout << r * ~r << endl;)

TEST (26, cout << r.qdot (s) << endl;)
TEST (27, cout << r.qdot (r) << endl;)
TEST (28, cout << r.qcross (s) << endl;)
TEST (29, cout << r.qcross (r) << endl;)
TEST (30, cout << R2D (r.qang (s)) << endl;)
TEST (31, cout << R2D (r.qang (r)) << endl;)
TEST (32, cout << r.qstr () << endl;)

TEST (33, cout << r/+r << endl;)   	// unit
TEST (34, cout << +r/+r << endl;)   	// norm of unit

TEST (35, cout << x << endl;)

TEST (36, Rotation *v = x.toRotation (); v->show ();)
TEST (37, Rotation *v = x.toRotation (); cout << v << endl;)
TEST (38, Rotation *v = x.toRotation (); Quat w = v->toQuaternion (); cout << w << endl;)

typedef void (*fcn_t)();

fcn_t fcns[] = {
  NULL,
  test01,
  test02,
  test03,
  test04,
  test05,
  test06,
  test07,
  test08,
  test09,
  test10,
  test11,
  test12,
  test13,
  test14,
  test15,
  test16,
  test17,
  test18,
  test19,
  test20,
  test21,
  test22,
  test23,
  test24,
  test25,
  test26,
  test27,
  test28,
  test29,
  test30,
  test31,
  test32,
  test33,
  test34,
  test35,
  test36,
  test37,
  test38,
};
      
int nr_opts = sizeof(fcns) / sizeof(fcn_t);
#endif
            
int
main (int ac, char *av[])
{
  int opt;
  bool do_all = false;
  while ((opt = getopt(ac, av, "an")) != -1) {
    switch(opt) {
    case 'a':
      do_all = true;
      break;
    case 'n':
      cout << nr_tests << endl;
      return 0;
      break;
    }
  }

  if (optind >= ac) do_all = true;

  //  if (optind >= ac) return 0;

  if (do_all) {
    for (int i = 1; i < nr_tests; i++) {
      fprintf (stdout, "test %2d: ", i);
      (*fcns[i])();
    }
  }
  else {
    long int wch = strtol (av[optind], nullptr, 10);
    if (wch < 1 || wch > nr_tests) return 1;

    (*fcns[wch])();
  }

  return 0;
}
