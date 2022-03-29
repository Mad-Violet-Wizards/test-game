if exist ..\test-game\ (
  cd ../test-game/bin
  onyx_engine_app.exe
) else (
  compile-windows.bat
  cd ../test-game/bin
  onyx_engine_app.exe
)