cd ..
git submodule update --init
rd /s /q build
md build
cd .\build
cmake .. -G "MinGW Makefiles"
cmake --build .