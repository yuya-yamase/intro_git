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

rem *** 非稼働面先頭アドレス
set ROM_B_STA=0x0201C000

rem *** HOST設定
set HOST_OUT=%HOST_ROM_DIR%host.elf
set HOST_MAP=%HOST_ROM_DIR%host.map
set HOST_ROM_STA=0x003C0000
set HOST_ROM_END=0x003FFFFF
set HOST_TEMP=host_temp.mot

rem *** PE0VM0設定
set PE0VM0_OUT=%PE0VM0_ROM_DIR%PE0VM0.elf
set PE0VM0_MAP=%PE0VM0_ROM_DIR%PE0VM0.map
set PE0VM0_ROM_STA=0x00210000
set PE0VM0_ROM_END=0x003BFDFF
rem *** 共有ROM範囲はPadding対象外(0x003BFE00 - 0x003BFE2F)
set PE0VM0_ROM1_STA=0x003BFE30
set PE0VM0_ROM1_END=0x003BFFFF
set PE0VM0_TEMP=vm0_temp.mot

rem *** PE1VM1設定
set PE1VM1_OUT=%PE1VM1_ROM_DIR%PE1VM1.elf
set PE1VM1_MAP=%PE1VM1_ROM_DIR%PE1VM1.map
set PE1VM1_ROM_STA=0x0001C000
set PE1VM1_ROM_END=0x0020FFFF
set PE1VM1_TEMP=vm1_temp.mot

rem *** PE2VM2設定
set PE2VM2_OUT=%PE2VM2_ROM_DIR%PE2VM2.elf
set PE2VM2_MAP=%PE2VM2_ROM_DIR%PE2VM2.map
set PE2VM2_ROM_STA=0x00400000
set PE2VM2_ROM_END=0x005EFFFF
set PE2VM2_TEMP=vm2_temp.mot

rem *** PE3VM3設定
set PE3VM3_OUT=%PE3VM3_ROM_DIR%PE3VM3.elf
set PE3VM3_MAP=%PE3VM3_ROM_DIR%PE3VM3.map
set PE3VM3_ROM_STA=0x005F0000
set PE3VM3_ROM_END=0x007BFDDF
set PE3VM3_TEMP=vm3_temp.mot

set X_FILE=CDC_Hypervisor_U2A16.x
set X_B_FILE=CDC_Hypervisor_U2A16_B.x

echo ***************************************
echo ****** xCreateバッチファイル実行 ******
echo ***************************************

rem *** 成果物収集用フォルダ（OUT）の生成or存在確認 および 古い実行ファイル(*.x)の削除
del %X_FILE%
del %X_B_FILE%
rem '*** テンポラリファイル削除
del *temp.mot
del ..\..\tool\XMerge\*temp.mot

rem *** HVM/rom内のelfファイル存在チェック
if not exist "%HOST_OUT%" (
    echo.
    echo [ERROR]:EHVMのdstフォルダに host.elf が存在しません。処理を中断します。
    echo.
    pause
    exit /b 1
)

rem *** \PE0VM0\dst\内のelfファイル存在チェック
if not exist "%PE0VM0_OUT%" (
    echo.
    echo [ERROR]:PE0VM0のdstフォルダに PE0VM0.elf が存在しません。処理を中断します。
    echo.
    pause
    exit /b 1
)

rem *** \PE1VM1\dst\内のelfファイル存在チェック
if not exist "%PE1VM1_OUT%" (
    echo.
    echo [ERROR]:PE1VM1のdstフォルダに PE1VM1.elf が存在しません。処理を中断します。
    echo.
    pause
    exit /b 1
)

rem *** \PE2VM2\dst\内のelfファイル存在チェック
if not exist "%PE2VM2_OUT%" (
    echo.
    echo [ERROR]:PE2VM2のdstフォルダに PE2VM2.elf が存在しません。処理を中断します。
    echo.
    pause
    exit /b 1
)

rem *** \PE3VM3\dst\内のelfファイル存在チェック
if not exist "%PE3VM3_OUT%" (
    echo.
    echo [ERROR]:PE3VM3のdstフォルダに PE3VM3.elf が存在しません。処理を中断します。
    echo.
    pause
    exit /b 1
)

goto DATA_ENOUTH

:ERROR_DATA_SHORT
echo.
echo [ERROR]:必要なオブジェクトが不足してます。処理を中断します。
echo.
pause
exit /b 1

rem xファイル生成に必要なオブジェクトが揃っている場合
:DATA_ENOUTH


