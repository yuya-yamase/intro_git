@echo OFF
SETLOCAL ENABLEDELAYEDEXPANSION

call build_cfg.bat

rem ---------------------------------------------------------------------------------------------
rem Target *.mot/x Definition
rem ---------------------------------------------------------------------------------------------
set GHS_MOT_OPB_TRGT=bs3ckpt_opbt
set GHS_MOT_TSW_TGRT=bs3ckpt_usr_tsw.x
set GHS_MOT_RFP_TGRT=%MOT_FILE%

rem ---------------------------------------------------------------------------------------------
echo -------------------------------------------------------------------------------------
echo ghsmot build start : %date%  %time%
echo -------------------------------------------------------------------------------------
echo ------------------------------------------------------------------------------------- >  build.log
echo ghsmot build start : %date%  %time%                                                   >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------

rem === バッチファイルのパスに移動
cd /d %~dp0

set PATH=C:\GHS\RH850_V.R9144\comp_201715;%PATH%
set MOTTR_PY=python ..\..\tool\pyutils\mottr.py

if "%1"=="throughput_on" (
   goto GHS_MOT_THROUGHPUT_EN 
)

echo "-D__AIP_THROUGHPUT__ = 0U"
set GHS_MOT_MACRO=-D__GMM_AIP_THROUGHPUT__=0U
goto GHS_MOT_BUILD

:GHS_MOT_THROUGHPUT_EN 
echo "-D__AIP_THROUGHPUT__ = 1U"
set GHS_MOT_MACRO=-D__GMM_AIP_THROUGHPUT__=1U

:GHS_MOT_BUILD

rem ---------------------------------------------------------------------------------------------
echo -- OPBT --
echo ------------------------------------------------------------------------------------- >> build.log
echo -- OPBT --                                                                            >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------
gbuild -top OPBT\OPBT.gpj -D__GMM_RH850_U2A16_OPBT_CFM_HSM__=0 -strict >> build.log 2>&1
copy OPBT\dst\OPBT.mot RFP\bin\%GHS_MOT_OPB_TRGT%_ac_wo_hsm.mot
rmdir /s /q OPBT\obj
rmdir /s /q OPBT\dst
gbuild -top OPBT\OPBT.gpj -D__GMM_RH850_U2A16_OPBT_CFM_HSM__=1 -strict >> build.log 2>&1
copy OPBT\dst\OPBT.mot RFP\bin\%GHS_MOT_OPB_TRGT%_ac_w__hsm.mot
rmdir /s /q OPBT\obj
rmdir /s /q OPBT\dst
gbuild -top OPBT\OPBT.gpj -D__GMM_RH850_U2A16_OPBT_CFM_HSM__=2 -strict >> build.log 2>&1
copy OPBT\dst\OPBT.mot RFP\bin\%GHS_MOT_OPB_TRGT%_bd_wo_hsm.mot
rmdir /s /q OPBT\obj
rmdir /s /q OPBT\dst

rem ---------------------------------------------------------------------------------------------
echo -- EHVM --
echo ------------------------------------------------------------------------------------- >> build.log
echo -- EHVM --                                                                            >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------
gbuild -top EHVM\EHVM.gpj %GHS_MOT_MACRO% -strict >> build.log 2>&1

rem ---------------------------------------------------------------------------------------------
echo -- PE0VM0 -- 
echo ------------------------------------------------------------------------------------- >> build.log
echo -- PE0VM0 --                                                                          >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------
gbuild -top PE0VM0\PE0VM0.gpj %GHS_MOT_MACRO% -strict >> build.log 2>&1

rem ---------------------------------------------------------------------------------------------
echo -- PE1VM1 --
echo ------------------------------------------------------------------------------------- >> build.log
echo -- PE1VM1 --                                                                          >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------
gbuild -top PE1VM1\PE1VM1.gpj %GHS_MOT_MACRO% -strict >> build.log 2>&1

