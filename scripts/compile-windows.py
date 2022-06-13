# TODO: Create script for compilation.
import argparse
import subprocess
import os
import shutil

print("[Compile-Windows] Working.")

installProjectList = ["all", "core", "gui", "game", "app"]
buildProjectList   = ["all", "core", "gui", "game", "app"]
buildChainProjectList = ["core", "gui", "game"]
exportProjectlist  = ["all", "core", "gui", "game"]

# ==============================================================

def installAll():
    installCore()
    installGui()
    installGame()
    installApp()

def installCore():
    os.system('cmd /c conan install ../lib/core/ -if ../lib/core/build')

def installGui():
    os.system('cmd /c conan install ../lib/gui/ -if ../lib/gui/build')

def installGame():
    os.system('cmd /c conan install ../game/ -if ../game/build')

def installApp():
    os.system('cmd /c conan install ../app/ -if ../app/build')

# ==============================================================

def buildAll():
    buildCore()
    buildGui()
    buildGame()
    buildApp()

def buildCore():
    os.system('cmd /c conan build ../lib/core/ -bf ../lib/core/build')

def buildGui():
    os.system('cmd /c conan build ../lib/gui/ -bf ../lib/gui/build')

def buildGame():
    os.system('cmd /c conan build ../game/ -bf ../game/build')

def buildApp():
    os.chdir('../app/build/')
    os.system('cmd /c cmake -G "Visual Studio 16 2019" ..')
    os.system('cmd /c cmake --build . --config Release')
    os.system('cmd /c conan imports ..')

    if (os.path.exists("assets")):
        shutil.rmtree("assets")

    os.chdir('../../')
    copy = shutil.copytree("assets", "app/build/assets")
    print(f"[Compile-Windows] Copied assets to ${copy}")

# ==============================================================

def buildChainCore():
    buildCore()
    exportCore()
    buildGui()
    exportGui()
    buildGame()
    exportGame()
    buildApp()

def buildChainGui():
    buildGui()
    exportGui()
    buildGame()
    exportGame()
    buildApp()

def buildChainGame():
    buildGame()
    exportGame()
    buildApp()

# ==============================================================

def exportAll():
    exportCore()
    exportGui()
    exportGame()

def exportCore():
    os.system('cmd /c conan export-pkg ../lib/core/ -bf ../lib/core/build -f')

def exportGui():
    os.system('cmd /c conan export-pkg ../lib/gui/ -bf ../lib/gui/build -f')

def exportGame():
    os.system('cmd /c conan export-pkg ../game/ -bf ../game/build -f')

# ==============================================================

def release():
    print("[Compile-Windows] Preparing release...")
    os.chdir('..')
    if (os.path.exists("test-game")):
      shutil.rmtree("test-game")

    os.mkdir("test-game")
    copy = shutil.copytree("./assets", "test-game/assets")
    copy = shutil.copytree("app/build/bin", "test-game/bin")
    copy = shutil.copytree("app/build/lib", "test-game/lib")
    print("[Compile-Windows] Release build done.")

# ==============================================================

def run():
  parser = argparse.ArgumentParser(description='Compilation script for test-game.')
  group = parser.add_mutually_exclusive_group()
  group.add_argument('--install', type=str, help='Which project to install: all, core, gui, game, app')
  group.add_argument('--build', type=str, help='Which project to build: all, core, gui, game, app')
  group.add_argument('--buildChain', type=str, help='Chain build of library and all of its childrens.')
  group.add_argument('--exportlib', type=str, help='Which project to export: all, core, gui, game')
  group.add_argument('--release', type=str, help='Create new folder with release version of game.')
  
  parser = parser.parse_args()

  if (parser.install):
    print("[Compile-Windows] Going to execute install.")

    if(parser.install in installProjectList):
      
      if (parser.install == "all"):
        print("[Compile-Windows] Installing all packages.")
        installAll()

      if(parser.install == "core"):
        installCore()

      elif(parser.install == "gui"):
        installGui()

      elif(parser.install == "game"):
        installGame()

      elif (parser.install == "app"):
        installApp()

      print("[Compile-Windows] Installing done.")

    else:
      print("[Compile-Windows] Provide valid argument.")

  if (parser.build):
    print("[Compile-Windows] Going to execute build.")

    if(parser.build in buildProjectList):

      if (parser.build == "all"):
        buildAll()

      if (parser.build == "core"):
        buildCore()

      elif(parser.build == "gui"):
        buildGui()

      elif(parser.build == "game"):
        buildGame()

      elif (parser.build == "app"):
        buildApp()

      print("[Compile-Windows] Building done.")

    else:
      print("[Compile-Windows] Provide valid argument.")

  if (parser.buildChain):
    print("[Compile-Windows] Going to execute build-chain.")

    if(parser.buildChain in buildChainProjectList):

      if (parser.buildChain == "core"):
        buildChainCore()

      elif(parser.buildChain == "gui"):
        buildChainGui()

      elif(parser.buildChain == "game"):
        buildChainGame()

      print("[Compile-Windows] Chain building done done.")

    else:
      print("[Compile-Windows] Provide valid argument.")

  if (parser.exportlib):

    if (parser.exportlib in exportProjectlist):

      if (parser.exportlib == "all"):
        exportAll()

      elif (parser.exportlib == "core"):
        exportCore()

      elif (parser.exportlib == "gui"):
        exportGui()

      elif (parser.exportlib == "game"):
        exportGame()

      print("[Compile-Windows] Exporting lib done.")

    else:
      print("[Compile-Windows] Provide valid argument.")


  if (parser.release):
    release()
    

if __name__ == "__main__":
  run()