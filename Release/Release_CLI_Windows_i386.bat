@rem echo off

@rem --- Clean up ---
del   AVI_MetaEdit_CLI_Windows_i386.zip
rmdir AVI_MetaEdit_CLI_Windows_i386 /S /Q
mkdir AVI_MetaEdit_CLI_Windows_i386

rem --- Copying : Exe ---
xcopy ..\Project\MSVC2010\CLI\Win32\Release\avimetaedit.exe AVI_MetaEdit_CLI_Windows_i386\ /S

rem --- Copying : Plugins ---
xcopy ..\Source\Ressource\Plugin\Custom\* AVI_MetaEdit_CLI_Windows_i386\Plugin\Custom\ /S

rem --- Copying : Information files ---
copy ..\License.html AVI_MetaEdit_CLI_Windows_i386\
copy ..\History_CLI.txt AVI_MetaEdit_CLI_Windows_i386\History.txt
copy ..\conformance_point_document.xsd AVI_MetaEdit_CLI_Windows_i386\
copy Readme_CLI_Windows.txt AVI_MetaEdit_CLI_Windows_i386\ReadMe.txt

rem --- Compressing Archive ---
cd AVI_MetaEdit_CLI_Windows_i386\
..\..\..\Shared\Binary\Windows_i386\7-Zip\7z a -r -tzip ..\AVI_MetaEdit_CLI_Windows_i386.zip *
cd ..


rem --- Clean up ---
if "%1"=="SkipCleanUp" goto SkipCleanUp
rmdir AVI_MetaEdit_CLI_Windows_i386\ /S /Q
:SkipCleanUp
