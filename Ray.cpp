//
// Created by Jiang Kairong on 3/7/18.
//

#include "Ray.h"

Ray::Ray(const Vector3d &s, const Vector3d &d, bool isInside) : s(s), d(d.normalize()), isInside(isInside) {}

Vector3d Ray::getPoint(double t) {
  return s + d.normalize() * t;
}

const Vector3d &Ray::getS() const {
  return s;
}

void Ray::setS(const Vector3d &s) {
  Ray::s = s;
}

const Vector3d &Ray::getD() const{
  return d;
}

void Ray::setD(const Vector3d &d) {
  Ray::d = d.normalize();
}

const Vector3d Ray::getPoint(double t) const {
  return s + d.normalize() * t;
}

bool Ray::isIsInside() const {
  return isInside;
}

void Ray::setIsInside(bool isInside) {
  Ray::isInside = isInside;
}
