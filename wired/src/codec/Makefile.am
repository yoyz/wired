SUBDIRS = wiredcodec

CPPFLAGS = $(shell wx-config --cflags) -g3 -ggdb

LDFLAGS = $(shell wx-config --libs) -ldl -lefence

noinst_LIBRARIES = libwiredCodec.a

libwiredCodec_a_SOURCES =			\
		WiredCodec.cpp			\
		WiredCodec.h			\
		wiredcodec/WiredApiCodec.h

