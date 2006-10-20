CPPFLAGS = $(shell wx-config --cflags) -I../gui -I../plugins/WiredPluginApi/include -I../libs/WiredWidgets/src -I../fileloader -I../sequencer -I../audio -I../mixer -I../midi -I../midi/portmidi/pm_common -I../midi/portmidi/porttime -I../editmidi -I../undo -Wall -Wunused

if PORTAUDIO
CPPFLAGS += -I../portaudio/include
endif


LDFLAGS = $(shell wx-config --libs) -lm

noinst_LIBRARIES = libwireddssi.a

libwireddssi_a_SOURCES =				\
		WiredExternalPluginMgr.cpp		\
		WiredExternalPluginMgr.h		\
		WiredExternalPlugin.cpp			\
		WiredExternalPlugin.h			\
		WiredExternalPluginLADSPA.cpp		\
		WiredExternalPluginLADSPA.h		\
		dssi.h					\
		WiredExternalPluginGui.cpp		\
		WiredExternalPluginGui.h		\
		ladspa.h
