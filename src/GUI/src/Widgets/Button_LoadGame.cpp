#include "Widgets/Button_LoadGame.hpp"

Button_LoadGame::Button_LoadGame(Window* window)
  : GuiTextWidget(window)
{
  SetCharacterSize(24);
  SetString(std::string{ "Load Game" });
  SetRelativePosition(50, 38);
}

Button_LoadGame::~Button_LoadGame()
{

}