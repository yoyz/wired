CPPFLAGS = $(shell wx-config --cflags) -I../gui -I../plugins/ -I../plugins/WiredPluginApi/include -I../libs/WiredWidgets/include -I../fileloader -I../sequencer -I../audio -I../mixer -I../midi -I../midi/portmidi/pm_common -I../midi/portmidi/porttime -I../editmidi -I../undo

if PORTAUDIO
CPPFLAGS += -I../portaudio/include
endif


LDFLAGS = $(shell wx-config --libs)

noinst_LIBRARIES = libengine.a

noinst_HEADERS = 			\
		AudioCenter.h		\
		AudioEngine.h		\
		Device.h		\
		EngineError.h		\
		RingBuffer.h		\
		RingBuffer.hxx		\
		RingError.h		\
		Settings.h		\
		WiredSession.h


libengine_a_SOURCES =			\
		AudioCenter.cpp		\
		AudioEngine.cpp		\
		Device.cpp		\
		Settings.cpp		\
		WiredSession.cpp
