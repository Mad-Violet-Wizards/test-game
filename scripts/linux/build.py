#!/usr/bin/env python3
import os
import shutil
import fire
from utility.utility_detector import Detector


class Build:

    def __init__(self):

        self.compiler = "g++"
        self.detect_compiler: bool = Detector(self.compiler).detect()
        self.detect_conan: bool = Detector("conan").detect()
        self.detect_cmake: bool = Detector("cmake").detect()
        self.project_path = os.path.abspath(os.path.join(
            os.path.abspath(os.path.dirname(__file__)), os.pardir, os.pardir))
        self.cwd = os.getcwd()

    def check(self):
        if (self.detect_compiler and self.detect_cmake and self.detect_conan):
            return True
        else:
            return False

    def install(self):

        if self.check() is False:
            return

        os.chdir(self.project_path)
        print(os.system('pwd'))

        if (os.path.exists("build") == False):
            os.mkdir('build')

        os.chdir('./build')
        os.system('conan install .. --build=missing')

    def build(self):
        if self.check() is False:
            return

        print(
            f"[Build] Going to execute build with compilator: {self.compiler}")

        os.chdir(self.project_path)

        if (os.path.exists("build") == False):
            os.mkdir('build')

        os.chdir('./build')
        os.system('conan install .. --build=missing')
        os.system(f'cmake -G "Ninja" ..')
        os.system('cmake --build . --config Release')
        os.system('conan imports ..')

        print("[Build] Build finished")

    def release(self):

        print("[Build] Preparing release")
        os.chdir(self.project_path)

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

        os.chdir(self.project_path)
        os.mkdir("test-game/bin/")

        copy = shutil.copytree("./assets", "test-game/assets")
        shutil.copy("build/src/app/bin/app", "test-game/bin/")

        for file in os.listdir("build/bin"):
            shutil.copy(f"build/bin/{file}", f"test-game/bin/{file}")

        print("[Build] Release prepared")


if __name__ == "__main__":
    fire.Fire(Build)
