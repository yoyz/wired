LDFLAGS = $(shell wx-config --libs) -L../../fileloader -lfileloader -L../../libs/WiredWidgets/src/.libs/ -lWiredWidgets -L../../libs/WiredAkai/src/.libs/ -lWiredAkai -L../../libs/WiredAkai/src/.libs/ -lWiredAudioUtilities

CPPFLAGS = $(shell wx-config --cflags) -I../../libs/WiredWidgets/src -I../../libs/WiredAkai/include -I../../libs/WiredAudioUtilities/src -I../../gui -I../../plugins -I../../fileloader -I/opt/gnome/include -I../../audio -I../../redist -I../../engine -I../../mixer -I../../midi -I../../midi/portmidi/pm_common -I../../midi/portmidi/porttime -I../../asm -I../../editmidi -I../../undo

lib_LTLIBRARIES = libWiredCompressor.la

libWiredCompressor_la_SOURCES =			\
			CompressorPlug.h	\
			CompressorPlug.cpp

#			../../redist/Plugin.cpp

libWiredCompressor_la_LIBADD = $(DEPS_LIBS)