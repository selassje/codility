export CC=/usr/bin/gcc-6
export CXX=/usr/bin/g++-6
conan install -s arch=x86 -s arch_build=x86 ../..
cmake "../.."
cat Makefile
cmake --build .