rem ---------------------------------------------------------------------------------------------
echo -- PE2VM2 --
echo ------------------------------------------------------------------------------------- >> build.log
echo -- PE2VM2 --                                                                          >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------
gbuild -top PE2VM2\PE2VM2.gpj %GHS_MOT_MACRO% -strict >> build.log 2>&1

rem ---------------------------------------------------------------------------------------------
echo -- PE3VM3 --
echo ------------------------------------------------------------------------------------- >> build.log
echo -- PE3VM3 --                                                                          >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------
gbuild -top PE3VM3\PE3VM3.gpj %GHS_MOT_MACRO% -strict >> build.log 2>&1

rem ---------------------------------------------------------------------------------------------
echo -- RpgCAN --
echo ------------------------------------------------------------------------------------- >> build.log
echo -- RpgCAN --                                                                          >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------
gbuild -top ..\..\src\DevRRPG\ReprogAPL_Info\env\Multi_V800\default.gpj -strict >> build.log 2>&1
gbuild -top ..\..\src\DevRRPG\ReprogProject\env\Multi\Multi_V800\default.gpj -strict >> build.log 2>&1

rem ---------------------------------------------------------------------------------------------
echo -- RpgCAN : CRC Generation --
echo ------------------------------------------------------------------------------------- >> build.log
echo -- RpgCAN : CRC Generation --                                                         >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------
echo S0030000FC > RFP\bin\bs3ckpt_usr_tsw.mot
%MOTTR_PY% PE1VM1\dst\PE1VM1_ac.mot RFP\bin\bs3ckpt_usr_tsw.mot
%MOTTR_PY% PE0VM0\dst\PE0VM0_ac.mot RFP\bin\bs3ckpt_usr_tsw.mot
%MOTTR_PY% EHVM\dst\EHVM_ac.mot     RFP\bin\bs3ckpt_usr_tsw.mot
%MOTTR_PY% PE2VM2\dst\PE2VM2_ac.mot RFP\bin\bs3ckpt_usr_tsw.mot
%MOTTR_PY% PE3VM3\dst\PE3VM3_ac.mot RFP\bin\bs3ckpt_usr_tsw.mot
%MOTTR_PY% ..\..\src\DevRRPG\ReprogAPL_Info\env\out\Info_Full.run RFP\bin\bs3ckpt_usr_tsw.mot
echo S70500000000FA >> RFP\bin\bs3ckpt_usr_tsw.mot

copy RFP\bin\bs3ckpt_usr_tsw.mot ..\..\src\DevRRPG\Tool\Converter\bs3ckpt_usr_tsw.mot
pushd ..\..\src\DevRRPG\Tool\Converter
python ReprogTargetConverter.py > convert.log 2>&1
popd
type ..\..\src\DevRRPG\Tool\Converter\convert.log >> build.log

rem ---------------------------------------------------------------------------------------------
echo -- %GHS_MOT_TSW_TGRT% --
echo ------------------------------------------------------------------------------------- >> build.log
echo -- %GHS_MOT_TSW_TGRT% --                                                              >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------
echo S0030000FC > RFP\bin\%GHS_MOT_TSW_TGRT%
%MOTTR_PY% RFP\bin\bs3ckpt_usr_tsw.mot RFP\bin\%GHS_MOT_TSW_TGRT%
%MOTTR_PY% ..\..\src\DevRRPG\ReprogProject\env\out\Reprog_SBL.run RFP\bin\%GHS_MOT_TSW_TGRT%
echo S70500000000FA >> RFP\bin\%GHS_MOT_TSW_TGRT%

