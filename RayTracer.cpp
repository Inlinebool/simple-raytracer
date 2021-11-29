//
// Created by Jiang Kairong on 3/10/18.
//

#include <cassert>
#include "RayTracer.h"
#include <iostream>

RayTracer::RayTracer(const std::string &sceneFileName, double randomMu, double randomSigma, int maxRecursiveDepth,
                     int sampleRate, bool distributionEnabled)
  : scene(sceneFileName),
    randomMu(randomMu),
    randomSigma(randomSigma), maxRecursiveDepth(maxRecursiveDepth), distributionEnabled(distributionEnabled),
    sampleRate(sampleRate) {
  std::random_device r;
  randomEngine = std::default_random_engine(r());
  uniformRandomGenerator = std::uniform_real_distribution<double>(0.0, 1.0);
}

Image8i RayTracer::renderForDisplay() {
  if (!distributionEnabled) {
    std::cout << "doing simple ray tracing." << std::endl;
    return convertFloatImage2Int(render(distributionEnabled));
  } else {
    std::cout << "doing distribution ray tracing." << std::endl;
    std::cout << "running sample 1 / " << sampleRate << std::endl;
    Image32f result = render(distributionEnabled);
    for (int i = 0; i < sampleRate - 1; i++) {
      std::cout << "running sample " << i + 2 << " / " << sampleRate << std::endl;
      result += render(distributionEnabled);
    }
    return convertFloatImage2Int(result / sampleRate);
  }
}

Image8i RayTracer::convertFloatImage2Int(Image32f image) {
  Image8i result;
  result.resize(image.rows(), image.cols());
  for (int i = 0; i < result.rows(); i++) {
    for (int j = 0; j < result.cols(); j++) {
      Vector3f scaledPixel = image(i, j) * 255.f;
      for (int k = 0; k < 3; k++) {
        scaledPixel(k) = std::min(255.f, scaledPixel(k));
        scaledPixel(k) = std::max(0.f, scaledPixel(k));
      }
      result(i, j) = ColorRGB8i({static_cast<unsigned char>(scaledPixel(0)), static_cast<unsigned char>(scaledPixel(1)),
                                 static_cast<unsigned char>(scaledPixel(2))});
    }
  }
  return result;
}

Image32f RayTracer::render(bool doDistribution) {
  Camera camera = scene.getMainCamera();
  int imageWidth = camera.getImageResolution().first;
  int imageHeight = camera.getImageResolution().second;
  Image32f result;
  result.resize(static_cast<unsigned long>(imageHeight), static_cast<unsigned long>(imageWidth));
  std::vector<Ray> rays = prepareRays(camera, doDistribution);
  for (int i = 0; i < result.rows(); i++) {
    for (int j = 0; j < result.cols(); j++) {
      result(i, j) = shading(rays[i * result.cols() + j], doDistribution, 0);
    }
  }
  return result;
}

