#ifndef __WIREDPLUGINSTARTINFO_H__
#define __WIREDPLUGINSTARTINFO_H__

#include "WiredCorePlugins.h"
#include "WiredPlugin.h"
#include "WiredCorePlugins.h"
//#include "WiredPluginMgr.h"

#include <wx/string.h>
#include <wx/wx.h>

class WiredPlugin;
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

 private:
  WiredCorePlugins*	Core;
  wxString		Version;
  wxWindow*		Parent;
  wxPoint		Pos;
  wxSize		Size;



  WiredPluginStartInfo();
  ~WiredPluginStartInfo();


  WiredCorePlugins*	GetCore();
  wxString		GetVersion();
  wxWindow*		GetRack();
  wxPoint		GetPos();
  wxSize		GetSize();

 public:
};

#endif // __WIREDPLUGINSTARTINFO_H__