rem ---------------------------------------------------------------------------------------------
echo -- %GHS_MOT_RFP_TGRT% --
echo ------------------------------------------------------------------------------------- >> build.log
echo -- %GHS_MOT_RFP_TGRT% --                                                              >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
echo S0030000FC > RFP\bin\%GHS_MOT_RFP_TGRT%
%MOTTR_PY% ..\..\src\DevRRPG\ReprogProject\env\out\Reprog.run RFP\bin\%GHS_MOT_RFP_TGRT%
%MOTTR_PY% ..\..\src\DevRRPG\ReprogAPL_Info\env\out\Keyword_OK.run RFP\bin\%GHS_MOT_RFP_TGRT%
%MOTTR_PY% RFP\bin\bs3ckpt_usr_tsw.mot RFP\bin\%GHS_MOT_RFP_TGRT%
del /q RFP\bin\bs3ckpt_usr_tsw.mot

%MOTTR_PY% ..\..\src\DevRRPG\ReprogProject\env\out\Reprog_B.run RFP\bin\%GHS_MOT_RFP_TGRT%
%MOTTR_PY% ..\..\src\DevRRPG\ReprogAPL_Info\env\out\Keyword_OK_B.run RFP\bin\%GHS_MOT_RFP_TGRT%
%MOTTR_PY% PE1VM1\dst\PE1VM1_bd.mot RFP\bin\%GHS_MOT_RFP_TGRT%
%MOTTR_PY% PE0VM0\dst\PE0VM0_bd.mot RFP\bin\%GHS_MOT_RFP_TGRT%
%MOTTR_PY% EHVM\dst\EHVM_bd.mot     RFP\bin\%GHS_MOT_RFP_TGRT%
%MOTTR_PY% PE2VM2\dst\PE2VM2_bd.mot RFP\bin\%GHS_MOT_RFP_TGRT%
%MOTTR_PY% PE3VM3\dst\PE3VM3_bd.mot RFP\bin\%GHS_MOT_RFP_TGRT%
%MOTTR_PY% ..\..\src\DevRRPG\ReprogAPL_Info\env\out\Info_Full_B.run RFP\bin\%GHS_MOT_RFP_TGRT%
echo S70500000000FA >> RFP\bin\%GHS_MOT_RFP_TGRT%

copy ..\..\src\PE0VM0\BSW\Aubist\CycurHSM\ecy_hsm_RH850_GHS_D7_DM\bin\HSM.hex RFP\bin\cychsm_v2716_rfp_ac.hex
copy ..\..\src\PE0VM0\BSW\Aubist\CycurHSM\ecy_hsm_RH850_GHS_D7_DM\bin\HSM_B.hex RFP\bin\cychsm_v2716_rfp_bd.hex

rem ---------------------------------------------------------------------------------------------
echo -- Generate Binary from ELF files --
echo ------------------------------------------------------------------------------------- >> build.log
echo -- Generate Binary from ELF files --                                                 >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------
gmemfile -fill1 0x00210000 0x003bffff 0xff -start 0x00210000 -end 0x003bffff -o PE0VM0\dst\PE0VM0_ac.bin PE0VM0\dst\PE0VM0.elf
gmemfile -fill1 0x0001c000 0x0020ffff 0xff -start 0x0001c000 -end 0x0020ffff -o PE1VM1\dst\PE1VM1_ac.bin PE1VM1\dst\PE1VM1.elf
gmemfile -fill1 0x00400000 0x005effff 0xff -start 0x00400000 -end 0x005effff -o PE2VM2\dst\PE2VM2_ac.bin PE2VM2\dst\PE2VM2.elf
gmemfile -fill1 0x005f0000 0x007bfddf 0xff -start 0x005f0000 -end 0x007bfddf -o PE3VM3\dst\PE3VM3_ac.bin PE3VM3\dst\PE3VM3.elf
gmemfile -fill1 0x003c0000 0x003fffff 0xff -start 0x003c0000 -end 0x003fffff -o EHVM\dst\EHVM_ac.bin EHVM\dst\EHVM.elf
gmemfile -fill2 0x007BFDE0 0x007BFDFF 0x5AA5 -fill1 0x007BFE00 0x007BFFFF 0xFF -start 0x007BFDE0 -end 0x007BFFFF -o ..\..\src\DevRRPG\ReprogAPL_Info\env\out\Info_Full.bin ..\..\src\DevRRPG\ReprogAPL_Info\env\out\ReprogAPL.elf