rem *** オブジェクトの変換(elf->x) 非稼働面
%GSREC_EXE% %GSREC_OPTION% -pad1 %HOST_ROM_STA%   %HOST_ROM_END%   0xFF -start %PE1VM1_ROM_STA% -end %PE3VM3_ROM_END% -romaddr %ROM_B_STA% -o %HOST_TEMP%   %HOST_OUT%
%GSREC_EXE% %GSREC_OPTION% -pad1 %PE0VM0_ROM_STA% %PE0VM0_ROM_END% 0xFF -pad1 %PE0VM0_ROM1_STA% %PE0VM0_ROM1_END% 0xFF -start %PE1VM1_ROM_STA% -end %PE3VM3_ROM_END% -romaddr %ROM_B_STA% -o %PE0VM0_TEMP% %PE0VM0_OUT%
%GSREC_EXE% %GSREC_OPTION% -pad1 %PE1VM1_ROM_STA% %PE1VM1_ROM_END% 0xFF -start %PE1VM1_ROM_STA% -end %PE3VM3_ROM_END% -romaddr %ROM_B_STA% -o %PE1VM1_TEMP% %PE1VM1_OUT%
%GSREC_EXE% %GSREC_OPTION% -pad1 %PE2VM2_ROM_STA% %PE2VM2_ROM_END% 0xFF -start %PE1VM1_ROM_STA% -end %PE3VM3_ROM_END% -romaddr %ROM_B_STA% -o %PE2VM2_TEMP% %PE2VM2_OUT%
%GSREC_EXE% %GSREC_OPTION% -pad1 %PE3VM3_ROM_STA% %PE3VM3_ROM_END% 0xFF -start %PE1VM1_ROM_STA% -end %PE3VM3_ROM_END% -romaddr %ROM_B_STA% -o %PE3VM3_TEMP% %PE3VM3_OUT%

copy .\*temp.mot ..\..\tool\XMerge\

rem '*** Sレコードファイルの結合
pushd ..\..\tool\XMerge\
python TargetConbineMOT4TSW.py
move CDC_Hypervisor_U2A16.x CDC_Hypervisor_U2A16_B.x
popd

rem '*** テンポラリファイル削除
del *temp.mot
del ..\..\tool\XMerge\*temp.mot

rem *** オブジェクトの変換(elf->x)
%GSREC_EXE% %GSREC_OPTION% -pad1 %HOST_ROM_STA%   %HOST_ROM_END%   0xFF -o %HOST_TEMP%   %HOST_OUT%
%GSREC_EXE% %GSREC_OPTION% -pad1 %PE0VM0_ROM_STA% %PE0VM0_ROM_END% 0xFF -pad1 %PE0VM0_ROM1_STA% %PE0VM0_ROM1_END% 0xFF -o %PE0VM0_TEMP% %PE0VM0_OUT%
%GSREC_EXE% %GSREC_OPTION% -pad1 %PE1VM1_ROM_STA% %PE1VM1_ROM_END% 0xFF -o %PE1VM1_TEMP% %PE1VM1_OUT%
%GSREC_EXE% %GSREC_OPTION% -pad1 %PE2VM2_ROM_STA% %PE2VM2_ROM_END% 0xFF -o %PE2VM2_TEMP% %PE2VM2_OUT%
%GSREC_EXE% %GSREC_OPTION% -pad1 %PE3VM3_ROM_STA% %PE3VM3_ROM_END% 0xFF -o %PE3VM3_TEMP% %PE3VM3_OUT%

copy .\*temp.mot ..\..\tool\XMerge\

rem '*** Sレコードファイルの結合
pushd ..\..\tool\XMerge\
python TargetConbineMOT4TSW.py
popd

move ..\..\tool\XMerge\*.x .\

rem %GSREC_EXE% %GSREC_OPTION% -pad1 %ROM_STA% %ROM_END% 0xFF -o %X_FILE% %PE0VM0_OUT% %PE1VM1_OUT% %HOST_OUT% %PE2VM2_OUT% %PE3VM3_OUT%
if not exist "%X_FILE%" (
    goto ERROR_CONVERT
)

goto CONVERT_COMPLETE

:ERROR_CONVERT
echo.
echo [ERROR]:CDC_Hypervisor_U2A16.x は作成できませんでした。
echo.
REM pause
exit /b 1

:CONVERT_COMPLETE
echo.
echo [COMPLETE]:CDC_Hypervisor_U2A16.x を作成しました。
echo.

REM pause

rem '*** テンポラリファイル削除
del *temp.mot
del ..\..\tool\XMerge\*temp.mot

exit /b 0
