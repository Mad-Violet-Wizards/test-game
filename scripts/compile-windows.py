# TODO: Create script for compilation.
import argparse
import subprocess
import os
import shutil

print("[Compile-Windows] Working.")

buildChainAndTestProjectList = ["core", "gui", "game"]
testProjectList              = ["core", "gui", "game"]

# ==============================================================

def install():
  os.chdir('..')

  if (os.path.exists("build") == False):
    os.mkdir('build')

  os.chdir('./build')
  os.system('cmd /c conan install .. --build=missing')

# ==============================================================

def build():
  os.chdir('..')

  if (os.path.exists("build") == False):
    os.mkdir('build')

  os.chdir('./build')
  os.system('cmd /c conan install .. --build=missing')
  os.system('cmd /c cmake -G "Visual Studio 16 2019" ../src')
  os.system('cmd /c cmake --build . --config Release')
  os.system('cmd /c conan imports ..')

# ==============================================================

def buildChainAndTestCore():
  # Always make sure we've the newest package compiled.
  os.system('cmd /c conan install ../src/core/ -if ../src/core/build')
  os.system('cmd /c conan build ../src/core/ -bf ../src/core/build')
  os.system('cmd /c conan export-pkg ../src/core/ -bf ../src/core/build -f')
  os.system('cmd /c conan install ../test/core/ -if ../test/core/build')
  os.chdir('../test/core/build/') # Enter test core build directory.
  os.system('cmd /c cmake -G "Visual Studio 16 2019" ..')
  os.system('cmd /c cmake --build . --config Release')
  os.system('cmd /c conan imports ..')
  subprocess.call(f"{os.getcwd()}/bin/coreTest.exe")
  os.chdir('../../..') # Go back to main directory.

def buildChainAndTestGui():
  # Always make sure we've the newest package compiled.
  os.system('cmd /c conan install ../src/core/ -if ../src/core/build')
  os.system('cmd /c conan build ../src/core/ -bf ../src/core/build')
  os.system('cmd /c conan export-pkg ../src/core/ -bf ../src/core/build -f')
  os.system('cmd /c conan install ../src/gui/ -if ../src/gui/build')
  os.system('cmd /c conan build ../src/gui/ -bf ../src/gui/build')
  os.system('cmd /c conan export-pkg ../src/gui/ -bf ../src/gui/build -f')
  os.system('cmd /c conan install ../test/gui/ -if ../test/gui/build')
  os.chdir('../test/gui/build/') # Enter test gui build directory.
  os.system('cmd /c cmake -G "Visual Studio 16 2019" ..')
  os.system('cmd /c cmake --build . --config Release')
  os.system('cmd /c conan imports ..')
  subprocess.call(f"{os.getcwd()}/bin/guiTest.exe")
  os.chdir('../../..') # Go back to main directory.

def buildChainAndTestGame():
  # Always make sure we've the newest package compiled.
  os.system('cmd /c conan install ../src/core/ -if ../src/core/build')
  os.system('cmd /c conan build ../src/core/ -bf ../src/core/build')
  os.system('cmd /c conan export-pkg ../src/core/ -bf ../src/core/build -f')
  os.system('cmd /c conan install ../src/gui/ -if ../src/gui/build')
  os.system('cmd /c conan build ../src/gui/ -bf ../src/gui/build')
  os.system('cmd /c conan export-pkg ../src/gui/ -bf ../src/gui/build -f')
  os.system('cmd /c conan install ../src/game/ -if ../src/game/build')
  os.system('cmd /c conan build ../src/game/ -bf ../src/game/build')
  os.system('cmd /c conan export-pkg ../src/game/ -bf ../src/game/build -f')
  os.system('cmd /c conan install ../test/game/ -if ../test/game/build')
  os.chdir('../test/game/build/') # Enter test game build directory.
  os.system('cmd /c cmake -G "Visual Studio 16 2019" ..')
  os.system('cmd /c cmake --build . --config Release')
  os.system('cmd /c conan imports ..')
  subprocess.call(f"{os.getcwd()}/bin/guiTest.exe")
  os.chdir('../../..') # Go back to main directory.

