CPPFLAGS = $(shell wx-config --cflags) -I../gui -I../plugins/WiredPluginApi/include -I../libs/WiredWidgets/src -I../fileloader -I../sequencer -I../audio -I../mixer -I../midi -I../midi/portmidi/pm_common -I../midi/portmidi/porttime -I../editmidi -I../undo

if PORTAUDIO
CPPFLAGS += -I../portaudio/include
endif


LDFLAGS = $(shell wx-config --libs)

noinst_LIBRARIES = libengine.a

libengine_a_SOURCES =			\
		AudioCenter.cpp		\
		AudioCenter.h		\
		AudioEngine.cpp		\
		AudioEngine.h		\
		Device.cpp		\
		Device.h		\
		EngineError.h		\
		RingBuffer.h		\
		RingBuffer.hxx		\
		RingError.h		\
		Settings.cpp		\
		Settings.h		\
		WiredSession.cpp	\
		WiredSession.h
