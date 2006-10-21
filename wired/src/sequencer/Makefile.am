LDFLAGS = $(shell wx-config --libs) `xml2-config --libs`
#-L/usr/pkg/lib/ 

CPPFLAGS = $(shell wx-config --cflags) -I../gui -I../libs/WiredAkai/include -I../plugins/WiredPluginApi/include -I../fileloader -I../audio -I../engine -I../mixer -I../midi -I../midi/portmidi/pm_common -I../midi/portmidi/porttime -I../asm -I../editmidi -I../undo -I.. -I../libs/WiredWidgets/include  `xml2-config --cflags`
# -I/usr/pkg/include/libxml2/ -I/usr/pkg/include

if PORTAUDIO
CPPFLAGS += -I../portaudio/include
endif


noinst_LIBRARIES = libsequencer.a

libsequencer_a_SOURCES = 		\
		Sequencer.cpp		\
		Sequencer.h		\
		../gui/AudioPattern.cpp \
		Track.cpp		\
		Track.h			\
		../gui/WaveDrawer.cpp
