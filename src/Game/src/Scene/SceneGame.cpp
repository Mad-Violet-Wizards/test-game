#include "Scene/SceneGame.hpp"

SceneGame::SceneGame() {}

SceneGame::~SceneGame() {}

void SceneGame::OnCreate() 
{
  m_testShape.setRadius(50.f);
  m_testShape.setFillColor(sf::Color(255, 0, 0));
}

void SceneGame::OnDestroy() {}

void SceneGame::ProcessInput()
{
  m_input.Update();
}

void SceneGame::Update(float deltaTime) 
{

  const sf::Vector2f& testPosition = m_testShape.getPosition();
  const int moveSpeed = 100;

  int xMove = 0;
  if (m_input.IsKeyPressed(Input::Key::Left))
  {
    xMove = -moveSpeed;
  }
  else if (m_input.IsKeyPressed(Input::Key::Right))
  {
    xMove = moveSpeed;
  }
    
  int yMove = 0;
  if (m_input.IsKeyPressed(Input::Key::Up))
  {
    yMove = -moveSpeed;
  }
  else if (m_input.IsKeyPressed(Input::Key::Down))
  {
    yMove = moveSpeed;
  }
    
  float xFrameMove = xMove * deltaTime;
  float yFrameMove = yMove * deltaTime;
  
  m_testShape.setPosition(testPosition.x + xFrameMove, testPosition.y + yFrameMove);
}

void SceneGame::Draw(Window& window) 
{
  window.Draw(m_testShape);
}