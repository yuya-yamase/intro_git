@echo off

rem '*** elf->xファイル変換用パスとオプション
set BUILDER=C:\GHS\RH850_V.R9144\comp_201715\
set GSREC_EXE=%BUILDER%\gsrec.exe
set GSREC_OPTION=-sort -S3 -noS0 -noS5 -bytes 16

set PRJ_DIR=..\..\Runfiles\

rem '*** EVHMのROMディレクトリ
set HOST_ROM_DIR=%PRJ_DIR%

rem '*** PE0VM0のROMディレクトリ
set PE0VM0_ROM_DIR=%PRJ_DIR%

rem '*** PE1VM1のROMディレクトリ
set PE1VM1_ROM_DIR=%PRJ_DIR%

rem '*** PE2VM2のROMディレクトリ
set PE2VM2_ROM_DIR=%PRJ_DIR%

rem '*** PE3VM3のROMディレクトリ
set PE3VM3_ROM_DIR=%PRJ_DIR%

rem '*** RepogAPLのROMディレクトリ
set RPGAPL_ROM_DIR=..\..\ReprogAPL_Info\env\out\

rem *** HOST設定
set HOST_OUT=%HOST_ROM_DIR%host.elf
rem set HOST_MAP=%HOST_ROM_DIR%host.map
set HOST_ROM_STA=0x00020000
set HOST_ROM_END=0x0005FFFF
set HOST_TEMP=host_temp.mot

rem *** PE0VM0設定
set PE0VM0_OUT=%PE0VM0_ROM_DIR%PE0VM0.elf
rem set PE0VM0_MAP=%PE0VM0_ROM_DIR%PE0VM0.map
set PE0VM0_ROM_STA=0x00060000
set PE0VM0_ROM_END=0x001FFFFF
set PE0VM0_TEMP=vm0_temp.mot

rem *** PE1VM1設定
set PE1VM1_OUT=%PE1VM1_ROM_DIR%PE1VM1.elf
rem set PE1VM1_MAP=%PE1VM1_ROM_DIR%PE1VM1.map
set PE1VM1_ROM_STA=0x00200000
set PE1VM1_ROM_END=0x003FFFFF
set PE1VM1_TEMP=vm1_temp.mot

rem *** PE2VM2設定
set PE2VM2_OUT=%PE2VM2_ROM_DIR%PE2VM2.elf
rem set PE2VM2_MAP=%PE2VM2_ROM_DIR%PE2VM2.map
set PE2VM2_ROM_STA=0x00400000
set PE2VM2_ROM_END=0x005FFFFF
set PE2VM2_TEMP=vm2_temp.mot

rem *** PE3VM3設定
set PE3VM3_OUT=%PE3VM3_ROM_DIR%PE3VM3.elf
rem set PE3VM3_MAP=%PE3VM3_ROM_DIR%PE3VM3.map
set PE3VM3_ROM_STA=0x00600000
set PE3VM3_ROM_END=0x007FFDDF
set PE3VM3_TEMP=vm3_temp.mot

rem *** REPRO APL設定
set RPGAPL_OUT=%RPGAPL_ROM_DIR%ReprogAPL.elf
set RPGAPL_ROM_STA=0x007FFDF0
set RPGAPL_ROM_END=0x007FFDFF
set RPGAPL_TEMP=rpgapl_temp.mot

set X_FILE=TSW-SendData.x

echo *********************************************************
echo ****** TS-Writer用送信データ作成バッチファイル実行 ******
echo *********************************************************

rem *** 成果物収集用フォルダ（OUT）の生成or存在確認 および 古い実行ファイル(*.x)の削除
del %X_FILE%

rem *** HVM/rom内のelfファイル存在チェック
if not exist "%HOST_OUT%" (
    echo.
    echo [ERROR]:EHVMのdstフォルダに host.elf が存在しません。処理を中断します。
    echo.
    pause
    exit \b
)

rem *** \PE0VM0\dst\内のelfファイル存在チェック
if not exist "%PE0VM0_OUT%" (
    echo.
    echo [ERROR]:PE0VM0のdstフォルダに PE0VM0.elf が存在しません。処理を中断します。
    echo.
    pause
    exit \b
)

rem *** \PE1VM1\dst\内のelfファイル存在チェック
if not exist "%PE1VM1_OUT%" (
    echo.
    echo [ERROR]:PE1VM1のdstフォルダに PE1VM1.elf が存在しません。処理を中断します。
    echo.
    pause
    exit \b
)

rem *** \PE2VM2\dst\内のelfファイル存在チェック
if not exist "%PE2VM2_OUT%" (
    echo.
    echo [ERROR]:PE2VM2のdstフォルダに PE2VM2.elf が存在しません。処理を中断します。
    echo.
    pause
    exit \b
)

rem *** \PE3VM3\dst\内のelfファイル存在チェック
if not exist "%PE3VM3_OUT%" (
    echo.
    echo [ERROR]:PE3VM3のdstフォルダに PE3VM3.elf が存在しません。処理を中断します。
    echo.
    pause
    exit \b
)

rem *** リプロのelfファイル存在チェック
rem if not exist "%RPGAPL_OUT%" (
rem    echo.
rem    echo [ERROR]:ReprogAplのoutフォルダに ReprogAPL.elf が存在しません。処理を中断します。
rem    echo.
rem    pause
rem    exit \b
rem )

goto DATA_ENOUTH

:ERROR_DATA_SHORT
echo.
echo [ERROR]:必要なオブジェクトが不足してます。処理を中断します。
echo.
pause
exit \b

rem xファイル生成に必要なオブジェクトが揃っている場合
:DATA_ENOUTH

rem '*** オブジェクトの変換(elf->***_temp.mot)
%GSREC_EXE% %GSREC_OPTION% -pad1 %HOST_ROM_STA% %HOST_ROM_END% 0xFF -o %HOST_TEMP% %HOST_OUT%
%GSREC_EXE% %GSREC_OPTION% -pad1 %PE0VM0_ROM_STA% %PE0VM0_ROM_END% 0xFF -o %PE0VM0_TEMP% %PE0VM0_OUT%
%GSREC_EXE% %GSREC_OPTION% -pad1 %PE1VM1_ROM_STA% %PE1VM1_ROM_END% 0xFF -o %PE1VM1_TEMP% %PE1VM1_OUT%
%GSREC_EXE% %GSREC_OPTION% -pad1 %PE2VM2_ROM_STA% %PE2VM2_ROM_END% 0xFF -o %PE2VM2_TEMP% %PE2VM2_OUT%
%GSREC_EXE% %GSREC_OPTION% -pad1 %PE3VM3_ROM_STA% %PE3VM3_ROM_END% 0xFF -o %PE3VM3_TEMP% %PE3VM3_OUT%
%GSREC_EXE% %GSREC_OPTION% -pad2 0x007FFDE0 0x007FFDFF 0x5AA5 -start 0x007FFDE0 -end 0x007FFDFF -bytes 16 %RPGAPL_OUT% -o %RPGAPL_TEMP%

rem '*** Sレコードファイルの結合
python TargetConbineMOT4TSW.py

if not exist "%X_FILE%" (
    goto ERROR_CONVERT
)

goto CONVERT_COMPLETE

:ERROR_CONVERT
echo.
echo [ERROR]:%X_FILE% は作成できませんでした。
echo.
pause
rem exit \b

:CONVERT_COMPLETE
echo.
echo [COMPLETE]:%X_FILE% を作成しました。
echo.

REM pause

rem '*** テンポラリファイル削除
del *temp.mot

@echo on
