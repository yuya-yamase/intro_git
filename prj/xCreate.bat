@echo off

rem *** elf->xファイル変換用パスとオプション
set BUILDER=C:\GHS\RH850_V.R9144\comp_201715\
set GSREC_EXE=%BUILDER%\gsrec.exe
set GSREC_OPTION=-sort -S3 -noS0 -noS5 -bytes 16

rem *** EVHMのROMディレクトリ
set HOST_ROM_DIR=.\EHVM\dst\

rem *** PE0VM0のROMディレクトリ
set PE0VM0_ROM_DIR=.\PE0VM0\dst\

rem *** PE1VM1のROMディレクトリ
set PE1VM1_ROM_DIR=.\PE1VM1\dst\

rem *** PE2VM2のROMディレクトリ
set PE2VM2_ROM_DIR=.\PE2VM2\dst\

rem *** PE3VM3のROMディレクトリ
set PE3VM3_ROM_DIR=.\PE3VM3\dst\

rem *** HOST設定
set HOST_OUT=%HOST_ROM_DIR%host.elf
set HOST_MAP=%HOST_ROM_DIR%host.map

rem *** PE0VM0設定
set PE0VM0_OUT=%PE0VM0_ROM_DIR%PE0VM0.elf
set PE0VM0_MAP=%PE0VM0_ROM_DIR%PE0VM0.map

rem *** PE1VM1設定
set PE1VM1_OUT=%PE1VM1_ROM_DIR%PE1VM1.elf
set PE1VM1_MAP=%PE1VM1_ROM_DIR%PE1VM1.map

rem *** PE2VM2設定
set PE2VM2_OUT=%PE2VM2_ROM_DIR%PE2VM2.elf
set PE2VM2_MAP=%PE2VM2_ROM_DIR%PE2VM2.map

rem *** PE3VM3設定
set PE3VM3_OUT=%PE3VM3_ROM_DIR%PE3VM3.elf
set PE3VM3_MAP=%PE3VM3_ROM_DIR%PE3VM3.map

set X_FILE=CDC_Hypervisor_U2A16.x

echo ***************************************
echo ****** xCreateバッチファイル実行 ******
echo ***************************************

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

goto DATA_ENOUTH

:ERROR_DATA_SHORT
echo.
echo [ERROR]:必要なオブジェクトが不足してます。処理を中断します。
echo.
pause
exit \b

rem xファイル生成に必要なオブジェクトが揃っている場合
:DATA_ENOUTH

rem *** オブジェクトの変換(elf->x)
%GSREC_EXE% %GSREC_OPTION% -o %X_FILE% %HOST_OUT% %PE0VM0_OUT% %PE1VM1_OUT% %PE2VM2_OUT% %PE3VM3_OUT%
if not exist "%X_FILE%" (
    goto ERROR_CONVERT
)

goto CONVERT_COMPLETE

:ERROR_CONVERT
echo.
echo [ERROR]:CDC_Hypervisor_U2A16.x は作成できませんでした。
echo.
REM pause
exit \b

:CONVERT_COMPLETE
echo.
echo [COMPLETE]:CDC_Hypervisor_U2A16.x を作成しました。
echo.

REM pause

@echo on
