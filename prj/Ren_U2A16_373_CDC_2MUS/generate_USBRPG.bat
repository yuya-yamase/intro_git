@echo OFF

rem === バッチファイルのパスに移動
cd /d %~dp0

set PATH=C:\GHS\RH850_V.R9144\comp_201715;%PATH%

rem ---------------------------------------------------------------------------------------------
echo -- Generate Binary from ELF files --
echo ------------------------------------------------------------------------------------- >> build.log
echo -- Generate Binary from ELF files --                                                 >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------
gmemfile -fill1 0x00210000 0x003bffff 0xff -start 0x00210000 -end 0x003bffff -o dst\pe0vm0_ac.bin dst\pe0vm0.elf
gmemfile -fill1 0x00020000 0x0020ffff 0xff -start 0x00020000 -end 0x0020ffff -o dst\pe1vm1_ac.bin dst\pe1vm1.elf
gmemfile -fill1 0x00400000 0x005effff 0xff -start 0x00400000 -end 0x005effff -o dst\pe2vm2_ac.bin dst\pe2vm2.elf
gmemfile -fill1 0x005f0000 0x007bfddf 0xff -start 0x005f0000 -end 0x007bfddf -o dst\pe3vm3_ac.bin dst\pe3vm3.elf
gmemfile -fill1 0x003c0000 0x003fffff 0xff -start 0x003c0000 -end 0x003fffff -o dst\ehvm_ac.bin dst\ehvm.elf
gmemfile -fill2 0x007BFDE0 0x007BFDFF 0x5AA5 -fill1 0x007BFE00 0x007BFFFF 0xFF -start 0x007BFDE0 -end 0x007BFFFF -o ..\..\src\DevRRPG\ReprogAPL_Info\env\out\Info_Full.bin ..\..\src\DevRRPG\ReprogAPL_Info\env\out\ReprogAPL.elf

rem ---------------------------------------------------------------------------------------------
echo -- Concatenate Binary files --
echo ------------------------------------------------------------------------------------- >> build.log
echo -- Concatenate Binary files --                                                       >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------

copy /b dst\pe1vm1_ac.bin + dst\pe0vm0_ac.bin + dst\ehvm_ac.bin + dst\pe2vm2_ac.bin + dst\pe3vm3_ac.bin + ..\..\src\DevRRPG\ReprogAPL_Info\env\out\Info_Full.bin ..\RFP\bin\b3ckpt_usr_ac_wo_header.bin

rem ---------------------------------------------------------------------------------------------
echo -- Calculate CRC32 for b3ckpt_usr_ac_wo_header.bin --
echo ------------------------------------------------------------------------------------- >> build.log
echo -- Calculate CRC32 for b3ckpt_usr_ac_wo_header.bin --                                >> build.log
echo ------------------------------------------------------------------------------------- >> build.log
rem ---------------------------------------------------------------------------------------------
python ..\..\src\USBRPG\Tool\update_crc_and_build.py ..\RFP\bin\b3ckpt_usr_ac_wo_header.bin
python ..\..\src\USBRPG\Tool\update_crc_and_build.py ..\RFP\bin\b3ckpt_usr_ac_wo_header.bin >> build.log
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
copy /b USBRPG\dst\USBRPG.bin + ..\RFP\bin\b3ckpt_usr_ac_wo_header.bin ..\RFP\bin\%1
