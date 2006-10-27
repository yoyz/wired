LDFLAGS = $(shell wx-config --libs) -L../WiredPluginApi/src/.libs/ -lWiredPluginApi -L../../libs/WiredWidgets/src/.libs/ -lWiredWidgets -L../../libs/WiredAudioUtilities/src/.libs/ -lWiredAudioUtilities

CPPFLAGS = $(shell wx-config --cflags) -I../WiredPluginApi/include -I../../libs/WiredWidgets/include -I../../libs/WiredAudioUtilities/include
#-I../../gui -I../../plugins -I/opt/gnome/include -I../../audio -I../../redist -I../../engine -I../../mixer -I../../midi -I../../midi/portmidi/pm_common -I../../midi/portmidi/porttime -I../../asm -I../../editmidi -I../../undo  -Wall  -Wunused

lib_LTLIBRARIES = libWiredReverb.la


noinst_HEADERS =				\
			Stk.h			\
			Effect.h 		\
			Filter.h		\
			PRCRev.h		\
			NRev.h			\
			JCRev.h			\
			Delay.h			\
			ReverbPlug.h


libWiredReverb_la_SOURCES =			\
			Stk.cpp			\
			Effect.cpp 		\
			Filter.cpp		\
			PRCRev.cpp		\
			NRev.cpp		\
			JCRev.cpp		\
			Delay.cpp		\
			ReverbPlug.cpp


libWiredReverb_la_LIBADD = $(DEPS_LIBS)