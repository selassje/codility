conan  install -s arch=x86_64 -s arch_build=x86_64 ../..
cmake -G "Visual Studio 15 2017 Win64" ../..
cmake --build . --config Release

