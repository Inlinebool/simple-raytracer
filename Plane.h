//
// Created by Jiang Kairong on 3/10/18.
//

#ifndef PROG03_INLINEBOOL_PLANE_H
#define PROG03_INLINEBOOL_PLANE_H


#include "Surface.h"
#include "Matrix.h"

class Plane : public Surface {
public:
  Plane(const Vector3d &point, const Vector3d &normal, const ColorRGB32f &colorAmbient, const ColorRGB32f &colorDiffuse,
        const ColorRGB32f &colorSpecular, double phongExponent);

  virtual bool intersect(const Ray& ray, IntersectionInfo& info);

private:
  Vector3d point, normal;
};


#endif //PROG03_INLINEBOOL_PLANE_H
