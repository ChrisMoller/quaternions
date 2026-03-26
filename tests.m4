dnl generator for quat tests
define(`RQ',`changequote(<,>)dnl`
'changequote`'')
dnl start at 1000 just so we don't have to with a null pointer
define(`offset', 0001)dnl
define(`cnt',    offset)dnl
define(`xinc', `define(`$1',incr($1))')dnl
define(`upcase', `translit($1, `a-z', `A-Z')')dnl
define(`entry', `void `test_'cnt () {cout << $1 << ": "; $2}dnl
divert(1)  `test_'cnt xinc(`cnt') `,'
divert(0)'dnl
)dnl

`/********* DON'RQ()`T MODIFY THIS FILE! ********/'
`/**** Make all changes in tests.m4. ****/'

#ifndef TESTS_H
#define TESTS_H

entry("     r",cout << r << endl;)
entry("     s",cout << s << endl;)

entry("   r+s",cout << r + s << endl;)
entry("  t+=s",{Quat t = r; t += s; cout << t << endl;})

entry("   r-s",cout << r - s << endl;)
entry("  t-=s",{Quat t = r; t -= s; cout << t << endl;})

entry("   r*s",cout << r * s << endl;)
entry("   s*r",cout << s * r << endl;)
entry("   r*2",cout << r * 2.0 << endl;)
entry("  t*=s",{Quat t = r; t *= s; cout << t << endl;})
entry("  t*=2",{Quat t = r; t *= 2.0; cout << t << endl;})

entry("   r/s",cout << r / s << endl;)
entry("   r/2",cout << r / 2.0 << endl;)
entry("  t/=s",{Quat t = r; cout << (t /= s) << endl;})
entry("  t/=2",{Quat t = r; cout << (t /= 2.0) << endl;})

entry("    *r",cout << *r << endl;)

entry("    ==",cout << (r*s == s*r)  << endl;)
entry("    !=",cout << (r*s != s*r)  << endl;)

entry("*(r*s)",cout << *(r*s) << endl;)

entry(" *r**s",cout << *r * *s << endl;)
entry(" *s**r",cout << *s * *r << endl;)

entry("    +r",cout << +r << endl;)          // norm
entry("    -r",cout << -r << endl;)
entry("  r*-r",cout << r * ~r << endl;)

entry("   r.s",cout << r.qdot (s) << endl;)
entry("   r.r",cout << r.qdot (r) << endl;)
entry(" cross",cout << r.qcross (s) << endl;)
entry(" cross",cout << r.qcross (r) << endl;)
entry("   ang",cout << R2D (r.qang (s)) << endl;)
entry("   ang",cout << R2D (r.qang (r)) << endl;)
entry("string",cout << r.qstr () << endl;)

entry("  r/+r",cout << r/+r << endl;)        // unit
entry(" +r/+r",cout << +r/+r << endl;)       // norm of unit

entry("     x",cout << x << endl;)

entry("x to r",Rotation *v = x.toRotation (); v->show ();)
entry("x to r",Rotation *v = x.toRotation (); cout << v << endl;)
entry("unrot",Rotation *v = d.toRotation ();
      Quat w = v->toQuaternion ();
      cout << d << " " << w << " " << (d/w).round(1e-9) << endl;)
entry("unrot",Rotation *v = d.toRotation ();
      Quat w = v->toQuaternion ();
      cout << d << " " << w << " " << (d/w).round() << endl;)
entry("  exp",cout << u << " " << u.qexp() << endl;)

entry("   ln",cout << u << " " << u.qln() << endl;)
entry("   ln",cout << r << " " << r.qln() << endl;)
entry(" unln",cout << r << " " << (r.qln()).qexp() << endl;)
entry(" qpow",cout << r << " " << r.qpow(1.0) << endl;)
entry(" qpow",cout << r << " " << r * r << " " << r.qpow(2.0) << endl;)
entry("uqpow",cout << r << " " << r * r << " " << (r.qpow(2.0)).qpow(.5) << endl;)
entry(" qpow",cout << r << " " << r.qpow(3.5) << endl;)
entry(" qpow",cout << u << " " << u.qpow(3) << endl;)

typedef void (*fcn_t)();

fcn_t fcns[] {
  NULL,
undivert
`};

int nr_tests =' eval(1 + cnt - offset)`;'

#endif /* TESTS_H*/

