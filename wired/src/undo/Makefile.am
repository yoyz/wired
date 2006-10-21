LDFLAGS = $(shell wx-config --libs)

CPPFLAGS = $(shell wx-config --cflags) -I../libs/WiredAkai/include -I../gui -I../plugins/WiredPluginApi/include -I../fileloader -I../sequencer -I../engine -I../mixer -I../midi -I../midi/portmidi/pm_common -I../midi/portmidi/porttime -I../asm -I../editmidi -I../audio -I../libs/WiredWidgets/include

if PORTAUDIO
CPPFLAGS += -I../portaudio/include
endif


noinst_LIBRARIES = libundo.a


noinst_HEADERS = 			\
		Visitor.h		\
		cAction.h		\
		cActionManager.h	\
		cAddTrackAction.h	\
		cImportMidiAction.h

libundo_a_SOURCES = 			\
		Visitor.cpp		\
		cAction.cpp		\
		cActionManager.cpp	\
		cImportMidiAction.cpp
