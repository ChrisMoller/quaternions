#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <libquat/Quat.hh>

using namespace std;

#define D2R(d) (M_PI * (d)/180.0)
#define R2D(r) (180.0 * (r)/M_PI)


Quat r (1, 2, 3, 4);
Quat s (2, 3, 4, 5);

#define TEST(n,f) void test##n () {f}

TEST (01, cout << r << endl;)
TEST (02, cout << s << endl;)
TEST (03, cout << r + s << endl;)
TEST (04, {Quat t = r; cout << (t += s) << endl;})
TEST (05, {Quat t = r; cout << (t -= s) << endl;})
TEST (06, cout << r * s << endl;)
TEST (07, cout << s * r << endl;)
TEST (08, cout << (r*s == s*r)  << endl;)
TEST (09, cout << (r*s != s*r)  << endl;)
TEST (10, cout << r/s << endl;)
TEST (11, cout << *(r*s) << endl;)
TEST (12, cout << *r * *s << endl;)
TEST (13, cout << *s * *r << endl;)
TEST (14, cout << +r << endl;)
TEST (15, cout << -r << endl;)
TEST (16, cout << ~r << endl;)
TEST (17, cout << r * ~r << endl;)
TEST (18, cout <<  r * 7 << endl;)
TEST (19, cout <<  r / 7 << endl;)
TEST (20, {Quat x = r; cout << (x *= s) << endl;})
TEST (21, {Quat x = r; cout << (x /= s) << endl;})
TEST (22, cout << r.qdot (s) << endl;)
TEST (23, cout << r.qdot (r) << endl;)
TEST (24, cout << r.qcross (s) << endl;)
TEST (25, cout << r.qcross (r) << endl;)
TEST (26, cout << R2D (r.qang (s)) << endl;)
TEST (27, cout << R2D (r.qang (r)) << endl;)
TEST (28, cout << r.qstr () << endl;)

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
  test28
};
      
int nr_opts = sizeof(fcns) / sizeof(fcn_t);
            
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
      cout << nr_opts << endl;
      return 0;
      break;
    }
  }

  if (optind >= ac) do_all = true;

  //  if (optind >= ac) return 0;

  if (do_all) {
    for (int i = 1; i < nr_opts; i++) {
      fprintf (stdout, "test %d\n", i);
      (*fcns[i])();
    }
  }
  else {
    long int wch = strtol (av[optind], nullptr, 10);
    if (wch < 1 || wch > nr_opts) return 1;

    (*fcns[wch])();
  }

  return 0;
}
