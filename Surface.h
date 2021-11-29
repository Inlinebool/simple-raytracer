//
// Created by Jiang Kairong on 3/7/18.
//

#ifndef PROG03_INLINEBOOL_SURFACE_H
#define PROG03_INLINEBOOL_SURFACE_H


#include "Matrix.h"
#include "Ray.h"
#include "Color.h"

struct IntersectionInfo;

class Surface {
public:
  const ColorRGB32f &getColorAmbient() const;

  void setColorAmbient(const ColorRGB32f &colorAmbient);

  const ColorRGB32f &getColorDiffuse() const;

  void setColorDiffuse(const ColorRGB32f &colorDiffuse);

  const ColorRGB32f &getColorSpecular() const;

  void setColorSpecular(const ColorRGB32f &colorSpecular);

  double getPhongExponent() const;

  void setPhongExponent(double phongExponent);

  Surface(const ColorRGB32f &colorAmbient, const ColorRGB32f &colorDiffuse, const ColorRGB32f &colorSpecular,
          double phongExponent);

  virtual bool intersect(const Ray& ray, IntersectionInfo& info) = 0;

  bool updateIntersectInfo(IntersectionInfo& info, const Ray& ray, double t);

protected:
  ColorRGB32f colorAmbient, colorDiffuse, colorSpecular;
  double phongExponent;
};

struct IntersectionInfo {
  Surface* hitObject = nullptr;
  Vector3d hitPoint = Vector3d();
  Vector3d hitNormal = Vector3d();
};


#endif //PROG03_INLINEBOOL_SURFACE_H
