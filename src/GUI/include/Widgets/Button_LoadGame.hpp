#pragma once

#include "GuiTextWidget.hpp"

#include "Window.hpp"

class Button_LoadGame : public GuiTextWidget
{
  public:

    Button_LoadGame(Window* window);
    ~Button_LoadGame();
};