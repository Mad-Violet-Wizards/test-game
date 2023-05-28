#include <SFML/Graphics.hpp>
#include <memory>

#include "Game.hpp"
#include "ProjectileStorage.hpp"
#include "ThreadTask.hpp"
#include "ThreadPool.hpp"
#include "EventHandler.hpp"

int main()
{
  Game game;
  game.CreateLoadingScene();

  ThreadPool *loadingPool = new ThreadPool { 2 };

  auto loadAssets = []() { AssetsStorageSingleton::Instance().LoadAssets("../../tools/assets.pak"); };

  loadingPool -> Submit(loadAssets);
  loadingPool -> Submit(ProjectileStorage::Initialize);

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
