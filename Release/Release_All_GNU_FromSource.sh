#! /bin/sh

#-----------------------------------------------------------------------
# Clean up
test -e AVI_MetaEdit_GNU_FromSource.tar     && rm    AVI_MetaEdit_GNU_FromSource.tar
test -e AVI_MetaEdit_GNU_FromSource.tar.bz2 && rm    AVI_MetaEdit_GNU_FromSource.tar.bz2
test -d AVI_MetaEdit_GNU_FromSource         && rm -r AVI_MetaEdit_GNU_FromSource
mkdir AVI_MetaEdit_GNU_FromSource


#-----------------------------------------------------------------------
# Preparing : Project
cd ../Project/GNU/CLI
chmod u+x autogen
./autogen
cd ../../../Release
cd ../Project/GNU/GUI
chmod u+x autogen
./autogen
cd ../../../Release


#-----------------------------------------------------------------------
# Copying : Project
mkdir -p AVI_MetaEdit_GNU_FromSource/Project/GNU/CLI
cp ../Project/GNU/CLI/aclocal.m4 AVI_MetaEdit_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/autogen AVI_MetaEdit_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/config.guess AVI_MetaEdit_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/config.sub AVI_MetaEdit_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/configure AVI_MetaEdit_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/configure.ac AVI_MetaEdit_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/depcomp AVI_MetaEdit_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/install-sh AVI_MetaEdit_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/Makefile.am AVI_MetaEdit_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/Makefile.in AVI_MetaEdit_GNU_FromSource/Project/GNU/CLI/
cp ../Project/GNU/CLI/missing AVI_MetaEdit_GNU_FromSource/Project/GNU/CLI/
mkdir -p AVI_MetaEdit_GNU_FromSource/Project/GNU/GUI
cp ../Project/GNU/GUI/aclocal.m4 AVI_MetaEdit_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/autogen AVI_MetaEdit_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/config.guess AVI_MetaEdit_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/config.sub AVI_MetaEdit_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/configure AVI_MetaEdit_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/configure.ac AVI_MetaEdit_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/depcomp AVI_MetaEdit_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/install-sh AVI_MetaEdit_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/Makefile.am AVI_MetaEdit_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/Makefile.in AVI_MetaEdit_GNU_FromSource/Project/GNU/GUI/
cp ../Project/GNU/GUI/missing AVI_MetaEdit_GNU_FromSource/Project/GNU/GUI/

