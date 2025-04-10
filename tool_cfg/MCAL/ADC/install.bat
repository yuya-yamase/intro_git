@echo OFF
SETLOCAL
 
set TARGET_FUNCTION=ADC
set INPUT_PATH=Output\gen

pushd %~dp0
echo %cd% > install_config.log
call :copyConfig EHVM
call :copyConfig PE0VM0
call :copyConfig PE1VM1
call :copyConfig PE2VM2
call :copyConfig PE3VM3
popd

ENDLOCAL
exit /b

:copyConfig
set TARGET_FOLDER=..\..\..\src\%1\BSW\MCAL\Ren_U2Ax\A16_373\%TARGET_FUNCTION%

set CONFIG_FOLDER=config_
rem VMごとにフォルダが分かれている場合、EHVMまたは各VMフォルダ内を探索する
if exist %1 set CONFIG_FOLDER=%1\config_

if exist "%TARGET_FOLDER%" (
    for /d %%i in (%CONFIG_FOLDER%*) do (
        rem 以下のforはファイルのフルパスをログ出力する為だけの行でループ回数は常に1回
        for /d %%j in (%TARGET_FOLDER%\%%~ni) do (
            echo copy %%~fi\%INPUT_PATH% to %%~fj >> install_config.log
        )
        copy %%~fi\%INPUT_PATH%\* %TARGET_FOLDER%\%%~ni >> install_config.log
    )
) else (
    echo Skip %TARGET_FOLDER% >> install_config.log
)

exit /b

