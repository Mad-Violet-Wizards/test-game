::======
:: TODO: Detect Visual Studio Release.
::======

echo Compile-Windows: Starting compilation.

if exist ..\build\ (
  echo Compile-Windows: Build folder found.
  cd ../build
  conan install ..
  cmake -G "Visual Studio 16 2019" ../src 
  cmake --build . --config Release
) else (
  echo Compile-Windows: Build folder not found.
  cd ..
  mkdir build
  cd ./build
  conan install ..
  cmake -G "Visual Studio 16 2019" ../src 
  cmake --build . --config Release
)

echo Compile-Windows: End of compilation, run .exe.