# ==============================================================

def testCore():
  os.system('cmd /c conan install ../test/core/ -if ../test/core/build')
  os.chdir('../test/core/build/') # Enter test core build directory.
  os.system('cmd /c cmake -G "Visual Studio 16 2019" ..')
  os.system('cmd /c cmake --build . --config Release')
  os.system('cmd /c conan imports ..')
  subprocess.call(f"{os.getcwd()}/bin/coreTest.exe")
  os.chdir('../../..') # Go back to main directory.

def testGui():
  os.system('cmd /c conan install ../test/gui/ -if ../test/gui/build')
  os.chdir('../test/gui/build/') # Enter test gui build directory.
  os.system('cmd /c cmake -G "Visual Studio 16 2019" ..')
  os.system('cmd /c cmake --build . --config Release')
  os.system('cmd /c conan imports ..')
  subprocess.call(f"{os.getcwd()}/bin/guiTest.exe")
  os.chdir('../../..') # Go back to main directory.

def testGame():
  os.system('cmd /c conan install ../test/game/ -if ../test/game/build')
  os.chdir('../test/game/build/') # Enter test game build directory.
  os.system('cmd /c cmake -G "Visual Studio 16 2019" ..')
  os.system('cmd /c cmake --build . --config Release')
  os.system('cmd /c conan imports ..')
  subprocess.call(f"{os.getcwd()}/bin/gameTest.exe")
  os.chdir('../../..')

# ==============================================================

def release():
  print("[Compile-Windows] Preparing release...")
  os.chdir('..')

  if (os.path.exists("test-game")):
    os.chdir('./test-game')

    if (os.path.exists("bin")):
      shutil.rmtree("bin")
    if (os.path.exists("assets")):
      shutil.rmtree("assets")
    if (os.path.exists("lib")):
      shutil.rmtree("lib")

    os.chdir("..")

  copy = shutil.copytree("./assets", "test-game/assets")
  copy = shutil.copytree("build/app/bin", "test-game/bin")
  copy = shutil.copytree("build/app/lib", "test-game/lib")

  for file in os.listdir("build/bin"):
    shutil.copy(f"build/bin/{file}", f"test-game/bin/{file}")

  print("[Compile-Windows] Release build done.")

# ==============================================================

def run():
  parser = argparse.ArgumentParser(description='Compilation script for test-game.')
  group = parser.add_mutually_exclusive_group()
  group.add_argument('--install', type=str, help='Which project to install: all, core, gui, game, app')
  group.add_argument('--build', type=str, help='Which project to build: all, core, gui, game, app')
  group.add_argument('--buildChainAndTest', type=str, help='Build chain for selected project, build test and run test.')
  group.add_argument('--test', type=str, help='Build test project and run tests.')
  group.add_argument('--release', type=str, help='Create new folder with release version of game.')
  
  parser = parser.parse_args()

  if (parser.install):
    print("[Compile-Windows] Going to execute install.")

    install()

  if (parser.build):
    print("[Compile-Windows] Going to execute build.")

    build()

  if (parser.buildChainAndTest):

    if (parser.buildChainAndTest in buildChainAndTestProjectList):

      if(parser.buildChainAndTest == "core"):
        buildChainAndTestCore()

      elif(parser.buildChainAndTest == "gui"):
        buildChainAndTestGui()

      elif(parser.buildChainAndTest == "game"):
        buildChainAndTestGame()

  if (parser.test):

    if (parser.test in testProjectList):

      if(parser.test == "core"):
        testCore()

      elif(parser.test == "gui"):
        testGui()

      elif(parser.test == "game"):
        testGame()

  if (parser.release):
    release()

if __name__ == "__main__":
  run()