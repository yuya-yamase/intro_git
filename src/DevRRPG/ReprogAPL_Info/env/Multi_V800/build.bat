@echo off

call .\build_env.bat

gbuild -top default.gpj > build.log 2>&1

if not %ERRORLEVEL% == 0 (
	exit /b 1
)

EXIT /B 0