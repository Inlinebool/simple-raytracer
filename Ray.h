//
// Created by Jiang Kairong on 3/7/18.
//

#ifndef PROG03_INLINEBOOL_RAY_H
#define PROG03_INLINEBOOL_RAY_H

#include "Matrix.h"

class Ray {
public:

  Ray(const Vector3d &s, const Vector3d &d, bool isInside = false);

  const Vector3d &getS() const;

  void setS(const Vector3d &s);

  const Vector3d &getD() const;

  void setD(const Vector3d &d);

  Vector3d getPoint(double t);

  const Vector3d getPoint(double t) const;

  bool isIsInside() const;

  void setIsInside(bool isInside);

private:
  Vector3d s, d;
  bool isInside;
};


#endif //PROG03_INLINEBOOL_RAY_H
