LDFLAGS = $(shell wx-config --libs) -L../WiredPluginApi/src/.libs/ -lWiredPluginApi -L../../libs/WiredWidgets/src/.libs/ -lWiredWidgets -L../../libs/WiredAudioUtilities/src/.libs/ -lWiredAudioUtilities

CPPFLAGS = $(shell wx-config --cflags) -I../WiredPluginApi/include -I../../libs/WiredWidgets/include -I../../libs/WiredAudioUtilities/include
#-I../../gui -I../../plugins -I../../fileloader -I/opt/gnome/include -I../../audio -I../../redist -I../../engine -I../../mixer -I../../midi -I../../midi/portmidi/pm_common -I../../midi/portmidi/porttime -I../../asm -I../../editmidi -I../../undo

if PORTAUDIO
CPPFLAGS += -I../../portaudio/include
endif


lib_LTLIBRARIES = libWiredBeatBox.la

noinst_HEADERS =			\
		BeatBox.h		\ 
		BeatButton.h		\
		BeatBoxChannel.h	\
		BeatBoxView.h		\
		BeatNote.h


libWiredBeatBox_la_SOURCES =			\
			BeatBox.cpp		\
			BeatButton.cpp		\
			BeatBoxChannel.cpp	\
			BeatBoxView.cpp		\
			BeatNote.cpp

#			../../redist/Polyphony.cpp	\
#			../../redist/Plugin.cpp		\
#			../../gui/WaveView.cpp          \
#			../../gui/WaveDrawer.cpp        \
#			../../engine/Settings.cpp	\
#			../../audio/WaveFile.cpp


libWiredBeatBox_la_LIBADD = $(DEPS_LIBS)