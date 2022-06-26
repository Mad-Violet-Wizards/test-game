from conans import ConanFile, CMake, tools

class CoreConan(ConanFile):
    name = "core"
    version = "1.0"
    requires = [("sfml/2.5.1"), ("boost/1.77.0")]
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    generators = "cmake"
    no_copy_source = True

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def source(self):
        return

    def build(self):
        cmake = CMake(self)
        cmake.verbose = True
        cmake.configure(source_folder="")
        cmake.build()

    def package(self):
        self.copy("*.hpp", dst="include", src="include")
        self.copy("*core.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["core"]
        self.cpp_info.includedirs = ["include"]