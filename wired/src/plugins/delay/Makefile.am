LDFLAGS = $(shell wx-config --libs)  -L../WiredPluginApi/src/.libs/ -lWiredPluginApi -L../../libs/WiredWidgets/src/.libs/ -lWiredWidgets -L../../libs/WiredAudioUtilities/src/.libs/ -lWiredAudioUtilities

CPPFLAGS = $(shell wx-config --cflags) -I../WiredPluginApi/include -I../../libs/WiredWidgets/src -I../../libs/WiredAudioUtilities/src
#-I../../gui -I../../plugins -I../../fileloader -I/opt/gnome/include -I../../audio -I../../redist -I../../engine -I../../mixer -I../../midi -I../../midi/portmidi/pm_common -I../../midi/portmidi/porttime -I../../asm -I../../editmidi -I../../undo

lib_LTLIBRARIES = libWiredDelay.la

libWiredDelay_la_SOURCES =			\
			DelayPlug.h		\
			DelayPlug.cpp


libWiredDelay_la_LIBADD = $(DEPS_LIBS)