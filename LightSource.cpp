//
// Created by Jiang Kairong on 3/10/18.
//

#include "LightSource.h"

LightSource::LightSource(const Vector3d &position, const ColorRGB32f &intensity,
                         const Vector3d &directionA, const Vector3d &directionB) : position(position),
                                                                                   intensity(intensity),
                                                                                   directionA(directionA),
                                                                                   directionB(directionB) {}

const Vector3d &LightSource::getPosition() const {
  return position;
}

void LightSource::setPosition(const Vector3d &position) {
  LightSource::position = position;
}

const ColorRGB32f &LightSource::getIntensity() const {
  return intensity;
}

void LightSource::setIntensity(const ColorRGB32f &intensity) {
  LightSource::intensity = intensity;
}

const Vector3d &LightSource::getDirectionA() const {
  return directionA;
}

void LightSource::setDirectionA(const Vector3d &directionA) {
  LightSource::directionA = directionA;
}

const Vector3d &LightSource::getDirectionB() const {
  return directionB;
}

void LightSource::setDirectionB(const Vector3d &directionB) {
  LightSource::directionB = directionB;
}
