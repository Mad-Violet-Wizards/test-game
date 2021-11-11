#include "Widgets/Button_Exit.hpp"

Button_Exit::Button_Exit(Window *window)
  : GuiTextWidget(window)
{
  SetCharacterSize(24);
  SetString(std::string{ "Exit Game" });
  SetRelativePosition(50, 54);
}

Button_Exit::~Button_Exit()
{

}