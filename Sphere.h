//
// Created by Jiang Kairong on 3/10/18.
//

#ifndef PROG03_INLINEBOOL_SPHERE_H
#define PROG03_INLINEBOOL_SPHERE_H


#include "Matrix.h"
#include "Surface.h"

class Sphere: public Surface {
public:
  Sphere(const Vector3d &centerPosition, double radius, const ColorRGB32f &colorAmbient, const ColorRGB32f &colorDiffuse,
         const ColorRGB32f &colorSpecular, double phongExponent);

  virtual bool intersect(const Ray& ray, IntersectionInfo& info);

private:
  Vector3d centerPosition;
  double radius;
};


#endif //PROG03_INLINEBOOL_SPHERE_H
