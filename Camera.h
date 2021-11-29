//
// Created by Jiang Kairong on 2/18/18.
//

#ifndef PROG03_INLINEBOOL_CAMERA_H
#define PROG03_INLINEBOOL_CAMERA_H

#include "Matrix.h"
#include "Ray.h"

class Camera {
public:
  explicit Camera();

  Camera(const Vector3d &eyePosition, const Vector3d &lookAtPoint, const Vector3d &upDirection, double verticalAngle,
         const std::pair<int, int> &imageResolution, double imageDistance = 1., double aperture = 1, Vector3d offset = {0, 0, 0});

  const Vector3d &getEyePosition() const;

  void setEyePosition(const Vector3d &eyePosition);

  const Vector3d &getLookAtDirection() const;

  void setLookAtDirection(const Vector3d &lookAtDirection);

  const Vector3d &getUpDirection() const;

  void setUpDirection(const Vector3d &upDirection);

  double getVerticalAngle() const;

  void setVerticalAngle(double verticalAngle);

  const std::pair<int, int> &getImageResolution() const;

  void setImageResolution(const std::pair<int, int> &imageResolution);

  double getImageDistance() const;

  void setImageDistance(double imageDistance);

  double getFocalLength() const;

  void setFocalLength(double focalLength);

  double getAperture() const;

  void setAperture(double aperture);

  double getFocalDistance() const;

  void setFocalDistance(double focalDistance);

  const Vector3d &getOffset() const;

  void setOffset(const Vector3d &offset);

  void setLookAtPoint(const Vector3d &lookAtPoint);

private:
  Vector3d eyePosition, lookAtDirection, upDirection;
  double verticalAngle;
  std::pair<int, int> imageResolution;
  double imageDistance, focalDistance;
  double focalLength, aperture;
  Vector3d offset;
};


#endif //PROG03_INLINEBOOL_CAMERA_H
