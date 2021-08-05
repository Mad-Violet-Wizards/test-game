#pragma once

#include "Scene/Scene.hpp"

class SceneGame : public Scene
{
  public:

    SceneGame();
    ~SceneGame();

    void OnCreate() override;
    void OnDestroy() override;
    void Update(float deltaTime) override;
    void Draw(Window& window) override;
};