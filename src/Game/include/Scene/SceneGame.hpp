#pragma once

#include <SFML/Graphics.hpp>

#include "Scene/Scene.hpp"
#include "Input.hpp"
#include "Object.hpp"
#include "Components/C_Sprite.hpp"

class SceneGame : public Scene
{
  public:

    SceneGame();
    ~SceneGame();

    void OnCreate() override;
    void OnDestroy() override;

    void ProcessInput() override;
    void Update(float deltaTime) override;
    void Draw(Window& window) override;

  private:
    std::shared_ptr<Object> m_player;


    Input m_input;

    sf::CircleShape m_testShape;
};
