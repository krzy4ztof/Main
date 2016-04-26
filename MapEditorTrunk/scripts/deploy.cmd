call clean.cmd

REM create Jar
set TEMP_PATH=%PATH%
set LOCAL_JAVA_HOME=C:\Program Files\Java\jdk1.7.0_67
set PATH=%PATH%;%LOCAL_JAVA_HOME%\bin
cd ../bin
jar -cf ..\target\MapEditor.jar .
cd ../scripts
SET PATH=%TEMP_PATH%

REM copy Resources folder
md ..\target\resources
xcopy ..\resources ..\target\resources /s /e /h /y

REM copy run script
xcopy runJar.cmd ..\target\run.cmd* /y

