#ifndef ICOSAHEDRON_H
#define ICOSAHEDRON_H
#include "Quat.hh"
vector<Quat> icosahedron = {
  Quat (0.0, 0, 1, 0.404508),
  Quat (0.0, 0, -1, 0.404508),
  Quat (0.0, 0, 1, -0.404508),
  Quat (0.0, 0, -1, -0.404508),
  Quat (0.0, 1, 0.404508, 0),
  Quat (0.0, -1, 0.404508, 0),
  Quat (0.0, 1, -0.404508, 0),
  Quat (0.0, -1, -0.404508, 0),
  Quat (0.0, 0.404508, 0, 1),
  Quat (0.0, -0.404508, 0, 1),
  Quat (0.0, 0.404508, 0, -1),
  Quat (0.0, -0.404508, 0, -1),
};
#endif // ICOSAHEDRON_H
