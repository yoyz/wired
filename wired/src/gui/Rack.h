// Copyright (C) 2004-2006 by Wired Team
// Under the GNU General Public License Version 2, June 1991

// Copyright (C) 2004-2006 by Wired Team
// Under the GNU General Public License

#ifndef __RACK_H__
#define __RACK_H__

#include <wx/wx.h>
#include <wx/file.h>
#include <list>

using namespace					std;

#define 	UNIT_W				(200)
#define 	UNIT_H				(100)
#define 	UNIT_S				(2)
#define 	SCROLL_PIX			(50)

class PluginLoader;
class WiredPlugin;
class Rack;
class RackTrack;
class ChannelGui;

#ifndef __TRACK_H__
	class Channel;
#endif


typedef 	struct s_PlugStartInfo			PlugStartInfo;
typedef		list<RackTrack *>			t_ListRackTrack;
typedef		list<WiredPlugin *>::const_iterator	t_ListPluginIterator;

typedef struct	s_RackTrackPlugin
{
  RackTrack*	rackTrack;
  WiredPlugin*	plugin;
}		t_RackTrackPlugin;

class			RackTrack
{
 public:
	RackTrack(Rack* parent, int index);
	RackTrack(const RackTrack& copy){*this = copy;};
	~RackTrack();

	WiredPlugin*				AddRack(PlugStartInfo& startinfo, PluginLoader* p,
								WiredPlugin* connect_to = 0x0);
	void				DeleteRack(WiredPlugin* plugin);
	int				GetYPos();
	void				RemoveRack();
	void				RemoveChannel();
	void				DeleteAllRacks();

	RackTrack			operator=(const RackTrack &right);

	// Debug - Shows member variables
	void				Dump();

	// Pas du tout objet, mais plus simple pour l'instant (ca permet de ne pas changer
	void				DumpPlugins();

	// l'API du plugin qui va de tte maniere l'etre pour les DSSI)
	int				Units;
	Rack*				Parent;
	int				Index;
	list<WiredPlugin *>		Racks;
	Channel*			Output;
	ChannelGui*			ChanGui;
	float**				CurrentBuffer;
};

class				Rack: public wxScrolledWindow
{
 public:
	Rack(wxWindow* parent, wxWindowID id = -1,
    	 const wxPoint& pos = wxDefaultPosition,
	     const wxSize& size = wxDefaultSize);
	Rack(const Rack& copy){*this = copy;};
	~Rack();

	// Kept for compatibility but shouldn't be used anymore
	WiredPlugin*			AddTrack(PlugStartInfo& startinfo, PluginLoader* p);
	void				AddTrack(WiredPlugin* p);

	// Should be used instead of AddTrack
	// Adds a rack and a channel (channel == Mixer object in Mixer window)
	t_RackTrackPlugin*		AddRackAndChannel(PlugStartInfo& startinfo, PluginLoader* p);
	RackTrack*			AddTrack();

	// Kept for compatibility but shouldn't be used anymore
	WiredPlugin*			AddToSelectedTrack(PlugStartInfo& startinfo, PluginLoader *p);

	// Should be used instead of AddToSelectedTrack
	// Adds a rack and a channel (== Mixer object in Mixer window) and selects the rack
	WiredPlugin*			AddSelectedRackAndChannel(PlugStartInfo& startinfo, PluginLoader *p);

	void				DeleteRack(WiredPlugin* plug);
	void				DeleteAllRacks();
	RackTrack*			GetRackTrack(WiredPlugin* plug);
	int				GetXPos(int index);

	// Applies scrolling on all racks
	void				SetScrolling();
	// Resizes racks positions from index with scrolling
	void				ResizeTracks();
	// Seems to select a rack
	void				SetSelected(WiredPlugin* p);
	// Kept for compatibility but shouldn't be used anymore
	void				RemoveFromSelectedTrack();
	// Should be used instead of RemoveFromSelectedTrack
	// Removes the selected rack and the attached channel
	bool				RemoveSelectedRackAndChannel();

	// Kept for compatibility but shouldn't be used anymore
	void				RemoveTrack();
	// Should be used instead of RemoveTrack
	// Removes a rack and a channel from index
	// RemoveRack() ? Not RemoveAllRackTracks() ?
	bool				RemoveTrack(int index);

	// Should be used instead of RemoveTrack
	bool				RemoveTrack(const RackTrack* rackTrack);

	// Debug - Shows member variables
	void				Dump();

	// Adds subMenuItems (Instruments or effects in Add menuItem)
	void				AddPlugToMenu();
	//  bool ProcessEvent(wxEvent& event);

	// Handles all mouse events
	void				HandleMouseEvent(WiredPlugin *plug, wxMouseEvent *event);
	// Handles key events
	void				HandleKeyEvent(WiredPlugin *plug, wxKeyEvent *event);
	// Handles all paint events like onPaint ???
	// Draws the selection rectangle
	void				HandlePaintEvent(WiredPlugin *plug, wxPaintEvent *event);


	Rack				operator=(const Rack& right);

	t_ListRackTrack			RackTracks;

	RackTrack*			selectedTrack;
	WiredPlugin*			selectedPlugin;


 protected:

	int				OldX;
	int				OldY;
	int				new_x;
	int				new_y;
	int				fd_size;

	bool				is_cut;
	WiredPlugin*			copy_plug;
	wxFile				tmpFile;
	wxMenu*				menu;
	wxMenu*				submenu;
	wxMenu*				instr_menu;
	wxMenu*				effects_menu;
	wxString			filePath;
	bool				WasDragging;

	// Not used ...
	virtual void			OnPaint(wxPaintEvent& event);
	// Event : Help handling
	void				OnHelp(wxMouseEvent& event);
	// Event : Click on rack : Sets unselect rack and plugin
	void				OnClick(wxMouseEvent& event);
	// Event : onContextMenuClick("Delete") ; new methode
	void				OnDeleteClick();
	// Event : From contextMenu, Cuts a rack
	void				OnCutClick();
	// Event : From contextMenu, Copy a rack
	void				OnCopyClick();
	// Event : From contextMenu, Pastes a rack
	void				OnPasteClick();
	// Event : Calls AddChangeParamsEffectAction while a plugin's param is changed
	void				OnPluginParamChange(wxMouseEvent &event);
	bool 				DndGetDest(t_ListRackTrack::iterator &k,
									list<WiredPlugin *>::iterator& l, int& new_x,
									int& new_y , WiredPlugin* plug);
	void				DndInsert(t_ListRackTrack::iterator& k,
									list<WiredPlugin *>::iterator& l, WiredPlugin* plug);
	void				UpdateUnitXSize();

private:

	// Removes a rack and a channel
	// Be carefull : Freezes if delete rack from contextMenu
	void				RemoveRackAndChannel(t_ListRackTrack::const_iterator iter);
	// Initializes contextMenu
	void				InitContextMenu();
	void				ConnectPluginChangeParamEventHandler(RackTrack* rackTrack);
	DECLARE_EVENT_TABLE()
};

// IDS
enum
{
  ID_MENU_ADD = 20000,
  ID_MENU_CUT,
  ID_MENU_COPY,
  ID_MENU_PASTE,
  ID_MENU_DELETE,
  ID_INSTR_MENU,
  ID_EFFECTS_MENU
};

extern Rack			*RackPanel;
extern int			RackCount;


#endif

