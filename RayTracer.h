//
// Created by Jiang Kairong on 3/10/18.
//

#ifndef PROG03_INLINEBOOL_RAYTRACER_H
#define PROG03_INLINEBOOL_RAYTRACER_H


#include "Scene.h"
#include "Image.h"
#include <random>

class RayTracer {
public:
  explicit RayTracer(const std::string &sceneFileName, double randomMu = 0., double randomSigma = 1.,
                     int maxRecursiveDepth = 5, int sampleRate = 100, bool distributionEnabled = false);

  Image8i renderForDisplay();

  Image8i convertFloatImage2Int(Image32f image);

  int getSampleRate() const;

  void setSampleRate(int sampleRate);

  bool isDistributionEnabled() const;

  void setDistributionEnabled(bool distributionEnabled);


private:
  const ColorRGB32f shading(const Ray &ray, bool doDistribution, int depth);

  Image32f render(bool doDistribution = false);

  std::vector<Ray> prepareRays(const Camera &camera, bool doDistribution = false);

  Scene scene;
  double randomMu, randomSigma;
  int maxRecursiveDepth;
  int sampleRate;
  bool distributionEnabled;

  std::default_random_engine randomEngine;
  std::uniform_real_distribution<double> uniformRandomGenerator;
};


#endif //PROG03_INLINEBOOL_RAYTRACER_H
