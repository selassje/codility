conan  install -s arch=x86 -s arch_build=x86 -build=outdated ../..
cmake ../..
cov-build --dir cov-int cmake --build . --config Release
