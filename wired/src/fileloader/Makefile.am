LDFLAGS = $(shell wx-config --libs)

CPPFLAGS = $(shell wx-config --cflags) -I../libs/WiredAkai/include -I../gui -I../plugins/WiredPluginApi/include -I../audio -I../sequencer -I../engine -I../mixer -I../midi -I../midi/portmidi/pm_common -I../midi/portmidi/porttime -I../asm -I../editmidi -I../undo

noinst_LIBRARIES = libfileloader.a

noinst_HEADERS =			\
		FileLoader.h		\
		TreeItemData.h		\
		akai.h			\
		list.h

libfileloader_a_SOURCES =		\
		FileLoader.cpp		\
		TreeItemData.cpp	\
		FileStat.cpp
