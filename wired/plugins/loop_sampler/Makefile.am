LDFLAGS = $(shell wx-config --libs) -L../WiredPluginApi/src/.libs/ -lWiredPluginApi -L../../libs/WiredWidgets/src/.libs/ -lWiredWidgets -L../../libs/WiredAudioUtilities/src/.libs/ -lWiredAudioUtilities

CPPFLAGS = $(shell wx-config --cflags) -I../WiredPluginApi/include -I../../libs/WiredWidgets/include -I../../libs/WiredAudioUtilities/include

if PORTAUDIO
CPPFLAGS += -I../../portaudio/include
endif


lib_LTLIBRARIES = libWiredLoopSampler.la


noinst_HEADERS =				\
		LoopSampler.h			\
		LoopSamplerView.h		\
			WaveLoop.h		\
			RulerLoop.h		\
			Slice.h			\
			SliceGui.h		\
			BeatDialog.h		\
			LoopCursor.h

libWiredLoopSampler_la_SOURCES =		\
			LoopSampler.cpp		\
			LoopSamplerView.cpp	\
			WaveLoop.cpp		\
			RulerLoop.cpp		\
			Slice.cpp		\
			SliceGui.cpp		\
			BeatDialog.cpp		\
			LoopCursor.cpp

#			../../redist/Polyphony.cpp	\
#			../../redist/Plugin.cpp		\
#			../../gui/WaveView.cpp		\
#			../../gui/WaveDrawer.cpp	\
#			../../engine/Settings.cpp	\
#			../../audio/WaveFile.cpp

libWiredLoopSampler_la_LIBADD = $(DEPS_LIBS) -lSoundTouch
