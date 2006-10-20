LDFLAGS = $(shell wx-config --libs) -L../../libs/WiredWidgets/src/.libs/ -lWiredWidgets -L../../libs/WiredAkai/src/.libs/ -lWiredAkai -L../../libs/WiredAkai/src/.libs/ -lWiredAudioUtilities

CPPFLAGS = $(shell wx-config --cflags) -I../../libs/WiredWidgets/src -I../../libs/WiredAkai/include -I../../libs/WiredAudioUtilities/src -I../../gui -I../../plugins -I../../fileloader -I/opt/gnome/include -I../../audio -I../../redist -I../../engine -I../../mixer -I../../midi -I../../midi/portmidi/pm_common -I../../midi/portmidi/porttime -I../../asm -I../../editmidi -I../../undo

if PORTAUDIO
CPPFLAGS += -I../../portaudio/include
endif


lib_LTLIBRARIES = libWiredPluginApi.la

libWiredPluginApi_la_SOURCES =			\
		WiredCorePlugins.h		\
		WiredCorePlugins.cpp		\
		WiredPluginStartInfo.h		\
		WiredPluginStartInfo.cpp	\
		WiredPluginGui.h		\
		WiredPluginGui.cpp		\
		WiredPluginAudio.h		\
		WiredPluginAudio.cpp		\
		WiredPluginData.h		\
		WiredPluginData.cpp		\
		WiredPlugin.h			\
		WiredPlugin.cpp			\
		WiredPluginInstaller.h		\
		WiredPluginInstaller.cpp
