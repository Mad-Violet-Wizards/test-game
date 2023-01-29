import os
import shutil

def run():

    if (os.path.exists("build") == False):
        os.mkdir("build")
    
    os.chdir("build")
    os.system("conan install .. --build missing")
    os.system(f' cmake -G "g++" ..')
    os.system('cmake --build . --config Debug')
    os.system('cmake --build . --config Release')
    os.system('conan imports ..')
    shutil.copyfile("./bin/onyx_lib_compressor.dll", "../../onyx_lib_compressor.dll")
    shutil.copyfile("./lib/onyx_lib_compressor.lib", "../../onyx_lib_compressor.lib")


if __name__ == "__main__":
    run()