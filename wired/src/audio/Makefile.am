LDFLAGS = $(shell wx-config --libs) -lsndfile

CPPFLAGS = $(shell wx-config --cflags) -I../gui -I../plugins/WiredPluginApi/include -I../fileloader -I../sequencer -I../engine -I../mixer -I../midi -I../midi/portmidi/pm_common -I../midi/portmidi/porttime -I../editmidi -I../undo -I../

noinst_LIBRARIES = libaudio.a

noinst_HEADERS = 			\
		ClipBoard.h		\
		Error.hh		\
		WaveFile.h		\
		WriteWaveFile.h

libaudio_a_SOURCES = 			\
		ClipBoard.cpp		\
		WaveFile.cpp		\
		WriteWaveFile.cpp