rem ---------------------------------------------------------------------------------------------
echo -- Concatenate Binary files --
echo ------------------------------------------------------------------------------------- >> build.log
echo -- Concatenate Binary files --                                                       >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------

copy /b PE1VM1\dst\PE1VM1_ac.bin + PE0VM0\dst\PE0VM0_ac.bin + EHVM\dst\EHVM_ac.bin + PE2VM2\dst\PE2VM2_ac.bin + PE3VM3\dst\PE3VM3_ac.bin + ..\..\src\DevRRPG\ReprogAPL_Info\env\out\Info_Full.bin RFP\bin\b3ckpt_usr_ac_wo_header.bin

rem ---------------------------------------------------------------------------------------------
echo -- Calculate CRC32 for b3ckpt_usr_ac_wo_header.bin --
echo ------------------------------------------------------------------------------------- >> build.log
echo -- Calculate CRC32 for b3ckpt_usr_ac_wo_header.bin --                                >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------
python ..\..\src\USBRPG\Tool\update_crc_and_build.py RFP\bin\b3ckpt_usr_ac_wo_header.bin
python ..\..\src\USBRPG\Tool\update_crc_and_build.py RFP\bin\b3ckpt_usr_ac_wo_header.bin >> build.log
rem ---------------------------------------------------------------------------------------------
echo -- USBRPG --
echo ------------------------------------------------------------------------------------- >> build.log
echo -- USBRPG --                                                                          >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------
gbuild -top USBRPG\USBRPG.gpj -D__GMM_RH850_U2A16_USBRPG_CFM_HSM__=0 -strict >> build.log 2>&1
if %ERRORLEVEL% neq 0 (echo [ERROR] USBRPG build failed & echo [ERROR] USBRPG build failed >> build.log) else (echo [OK] USBRPG build completed & echo [OK] USBRPG build completed >> build.log)

rem Wait for file to be released
timeout /t 1 /nobreak > nul

rem Verify USBRPG.bin exists
if not exist "USBRPG\dst\USBRPG.bin" (
    echo [ERROR] USBRPG.bin not found
    echo [ERROR] USBRPG.bin not found >> build.log
    goto END_BUILD
)

rem ---------------------------------------------------------------------------------------------
echo -- Generate Final Binary with USBRPG Header --
echo ------------------------------------------------------------------------------------- >> build.log
echo -- Generate Final Binary with USBRPG Header --                                       >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------
copy /b USBRPG\dst\USBRPG.bin + RFP\bin\b3ckpt_usr_ac_wo_header.bin RFP\bin\b3ckpt_usr_ac.bin

rem ---------------------------------------------------------------------------------------------
@echo OFF
echo -- Step: Calculate ROM/RAM  --
set "current=%cd%"
rem ---------------------------------------------------------------------------------------------

REM 上位フォルダ名を取得
for %%a in ("%current%") do set "foldername=%%~nxa"

REM 最後の8文字を取得
set "last8=%foldername:~-8%"
echo selected_variation: %last8%

pushd ..\..\tool\MemAnalysis
python SectionAnalysis.py %last8%
move "Section_Size_EHVM.xlsx" "%current%\EHVM"
move "Section_Size_PE0VM0.xlsx" "%current%\PE0VM0"
move "Section_Size_PE1VM1.xlsx" "%current%\PE1VM1"
move "Section_Size_PE2VM2.xlsx" "%current%\PE2VM2"
move "Section_Size_PE3VM3.xlsx" "%current%\PE3VM3"
popd

rem ---------------------------------------------------------------------------------------------
echo -------------------------------------------------------------------------------------
echo ghsmot build finish : %date%  %time%
echo -------------------------------------------------------------------------------------
echo ------------------------------------------------------------------------------------- >> build.log
echo ghsmot build finish : %date%  %time%                                                  >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------

pause

ENDLOCAL
