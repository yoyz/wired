LDFLAGS = $(shell wx-config --libs)

CPPFLAGS = $(shell wx-config --cflags) -I../../../gui -I../../../plugins/WiredPluginApi/include -I../../../fileloader -I../../../sequencer -I../../../engine -I../../../mixer -I../../../midi -I../../../midi/portmidi/pm_common -I../../../midi/portmidi/porttime -I../../../asm -I../../../editmidi -I../../../undo

lib_LTLIBRARIES = libWiredAudioUtilities.la

instdir = $(includedir)
inst_HEADERS =				\
		WiredAudioUtilities.h


libWiredAudioUtilities_la_SOURCES =