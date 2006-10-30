#ifndef __WIREDPLUGINGUI_H__
#define __WIREDPLUGINGUI_H__


#include <wx/wxprec.h>
#ifndef WX_PRECOMP
   #include <wx/wx.h>
#endif

//#include "WiredPluginStartInfo.h"
#include "Sequencer.h"

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
  WiredPluginGui(WiredPluginStartInfo* parent) { _StartInfo = parent; };
  ~WiredPluginGui();

  /*
   * VIRTUAL METHODS
   */
  /* Called by the host that the plugin can update its graphical controls */
  virtual void	 Update() {};

  /* Called when host needs to show the plugin's help */
  virtual wxString GetHelpString() { return _("No help provided for this plugin"); };

  /* Is the Help window being shown ? */
  virtual void EnableHelpMode(bool On = true) {};

  /* Returns a 32x16 bitmap used for displaying the connected to track plugin */
  virtual wxBitmap* GetBitmap() { return NULL; };

  /* Called by the host to know if the plugin has an optional view or not */
  virtual bool	 HasView() { return false; };
  /* Called by the host to create the optional view */
  virtual wxWindow* CreateView(wxWindow *zone, wxPoint& pos, wxSize& size) { return 0x0; };
  /* Called when the optional view needs to be destroyed */
  virtual void	 DestroyView() {};



  /* Opens the Wired file loader with given title, extensions, and if it should read
     AKAI audio cds/files or not. Returns the selected file name or an empty wstring if
     cancelled. If 'exts' is NULL, default audio extensions are used. */
  wxString OpenFileLoader(wxString& title,
			  std::vector<wxString>* exts = NULL,
			  bool addExts = true,
			  bool akai = false);

  /* Opens the Wired file loader with given title, extensions, for saving a file.
     Returns the file name or an empty wstring if cancelled */
  wxString SaveFileLoader(wxString& title,
			  std::vector<wxString>* exts = NULL,
			  bool addExts = true);
  void	SendHelp(wxString str);

};

#endif // __WIREDPLUGINGUI_H__
