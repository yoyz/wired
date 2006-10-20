CPPFLAGS = $(shell wx-config --cflags) -I../gui -I../plugins/WiredPluginApi/include -I../fileloader -I../sequencer -I../audio -I../mixer -I../midi -I../midi/portmidi/pm_common -I../midi/portmidi/porttime -I../editmidi -I../undo -I../libs/WiredWidgets/src `xml2-config --cflags`
# -I/usr/pkg/include/libxml2/ -I/usr/pkg/include 

if PORTAUDIO
CPPFLAGS += -I../portaudio/include
endif


LDFLAGS = $(shell wx-config --libs) `xml2-config --libs`
#-L/usr/pkg/lib/

noinst_LIBRARIES = libwiredxml.a

libwiredxml_a_SOURCES =			\
		../redist/Plugin.cpp	\
		WiredXml.cpp		\
		WiredXml.h		\
		WiredSessionXml.cpp	\
		WiredSessionXml.h	