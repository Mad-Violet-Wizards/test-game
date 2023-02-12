#include <SFML/Graphics.hpp>
#include <memory>

#include "Game.hpp"
#include "AssetsStorage.hpp"
#include "ProjectileStorage.hpp"
#include "ConsoleLog.hpp"
#include "Timer.hpp"
#include "ThreadTask.hpp"
#include "ThreadPool.hpp"

int main()
{
  Game game;
  game.CreateLoadingScene();

  ThreadPool *loadingPool = new ThreadPool { 2 };

  auto loadAssets = []() { AssetsStorage::GetInstance().LoadAssets("../assets/"); };

  loadingPool -> Submit(ProjectileStorage::Initialize);
  loadingPool -> Submit(loadAssets);

  loadingPool -> Start();

  while (game.IsRunning())
  {
    game.GameLoop();

    if (loadingPool && !loadingPool -> IsRunning())
    {
      game.CreateScenesAfterLoading();

      delete loadingPool;
      loadingPool = nullptr;
    }
  }

  return EXIT_SUCCESS;
}
