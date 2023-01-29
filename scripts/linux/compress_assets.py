import ctypes
import os
import shutil

if __name__ == "__main__":

    project_path = os.path.abspath(os.path.join(
        os.path.abspath(os.path.dirname(__file__)), os.pardir, os.pardir))

    os.chdir(project_path)

    if (os.path.exists(f"{project_path}/tools/onyx_lib_compressor.dll") == False):
        print("[Compress-Assets] Error: onyx_lib_compressor.dll not found")
        exit()

    if (os.path.exists("assets_compressed")):
        shutil.rmtree("assets_compressed")

    os.mkdir("assets_compressed")

    file_compressor_dll = ctypes.cdll.LoadLibrary(
        "./tools/onyx_lib_compressor.dll")

    c_assets_input_dir_wrapper = file_compressor_dll.Py_GetAssetsDirectoryInput
    c_assets_input_dir_wrapper.restype = ctypes.c_char_p

    c_assets_compressor_wrapper = file_compressor_dll.Py_CreateAssetsContainer
    c_assets_compressor_wrapper.restype = ctypes.c_void_p

    c_assets_input_dir = ctypes.c_char_p(c_assets_input_dir_wrapper())
    c_assets_compressor = ctypes.c_void_p(c_assets_compressor_wrapper())

    file_compressor_dll.Py_Compress(
        c_assets_compressor, c_assets_input_dir, ctypes.c_bool(True))

    file_compressor_dll.Py_DestroyClass(c_assets_compressor)
