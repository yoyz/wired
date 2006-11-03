#ifndef __WIREDPLUGINSTARTINFO_H__
#define __WIREDPLUGINSTARTINFO_H__


#include <wx/wxprec.h>
#ifndef WX_PRECOMP
   #include <wx/wx.h>
#endif
#include <wx/string.h>

class WiredPlugin;
class WiredPluginGui;
class WiredPluginAudio;
class WiredCorePlugins;
//class WiredPluginMgr;


/**
   * \dad Window ptr of plugin's parent
   * \pos Position
   * \size
   */

class	WiredPluginStartInfo
{
  //  friend WiredPluginMgr;
  friend class WiredPlugin;
  friend class WiredPluginGui;
  friend class WiredPluginAudio;
  friend class WiredCorePlugins;

  // well... it's bad, but it should be substitued with a method of PluginCenter
  friend class RackTrack;

 private:
  WiredCorePlugins*	_Core;
  wxString		_Version;
  wxWindow*		_Parent;
  wxPoint		_Pos;
  wxSize		_Size;



  WiredPluginStartInfo();
  ~WiredPluginStartInfo();


  WiredCorePlugins*	GetCore();
  wxString		GetVersion();
  wxWindow*		GetRack();
  wxPoint		GetPos();
  wxSize		GetSize();

  void			SetPos(wxPoint& pos);
  void			SetSize(wxSize& size);

 public:
};

#endif // __WIREDPLUGINSTARTINFO_H__
