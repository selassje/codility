for /f %%F in ('dir /s /b /a-d ^| findstr /vile ".bat"') do del /q "%%F"
for /d %%p in (.\*) do rd /s /q "%%p"