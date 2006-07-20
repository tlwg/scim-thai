#!/bin/sh

echo "Applying autoheader..."
autoheader

echo "Applying libtoolize..."
libtoolize --force

echo "Applying gettextize..."
gettextize

echo "Applying aclocal..."
aclocal

echo "Applying automake..."
automake --add-missing

echo "Applying autoconf..."
autoconf

