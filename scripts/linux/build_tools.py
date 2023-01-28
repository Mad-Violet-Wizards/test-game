import os
import fire
from utility.utility_detector import Detector


class BuildTools:

    def __init__(self):

        self.compiler = Detector("g++").detect()
        self.detect_conan = Detector("conan").detect()
        self.detect_cmake = Detector("cmake").detect()
        self.project_path = os.path.abspath(os.path.join(
            os.path.abspath(os.path.dirname(__file__)), os.pardir, os.pardir))

        self.cwd = os.getcwd()

    def check(self):
        if (self.compiler and self.found_cmake and self.found_conan):
            return True
        else:
            return False

    def build_compressor(self):

        if self.check() is False:
            return

        print(
            f"[Build-Tools] Going to execute build with compiler: {self.compiler}")

        os.chdir(f'{self.project_path}/tools/onyx_file_compressor')
        os.system('cmd /c py build.py')


if __name__ == "__main__":
    fire.Fire(BuildTools)
