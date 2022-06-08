# TODO: Create script for compilation.
import argparse
import subprocess
import os
import shutil

print("[Compile-Windows] Working.")

installProjectList = ["all", "core", "gui", "game", "app"]
buildProjectList   = ["all", "core", "gui", "game", "app"]
exportProjectlist  = ["all", "core", "gui", "game"]


def run():
  parser = argparse.ArgumentParser(description='Compilation script for test-game.')
  group = parser.add_mutually_exclusive_group()
  group.add_argument('--build', type=str, help='Which project to build: all, core, gui, game, app')
  group.add_argument('--install', type=str, help='Which project to install: all, core, gui, game, app')
  group.add_argument('--exportlib', type=str, help='Which project to export: all, core, gui, game')
  group.add_argument('--release', type=str, help='Create new folder with release version of game.')
  
  parser = parser.parse_args()

  if (parser.install):
    print("[Compile-Windows] Going to execute install.")

    if(parser.install in installProjectList):
      
      if (parser.install == "all"):
        print("[Compile-Windows] Installing all packages.")
        os.system('cmd /c conan install ../lib/core/ -if ../lib/core/build')
        os.system('cmd /c conan install ../lib/gui/ -if ../lib/gui/build')
        os.system('cmd /c conan install ../game/ -if ../game/build')
        os.system('cmd /c conan install ../app/ -if ../app/build')

      if(parser.install == "core"):
        os.system('cmd /c conan install ../lib/core/ -if ../lib/core/build')

      elif(parser.install == "gui"):
        os.system('cmd /c conan install ../lib/gui/ -if ../lib/gui/build')

      elif(parser.install == "game"):
        os.system('cmd /c conan install ../game/ -if ../game/build')

      elif (parser.install == "app"):
        os.system('cmd /c conan install ../app/ -if ../app/build')

      print("[Compile-Windows] Installing done.")

    else:
      print("[Compile-Windows] Provide valid argument.")

  if (parser.build):
    print("[Compile-Windows] Going to execute build.")

    if(parser.build in buildProjectList):

      if (parser.build == "all"):
        print("[Compile-Windows] Building all packages.")
        os.system('cmd /c conan build ../lib/core/ -bf ../lib/core/build')
        os.system('cmd /c conan build ../lib/gui/ -bf ../lib/gui/build')
        os.system('cmd /c conan build ../game/ -bf ../game/build')
        os.chdir('../app/build/')
        os.system('cmd /c cmake -G "Visual Studio 16 2019" ..')
        os.system('cmd /c cmake --build . --config Release')
        os.system('cmd /c conan imports ..')

        if (os.path.exists("assets")):
          shutil.rmtree("assets")

        os.chdir('../../')
        copy = shutil.copytree("assets", "app/build/assets")
        print(f"[Compile-Windows] Copied assets to ${copy}")

      if (parser.build == "core"):
        os.system('cmd /c conan build ../lib/core/ -bf ../lib/core/build')

      elif(parser.build == "gui"):
        os.system('cmd /c conan build ../lib/gui/ -bf ../lib/gui/build')

      elif(parser.build == "game"):
        os.system('cmd /c conan build ../game/ -bf ../game/build')

      elif (parser.build == "app"):
        os.chdir('../app/build/')
        os.system('cmd /c cmake -G "Visual Studio 16 2019" ..')
        os.system('cmd /c cmake --build . --config Release')
        os.system('cmd /c conan imports ..')

        if (os.path.exists("assets")):
          shutil.rmtree("assets")

        os.chdir('../../')
        copy = shutil.copytree("assets", "app/build/assets")
        print(f"[Compile-Windows] Copied assets to ${copy}")

      print("[Compile-Windows] Building done.")

    else:
      print("[Compile-Windows] Provide valid argument.")

  if (parser.exportlib):

    if (parser.exportlib in exportProjectlist):

      if (parser.exportlib == "all"):
        os.system('cmd /c conan export-pkg ../lib/core/ -bf ../lib/core/build -f')
        os.system('cmd /c conan export-pkg ../lib/gui/ -bf ../lib/gui/build -f')
        os.system('cmd /c conan export-pkg ../game/ -bf ../game/build -f')

      elif (parser.exportlib == "core"):
        os.system('cmd /c conan export-pkg ../lib/core/ -bf ../lib/core/build -f')

      elif (parser.exportlib == "gui"):
        os.system('cmd /c conan export-pkg ../lib/gui/ -bf ../lib/gui/build -f')

      elif (parser.exportlib == "game"):
        os.system('cmd /c conan export-pkg ../game/ -bf ../game/build -f')

      print("[Compile-Windows] Exporting lib done.")

    else:
      print("[Compile-Windows] Provide valid argument.")


  if (parser.release):
    print("[Compile-Windows] Preparing release...")
    os.chdir('..')
    if (os.path.exists("test-game")):
      shutil.rmtree("test-game")

    os.mkdir("test-game")
    copy = shutil.copytree("app/build/assets", "test-game/assets")
    copy = shutil.copytree("app/build/bin", "test-game/bin")
    copy = shutil.copytree("app/build/lib", "test-game/lib")
    print("[Compile-Windows] Release build done.")
    

if __name__ == "__main__":
  run()