const ColorRGB32f RayTracer::shading(const Ray &ray, bool doDistribution, int depth) {
  if (depth > maxRecursiveDepth) {
    return ColorRGB32f({0.f, 0.f, 0.f});
  }
  IntersectionInfo info;
  for (auto *object: scene.getObjects()) {
    object->intersect(ray, info);
  }
  if (info.hitObject == nullptr) {
    return ColorRGB32f({0.f, 0.f, 0.f});
  } else {
    ColorRGB32f result({0.f, 0.f, 0.f});
    for (auto &lightSource : scene.getLightSources()) {
      if (!distributionEnabled) {
        result += info.hitObject->getColorAmbient().cwiseProduct(lightSource.getIntensity());
      }
      Vector3d realLightPosition = lightSource.getPosition();
      if (doDistribution) {
        Vector3d aOffset = lightSource.getDirectionA() * uniformRandomGenerator(randomEngine);
        Vector3d bOffset = lightSource.getDirectionB() * uniformRandomGenerator(randomEngine);
        realLightPosition += aOffset + bOffset;
      }
      Vector3d lightDirection = (realLightPosition - info.hitPoint).normalize();
      Ray lightRay(info.hitPoint + lightDirection * 0.001, lightDirection);
      IntersectionInfo lightRayInfo;
      for (auto *object: scene.getObjects()) {
        object->intersect(lightRay, lightRayInfo);
      }
      if (lightRayInfo.hitObject != nullptr &&
          ((lightRayInfo.hitPoint - info.hitPoint).norm() < (lightSource.getPosition() - info.hitPoint).norm())) {
        continue;
      }
      double diffuseAngle = info.hitNormal.dot(lightDirection);
      if (diffuseAngle > 0) {
        result += info.hitObject->getColorDiffuse().cwiseProduct(lightSource.getIntensity()) * diffuseAngle;
      }
      if (!distributionEnabled) {
        Vector3d h = (lightDirection - ray.getD()).normalize();
        double specularAngle = info.hitNormal.dot(h);
        if (specularAngle > 0) {
          ColorRGB32f diffuseComponent = info.hitObject->getColorSpecular().cwiseProduct(lightSource.getIntensity()) *
                                         std::pow(specularAngle, info.hitObject->getPhongExponent());
          result += diffuseComponent;
        }
      }
    }
    if (distributionEnabled) {
      double R = -1.;
      double nt = info.hitObject->getPhongExponent();
      double reflectionAngle = -info.hitNormal.dot(ray.getD());
      if (!nt) {
        return result;
      } else {
        double R0 = ((nt - 1) / (nt + 1)) * ((nt - 1) / (nt + 1));
        R = R0 + (1 - R0) * std::pow(1 - reflectionAngle, 5);
      }
      Vector3d reflectionDirection = (ray.getD() - info.hitNormal * ray.getD().dot(info.hitNormal) * 2.).normalize();
      double coin = uniformRandomGenerator(randomEngine);
      if (coin > R) {
        if (!ray.isIsInside()) {
          reflectionDirection = (ray.getD() - info.hitNormal * (ray.getD().dot(info.hitNormal))) * nt -
                                info.hitNormal *
                                std::sqrt(1 - (1 - std::pow(ray.getD().dot(info.hitNormal), 2.)) / (nt * nt));
        } else {
          reflectionDirection = (ray.getD() - info.hitNormal * (ray.getD().dot(info.hitNormal))) / nt -
                                info.hitNormal *
                                std::sqrt(1 - (1 - std::pow(ray.getD().dot(info.hitNormal), 2.)) * (nt * nt));
        }
      }
      if (doDistribution) {
        std::normal_distribution<double> normalRandomGenerator(0, info.hitObject->getColorAmbient()(0));
        double xOffset = normalRandomGenerator(randomEngine);
        double yOffset = normalRandomGenerator(randomEngine);
        double zOffset = normalRandomGenerator(randomEngine);
        reflectionDirection += Vector3d({xOffset, yOffset, zOffset});
        reflectionDirection.normalize();
      }
      Ray reflectionRay(info.hitPoint + reflectionDirection * 0.001, reflectionDirection);
      return result + shading(reflectionRay, doDistribution, depth + 1).cwiseProduct(info.hitObject->getColorSpecular());
    }
    return result;
  }
}

std::vector<Ray> RayTracer::prepareRays(const Camera &camera, bool doDistribution) {
  std::vector<Ray> rays;
  auto &imageResolution = camera.getImageResolution();
  Vector3d centerPosition = camera.getEyePosition() + camera.getLookAtDirection() * camera.getFocalDistance();
  double height = 2. * std::tan(camera.getVerticalAngle() * M_PI / 360.) * camera.getFocalDistance();
  double width = height * imageResolution.first / imageResolution.second;

  Vector3d v = camera.getLookAtDirection().cross(camera.getUpDirection()).normalize();
  Vector3d u = v.cross(camera.getLookAtDirection()).normalize();

  Vector3d realEyePosition = camera.getEyePosition();
  if (doDistribution) {
    double lensRadius = camera.getFocalLength() / camera.getAperture() * 0.5;
    double uNoise = uniformRandomGenerator(randomEngine) * lensRadius;
    double vNoise = uniformRandomGenerator(randomEngine) * lensRadius;
    realEyePosition += u * uNoise + v * vNoise;
  }

  for (int i = 0; i < imageResolution.second; i++) {
    for (int j = 0; j < imageResolution.first; j++) {
      double uOffset = 0.5 * height - i * height / imageResolution.second;
      double vOffset = j * width / imageResolution.first - 0.5 * width;
      if (doDistribution) {
        double pixelSize = height / camera.getImageResolution().second;
        uOffset += (uniformRandomGenerator(randomEngine) - 0.5) * pixelSize;
        vOffset += (uniformRandomGenerator(randomEngine) - 0.5) * pixelSize;
      }
      Vector3d pointPosition = centerPosition + u * uOffset + v * vOffset;
      rays.emplace_back(realEyePosition, (pointPosition - realEyePosition).normalize());
    }
  }

  return rays;
}

int RayTracer::getSampleRate() const {
  return sampleRate;
}

void RayTracer::setSampleRate(int sampleRate) {
  RayTracer::sampleRate = sampleRate;
}

bool RayTracer::isDistributionEnabled() const {
  return distributionEnabled;
}

void RayTracer::setDistributionEnabled(bool distributionEnabled) {
  RayTracer::distributionEnabled = distributionEnabled;
}
