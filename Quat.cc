
/*
    libquat Copyright (C) 2025 C. H. L. Moller under the terms of the
    GNU General Public License Version 3.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <string>
#include <cmath>

#include "Quat.hh"

Quat::Quat ()
{
  a = NAN;
  b = NAN;
  c = NAN;
  d = NAN;
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

Quat::Quat (double *v)
{
  a = v[0];
  b = v[1];
  c = v[2];
  d = v[3];
}

Quat::Quat (double theta, double *v)
{
  a = cos (theta/2.0);
  b = v[0];
  c = v[1];
  d = v[2];
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
Quat::operator*(Quat v)	// multiply / product
{
  Quat s;
  s.a = (a * v.a) - ((b * v.b) + (c * v.c) + (d * v.d));
  s.b = ((a * v.b) + (b * v.a) + (c * v.d)) - (d * v.c);
  s.c = ((a * v.c) + (c * v.a) + (d * v.b)) - (b * v.d);
  s.d = ((a * v.d) + (b * v.c) + (d * v.a)) - (c * v.b);
  return s;
}

Quat
Quat::operator*=(Quat &v)	// multiply-assign
{
  Quat s;
  s.a = (a * v.a) - ((b * v.b) + (c * v.c) + (d * v.d));
  s.b = ((a * v.b) + (b * v.a) + (c * v.d)) - (d * v.c);
  s.c = ((a * v.c) + (c * v.a) + (d * v.b)) - (b * v.d);
  s.d = ((a * v.d) + (b * v.c) + (d * v.a)) - (c * v.b);
  a = s.a;
  b = s.b;
  c = s.c;
  d = s.d;
  return *this;
}

Quat
Quat::operator*(const double v)	// multiply by double
{
  Quat s;
  s.a = a * v;
  s.b = b * v;
  s.c = c * v;
  s.d = d * v;
  return s;
}

Quat
Quat::operator*=(const double v)	// multiply by double assign
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
  Quat t = *this * s;
  return t;
}

Quat
Quat::operator/=(Quat &v)	// divide-assign
{
  Quat s = ~v;			// invert denominator
  Quat t = *this * s;
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

Quat
Quat::operator/=(const double v)	// multiply by double assign
{
  a = a / v;
  b = b / v;
  c = c / v;
  d = d / v;
  return *this;
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
Quat::operator~()		// reciprocal / invert
{
  Quat s;
  double m2 = (a * a) + (b * b) + (c * c) + (d * d);
  s.a =  a/m2;
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

string
Quat::qstr ()			// stringify
{
  char *s;
  asprintf (&s, "[%#08g [%#08g %#08g %#08g]]", a, b, c, d);
  string t (s);
  free (s);
  return t;
}

double *
Quat::qvec ()			// convert to array
{
  double *v = new double[4];
  v[0] = a;
  v[1] = b;
  v[2] = c;
  v[3] = d;
  return v;
}

double *
Quat::qaxis ()			// extract axis component
{
  double *v = new double[3];
  v[0] = b;
  v[1] = c;
  v[2] = d;
  return v;
}

double
Quat::qscalar ()		// extract scalar component
{
  return a;
}

ostream&
operator<<(ostream& os, const Quat &v)
{
  os << "[ " << v.a << " " << v.b << " " << v.c << " " << v.d << " ]";
    return os;
}

double
Quat::qdot (Quat &v)
{
  return (b * v.b) + (c * v.c) + (d * v.d);
}

Quat
Quat::qrot (Quat &v)
{
  Quat q =  (*this) * v * ~(*this);
  return q;
}

Quat
Quat::qcross (Quat &v)
{
  Quat s;
  s.a = 0.0;
  s.b = (c * v.d) - (d * v.c);
  s.c = (d * v.b) - (b * v.d);
  s.d = (b * v.c) - (c * v.b);
  return s;
}

double
Quat::qang (Quat &v)
{
  double dt = (a * v.a) + (b * v.b) + (c * v.c) + (d * v.d);
  return acos (dt / ((+*this) * +v));
}

Rotation *
Quat::toRotation ()
{
  Rotation *h = new Rotation;

  Quat q = *this;
  q/=+q;			//normalise;
  double q0 = q.a;
  double q02 = q0 * q0;
  
  double q1 = q.b;
  double q12 = q1 * q1;

  double q2 = q.c;
  double q22 = q2 * q2;

  double q3 = q.d;
  double q32 = q3 * q3;
  
  h->mtx[0][0] = (2.0 * (q02 + q12)) -1.0;
  h->mtx[0][1] =  2.0 * (q1 * q2  -  q0 * q3);
  h->mtx[0][2] =  2.0 * (q1 * q3  +  q0 * q2);

  h->mtx[1][0] =  2.0 * (q1 * q2  +  q0 * q3);
  h->mtx[1][1] = (2.0 * (q02 + q22)) -1.0;
  h->mtx[1][2] =  2.0 * (q1 * q3  -  q0 * q1);
  
  h->mtx[2][0] =  2.0 * (q1 * q3  -  q0 * q2);
  h->mtx[2][1] =  2.0 * (q2 * q3  +  q0 * q2);
  h->mtx[2][2] = (2.0 * (q02 + q32)) -1.0;

  return h;
}

void
Rotation::show (ostream& os, const Rotation *obj)
{
  double q00 = obj->mtx[0][0];
  double q01 = obj->mtx[0][1];
  double q02 = obj->mtx[0][2];
  double q10 = obj->mtx[1][0];
  double q11 = obj->mtx[1][1];
  double q12 = obj->mtx[1][2];
  double q20 = obj->mtx[2][0];
  double q21 = obj->mtx[2][1];
  double q22 = obj->mtx[2][2];

  os << "[[" << q00 << " " << q01 << "  " << q02 << "]  "
     <<  "[" << q10 << " " << q11 << "  " << q12 << "]  "
     <<  "[" << q20 << " " << q21 << "  " << q22 << "]]";
}

void
Rotation::show ()
{
  fprintf (stdout, "[[ %g %g %g]  ",
	   this->mtx[0][0], this->mtx[0][1], this->mtx[0][2]);
  fprintf (stdout, " [ %g %g %g]  ",
	   this->mtx[1][0], this->mtx[1][1], this->mtx[1][2]);
  fprintf (stdout, " [ %g %g %g]]\n",
	   this->mtx[2][0], this->mtx[2][1], this->mtx[2][2]);
}

#define dsign(v) (signbit (v) ? -1.0 : 1.0)
Quat
Rotation:: toQuaternion ()
{
  double q00 = this->mtx[0][0];
  double q01 = this->mtx[0][1];
  double q02 = this->mtx[0][2];
  double q10 = this->mtx[1][0];
  double q11 = this->mtx[1][1];
  double q12 = this->mtx[1][2];
  double q20 = this->mtx[2][0];
  double q21 = this->mtx[2][1];
  double q22 = this->mtx[2][2];

  double ta = 1.0 + q00 + q11 + q22;
  if (ta < 0.0 && fabs (ta) < 1.0e-10) ta = 0.0;
  double tb = 1.0 + q00 - q11 - q22;
  if (tb < 0.0 && fabs (tb) < 1.0e-10) tb = 0.0;
  double tc = 1.0 - q00 + q11 - q22;
  if (tc < 0.0 && fabs (tc) < 1.0e-10) tc = 0.0;
  double td = 1.0 - q00 - q11 + q22;
  if (td < 0.0 && fabs (td) < 1.0e-10) td = 0.0;
  double a = sqrt (ta) / 2.0;
  double b = sqrt (tb) * dsign (q21 - q12) / 2.0; //?
  double c = sqrt (tc) * dsign (q02 - q20) / 2.0;
  double d = sqrt (td) * dsign (q10 - q01) / 2.0;

  return Quat (a, b, c, d);
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
