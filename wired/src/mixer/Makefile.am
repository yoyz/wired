LDFLAGS = $(shell wx-config --libs)

CPPFLAGS = $(shell wx-config --cflags) -I../gui -I../plugins/WiredPluginApi/include -I../fileloader -I../sequencer -I../engine -I../audio -I../midi -I../midi/portmidi/pm_common -I../midi/portmidi/porttime -I../asm -I../editmidi -I../undo -I../libs/WiredWidgets/src

if PORTAUDIO
CPPFLAGS += -I../portaudio/include
endif


noinst_LIBRARIES = libmixer.a

libmixer_a_SOURCES = 			\
		Channel.cpp		\
		Channel.h		\
		Mixer.cpp		\
		Mixer.h			\
		MixerError.h


