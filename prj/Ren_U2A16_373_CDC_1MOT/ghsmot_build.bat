@echo OFF
SETLOCAL ENABLEDELAYEDEXPANSION

call build_cfg.bat

rem ---------------------------------------------------------------------------------------------
rem Target *.mot/x Definition
rem ---------------------------------------------------------------------------------------------
set GHS_MOT_OPB_TRGT=..\RFP\bin\bs3ckpt_opbt
set GHS_MOT_TSW_TRGT=..\RFP\bin\bs3ckpt_1m_oth_usr_tsw
set GHS_MOT_OTA_TRGT=..\RFP\bin\bs3ckpt_1m_oth_usr_ota
set GHS_MOT_RFP_TRGT=..\RFP\bin\%MOT_FILE%
set GHS_MOT_HSM_TRGT=..\RFP\bin\cychsm_v2716_rfp

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
gbuild -top opbt.gpj -D__GMM_RH850_U2A16_OPBT_CFM_HSM__=0 -strict >> build.log 2>&1
copy dst\opbt.mot %GHS_MOT_OPB_TRGT%_ac_wo_hsm.mot
rmdir /s /q obj\opbt
rmdir /s /q dst
gbuild -top opbt.gpj -D__GMM_RH850_U2A16_OPBT_CFM_HSM__=1 -strict >> build.log 2>&1
copy dst\opbt.mot %GHS_MOT_OPB_TRGT%_ac_w__hsm.mot
rmdir /s /q obj\opbt
rmdir /s /q dst
gbuild -top opbt.gpj -D__GMM_RH850_U2A16_OPBT_CFM_HSM__=2 -strict >> build.log 2>&1
copy dst\opbt.mot %GHS_MOT_OPB_TRGT%_bd_wo_hsm.mot
rmdir /s /q obj\opbt
rmdir /s /q dst

rem ---------------------------------------------------------------------------------------------
echo -- EHVM --
echo ------------------------------------------------------------------------------------- >> build.log
echo -- EHVM --                                                                            >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------
gbuild -top ehvm.gpj %GHS_MOT_MACRO% -strict >> build.log 2>&1

rem ---------------------------------------------------------------------------------------------
echo -- PE0VM0 -- 
echo ------------------------------------------------------------------------------------- >> build.log
echo -- PE0VM0 --                                                                          >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------
gbuild -top pe0vm0.gpj %GHS_MOT_MACRO% -strict >> build.log 2>&1

rem ---------------------------------------------------------------------------------------------
echo -- PE1VM1 --
echo ------------------------------------------------------------------------------------- >> build.log
echo -- PE1VM1 --                                                                          >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------
gbuild -top pe1vm1.gpj %GHS_MOT_MACRO% -strict >> build.log 2>&1

rem ---------------------------------------------------------------------------------------------
echo -- PE2VM2 --
echo ------------------------------------------------------------------------------------- >> build.log
echo -- PE2VM2 --                                                                          >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------
gbuild -top pe2vm2.gpj %GHS_MOT_MACRO% -strict >> build.log 2>&1

rem ---------------------------------------------------------------------------------------------
echo -- PE3VM3 --
echo ------------------------------------------------------------------------------------- >> build.log
echo -- PE3VM3 --                                                                          >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------
gbuild -top pe3vm3.gpj %GHS_MOT_MACRO% -strict >> build.log 2>&1

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
echo S0030000FC > dst\bs3ckpt_usr_tsw.mot
%MOTTR_PY% dst\pe1vm1_ac.mot dst\bs3ckpt_usr_tsw.mot
%MOTTR_PY% dst\pe0vm0_ac.mot dst\bs3ckpt_usr_tsw.mot
%MOTTR_PY% dst\ehvm_ac.mot   dst\bs3ckpt_usr_tsw.mot
%MOTTR_PY% dst\pe2vm2_ac.mot dst\bs3ckpt_usr_tsw.mot
%MOTTR_PY% dst\pe3vm3_ac.mot dst\bs3ckpt_usr_tsw.mot
%MOTTR_PY% ..\..\src\DevRRPG\ReprogAPL_Info\env\out\Info_Full.run dst\bs3ckpt_usr_tsw.mot
echo S70500000000FA >> dst\bs3ckpt_usr_tsw.mot

echo S0030000FC > dst\bs3ckpt_usr_ota.mot
%MOTTR_PY% dst\bs3ckpt_usr_tsw.mot dst\bs3ckpt_usr_ota.mot
%MOTTR_PY% ..\..\src\DevRRPG\ReprogAPL_Info\env\out\FpSig.run dst\bs3ckpt_usr_ota.mot
echo S70500000000FA >> dst\bs3ckpt_usr_ota.mot

