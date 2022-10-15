import ctypes
import shutil
import os

if __name__ == "__main__":
  file_compressor_dll = ctypes.cdll.LoadLibrary("./onyx_file_compressor.dll")

  if (os.path.exists("assets")):
    shutil.rmtree("assets")

  os.mkdir("assets")

  c_assets_input_dir_wrapper = file_compressor_dll.GetAssetsDirectoryInput
  c_assets_input_dir_wrapper.restype = ctypes.c_char_p

  c_assets_compressor_wrapper = file_compressor_dll.CreateAssetsContainer
  c_assets_compressor_wrapper.restype = ctypes.c_void_p

  c_assets_input_dir = ctypes.c_char_p(c_assets_input_dir_wrapper())
  c_assets_compressor = ctypes.c_void_p(c_assets_compressor_wrapper())

  file_compressor_dll.Compress(c_assets_compressor, c_assets_input_dir, ctypes.c_bool(True))

  file_compressor_dll.DestroyClass(c_assets_compressor)

