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

echo Compile-Windows: End of compilation, creating release.

if exist ..\test-game\ (
  echo Compile-Windows: Found release folder.
  cd ..
  rmdir /s /q test-game
  mkdir test-game
  cd test-game
  robocopy ../build/App/bin ./bin
  robocopy ../build/App/lib ./lib
  robocopy ../src/Assets ./assets
) else (
  echo Compile-Windows: Didn't found release folder.
  cd ..
  mkdir test-game
  cd test-game
  robocopy ../build/App/bin ./bin
  robocopy ../build/App/lib ./lib
  robocopy ../src/Assets ./assets
)
