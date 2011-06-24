#!/bin/sh

echo "Applying libtoolize..."
libtoolize --force

echo "Applying autopoint..."
autopoint -f

echo "Applying aclocal..."
aclocal

echo "Applying autoheader..."
autoheader

echo "Applying automake..."
automake --add-missing

echo "Applying autoconf..."
autoconf

