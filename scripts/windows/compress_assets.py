import ctypes
import os
import shutil

if __name__ == "__main__":

    os.chdir("../..")

    if (os.path.exists("./tools/onyx_lib_compressor.dll") == False):
      print("[Compress-Assets] Error: onyx_lib_compressor.dll not found")
      exit()

    if (os.path.exists("assets_compressed")):
      shutil.rmtree("assets_compressed")

    os.mkdir("assets_compressed")

    file_compressor_dll = ctypes.cdll.LoadLibrary("./tools/onyx_lib_compressor.dll")

    c_assets_input_dir_wrapper = file_compressor_dll.GetAssetsDirectoryInput
    c_assets_input_dir_wrapper.restype = ctypes.c_char_p

    c_assets_compressor_wrapper = file_compressor_dll.CreateAssetsContainer
    c_assets_compressor_wrapper.restype = ctypes.c_void_p

    c_assets_input_dir = ctypes.c_char_p(c_assets_input_dir_wrapper())
    c_assets_compressor = ctypes.c_void_p(c_assets_compressor_wrapper())

    file_compressor_dll.Compress(c_assets_compressor, c_assets_input_dir, ctypes.c_bool(True))

    file_compressor_dll.DestroyClass(c_assets_compressor)



    