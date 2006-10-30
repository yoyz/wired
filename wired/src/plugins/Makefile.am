SUBDIRS = WiredPluginApi dssi

LDFLAGS = $(shell wx-config --libs)

CPPFLAGS = $(shell wx-config --cflags) -IWiredPluginApi/ -I../engine/

if DSSI
CPPFLAGS += -Idssi/
endif

if PORTAUDIO
CPPFLAGS += -I../portaudio/include
endif

noinst_LIBRARIES = libplugins.a

libplugins_a_SOURCES = 			\
		PluginCenter.h		\
		PluginCenter.cpp	\
		PluginLoader.cpp	\
		PluginLoader.h
