export CC=/usr/bin/gcc-6
export CXX=/usr/bin/g++-6
cmake ../..
cov-build --dir cov-int cmake --build .
