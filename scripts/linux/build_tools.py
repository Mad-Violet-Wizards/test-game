import os
import fire

from utility.compilator_detector import CompilatorDetector
from utility.conan_detector import ConanDetector
from utility.cmake_detector import CmakeDetector

class BuildTools:

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

  def build_compressor(self):

    if self.check() is False:
      return

    print(f"[Build-Tools] Going to execute build with compilator: {self.compilator}")

    os.chdir('../../tools/onyx_file_compressor')
    os.system('cmd /c py build.py')

if __name__ == "__main__":
  fire.Fire(BuildTools)