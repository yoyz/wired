#ifndef __WIREDPLUGIN_H__
#define __WIREDPLUGIN_H__


#include <wx/wxprec.h>
#ifndef WX_PRECOMP
   #include <wx/wx.h>
#endif

#include "WiredPluginStartInfo.h"

class WiredPluginStartInfo;


////
// Current version of API
//
// this number increment only when methods or function of API are modified
//
#define WIRED_CURRENT_VERSION_API (2)


class		WiredPluginGui
{
 private:
  WiredPluginStartInfo*	_StartInfo;

 public:
  WiredPluginGui(WiredPluginStartInfo* parent) { StartInfo = parent; } ;
  ~WiredPluginGui();

  /* Ask the host application to call Update() whenever the main thread can process gui calls  */
  void	 UpdatePluginGui();

  /* Called by the host that the plugin can update its graphical controls */
  virtual void	 Update() {}

  /* Called when host needs to show the plugin's help */
  virtual wxString GetHelpString() { return _("No help provided for this plugin"); }

  /* Is the Help window being shown ? */
  virtual void EnableHelpMode(bool On = true) { }

  /* Returns a 32x16 bitmap used for displaying the connected to track plugin */
  virtual wxBitmap *GetBitmap() = 0;

  /* Used to know if a keyboard event occured. No need to overload */
  virtual void	OnKeyEvent(wxKeyEvent &event);
  /* Used to know if a mouse event occured. No need to overload */
  virtual void  OnMouseEvent(wxMouseEvent &event);
  /* Used to know if a paint event occured. No need to overload */
  virtual void  OnPaintEvent(wxPaintEvent &event);

  // User interface events
  bool ShowMidiController();

  /* Shows plugin's optional view */
  void ShowOptionalView();
  /* Closes plugin's optional view */
  void CloseOptionalView();

  int	WiredCorePlugins::GetLastMidiType();
  int	WiredCorePlugins::GetLastMidiController();
  int	WiredCorePlugins::GetLastMidiValue();

  /* Opens the Wired file loader with given title, extensions, and if it should read
     AKAI audio cds/files or not. Returns the selected file name or an empty wstring if
     cancelled. If 'exts' is NULL, default audio extensions are used. */
  wxString OpenFileLoader(wxString& title,
			     std::vector<wxString>& exts,
			     bool akai = false);
  /* Opens the Wired file loader with given title, extensions, for saving a file.
     Returns the file name or an empty wstring if cancelled */
  wxString SaveFileLoader(wxString& title,
			     std::vector<wxString>& exts);

  // Sequencer events
  /* Create a MIDI pattern containing a list of event in the host's sequencer */
  bool	AddMidiPattern(std::list<SeqCreateEvent *>& midi);

  /* Called by the host to know if the plugin has an optional view or not */
  virtual bool	 HasView() { return false; }
  /* Called by the host to create the optional view */
  virtual wxWindow *CreateView(wxWindow *zone, wxPoint &pos, wxSize &size) { return 0x0; }
  /* Called when the optional view needs to be destroyed */
  virtual void	 DestroyView() {}

};

#endif // __WIREDPLUGIN_H__
