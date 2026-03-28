#ifndef CUBEVERTS_H
#define CUBEVERTS_H

#include <vector>
#include "Quat.hh"

vector<Quat> cube = {
  Quat (0, -0.4,  0.4, -0.4),	// left  lower rear
  Quat (0,  0.4,  0.4, -0.4),	// right lower rear
  Quat (0,  0.4, -0.4, -0.4),	// right upper rear
  Quat (0, -0.4, -0.4, -0.4),	// left  upper rear
  Quat (0, -0.4,  0.4,  0.4),    // left  lower front
  Quat (0,  0.4,  0.4,  0.4),    // right lower front
  Quat (0,  0.4, -0.4,  0.4),    // right upper front
  Quat (0, -0.4, -0.4,  0.4)     // left  upper front
};
#endif // CUBEVERTS_H
