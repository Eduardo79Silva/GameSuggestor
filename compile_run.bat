cmake -S . -B .\build\ -G "MinGW Makefiles"
cmake --build .\build\ --clean-first
.\build\bin\SteamSuggestor.exe
