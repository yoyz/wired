LDFLAGS = -lFLAC++ $(shell wx-config --libs)

CPPFLAGS =  $(shell wx-config --cflags) -I..

lib_LTLIBRARIES = libWiredFlac.la

noinst_HEADERS = WiredLibFlac.h

libWiredFlac_la_SOURCES = WiredLibFlac.cpp	

libWiredFlac_la_LIBADD = $(DEPS_LIBS)
