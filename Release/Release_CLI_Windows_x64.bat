@rem echo off

@rem --- Clean up ---
del   AVI_MetaEdit_CLI_Windows_x64.zip
rmdir AVI_MetaEdit_CLI_Windows_x64 /S /Q
mkdir AVI_MetaEdit_CLI_Windows_x64

rem --- Copying : Exe ---
xcopy ..\Project\MSVC2010\CLI\x64\Release\avimetaedit.exe AVI_MetaEdit_CLI_Windows_x64\ /S

rem --- Copying : Plugins ---
xcopy ..\Source\Ressource\Plugin\Custom\* AVI_MetaEdit_CLI_Windows_x64\Plugin\Custom\ /S

rem --- Copying : Information files ---
copy ..\License.html AVI_MetaEdit_CLI_Windows_x64\
copy ..\History_CLI.txt AVI_MetaEdit_CLI_Windows_x64\History.txt
copy ..\conformance_point_document.xsd AVI_MetaEdit_CLI_Windows_x64\
copy Readme_CLI_Windows.txt AVI_MetaEdit_CLI_Windows_x64\ReadMe.txt

rem --- Compressing Archive ---
cd AVI_MetaEdit_CLI_Windows_x64\
..\..\..\Shared\Binary\Windows_i386\7-Zip\7z a -r -tzip ..\AVI_MetaEdit_CLI_Windows_x64.zip *
cd ..


rem --- Clean up ---
if "%1"=="SkipCleanUp" goto SkipCleanUp
rmdir AVI_MetaEdit_CLI_Windows_x64\ /S /Q
:SkipCleanUp
