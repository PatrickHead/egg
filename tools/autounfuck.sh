#!/usr/bin/env sh

find . -name 'Makefile.in' -exec rm {} \;
rm -rf autom4te.cache
rm -f config.h.in
rm -f config/*
rm -f aclocal.m4
rm -rf m4
rm -f configure
