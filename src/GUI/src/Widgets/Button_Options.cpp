#include "Widgets/Button_Options.hpp"

Button_Options::Button_Options(Window *window)
  : GuiTextWidget(window)
{
  SetCharacterSize(24);
  SetString(std::string{ "Options" });
  SetRelativePosition(50, 46);
}

Button_Options::~Button_Options()
{

}