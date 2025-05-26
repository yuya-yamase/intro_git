@echo OFF
SETLOCAL ENABLEDELAYEDEXPANSION

rem === バッチファイルのパスに移動
cd /d %~dp0

set start_time=%time%

set RRPG_RUNFILE_FOLDER="..\..\..\src\DevRRPG\Runfiles\"

set VM_BUILD_ARG=%*

echo %~nx0 %VM_BUILD_ARG% > all_build.log

echo -- OPBT -- >> all_build.log
pushd ..\write_opbt\
call build.bat
type build.log >> ..\all_build.log
popd

echo -- EHVM -- >> all_build.log
pushd .\EHVM
call build.bat %VM_BUILD_ARG%
copy .\dst\*.run %RRPG_RUNFILE_FOLDER%
copy .\dst\*.elf %RRPG_RUNFILE_FOLDER%
type build.log >> ..\all_build.log
popd

echo -- VM0 -- >> all_build.log
pushd .\PE0VM0
call build.bat %VM_BUILD_ARG%
copy .\dst\*.run %RRPG_RUNFILE_FOLDER%
copy .\dst\*.elf %RRPG_RUNFILE_FOLDER%
type build.log >> ..\all_build.log
popd

echo -- VM1 -- >> all_build.log
pushd .\PE1VM1
call build.bat %VM_BUILD_ARG%
copy .\dst\*.run %RRPG_RUNFILE_FOLDER%
copy .\dst\*.elf %RRPG_RUNFILE_FOLDER%
type build.log >> ..\all_build.log
popd

echo -- VM2 -- >> all_build.log
pushd .\PE2VM2
call build.bat %VM_BUILD_ARG%
copy .\dst\*.run %RRPG_RUNFILE_FOLDER%
copy .\dst\*.elf %RRPG_RUNFILE_FOLDER%
type build.log >> ..\all_build.log
popd

echo -- VM3 -- >> all_build.log
pushd .\PE3VM3
call build.bat %VM_BUILD_ARG%
copy .\dst\*.run %RRPG_RUNFILE_FOLDER%
copy .\dst\*.elf %RRPG_RUNFILE_FOLDER%
type build.log >> ..\all_build.log
popd

REM echo -- OptByte -- >> all_build.log
REM pushd .\OptByte
REM call build.bat %VM_BUILD_ARG%
REM type build.log >> ..\all_build.log
REM popd

echo -- motCreate -- >> all_build.log
call U2A_BevCreateMot.bat >> all_build.log

@echo OFF
echo -- SectionAnalysis Start--
call SectionAnalysis.bat
echo -- SectionAnalysis End--

echo ===============================
echo Start Time: %start_time%
echo End Time  : %time%

@echo OFF
echo -- Step: ReprogAPL build --
pushd ..\..\src\DevRRPG\ReprogAPL_Info\env\Multi_V800
call build.bat
popd

echo -- Step: ReprogProject build --
pushd ..\..\src\DevRRPG\ReprogProject\env\Multi\Multi_V800
call build.bat
popd

echo -- Step: CombineMOT  --
echo -- CombineMOT -- >> all_build.log
pushd ..\..\src\DevRRPG\Tool\CombineMOT
python ReprogTargetConbineMOT.py
popd

echo -- Step: Converter  --
echo -- Converter -- >> all_build.log
pushd ..\..\src\DevRRPG\Tool\Converter
python ReprogTargetConverter.py
popd

echo -- Step: TS-Writer DL file  --
echo -- TS-Writer DL file -- >> all_build.log
pushd ..\..\src\DevRRPG\Tool\TS-WriterData
call CreateTSW.bat
popd

@echo '--- done all..'
