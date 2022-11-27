#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "ThreadPool.hpp"
#include "AssetsStorage.hpp"
#include "ProjectileStorage.hpp"
#include "ConsoleLog.hpp"

int main()
{
  Game game;

  auto LoadAssets = []()
  {
    AssetsStorage::GetInstance().ParseAssetsSchema("../assets/assets-schema.json");
    CONSOLE_LOG("[Info][Main] Thread: ", std::this_thread::get_id(), " finished loading assets.");
  };

  auto LoadProjectiles = []()
  {
    ProjectileStorage::Initialize();
    CONSOLE_LOG("[Info][Main] Thread: ", std::this_thread::get_id(), " finished loading projectiles.");
  };

  ThreadPool threadPool;

  threadPool.Submit(LoadAssets);
  threadPool.Submit(LoadProjectiles);

  threadPool.WaitForFinish();
  threadPool.Shutdown();


  game.CreateScenesAfterLoading();

  while (game.IsRunning())
  {
    game.GameLoop();
  }

  return EXIT_SUCCESS;
}
