LDFLAGS = $(shell wx-config --libs) -L../../../libs/WiredWidgets/src/.libs/ -lWiredWidgets -L../../../libs/WiredAkai/src/.libs/ -lWiredAkai -L../../../libs/WiredAkai/src/.libs/ -lWiredAudioUtilities

CPPFLAGS = $(shell wx-config --cflags) -I../../../libs/WiredWidgets/include -I../../../libs/WiredAkai/include -I../../../libs/WiredAudioUtilities/include -I../../../gui -I../../../fileloader -I../../../audio -I../../../sequencer -I../../../engine -I../../../mixer -I../../../midi -I../../../midi/portmidi/pm_common -I../../../midi/portmidi/porttime -I../../../asm -I../../../editmidi -I../../../undo -I../include

if PORTAUDIO
CPPFLAGS += -I../../../portaudio/include
endif


lib_LTLIBRARIES = libWiredPluginApi.la

instdir = $(includedir)
inst_HEADERS = 						\
		../include/WiredPlugin.h		\
		../include/WiredCorePlugins.h		\
		../include/WiredPluginStartInfo.h	\
		../include/WiredPluginGui.h		\
		../include/WiredPluginAudio.h		\
		../include/WiredPluginData.h		\
		../include/WiredPluginInstaller.h	\
		../include/Polyphony.h

libWiredPluginApi_la_SOURCES =			\
		WiredCorePlugins.cpp		\
		WiredPluginStartInfo.cpp	\
		WiredPluginGui.cpp		\
		WiredPluginAudio.cpp		\
		WiredPluginData.cpp		\
		WiredPlugin.cpp			\
		Polyphony.cpp



libWiredPluginApi_la_LIBADD = $(DEPS_LIBS)
