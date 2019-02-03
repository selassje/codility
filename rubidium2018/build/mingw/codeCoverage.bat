setlocal
set ENABLE_COVERAGE=1
call run.bat
cd CMakeFiles\rubidium.dir\
for /r %%i in (\*.gcno) do gcov -m %%i
cd ../..
endlocal