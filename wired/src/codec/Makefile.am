if CODECS
SUBDIRS = wiredcodec
endif

CPPFLAGS = $(shell wx-config --cflags) -I./wiredcodec

LDFLAGS = $(shell wx-config --libs) -ldl

noinst_LIBRARIES = libwiredCodec.a

noinst_HEADERS = WiredCodec.h


libwiredCodec_a_SOURCES = WiredCodec.cpp
