set CXX=mingw32-g++.exe
set CC=mingw32-gcc.exe
conan  install -s arch=x86 -s arch_build=x86 -s compiler=gcc -s compiler.libcxx=libstdc++11 -s compiler.version=6.3 --build=outdated ../..
cmake  ../.. -G "MinGW Makefiles" 
cov-build --dir cov-int cmake --build .

