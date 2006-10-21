LDFLAGS = $(shell wx-config --libs) -L../WiredPluginApi/src/.libs/ -lWiredPluginApi -L../..libs/WiredWidgets/src/.libs/ -lWiredWidgets -L../../libs/WiredAudioUtilities/src/.libs/ -lWiredAudioUtilities

CPPFLAGS = $(shell wx-config --cflags) -I../WiredPluginApi/include -I../../libs/WiredWidgets/include -I../../libs/WiredAudioUtilities/include
#-I../../gui -I../../plugins -I/opt/gnome/include -I../../audio -I../../redist -I../../engine -I../../mixer -I../../midi -I../../midi/portmidi/pm_common -I../../midi/portmidi/porttime -I../../asm -I../../editmidi -I../../undo -Wall -Wunused

lib_LTLIBRARIES = libWiredChorus.la


noinst_HEADERS = 				\
			ChorusPlug.h		\
			Effect.h		\
			WaveLoop.h		\
			WvIn.h			\
			WvOut.h			\
			DelayL.h		\
			Delay.h			\
			Stk.h			\
			Filter.h		\
			Chorus.h


libWiredChorus_la_SOURCES =			\
			ChorusPlug.cpp		\
			Effect.cpp		\
			WaveLoop.cpp		\
			WvIn.cpp		\
			WvOut.cpp		\
			DelayL.cpp		\
			Delay.cpp		\
			Stk.cpp			\
			Filter.cpp		\
			Chorus.cpp


libWiredChorus_la_LIBADD = $(DEPS_LIBS)