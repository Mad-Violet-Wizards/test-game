import subprocess
import os
import shutil
import fire

from utility.compilator_detector import CompilatorDetector
from utility.conan_detector import ConanDetector
from utility.cmake_detector import CmakeDetector

class Build:

  def __init__(self):

    self.detected_compilator = CompilatorDetector().detect()
    self.found_conan = ConanDetector().detect()
    self.found_cmake = CmakeDetector().detect()

    self.compilator = f"{self.detected_compilator['compilator']} {self.detected_compilator['version']} {self.detected_compilator['release_date']}"
    self.cwd = os.getcwd()

  def check(self):
    if (self.compilator and self.found_cmake and self.found_conan):
      return True
    else:
      return False

  def install(self):
    
    if self.check() is False:
      return

    os.chdir('..')

    if (os.path.exists("build") == False):
      os.mkdir('build')

    os.chdir('./build')
    os.system('cmd /c conan install .. --build=missing')


  def build(self):

    if self.check() is False:
      return

    print(f"[Build] Going to execute build with compilator: {self.compilator}")

    os.chdir('..')

    if (os.path.exists("build") == False):
      os.mkdir('build')

    os.chdir('./build')
    os.system('cmd /c conan install .. --build=missing')
    os.system(f'cmd /c cmake -G "{self.compilator}" ..')
    os.system('cmd /c cmake --build . --config Release')
    os.system('cmd /c conan imports ..')

    print("[Build] Build finished")

  def release(self):

    print("[Build] Preparing release for game.")
    os.chdir('..')

    if (not os.path.exists("test-game")):
      os.mkdir('test-game')
    
    os.chdir('./test-game')

    if (os.path.exists("bin")):
      shutil.rmtree("bin")
    if (os.path.exists("assets")):
      shutil.rmtree("assets")
    if (os.path.exists("lib")):
      shutil.rmtree("lib")
    if (os.path.exists("logs")):
      shutil.rmtree("logs")

    os.chdir("..")

    os.mkdir("test-game/bin/")

    copy = shutil.copytree("./assets", "test-game/assets")
    shutil.copy("build/src/app/bin/app.exe", "test-game/bin/")

    for file in os.listdir("build/bin"):
      shutil.copy(f"build/bin/{file}", f"test-game/bin/{file}")

    print("[Build] Release prepared")

  def release_tools(self):

      print("[Build] Preparing release for tools.")
      
      os.chdir("..")

      if (not os.path.exists("tools")):
        os.mkdir('tools')

      shutil.copy("build/src/pak-compiler/Release/pak-compiler.exe", "tools")

      print("[Build] Tools release prepared")

if __name__ == "__main__":
  fire.Fire(Build)