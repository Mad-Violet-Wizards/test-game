#pragma once

#include "GuiTextWidget.hpp"

#include "Window.hpp"

class Button_Exit : public GuiTextWidget
{

  public:

    Button_Exit(Window *window);
    ~Button_Exit();
};