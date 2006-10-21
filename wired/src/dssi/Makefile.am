LDFLAGS = $(shell wx-config --libs) -lm

CPPFLAGS = $(shell wx-config --cflags) -I../gui -I../plugins/WiredPluginApi/include -I../libs/WiredWidgets/include -I../fileloader -I../sequencer -I../audio -I../mixer -I../midi -I../midi/portmidi/pm_common -I../midi/portmidi/porttime -I../editmidi -I../undo -Wall -Wunused

if PORTAUDIO
CPPFLAGS += -I../portaudio/include
endif

noinst_LIBRARIES = libwireddssi.a

noinst_HEADERS = 				\
		WiredExternalPluginMgr.h	\
		WiredExternalPlugin.h		\
		WiredExternalPluginLADSPA.h	\
		dssi.h				\
		WiredExternalPluginGui.h	\
		ladspa.h


libwireddssi_a_SOURCES =			\
		WiredExternalPluginMgr.cpp	\
		WiredExternalPlugin.cpp		\
		WiredExternalPluginLADSPA.cpp	\
		WiredExternalPluginGui.cpp
