//
// Created by Jiang Kairong on 3/10/18.
//

#include "Plane.h"

Plane::Plane(const Vector3d &point, const Vector3d &normal, const ColorRGB32f &colorAmbient, const ColorRGB32f &colorDiffuse,
             const ColorRGB32f &colorSpecular, double phongExponent) : Surface(colorAmbient, colorDiffuse, colorSpecular,
                                                                            phongExponent), point(point),
                                                                    normal(normal.normalize()) {
}

bool Plane::intersect(const Ray &ray, IntersectionInfo &info){
  if (ray.getD().dot(normal) == 0.) {
    return false;
  }
  Vector3d k = ray.getS() - point;
  double t = -k.dot(normal) / ray.getD().dot(normal);
  if (t < 0) {
    return false;
  }
  if (updateIntersectInfo(info, ray, t)) {
    info.hitNormal = normal.normalize();
  }
  return true;
}