copy dst\bs3ckpt_usr_tsw.mot ..\..\src\DevRRPG\Tool\Converter\bs3ckpt_usr_tsw.mot
copy dst\bs3ckpt_usr_ota.mot ..\..\src\DevRRPG\Tool\Converter\bs3ckpt_usr_ota.mot
pushd ..\..\src\DevRRPG\Tool\Converter
python ReprogTargetConverter.py > convert.log 2>&1
popd
type ..\..\src\DevRRPG\Tool\Converter\convert.log >> build.log
copy ..\..\src\DevRRPG\Tool\Converter\bs3ckpt_usr_ota.bin %GHS_MOT_OTA_TRGT%.bin
copy ..\..\src\DevRRPG\Tool\Converter\bs3ckpt_usr_ota.crc %GHS_MOT_OTA_TRGT%.crc

rem ---------------------------------------------------------------------------------------------
echo -- %GHS_MOT_TSW_TRGT%.x --
echo ------------------------------------------------------------------------------------- >> build.log
echo -- %GHS_MOT_TSW_TRGT%.x --                                                            >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------
echo S0030000FC > %GHS_MOT_TSW_TRGT%.x
%MOTTR_PY% dst\bs3ckpt_usr_tsw.mot %GHS_MOT_TSW_TRGT%.x
%MOTTR_PY% ..\..\src\DevRRPG\ReprogProject\env\out\Reprog_SBL.run %GHS_MOT_TSW_TRGT%.x
echo S70500000000FA >> %GHS_MOT_TSW_TRGT%.x

rem ---------------------------------------------------------------------------------------------
echo -- %GHS_MOT_RFP_TRGT%.mot --
echo ------------------------------------------------------------------------------------- >> build.log
echo -- %GHS_MOT_RFP_TRGT%.mot --                                                          >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
echo S0030000FC > %GHS_MOT_RFP_TRGT%.mot
%MOTTR_PY% ..\..\src\DevRRPG\ReprogProject\env\out\Reprog.run %GHS_MOT_RFP_TRGT%.mot
%MOTTR_PY% ..\..\src\DevRRPG\ReprogAPL_Info\env\out\Keyword_OK.run %GHS_MOT_RFP_TRGT%.mot
%MOTTR_PY% dst\bs3ckpt_usr_ota.mot %GHS_MOT_RFP_TRGT%.mot

%MOTTR_PY% ..\..\src\DevRRPG\ReprogProject\env\out\Reprog_B.run %GHS_MOT_RFP_TRGT%.mot
%MOTTR_PY% ..\..\src\DevRRPG\ReprogAPL_Info\env\out\Keyword_OK_B.run %GHS_MOT_RFP_TRGT%.mot
%MOTTR_PY% dst\pe1vm1_bd.mot %GHS_MOT_RFP_TRGT%.mot
%MOTTR_PY% dst\pe0vm0_bd.mot %GHS_MOT_RFP_TRGT%.mot
%MOTTR_PY% dst\ehvm_bd.mot   %GHS_MOT_RFP_TRGT%.mot
%MOTTR_PY% dst\pe2vm2_bd.mot %GHS_MOT_RFP_TRGT%.mot
%MOTTR_PY% dst\pe3vm3_bd.mot %GHS_MOT_RFP_TRGT%.mot
%MOTTR_PY% ..\..\src\DevRRPG\ReprogAPL_Info\env\out\Info_Full_B.run %GHS_MOT_RFP_TRGT%.mot
%MOTTR_PY% ..\..\src\DevRRPG\ReprogAPL_Info\env\out\FpSig_B.run %GHS_MOT_RFP_TRGT%.mot
echo S70500000000FA >> %GHS_MOT_RFP_TRGT%.mot

if not exist %GHS_MOT_HSM_TRGT%_ac.hex ( 
    copy ..\..\src\PE0VM0\BSW\Aubist\CycurHSM\ecy_hsm_RH850_GHS_D7_DM\bin\HSM.hex   %GHS_MOT_HSM_TRGT%_ac.hex
)
if not exist %GHS_MOT_HSM_TRGT%_bd.hex ( 
    copy ..\..\src\PE0VM0\BSW\Aubist\CycurHSM\ecy_hsm_RH850_GHS_D7_DM\bin\HSM_B.hex %GHS_MOT_HSM_TRGT%_bd.hex
)

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
move "*.xlsx" "%current%"
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
