conan  install -s arch=x86 -s arch_build=x86 -s compiler=gcc -s compiler.libcxx=libstdc++11 -s compiler.version=6.3 --build=outdated ../..
cmake ../.. -G "MSYS Makefiles"
cmake --build . --config Release

