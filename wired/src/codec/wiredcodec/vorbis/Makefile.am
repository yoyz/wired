LDFLAGS =  $(shell wx-config --libs)

CPPFLAGS =  $(shell wx-config --cflags) -I..

lib_LTLIBRARIES = libWiredVorbis.la

noinst_HEADERS = WiredLibVorbis.h

libWiredVorbis_la_SOURCES = WiredLibVorbis.cpp	

libWiredVorbis_la_LIBADD = $(DEPS_LIBS)
