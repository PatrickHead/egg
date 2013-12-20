#!/usr/bin/env sh

echo "Gathering Useful Package Information"

if [ ! -e configure.ac ]
then
  echo "Can not find 'configure.ac'"
  exit 1
fi

tmp=`grep AC_INIT configure.ac | sed -e 's/AC_INIT(//' -e 's/) *$//' -e 's/\[//g' -e 's/]//g' -e 's/ *//g'`
PKGNAME=`echo $tmp | cut -d, -f1`
PKGVERSION=`echo $tmp | cut -d, -f2`
PKGRELEASE=1

mkdir packages

echo "Creating Binary Packages"

echo "Creating Slackware Package"

checkinstall --install=no -S -y --pkgname=$PKGNAME --pkgversion=$PKGVERSION --pkgrelease=$PKGRELEASE --pkggroup='Development/Tools' --maintainer='patrickhead@gmail.com' --strip=yes --stripso=yes --gzman=yes --newslack --pakdir=packages --backup=no --addso=yes

echo "Creating RPM Package"

checkinstall --install=no -R -y --pkgname=$PKGNAME --pkgversion=$PKGVERSION --pkgrelease=$PKGRELEASE --pkggroup='Development/Tools' --maintainer='patrickhead@gmail.com' --strip=yes --stripso=yes --gzman=yes --pakdir=packages --backup=no --addso=yes --spec=~/rpmbuild/SPECS/egg.spec

echo "Creating Debian Package"

checkinstall --install=no -D -y --pkgname=$PKGNAME --pkgversion=$PKGVERSION --pkgrelease=$PKGRELEASE --pkggroup='Development/Tools' --maintainer='patrickhead@gmail.com' --strip=yes --stripso=yes --gzman=yes --pakdir=packages --backup=no --addso=yes 

