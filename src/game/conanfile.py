from conans import ConanFile, CMake, tools

class GameConan(ConanFile):
    name = "game"
    version = "1.0"
    requires = [ ("sfml/2.5.1"), ("core/1.0"), ("gui/1.0") ]
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    generators = "cmake"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def source(self):
        pass

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="")
        cmake.build()


    def package(self):
        self.copy("*.hpp", dst="include", src="include")
        self.copy("*game.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["game"]
        self.cpp_info.includedirs = ["include"]