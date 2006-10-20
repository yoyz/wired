LDFLAGS = $(shell wx-config --libs)

CPPFLAGS = $(shell wx-config --cflags) -I../include -I../../../gui -I../../../plugins/WiredPluginApi/include -I../../../fileloader -I../../../sequencer -I../../../engine -I../../../mixer -I../../../midi -I../../../midi/portmidi/pm_common -I../../../midi/portmidi/porttime -I../../../asm -I../../../editmidi -I../../../undo

lib_LTLIBRARIES = libWiredAkai.la

libWiredAkai_la_SOURCES = 		\
				akai.c	\
				list.c
