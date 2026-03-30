@echo OFF

rmdir /s /q dst
rmdir /s /q obj

del ..\RFP\bin\bs3ckpt_2m_usa_usr*.*
del ..\RFP\bin\bs3ckpt_opbt*.mot
del .\*.log
del Section_Size_*.xlsx
del ..\..\tool\MemAnalysis\*_component.json

rmdir /s /q ..\..\src\DevRRPG\ReprogAPL_Info\env\out\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\EAL\CanIf\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\EAL\CanTrcv\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\EAL\Cdd_Canic_TJA1145A\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\EAL\CodeFlsIf\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\EAL\CodeRamIf\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\EAL\ExtCodeFlsIf\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\EAL\SleepIf\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\EAL\SubMiconIf\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\EAL\UsrSoftIf\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\EAL\WdgIf\obj
del      /q ..\..\src\DevRRPG\ReprogProject\bsw\MCAL\Can\obj\*.*
del      /q ..\..\src\DevRRPG\ReprogProject\bsw\MCAL\CodeFls\obj\*.*
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\MCAL\Dio\obj\libs
del      /q ..\..\src\DevRRPG\ReprogProject\bsw\MCAL\Ecc\obj\*.*
del      /q ..\..\src\DevRRPG\ReprogProject\bsw\MCAL\Gpt\obj\*.*
del      /q ..\..\src\DevRRPG\ReprogProject\bsw\MCAL\Int\obj\*.*
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\MCAL\IntHndlr\obj
del      /q ..\..\src\DevRRPG\ReprogProject\bsw\MCAL\Mcu\obj\*.*
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\MCAL\Port\obj\libs
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\MCAL\SPI\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\MCAL\Vect\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\MCAL\Wdg\obj\libs
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\RTE\Rte\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\SVL\BswM\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\SVL\CanSM\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\SVL\ComM\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\SVL\EcuM\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\SVL\GDN\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\SVL\MemErrM\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\SVL\MemM\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\SVL\PduR\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\SVL\SchM\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\SVL\Shutdown\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\SVL\Startup\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\SVL\Sys\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\SVL\Tm\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\bsw\SVL\WdgM\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\env\out\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\parts\Crc\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\parts\Csm\CryIf\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\parts\Csm\Crypto_83_sw_Dummy\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\parts\Csm\Csm\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\parts\Csm\SchM\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\parts\Csm\WrapCrypto\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\swc\CmpDecmp\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\swc\Decrypt\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\swc\Diag\DiagLib\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\swc\Diag\DiagSrv\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\swc\FscDtct\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\swc\PrgChk\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\swc\RpgEvtHk\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\swc\RpgLib\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\swc\RpgMfr\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\swc\RpgSpp\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\swc\Sec\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\swc\VehInf\obj
rmdir /s /q ..\..\src\DevRRPG\ReprogAPL_Info\env\out
rmdir /s /q ..\..\src\DevRRPG\ReprogProject\env\out
del      /q ..\..\src\DevRRPG\Tool\Converter\*.mot
del      /q ..\..\src\DevRRPG\Tool\Converter\*.log
del      /q ..\..\src\DevRRPG\Tool\Converter\*.bin
del      /q ..\..\src\DevRRPG\Tool\Converter\*.crc
del      /q ..\..\src\DevRRPG\Tool\Converter\*.txt
