CPPFLAGS = $(shell wx-config --cflags) -I/opt/gnome/include -I/usr/pkg/include/libxml2/ -I/usr/pkg/include `xml2-config --cflags`

if PORTAUDIO
CPPFLAGS += -I../portaudio/include
endif


LDFLAGS = $(shell wx-config --libs) -L/usr/pkg/lib/ `xml2-config --libs`

noinst_LIBRARIES = libwiredxml.a

libwiredxml_a_SOURCES =			\
		WiredXml.cpp		\
		WiredXml.h		