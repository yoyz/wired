#!/bin/sh

###
### classic bootstrap stuff
###
set -x

###
### cleanning part
###
#  remove autotools stuff
rm -rf config
rm -f aclocal.m4 configure config.log config.status
rm -rf autom4te*.cache
# remove libtool stuff
rm -f libtool
# remove gettext stuff
rm -f ABOUT-NLS


###
### configuration part
###
# create the config directory
mkdir -p config/m4
# autoheader writes config.h.in into src/include (AC_CONFIG_HEADERS)
mkdir -p src/include

# execute autotools cmds
autopoint -f				&& \
aclocal --force	-I config/m4		&& \
libtoolize --force -c			&& \
autoconf				&& \
autoheader --force			&& \
automake -a -f -c


# Shut up
set +x
