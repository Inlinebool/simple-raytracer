//
// Created by Jiang Kairong on 3/10/18.
//

#ifndef PROG03_INLINEBOOL_LIGHTSOURCE_H
#define PROG03_INLINEBOOL_LIGHTSOURCE_H


#include "Color.h"

class LightSource {
public:
  LightSource(const Vector3d &position, const ColorRGB32f &intensity,
              const Vector3d &directionA = Vector3d({0., 0., 0.}), const Vector3d &directionB = Vector3d({0., 0., 0.}));

  const Vector3d &getPosition() const;

  void setPosition(const Vector3d &position);

  const ColorRGB32f &getIntensity() const;

  void setIntensity(const ColorRGB32f &intensity);

  const Vector3d &getDirectionA() const;

  void setDirectionA(const Vector3d &directionA);

  const Vector3d &getDirectionB() const;

  void setDirectionB(const Vector3d &directionB);

private:
  Vector3d position;
  ColorRGB32f intensity;
  Vector3d directionA, directionB;
};


#endif //PROG03_INLINEBOOL_LIGHTSOURCE_H
