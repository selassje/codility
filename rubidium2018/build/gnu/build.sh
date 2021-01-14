export CC=/usr/bin/gcc-6
export CXX=/usr/bin/g++-6
conan install -s arch=x86_64 -s arch_build=x86_64 -s compiler=gcc -s compiler.libcxx=libstdc++11 -s compiler.version=7 ../..
cmake "../.."
cmake --build .
