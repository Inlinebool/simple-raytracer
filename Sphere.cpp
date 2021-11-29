//
// Created by Jiang Kairong on 3/10/18.
//

#include "Sphere.h"

Sphere::Sphere(const Vector3d &centerPosition, double radius, const ColorRGB32f &colorAmbient,
               const ColorRGB32f &colorDiffuse, const ColorRGB32f &colorSpecular, double phongExponent) : Surface(
  colorAmbient, colorDiffuse, colorSpecular, phongExponent), centerPosition(
  centerPosition), radius(radius) {
}

bool Sphere::intersect(const Ray &ray, IntersectionInfo &info) {
  Vector3d k = ray.getS() - centerPosition;
  double b = ray.getD().dot(k);
  double c = k.dot(k) - radius * radius;
  double delta = b * b - c;
  if (delta < 0.) {
    return false;
  } else {
    double t = -b - std::sqrt(delta);
    if (t < 0.) {
      t = -b + std::sqrt(delta);
    }
    if (t < 0.) {
      return false;
    }
    if (updateIntersectInfo(info, ray, t)) {
      info.hitNormal = (info.hitPoint - centerPosition).normalize();
    }
    return true;
  }
}
