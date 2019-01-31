conan install -s arch=x86 -s arch_build=x86 ../..
cmake ../..
cmake --build . --config Release

