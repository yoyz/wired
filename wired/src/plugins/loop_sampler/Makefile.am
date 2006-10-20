LDFLAGS = $(shell wx-config --libs) -L../WiredPluginApi/src/.libs/ -lWiredPluginApi -L../../libs/WiredWidgets/src/.libs/ -lWiredWidgets -L../../libs/WiredAudioUtilities/src/.libs/ -lWiredAudioUtilities

CPPFLAGS = $(shell wx-config --cflags) -I../WiredPluginApi/include -I../../libs/WiredWidgets/src -I../../libs/WiredAudioUtilities/src 
#-I/opt/gnome/include -I../../audio -I../../engine -I../../mixer -I../../midi -I../../midi/portmidi/pm_common -I../../midi/portmidi/porttime -I../../asm -I../../editmidi -I../../undo

if PORTAUDIO
CPPFLAGS += -I../../portaudio/include
endif


lib_LTLIBRARIES = libWiredLoopSampler.la

libWiredLoopSampler_la_SOURCES =		\
			LoopSampler.h		\
			LoopSampler.cpp		\
			LoopSamplerView.h	\
			LoopSamplerView.cpp	\
			WaveLoop.h		\
			WaveLoop.cpp		\
			RulerLoop.h		\
			RulerLoop.cpp		\
			Slice.h			\
			Slice.cpp		\
			SliceGui.h		\
			SliceGui.cpp		\
			BeatDialog.h		\
			BeatDialog.cpp		\
			LoopCursor.h		\
			LoopCursor.cpp

#			../../redist/Polyphony.cpp	\
#			../../redist/Plugin.cpp		\
#			../../gui/WaveView.cpp		\
#			../../gui/WaveDrawer.cpp	\
#			../../engine/Settings.cpp	\
#			../../audio/WaveFile.cpp

libWiredLoopSampler_la_LIBADD = $(DEPS_LIBS) -lSoundTouch
