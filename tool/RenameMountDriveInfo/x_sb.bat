@echo off

set INPUT=%1

net use %INPUT%: /delete
subst %INPUT%: /d
subst %INPUT%: ../..
del *.pif

python RenameMountDriveInfo.py %INPUT%
