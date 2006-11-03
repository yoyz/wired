// Copyright (C) 2004-2006 by Wired Team
// Under the GNU General Public License Version 2, June 1991

#ifndef __PLUGINCENTER_H__
#define __PLUGINCENTER_H__

#include "WiredPlugin.h"
#include "../dssi/WiredExternalPluginMgr.h"

#include <map>
#include <vector>

#include <wx/wx.h>
#include <wx/filename.h>
#include <wx/string.h>
#include <wx/menu.h>

/**
 * Manage all plugins in Wired
 */
class				PluginCenter
{
 private:
  std::vector<PluginLoader *>	LoadedPluginsList;
  WiredExternalPluginMgr*	LoadedExternalPlugins;

  std::map<wxMenu*,wxString>	menus;
  wxMenu*			menuInstruments;
  wxMenu*			menuEffects;


 public:
  PluginCenter();
  ~PluginCenter();

  int				LoadPlugin(wxString& filename);
  void				LoadPlugins();
  void				LoadExternalPlugins();
  int				AddPluginMenuItem(int Type, bool IsEffect, const wxString& MenuName);
  void				OnCreateExternalPlugin(wxCommandEvent &event);
  void				OnCreateRackClick(wxCommandEvent& event);
  void				OnCreateEffectClick(wxCommandEvent& event);


  int				LoadPluginFile(wxString& filename);
  int				LoadPluginDirectory(wxFileName& path);

  std::map<wxMenu*,wxString>&	GetMenus() { return (menus); };
};

#endif
