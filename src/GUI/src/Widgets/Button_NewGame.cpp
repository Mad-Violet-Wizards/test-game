#include "Widgets/Button_NewGame.hpp"

Button_NewGame::Button_NewGame(Window* window)
  : GuiTextWidget(window)
{
  SetCharacterSize(24);
  SetString(std::string{ "New Game" });
  SetRelativePosition(50, 30);
}

Button_NewGame::~Button_NewGame()
{

}