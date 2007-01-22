LDFLAGS = $(shell wx-config --libs)

CPPFLAGS = $(shell wx-config --cflags) -I../xml -I/usr/pkg/include/libxml2 \
		-I/usr/pkg/include `xml2-config --cflags`

noinst_LTLIBRARIES = libsave.la

libsave_la_SOURCES = 			\
		SaveCenter.cpp		\
		WiredDocument.cpp	\
		../xml/WiredXml.cpp
