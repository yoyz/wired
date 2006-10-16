LDFLAGS = $(shell wx-config --libs) -L../../fileloader -lfileloader -L../../libs/WiredWidgets/src/.libs/ -lWiredWidgets -L../../libs/WiredAkai/src/.libs/ -lWiredAkai -L../../libs/WiredAkai/src/.libs/ -lWiredAudioUtilities

CPPFLAGS = $(shell wx-config --cflags) -I../../libs/WiredWidgets/src -I../../libs/WiredAkai/include -I../../libs/WiredAudioUtilities/src  -I../../gui -I../../plugins -I../../fileloader -I/opt/gnome/include -I../../audio -I../../redist -I../../engine -I../../mixer -I../../midi -I../../midi/portmidi/pm_common -I../../midi/portmidi/porttime -I../../asm -I../../editmidi -I../../undo

if PORTAUDIO
CPPFLAGS += -I../../portaudio/include
endif


lib_LTLIBRARIES = libWiredBeatBox.la


libWiredBeatBox_la_SOURCES =			\
			BeatBox.h		\
			BeatBox.cpp		\
			BeatButton.h		\
			BeatButton.cpp		\
			BeatBoxChannel.h	\
			BeatBoxChannel.cpp	\
			BeatBoxView.h		\
			BeatBoxView.cpp		\
			BeatNote.h		\
			BeatNote.cpp

#			../../redist/Polyphony.cpp	\
#			../../redist/Plugin.cpp		\
#			../../gui/WaveView.cpp          \
#			../../gui/WaveDrawer.cpp        \
#			../../engine/Settings.cpp	\
#			../../audio/WaveFile.cpp


libWiredBeatBox_la_LIBADD = $(DEPS_LIBS)