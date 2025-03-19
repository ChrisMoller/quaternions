
#include <iostream>
#include <string>
#include <cmath>

#include "Quat.hh"

Quat::Quat ()
{
  a = 0;
  b = 0;
  c = 0;
  d = 0;
}

Quat::Quat (double ai, double bi, double ci, double di)
{
  a = ai;
  b = bi;
  c = ci;
  d = di;
}

Quat::Quat (double ai)
{
  a = ai;
  b = 0;
  c = 0;
  d = 0;
}

Quat::~Quat ()
{
}

Quat
Quat::operator+(Quat v)	// add
{
  Quat s;
  s.a = a + v.a;
  s.b = b + v.b;
  s.c = c + v.c;
  s.d = d + v.d;
  return s;
}

Quat
Quat::operator+=(Quat &v)	// add-assign
{
  Quat s;
  a += v.a;
  b += v.b;
  c += v.c;
  d += v.d;
  return *this;
}

Quat
Quat::operator-(Quat v)	// subtract
{
  Quat s;
  s.a = a - v.a;
  s.b = b - v.b;
  s.c = c - v.c;
  s.d = d - v.d;
  return s;
}

Quat
Quat::operator-=(Quat &v)	// subtract-assign
{
  Quat s;
  a -= v.a;
  b -= v.b;
  c -= v.c;
  d -= v.d;
  return *this;
}

Quat
Quat::operator*(Quat v)	// multiply
{
  Quat s;
  s.a = (a * v.a) - (b * v.b) - (c * v.c) - (d * v.d);
  s.b = (a * v.b) + (b * v.a) + (c * v.d) - (d * v.c);
  s.c = (a * v.c) - (b * v.d) + (c * v.a) + (d * v.b);
  s.d = (a * v.d) + (b * v.c) - (c * v.b) + (d * v.a);
  return s;
}

Quat
Quat::operator*=(Quat &v)	// multiply-assign
{
  Quat s;
  s.a = (a * v.a) - (b * v.b) - (c * v.c) - (d * v.d);
  s.b = (a * v.b) + (b * v.a) + (c * v.d) - (d * v.c);
  s.c = (a * v.c) - (b * v.d) + (c * v.a) + (d * v.b);
  s.d = (a * v.d) + (b * v.c) - (c * v.b) + (d * v.a);
  a = s.a;
  b = s.b;
  c = s.c;
  d = s.d;
  return *this;
}

Quat
Quat::operator*(double v)	// multiply by double
{
  Quat s;
  s.a = a * v;
  s.b = b * v;
  s.c = c * v;
  s.d = d * v;
  return s;
}

Quat
Quat::operator*=(double &v)	// multiply by double assign
{
  a = a * v;
  b = b * v;
  c = c * v;
  d = d * v;
  return *this;
}

Quat
Quat::operator/(Quat v)	// divide
{
  Quat s = ~v;			// invert denominator
  Quat t = s * *this;
  return t;
}

Quat
Quat::operator/=(Quat &v)	// divide-assign
{
  Quat s = ~v;			// invert denominator
  Quat t = s * *this;
  *this = t;
  return t;
}

Quat
Quat::operator/(double v)	// divide by double
{
  Quat s;
  s.a = a / v;
  s.b = b / v;
  s.c = c / v;
  s.d = d / v;
  return s;
}

// I'm using monadic * because quaternions have no use for
// a dereference operator
Quat
Quat::operator*()		// conjugation
{
  Quat s;
  s.a = a;
  s.b = -b;
  s.c = -c;
  s.d = -d;
  return s;
}

double
Quat::operator+()		// norm
{
  double s = sqrt ((a * a) + (b * b) + (c * c) + (d * d));
  return s;
}

Quat
Quat::operator-()		// negation
{
  Quat s;
  s.a = -a;
  s.b = -b;
  s.c = -c;
  s.d = -d;
  return s;
}

// Note that c++ doesn't support monadic / which would
// have made more sense, so I'm using monadic tilde (~)
// because quaternions have no use for a complement operator
Quat
Quat::operator~()		// reciprocal
{
  Quat s;
  double m2 = (a * a) + (b * b) + (c * c) + (d * d);
  s.a = a/m2;
  s.b = -b/m2;
  s.c = -c/m2;
  s.d = -d/m2;
  return s;
}

bool
Quat::operator==(Quat v)	// eq
{
  bool s = (a == v.a) && (b == v.b) && (c == v.c) && (d == v.d);
  return s;
}

bool
Quat::operator!=(Quat v)	// neq
{
  bool s = (a != v.a) || (b != v.b) || (c != v.c) || (d != v.d);
  return s;
}

double
Quat::qdot (Quat &a, Quat &b)
{
  return (a.b * b.a) + (a.c * b.c) + (a.d * b.d);
}

Quat
Quat::qcross (Quat &a, Quat &b)
{
  Quat s;
  s.a = 0.0;
  s.b = (a.c * b.d) - (a.d * b.c);
  s.c = (a.d * b.b) - (a.b * b.d);
  s.d = (a.b * b.c) - (a.c * b.b);
  return s;
}

ostream& operator<<(ostream& os, const Quat &v)
{
  os << "[ " << v.a << " " << v.b << " " << v.c << " " << v.d << " ]";
    return os;
}

void
Quat::show ()
{
  fprintf (stdout, "[ %g %g %g %g ]\n",
	   this->a,
	   this->b,
	   this->c,
	   this->d);
}

void
Quat::show (string l)
{
  fprintf (stdout, "%s = [ %g %g %g %g ]\n",
	   l.c_str (),
	   this->a,
	   this->b,
	   this->c,
	   this->d);
}
