LDFLAGS = $(shell wx-config --libs)  -L../WiredPluginApi/src/.libs/ -lWiredPluginApi

CPPFLAGS = $(shell wx-config --cflags) -I../gui -I../plugins -I../fileloader -I../sequencer -I../audio -I../engine -I../mixer -I../midi -I../midi/portmidi/pm_common -I../midi/portmidi/porttime -I../asm -I../undo -I../libs/WiredWidgets/include

noinst_LIBRARIES = libeditmidi.a

noinst_HEADERS = 			\
		Clavier.h		\
		EditMidi.h		\
		EditNote.h		\
		Key.h			\
		MidiAttr.h		\
		MidiPart.h		\
		Note.h			\
		RulerMidi.h

libeditmidi_a_SOURCES =			\
		Clavier.cpp		\
		EditMidi.cpp		\
		EditNote.cpp		\
		Key.cpp			\
		MidiAttr.cpp		\
		MidiPart.cpp		\
		Note.cpp		\
		RulerMidi.cpp