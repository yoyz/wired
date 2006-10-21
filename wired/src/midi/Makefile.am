SUBDIRS = portmidi

LDFLAGS = $(shell wx-config --libs)

CPPFLAGS = $(shell wx-config --cflags) -I../gui -I../plugins -I../fileloader -I../sequencer -I../engine -I../mixer -I../audio -I../midi/portmidi/pm_common -I../midi/portmidi/porttime -I../asm -I../editmidi -I../undo -I../libs/WiredWidgets/include

noinst_LIBRARIES = libmidi.a

noinst_HEADERS =
		MidiDevice.h		\
		MidiFile.h		\
		MidiInDevice.h		\
		MidiThread.h		\
		midi.h			\
		MidiController.h

libmidi_a_SOURCES = 			\
		MidiDevice.cpp		\
		MidiFile.cpp		\
		MidiInDevice.cpp	\
		MidiThread.cpp		\
		MidiController.cpp

