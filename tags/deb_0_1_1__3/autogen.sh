#!/bin/sh

echo "Applying autoheader..."
autoheader

echo "Applying libtoolize..."
libtoolize --force

echo "Applying gettextize..."
gettextize --force

echo "Applying aclocal..."
aclocal

echo "Applying automake..."
automake --add-missing

echo "Applying autoconf..."
autoconf

