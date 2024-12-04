@echo off
set PATH=%PATH%;c:\winAMS\bin
if %1=="" Exit
set GAIO_LOC=%~dp1
set GAIO_PRJ=%~nx1
set OUTPUT_FOLDER=%~dp0TestOutput

echo -------------------------------------------------------
echo  Start RIM parameter test
echo -------------------------------------------------------
mkdir "%OUTPUT_FOLDER%"
del /S /F /Q %OUTPUT_FOLDER%\*
mkdir "%GAIO_LOC%TestCsv\RimCsv"
mkdir "%GAIO_LOC%TestOutput\RimCsv"
mkdir "%GAIO_LOC%TestResult"
copy /Y "%~dp0TestCsv\" "%GAIO_LOC%TestCsv\RimCsv\"
rem "
cd /D "%GAIO_LOC%"
echo %date% %time% > "%OUTPUT_FOLDER%\log.txt"

echo -------------------------------------------------------
echo  Start SST Manager
echo -------------------------------------------------------
REM 1st Test
echo Executing 1st test
sstmanager -b -e -runS -output .\TestOutput\RimCsv -testCsv .\TestCsv\RimCsv\RimTest1.csv -xmlex .\TestResult\RimTest1st.amsyr "%GAIO_PRJ%"
copy /Y .\TestOutput\RimCsv\テスト結果報告書.htm "%OUTPUT_FOLDER%\TestSummary1st.htm"
copy /Y .\TestResult\RimTest1st.amsyr "%OUTPUT_FOLDER%\RimTest1st.amsyr"
type "%GAIO_LOC%AmsErrorLog.txt" >> "%OUTPUT_FOLDER%\log.txt"
del /F /Q .\TestResult\RimTest1st.amsyr

REM 2nd Test
echo Executing 2nd test
sstmanager -b -e -runS -output .\TestOutput\RimCsv -testCsv .\TestCsv\RimCsv\RimTest2.csv -xmlex .\TestResult\RimTest2nd.amsyr "%GAIO_PRJ%"
copy /Y .\TestOutput\RimCsv\テスト結果報告書.htm "%OUTPUT_FOLDER%\TestSummary2nd.htm"
copy /Y .\TestResult\RimTest2nd.amsyr "%OUTPUT_FOLDER%\RimTest2nd.amsyr"
type "%GAIO_LOC%AmsErrorLog.txt" >> "%OUTPUT_FOLDER%\log.txt"
del /F /Q .\TestResult\RimTest2nd.amsyr

echo -------------------------------------------------------
echo  Show test result
echo -------------------------------------------------------
copy /Y "%GAIO_LOC%TestOutput\RimCsv\*.csv" "%OUTPUT_FOLDER%\"
rem "
rmdir /s /q "%GAIO_LOC%TestCsv\RimCsv"
rmdir /s /q "%GAIO_LOC%TestOutput\RimCsv"
rmdir /s /q "%GAIO_LOC%TestResult"
"%OUTPUT_FOLDER%\TestSummary1st.htm"
"%OUTPUT_FOLDER%\TestSummary2nd.htm"
