#ifndef __WIREDPLUGINSTARTINFO_H__
#define __WIREDPLUGINSTARTINFO_H__

#include "WiredCorePlugins.h"
#include "WiredPlugin.h"

#include <wx/string.h>
#include <wx/wx.h>

class WiredPlugin;

/**
   * \dad Window ptr of plugin's parent
   * \pos Position 
   * \size 
   */

class	WiredPluginStartInfo
{
  friend WiredPluginMgr;
  friend WiredPlugin;

 private:
  WiredCorePlugins*	Core;
  wxString		Version;
  wxWindow*		Parent;
  wxPoint		Pos;
  wxSize		Size;

  //  HostInterface GetHostCallback();
  wxString	GetVersion();
  wxWindow*	GetRack();
  wxPoint	GetPos();
  wxSize	GetSize();

  WiredPluginStartInfo();
  ~WiredPluginStartInfo();
 public:
};

#endif // __WIREDPLUGINSTARTINFO_H__
