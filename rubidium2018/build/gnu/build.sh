export CC=/usr/bin/gcc-6
export CXX=/usr/bin/g++-6
conan install -s arch=x64 -s arch_build=x64 ../..
cmake "../.."
cat Makefile
make 2>&1
#cmake --build .
