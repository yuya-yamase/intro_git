@echo OFF
SETLOCAL ENABLEDELAYEDEXPANSION

rem === バッチファイルのパスに移動
cd /d %~dp0

echo ---------------------------------------
echo POST BUILD Start

rem
rem ROMSUMコード埋め込み実施
if not %ROMSUM_PARAM% == - (
    java -jar ..\..\RomSumTool\XssRomSum.jar -i %TARGET%.run -o %TARGET%_filled.run -p %ROMSUM_PARAM%
)
echo POST BUILD End
echo ---------------------------------------
