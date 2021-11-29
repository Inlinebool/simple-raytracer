//
// Created by Jiang Kairong on 2/18/18.
//

#include "Camera.h"

Camera::Camera(const Vector3d &eyePosition, const Vector3d &lookAtPoint, const Vector3d &upDirection,
               double verticalAngle, const std::pair<int, int> &imageResolution, double imageDistance,
               double aperture, Vector3d offset) : eyePosition(eyePosition), lookAtDirection((lookAtPoint - eyePosition).normalize()),
                                  upDirection(upDirection), verticalAngle(verticalAngle),
                                  imageResolution(imageResolution), focalDistance((lookAtPoint - eyePosition).norm()),
                                  imageDistance(imageDistance), aperture(aperture), offset(offset) {
  focalLength = focalDistance * imageDistance / focalDistance + imageDistance;
}

Camera::Camera()
  : eyePosition({0, 0, 0}), lookAtDirection({0, 1, 0}), upDirection({0, 0, 1}), verticalAngle(60.),
    imageResolution(std::pair<int, int>({400, 400})), imageDistance(1.), focalLength(1), aperture(2.8) {
}

const Vector3d &Camera::getEyePosition() const {
  return eyePosition;
}

void Camera::setEyePosition(const Vector3d &eyePosition) {
  Camera::eyePosition = eyePosition;
}

const Vector3d &Camera::getLookAtDirection() const {
  return lookAtDirection;
}

void Camera::setLookAtDirection(const Vector3d &lookAtDirection) {
  Camera::lookAtDirection = lookAtDirection;
}

const Vector3d &Camera::getUpDirection() const {
  return upDirection;
}

void Camera::setUpDirection(const Vector3d &upDirection) {
  Camera::upDirection = upDirection;
}

double Camera::getVerticalAngle() const {
  return verticalAngle;
}

void Camera::setVerticalAngle(double verticalAngle) {
  Camera::verticalAngle = verticalAngle;
}

const std::pair<int, int> &Camera::getImageResolution() const {
  return imageResolution;
}

void Camera::setImageResolution(const std::pair<int, int> &imageResolution) {
  Camera::imageResolution = imageResolution;
}

double Camera::getImageDistance() const {
  return imageDistance;
}

void Camera::setImageDistance(double imageDistance) {
  Camera::imageDistance = imageDistance;
}

double Camera::getFocalLength() const {
  return focalLength;
}

void Camera::setFocalLength(double focalLength) {
  Camera::focalLength = focalLength;
}

double Camera::getAperture() const {
  return aperture;
}

void Camera::setAperture(double aperture) {
  Camera::aperture = aperture;
}

void Camera::setLookAtPoint(const Vector3d &lookAtPoint) {
  lookAtDirection = (lookAtPoint - eyePosition).normalize();
  focalDistance = (lookAtPoint - eyePosition).norm();
  focalLength = focalDistance * imageDistance / focalDistance + imageDistance;
}

double Camera::getFocalDistance() const {
  return focalDistance;
}

void Camera::setFocalDistance(double focalDistance) {
  Camera::focalDistance = focalDistance;
  focalLength = focalDistance * imageDistance / focalDistance + imageDistance;
}

const Vector3d &Camera::getOffset() const {
  return offset;
}

void Camera::setOffset(const Vector3d &offset) {
  Camera::offset = offset;
}
