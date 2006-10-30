// Copyright (C) 2004-2006 by Wired Team
// Under the GNU General Public License Version 2, June 1991

#ifndef __PLUGINCENTER_H__
#define __PLUGINCENTER_H__

#include "WiredPlugin.h"
#include "../dssi/WiredExternalPluginMgr.h"

#include <map>

/**
 * Manage all plugins in Wired
 */
class				PluginCenter
{
 private:
  vector<PluginLoader *>	LoadedPluginsList;
  WiredExternalPluginMgr*	LoadedExternalPlugins;

  std::map<wxMenu,wxString>	menus;
  wxMenu			menuInstruments;
  wxMenu			menuEffects;


 public:
  PluginCenter();
  ~PluginCenter();

  int				LoadPluginFile(wxString& filename);
  int				LoadPluginDirectory(wxFilename& path);

  std::map<wxMenu,wxString>&	GetMenus() { return (menus); };
};

#endif
