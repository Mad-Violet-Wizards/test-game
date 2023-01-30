#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "ThreadPool.hpp"
#include "AssetsStorage.hpp"
#include "ProjectileStorage.hpp"
#include "ConsoleLog.hpp"
#include "ThreadPoolSFML.hpp"
#include "Timer.hpp"

int main()
{
  Game game;

  AssetsStorage::GetInstance().LoadAssets("../assets/");
  ProjectileStorage::Initialize();

  game.CreateScenesAfterLoading();

  while (game.IsRunning())
  {
    game.GameLoop();
  }


  // Game game;

  // ThreadPoolSFML threadPool;

  // auto LoadAssets = []()
  // {
  //   ThreadPoolSFML::s_totalJobs++;
  //   AssetsStorage::GetInstance().LoadAssets("../assets/");
  //   CONSOLE_LOG("[Info][Main] Thread: ", std::this_thread::get_id(), " finished loading assets.");
  //   ThreadPoolSFML::s_jobsFinished++;
  // };

  // auto LoadProjectiles = []()
  // {
  //   ThreadPoolSFML::s_totalJobs++;
  //   ProjectileStorage::Initialize();
  //   CONSOLE_LOG("[Info][Main] Thread: ", std::this_thread::get_id(), " finished loading projectiles.");
  //   ThreadPoolSFML::s_jobsFinished++;
  // };

  // Timer t;
  // t.Start();

  // threadPool.Submit(LoadAssets);
  // threadPool.Submit(LoadProjectiles);

  // threadPool.Process();

  // game.CreateLoadingScene();

  // while (game.IsRunning())
  // {
  //   game.GameLoop();

  //   if (ThreadPoolSFML::s_jobsFinished == ThreadPoolSFML::s_totalJobs)
  //   {
  //     ThreadPoolSFML::s_jobsFinished = 0;
  //     threadPool.Clear();
  //     game.CreateScenesAfterLoading();

  //     t.Stop();
  //     CONSOLE_LOG("[Info][Main] Loading time: ", t.GetElapsedTime<std::chrono::milliseconds>(), " ms.");
  //   }
  // }

  return EXIT_SUCCESS;
}
