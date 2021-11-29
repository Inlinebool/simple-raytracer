//
// Created by Jiang Kairong on 3/10/18.
//

#ifndef PROG03_INLINEBOOL_SCENE_H
#define PROG03_INLINEBOOL_SCENE_H


#include <vector>
#include "Surface.h"
#include "Camera.h"
#include "LightSource.h"
#include "Image.h"

class Scene {
public:
  explicit Scene(const std::string &sceneFileName);

  const std::vector<Surface*> &getObjects() const;

  void setObjects(const std::vector<Surface*> &objects);

  const Camera &getMainCamera() const;

  void setMainCamera(const Camera &mainCamera);

  const std::vector<LightSource> &getLightSources() const;

  void setLightSources(const std::vector<LightSource> &lightSources);

private:
  std::vector<Surface*> objects;
  Camera mainCamera;
  std::vector<LightSource> lightSources;
};


#endif //PROG03_INLINEBOOL_SCENE_H
