#pragma once

#include <SFML/Graphics.hpp>
#include "Window.hpp"

class GuiWidget : public sf::Drawable, public sf::Transformable
{

  public:

    GuiWidget(Window* window);
    ~GuiWidget();

    void OnDestroy();

    void Update() {};

    virtual void SetRelativePosition(const std::string& x, const std::string& y) {};
    virtual void SetRelativePosition(const char* x, const char* y) {};
    virtual void SetRelativePosition(const int x, const int y) {};


  protected:

    Window* m_window;
    sf::Vector2u m_layoutSize;

  private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::RectangleShape m_testRect;
};