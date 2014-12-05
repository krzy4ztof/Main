@echo off
set cur_dir=%CD%
cd "C:\Program Files (x86)\VisualSVN Server"
call vsvnvars.bat
cd %cur_dir%
