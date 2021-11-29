//
// Created by Jiang Kairong on 3/7/18.
//

#include "Surface.h"

Surface::Surface(const ColorRGB32f &colorAmbient, const ColorRGB32f &colorDiffuse, const ColorRGB32f &colorSpecular,
                 double phongExponent) : colorAmbient(colorAmbient), colorDiffuse(colorDiffuse),
                                         colorSpecular(colorSpecular), phongExponent(phongExponent) {}

const ColorRGB32f &Surface::getColorAmbient() const {
  return colorAmbient;
}

void Surface::setColorAmbient(const ColorRGB32f &colorAmbient) {
  Surface::colorAmbient = colorAmbient;
}

const ColorRGB32f &Surface::getColorDiffuse() const {
  return colorDiffuse;
}

void Surface::setColorDiffuse(const ColorRGB32f &colorDiffuse) {
  Surface::colorDiffuse = colorDiffuse;
}

const ColorRGB32f &Surface::getColorSpecular() const {
  return colorSpecular;
}

void Surface::setColorSpecular(const ColorRGB32f &colorSpecular) {
  Surface::colorSpecular = colorSpecular;
}

double Surface::getPhongExponent() const {
  return phongExponent;
}

void Surface::setPhongExponent(double phongExponent) {
  Surface::phongExponent = phongExponent;
}

bool Surface::updateIntersectInfo(IntersectionInfo &info, const Ray &ray, double t) {
  auto hitPoint = ray.getPoint(t);
  if (info.hitObject == nullptr || (info.hitObject != nullptr && ((hitPoint - ray.getS()).norm() < (info.hitPoint - ray.getS()).norm()))) {
    info.hitObject = this;
    info.hitPoint = hitPoint;
    return true;
  }
  return false;
}
