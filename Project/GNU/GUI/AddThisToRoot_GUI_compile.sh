#! /bin/sh

#############################################################################
# Configure
Home=`pwd`

#############################################################################
# Setup for parallel builds
Zen_Make()
{
 if test -e /proc/stat; then
  numprocs=`egrep -c ^cpu[0-9]+ /proc/stat || :`
  if [ "$numprocs" = "0" ]; then
   numprocs=1
  fi
  make -s -j$numprocs
 else
  make
 fi
}

#############################################################################
# AVI_MetaEdit
if test -e Project/GNU/GUI/configure; then
 cd Project/GNU/GUI/
 test -e Makefile && rm Makefile
 chmod u+x configure
 ./configure $*
 if test -e Makefile; then
  make clean
  Zen_Make
  if test -e avimetaedit-gui; then
   echo AVI_MetaEdit compiled
  else
   echo Problem while compiling AVI_MetaEdit
   exit
  fi
 else
  echo Problem while configuring AVI_MetaEdit
  exit
 fi
else
 echo AVI_MetaEdit directory is not found
 exit
fi
cd $Home

#############################################################################
# Going home
cd $Home
echo "AVI MetaEdit (GUI) executable is in Project/GNU/GUI"
echo "For installing, cd Project/GNU/GUI && make install"


