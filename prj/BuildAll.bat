@echo OFF
SETLOCAL ENABLEDELAYEDEXPANSION

rem === バッチファイルのパスに移動
cd /d %~dp0

set start_time=%time%

set VM_BUILD_ARG=%*

echo %~nx0 %VM_BUILD_ARG% > all_build.log

echo -- EHVM -- >> all_build.log
pushd .\EHVM
call build.bat %VM_BUILD_ARG%
type build.log >> ..\all_build.log
popd

echo -- VM0 -- >> all_build.log
pushd .\PE0VM0
call build.bat %VM_BUILD_ARG%
type build.log >> ..\all_build.log
popd

echo -- VM1 -- >> all_build.log
pushd .\PE1VM1
call build.bat %VM_BUILD_ARG%
type build.log >> ..\all_build.log
popd

echo -- VM2 -- >> all_build.log
pushd .\PE2VM2
call build.bat %VM_BUILD_ARG%
type build.log >> ..\all_build.log
popd

echo -- VM3 -- >> all_build.log
pushd .\PE3VM3
call build.bat %VM_BUILD_ARG%
type build.log >> ..\all_build.log
popd

REM echo -- OptByte -- >> all_build.log
REM pushd .\OptByte
REM call build.bat %VM_BUILD_ARG%
REM type build.log >> ..\all_build.log
REM popd

echo -- XCreate -- >> all_build.log
call xCreate.bat >> all_build.log

echo ===============================
echo Start Time: %start_time%
echo End Time  : %time%

@echo '--- done all..'
