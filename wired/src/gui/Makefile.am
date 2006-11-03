LDFLAGS = $(shell wx-config --libs) `xml2-config --libs`

CPPFLAGS = $(shell wx-config --cflags) -I../audio -I../libs/WiredAkai/include -I../plugins/WiredPluginApi/include -I../fileloader -I../sequencer -I../engine -I../mixer -I../midi -I../midi/portmidi/pm_common -I../midi/portmidi/porttime -I../asm -I../editmidi -I../undo -I../libs/WiredWidgets/include `xml2-config --cflags` -I../wiredvideo -I../include/ -I../plugins/dssi/ -I../xml -I../plugins/ -I../codec/wiredcodec

if PORTAUDIO
CPPFLAGS += -I../portaudio/include
endif

noinst_LIBRARIES = libgui.a

noinst_HEADERS = 			\
		AccelCenter.h		\
		ChannelGui.h		\
		ColoredLine.h		\
		ColoredBox.h		\
		Colour.h		\
		Cursor.h		\
		HelpCtrl.h		\
		HelpPanel.h		\
		MainApp.h		\
		MainWindow.h		\
		MediaLibrary.h		\
		MLTree.h		\
		MLTreeInfos.h		\
		MidiPattern.h		\
		MixerGui.h		\
		OptionPanel.h		\
		Pattern.h		\
		Rack.h			\
		Ruler.h			\
		SeqTrack.h		\
		SeqTrackPattern.h	\
		SequencerGui.h		\
		SelectionZone.h		\
		SettingWindow.h		\
		StaticLabel.h		\
		Transport.h		\
		WaveEditor.h		\
		WaveView.h		\
		WaveDrawer.h		\
		WaveEditorDrawer.h	\
		WavePanel.h		\
		PluginEffect.h		\
		FileConversion.h	\
		FloatingFrame.h	

libgui_a_SOURCES = 			\
		AccelCenter.cpp		\
		ChannelGui.cpp		\
		ColoredLine.cpp		\
		ColoredBox.cpp		\
		Cursor.cpp		\
		HelpCtrl.cpp		\
		HelpPanel.cpp		\
		MainApp.cpp		\
		MainWindow.cpp		\
		MediaLibrary.cpp	\
		MLTree.cpp		\
		MLTreeInfos.cpp		\
		MidiPattern.cpp		\
		MixerGui.cpp		\
		OptionPanel.cpp		\
		Pattern.cpp		\
		Rack.cpp		\
		Ruler.cpp		\
		SeqTrack.cpp		\
		SeqTrackPattern.cpp	\
		SequencerGui.cpp	\
		SelectionZone.cpp	\
		SettingWindow.cpp	\
		StaticLabel.cpp		\
		Transport.cpp		\
		WaveEditor.cpp		\
		WaveView.cpp		\
		WaveDrawer.cpp		\
		WaveEditorDrawer.cpp	\
		WavePanel.cpp		\
		PluginEffect.cpp	\
		FileConversion.cpp	\
		FloatingFrame.cpp
