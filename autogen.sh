#!/bin/sh

echo "Applying autoheader..."
autoheader

echo "Applying libtoolize..."
libtoolize --force

echo "Applying autopoint..."
autopoint -f

echo "Applying aclocal..."
aclocal

echo "Applying automake..."
automake --add-missing

echo "Applying autoconf..."
autoconf

