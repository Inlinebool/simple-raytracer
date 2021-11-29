//
// Created by Jiang Kairong on 3/10/18.
//

#include <fstream>
#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"

Scene::Scene(const std::string &sceneFileName) : objects(), mainCamera(), lightSources() {
  std::ifstream ifs;
  ifs.open(sceneFileName.data(), std::ifstream::in);
  std::string token;
  ifs >> token;
  while (ifs.good()) {
    if (token == "e") {
      double x, y, z;
      ifs >> x >> y >> z;
      mainCamera.setEyePosition(Vector3d({x, y, z}));
    } else if (token == "l") {
      double x, y, z;
      ifs >> x >> y >> z;
      mainCamera.setLookAtPoint(Vector3d({x, y, z}));
    } else if (token == "u") {
      double x, y, z;
      ifs >> x >> y >> z;
      mainCamera.setUpDirection(Vector3d({x, y, z}));
    } else if (token == "f") {
      double angle;
      ifs >> angle;
      mainCamera.setVerticalAngle(angle);
    } else if (token == "i") {
      int width, height;
      ifs >> width >> height;
      mainCamera.setImageResolution(std::pair<int, int>({width, height}));
    } else if (token == "L") {
      double x, y, z;
      ifs >> x >> y >> z;
      Vector3d position({x, y, z});
      float r, g, b;
      ifs >> r >> g >> b;
      ColorRGB32f intensity({r, g, b});
      lightSources.emplace_back(position, intensity);
    } else if (token == "A") {
      double x, y, z;
      ifs >> x >> y >> z;
      Vector3d position({x, y, z});
      ifs >> x >> y >> z;
      Vector3d da({x, y, z});
      ifs >> x >> y >> z;
      Vector3d db({x, y, z});
      float r, g, b;
      ifs >> r >> g >> b;
      ColorRGB32f intensity({r, g, b});
      lightSources.emplace_back(position, intensity, da, db);
    } else if (token == "S") {
      double x, y, z;
      ifs >> x >> y >> z;
      double radius;
      ifs >> radius;
      float r, g, b;
      ifs >> r >> g >> b;
      ColorRGB32f colorAmbient({r, g, b});
      ifs >> r >> g >> b;
      ColorRGB32f colorDiffuse({r, g, b});
      ifs >> r >> g >> b;
      ColorRGB32f colorSpecular({r, g, b});
      double phongExponent;
      ifs >> phongExponent;
      objects.push_back(new Sphere(Vector3d({x, y, z}), radius, colorAmbient, colorDiffuse, colorSpecular, phongExponent));
    } else if (token == "P") {
      double x, y, z;
      ifs >> x >> y >> z;
      Vector3d point({x, y, z});
      ifs >> x >> y >> z;
      Vector3d normal({x, y, z});
      float r, g, b;
      ifs >> r >> g >> b;
      ColorRGB32f colorAmbient({r, g, b});
      ifs >> r >> g >> b;
      ColorRGB32f colorDiffuse({r, g, b});
      ifs >> r >> g >> b;
      ColorRGB32f colorSpecular({r, g, b});
      double phongExponent;
      ifs >> phongExponent;
      objects.push_back(new Plane(point, normal, colorAmbient, colorDiffuse, colorSpecular, phongExponent));
    }
    ifs >> token;
  }
}

const std::vector<Surface*> &Scene::getObjects() const {
  return objects;
}

void Scene::setObjects(const std::vector<Surface*> &objects) {
  Scene::objects = objects;
}

const Camera &Scene::getMainCamera() const {
  return mainCamera;
}

void Scene::setMainCamera(const Camera &mainCamera) {
  Scene::mainCamera = mainCamera;
}

const std::vector<LightSource> &Scene::getLightSources() const {
  return lightSources;
}

void Scene::setLightSources(const std::vector<LightSource> &lightSources) {
  Scene::lightSources = lightSources;
}
