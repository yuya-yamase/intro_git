@echo OFF
SETLOCAL ENABLEDELAYEDEXPANSION

rem === バッチファイルのパスに移動
cd /d %~dp0

call ..\build_env.bat

rem === 動作設定
set BUILD_CLEAN=OFF
set OUT_CLEAN=OFF
set NO_PARALLEL= 
set GEN_PP=OFF
set GEN_LIST=OFF
set GEN_OPT=OFF
set TARGET=PE1VM1
set ROMSUM_PARAM=-

rem === 引数チェック
for %%f in (%*) do (
    if "%%f" == "" (
        echo .
    ) else if "%%f" == "clean" (
        set OUT_CLEAN=ON
    ) else if "%%f" == "noparallel" (
        set NO_PARALLEL=-noparallel
    ) else if "%%f" == "build" (
        set BUILD_CLEAN=OFF
    ) else if "%%f" == "rebuild" (
        set BUILD_CLEAN=ON
    ) else if "%%f" == "pp" (
        set GEN_PP=ON
    ) else if "%%f" == "list" (
        set GEN_LIST=ON
    ) else if "%%f" == "opt" (
        set GEN_OPT=ON
    ) else (
        echo .
    )
)

call build_pre.bat

echo ===============================
echo BUILD_CLEAN: %BUILD_CLEAN%
echo OUT_CLEAN: %OUT_CLEAN%
echo NO_PARALLEL: %NO_PARALLEL%
echo GEN_PP: %GEN_PP%
echo GEN_LIST: %GEN_LIST%
echo GEN_OPT: %GEN_OPT%
echo TARGET: %TARGET%
echo ROMSUM_PARAM: %ROMSUM_PARAM%
echo ===============================

if %GEN_OPT%==ON (
    gbuild -top %TARGET%.gpj -cleanfirst -commands -nested_commands %THROUGHPUT_DEFINE% > build_opt.log 2>&1
)

rem === preprocess
if %GEN_PP%==ON (
    if exist pp (
        rmdir /s /q pp
    )
    mkdir pp
    gbuild -cleanfirst -top %TARGET%.gpj -preprocess %THROUGHPUT_DEFINE% > build_pp.log 2>&1
    rem 空行(スペース、タブ、改行コードを含む)削除
    mv obj/*.i pp
    sed -b -i "/^\s*$/d" pp/*.i

    type build_pp.log
)

if %OUT_CLEAN%==ON (
    gbuild -top %TARGET%.gpj -strict -clean %THROUGHPUT_DEFINE% > build.log  2>&1
) else if %BUILD_CLEAN%==ON (
    gbuild -top %TARGET%.gpj %NO_PARALLEL% -strict -cleanfirst %THROUGHPUT_DEFINE% > build.log  2>&1
) else (
    gbuild -top %TARGET%.gpj %NO_PARALLEL% -strict %THROUGHPUT_DEFINE% > build.log  2>&1
)
TYPE build.log

rem === cleaning asm list file
rem ASM行番号がついてる行だけ残す。（28文字目、つまりASM行番号の一桁目が数字）
rem 行頭のアドレス, マシン語, ASM行番号を削除
rem （メモリ配置によって変わるアドレス、行ずれが差分にならないように）
rem アドレスラベルに含まれるアドレス値をマスクする（同上）
rem "--"からはじまる行を削除
rem 空行(スペース、タブ、改行コードを含む)削除
rem ..から行末まで削除。（ファイルパスの..、..lin, ..bof, ..eofとかをつぶすため。
rem .strz の行を削除。（ソースコードのファイルパスが混ざってる）
if %GEN_LIST%==ON (
    if exist lst (
        rmdir /s /q lst
    )
    mkdir lst
    cp obj/*.lst lst/
    rem sed -b -i -n "/^[0-9a-fA-F]\{8\}/p" lst/*.lst
    sed -b -i -n "/^[0-9a-fA-F *]\{27\}[0-9]/p" lst/*.lst
    sed -b -i "s/^[0-9a-fA-F *]\{8,28\}//" lst/*.lst
    sed -b -i -r "s/\.LDW_[0-9a-fA-F]+/\.LDW_xxxxxxxx/" lst/*.lst
    rem sed -b -i -r "/\.\.bof/d" lst/*.lst
    rem sed -b -i -r "/\.\.eof/d" lst/*.lst
    sed -i /^--/d lst/*.lst
    sed -b -i "/^\s*$/d" lst/*.lst
    sed -b -i "s/\.\..*$//" lst/*.lst
    sed -b -i "/\t\.strz/d" lst/*.lst
    
)

call build_post.bat

EXIT /B 0

ENDLOCAL
