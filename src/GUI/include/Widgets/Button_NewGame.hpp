#pragma once

#include "GuiTextWidget.hpp"

#include "Window.hpp"

class Button_NewGame : public GuiTextWidget
{
  public:

    Button_NewGame(Window* window);
    ~Button_NewGame();
};