#-----------------------------------------------------------------------
# Copying : Source
mkdir -p AVI_MetaEdit_GNU_FromSource/Source/CLI
cp -r ../Source/CLI/*.h AVI_MetaEdit_GNU_FromSource/Source/CLI/
cp -r ../Source/CLI/*.cpp AVI_MetaEdit_GNU_FromSource/Source/CLI/
mkdir -p AVI_MetaEdit_GNU_FromSource/Source/Common
cp -r ../Source/Common/*.h AVI_MetaEdit_GNU_FromSource/Source/Common/
cp -r ../Source/Common/*.cpp AVI_MetaEdit_GNU_FromSource/Source/Common/
mkdir -p AVI_MetaEdit_GNU_FromSource/Source/GUI/Qt
cp -r ../Source/GUI/Qt/*.h AVI_MetaEdit_GNU_FromSource/Source/GUI/Qt/
cp -r ../Source/GUI/Qt/*.cpp AVI_MetaEdit_GNU_FromSource/Source/GUI/Qt/
mkdir -p AVI_MetaEdit_GNU_FromSource/Source/MD5
cp -r ../Source/MD5/*.h AVI_MetaEdit_GNU_FromSource/Source/MD5/
cp -r ../Source/MD5/*.c AVI_MetaEdit_GNU_FromSource/Source/MD5/
mkdir -p AVI_MetaEdit_GNU_FromSource/Source/Resource
cp -r ../Source/Resource/*.qrc AVI_MetaEdit_GNU_FromSource/Source/Resource/
cp -r ../Source/Resource/*.html AVI_MetaEdit_GNU_FromSource/Source/Resource/
mkdir -p AVI_MetaEdit_GNU_FromSource/Source/Resource/Image/Menu
cp -r ../Source/Resource/Image/Menu/*.png AVI_MetaEdit_GNU_FromSource/Source/Resource/Image/Menu/
mkdir -p AVI_MetaEdit_GNU_FromSource/Source/Resource/Image/FADGI
cp -r ../Source/Resource/Image/FADGI/*.png AVI_MetaEdit_GNU_FromSource/Source/Resource/Image/FADGI/
mkdir -p AVI_MetaEdit_GNU_FromSource/Source/Resource/Documentation
cp -r ../Source/Resource/Documentation/*.html AVI_MetaEdit_GNU_FromSource/Source/Resource/Documentation/
mkdir -p AVI_MetaEdit_GNU_FromSource/Source/Riff
cp -r ../Source/Riff/*.h AVI_MetaEdit_GNU_FromSource/Source/Riff/
cp -r ../Source/Riff/*.cpp AVI_MetaEdit_GNU_FromSource/Source/Riff/
mkdir -p AVI_MetaEdit_GNU_FromSource/Source/TinyXml
cp -r ../Source/TinyXml/*.h AVI_MetaEdit_GNU_FromSource/Source/TinyXml/
cp -r ../Source/TinyXml/*.cpp AVI_MetaEdit_GNU_FromSource/Source/TinyXml/
mkdir -p AVI_MetaEdit_GNU_FromSource/Source/ZenLib
cp -r ../Source/ZenLib/*.h AVI_MetaEdit_GNU_FromSource/Source/ZenLib/
cp -r ../Source/ZenLib/*.cpp AVI_MetaEdit_GNU_FromSource/Source/ZenLib/

#-----------------------------------------------------------------------
# Copying : Release
mkdir -p AVI_MetaEdit_GNU_FromSource/Release
cp *.sub AVI_MetaEdit_GNU_FromSource/Release/
cp *.sh AVI_MetaEdit_GNU_FromSource/Release/
chmod u+x AVI_MetaEdit_GNU_FromSource/Release/*.sh

#-----------------------------------------------------------------------
# Copying : Information
cp ../License.html AVI_MetaEdit_GNU_FromSource/
cp ../History*.txt AVI_MetaEdit_GNU_FromSource/
cp ../conformance_point_document.xsd AVI_MetaEdit_GNU_FromSource/
dos2unix AVI_MetaEdit_GNU_FromSource/History*.txt
cp ReadMe_CLI_Linux.txt AVI_MetaEdit_GNU_FromSource/Release/
cp ReadMe_CLI_Mac.txt AVI_MetaEdit_GNU_FromSource/Release/
cp ReadMe_GUI_Linux.txt AVI_MetaEdit_GNU_FromSource/Release/
cp ReadMe_GUI_Mac.txt AVI_MetaEdit_GNU_FromSource/Release/


#-----------------------------------------------------------------------
# Preparing Archive : AVI_MetaEdit
mv AVI_MetaEdit_GNU_FromSource AVI_MetaEdit

#-----------------------------------------------------------------------
# Preparing Archive : Automation
cp ../Project/GNU/CLI/AddThisToRoot_CLI_compile.sh AVI_MetaEdit/CLI_Compile.sh
chmod u+x AVI_MetaEdit/CLI_Compile.sh
cp ../Project/GNU/GUI/AddThisToRoot_GUI_compile.sh AVI_MetaEdit/GUI_Compile.sh
chmod u+x AVI_MetaEdit/GUI_Compile.sh


#-----------------------------------------------------------------------
# Compressing Archive
tar jchf AVI_MetaEdit_GNU_FromSource.tar.bz2 AVI_MetaEdit/*

#-----------------------------------------------------------------------
# Clean up
rm -r AVI_MetaEdit
