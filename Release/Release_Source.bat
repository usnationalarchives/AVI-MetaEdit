@echo off

rem --- Clean up ---
del avimetaedit_.tar.bz2
del avimetaedit_Source.tar
del avimetaedit_-1.tar.gz 
del avimetaedit__AllInclusive.7z
rmdir AVI_MetaEdit_Source /S /Q
mkdir AVI_MetaEdit_Source


@rem --- Copying : Sources ---
xcopy ..\Source\*.cpp AVI_MetaEdit_Source\Source\ /S
xcopy ..\Source\*.c AVI_MetaEdit_Source\Source\ /S
xcopy ..\Source\*.h AVI_MetaEdit_Source\Source\ /S
xcopy ..\Source\*.dfm AVI_MetaEdit_Source\Source\ /S
xcopy ..\Source\*.xml AVI_MetaEdit_Source\Source\ /S
xcopy ..\Source\*.rc AVI_MetaEdit_Source\Source\ /S
xcopy ..\Source\*.txt AVI_MetaEdit_Source\Source\ /S
xcopy ..\Source\*.csv AVI_MetaEdit_Source\Source\ /S
xcopy ..\Source\*.ico AVI_MetaEdit_Source\Source\ /S
xcopy ..\Source\Install\AVI_MetaEdit.nsi AVI_MetaEdit_Source\Source\Install\
xcopy ..\Source\*.sh  AVI_MetaEdit_Source\Source\ /S
xcopy ..\Source\*.gif AVI_MetaEdit_Source\Source\ /S
xcopy ..\Source\*.png AVI_MetaEdit_Source\Source\ /S
xcopy ..\Source\*.html AVI_MetaEdit_Source\Source\ /S
xcopy ..\Source\*.qrc AVI_MetaEdit_Source\Source\ /S
xcopy ..\Source\*.bat AVI_MetaEdit_Source\Source\ /S
xcopy ..\Source\*.nsi AVI_MetaEdit_Source\Source\ /S

@rem --- Copying : Projects ---
xcopy ..\Project\*.bpg AVI_MetaEdit_Source\Project\ /S
xcopy ..\Project\*.bpf AVI_MetaEdit_Source\Project\ /S
xcopy ..\Project\*.bpr AVI_MetaEdit_Source\Project\ /S
xcopy ..\Project\*.cpp AVI_MetaEdit_Source\Project\ /S
del ..\Project\MSVC\GUI\_Automated\*.cpp
rmdir ..\Project\MSVC\GUI\_Automated
xcopy ..\Project\*.c AVI_MetaEdit_Source\Project\ /S
xcopy ..\Project\*.h AVI_MetaEdit_Source\Project\ /S
xcopy ..\Project\*.bdsgroup AVI_MetaEdit_Source\Project\ /S
xcopy ..\Project\*.bdsproj AVI_MetaEdit_Source\Project\ /S
xcopy ..\Project\*.dev AVI_MetaEdit_Source\Project\ /S
xcopy ..\Project\*.sln AVI_MetaEdit_Source\Project\ /S
xcopy ..\Project\*.vc AVI_MetaEdit_Source\Project\ /S
xcopy ..\Project\*.vcproj AVI_MetaEdit_Source\Project\ /S
xcopy ..\Project\*.vcxproj AVI_MetaEdit_Source\Project\ /S
xcopy ..\Project\*.vcxproj.filter AVI_MetaEdit_Source\Project\ /S
xcopy ..\Project\*.ico AVI_MetaEdit_Source\Project\ /S
xcopy ..\Project\*.workspace AVI_MetaEdit_Source\Project\ /S
xcopy ..\Project\*.cbp AVI_MetaEdit_Source\Project\ /S
xcopy ..\Project\*.def AVI_MetaEdit_Source\Project\ /S
xcopy ..\Project\*.idl AVI_MetaEdit_Source\Project\ /S
xcopy ..\Project\*.rgs AVI_MetaEdit_Source\Project\ /S
xcopy ..\Project\*.bat AVI_MetaEdit_Source\Project\ /S
xcopy ..\Project\BCB\AVI_MetaEdit*.res AVI_MetaEdit_Source\Project\BCB /S
xcopy ..\Project\MSVC2008\*.rc AVI_MetaEdit_Source\Project\MSVC2008\ /S
xcopy ..\Project\MSVC2010\*.rc AVI_MetaEdit_Source\Project\MSVC2010\ /S
xcopy ..\Project\GNU\* AVI_MetaEdit_Source\Project\GNU\ /S

@rem --- Copying : Release ---
xcopy *.txt AVI_MetaEdit_Source\Release\
xcopy *.bat AVI_MetaEdit_Source\Release\
xcopy *.sh  AVI_MetaEdit_Source\Release\
xcopy *.sub AVI_MetaEdit_Source\Release\
xcopy BCB\*.txt AVI_MetaEdit_Source\Release\BCB\ /S
xcopy MSVC\*.txt AVI_MetaEdit_Source\Release\MSVC\ /S
xcopy GCC_MinGW32\*.txt AVI_MetaEdit_Source\Release\GCC_MinGW32\ /S
xcopy GCC_Linux_i386\*.txt AVI_MetaEdit_Source\Release\GCC_Linux_i386\ /S
xcopy Make_GCC.sh AVI_MetaEdit_Source\Release\

@rem --- Copying : debian ---
xcopy ..\debian\* AVI_MetaEdit_Source\debian\ /S

rem --- Copying : Information files ---
xcopy ..\*.txt AVI_MetaEdit_Source\
xcopy ..\*.html AVI_MetaEdit_Source\
xcopy ..\*.xsd AVI_MetaEdit_Source\

rem --- Copying : Contrib files ---
xcopy ..\Contrib\*.doc AVI_MetaEdit_Source\Contrib\ /S

rem --- Copying : CVS files ---
xcopy ..\*.cvsignore AVI_MetaEdit_Source\


rem --- Compressing Archive ---
if "%2"=="SkipCompression" goto SkipCompression
move AVI_MetaEdit_Source AVI_MetaEdit
..\..\Shared\Binary\Windows_i386\7-zip\7z a -r -ttar -mx9 avimetaedit.tar AVI_MetaEdit\*
..\..\Shared\Binary\Windows_i386\7-zip\7z a -r -tbzip2 -mx9 avimetaedit_.tar.bz2 avimetaedit.tar
..\..\Shared\Binary\Windows_i386\7-zip\7z a -r -tgzip -mx9 avimetaedit_-1.tar.gz avimetaedit.tar
del avimetaedit.tar
move AVI_MetaEdit AVI_MetaEdit_Source
:SkipCompression

rem --- Clean up ---
if "%1"=="SkipCleanUp" goto SkipCleanUp
rmdir AVI_MetaEdit_Source /S /Q
:SkipCleanUp
