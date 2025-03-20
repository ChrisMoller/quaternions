
#pragma once
#include <string>
#include <iostream>

#include <stdio.h>

using namespace std;

class Quat
{
public:
  Quat ();
  Quat (double ai, double bi, double ci, double di);
  Quat (double ai);
  ~Quat ();
  
  Quat 		operator+(Quat v);	// add
  Quat 		operator+=(Quat &v);	// add-assign

  Quat 		operator-(Quat v);	// subtract
  Quat 		operator-=(Quat &v);	// subtract-assign

  Quat 		operator*(Quat v);	// multiply
  Quat 		operator*=(Quat &v);	// multiply-assign
  Quat 		operator*(double v);	// multiply by double
  Quat 		operator*=(double &v);	// multiply by double assign

  Quat 		operator/(Quat v);	// divide
  Quat 		operator/=(Quat &v);	// divide-assign
  Quat 		operator/(double v);	// divide by double

  // I'm using monadic * because quaternions have no use for
  // a dereference operator
  Quat		operator*();		// conjugation

  double	operator+();		// norm

  Quat		operator-();		// negation

  // Note that c++ doesn't support monadic / which would have made more sense,
  // so I'm using monadic tilde (~) because quaternions have no use for a
  // complement operator
  Quat		operator~();		// reciprocal

  bool		operator==(Quat v);	// eq

  bool		operator!=(Quat v);	// neq

  static double	qdot (Quat &a, Quat &b);
  static Quat	qcross (Quat &a, Quat &b);
  static double	qang (Quat &a, Quat &b);

  friend ostream& operator<<(ostream& os, const Quat &v);
  void show ();
  void show (string l);
private:
  double a;
  double b;
  double c;
  double d;
};
