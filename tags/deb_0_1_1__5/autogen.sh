#!/bin/sh

echo "Applying autoheader..."
autoheader

echo "Applying libtoolize..."
libtoolize --force

echo "Applying gettextize..."
cp configure.ac configure.ac.bk
cp Makefile.am Makefile.am.bk

gettextize --force --no-changelog

mv Makefile.am.bk Makefile.am
mv configure.ac.bk configure.ac

echo "Applying aclocal..."
aclocal

echo "Applying automake..."
automake --add-missing

echo "Applying autoconf..."
autoconf

