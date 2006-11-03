// Copyright (C) 2004-2006 by Wired Team
// Under the GNU General Public License Version 2, June 1991

#ifndef __PLUGINLOADER_H__
#define __PLUGINLOADER_H__

#include "WiredPlugin.h"
#include "WiredExternalPluginMgr.h"
#include <wx/wx.h>
#include <wx/dynlib.h>

using namespace std;

// MANDATORY C FUNCTIONS

// Called when the host initializes the plugin's shared library (usually at startup)
typedef WiredPluginInstaller*	(*f_installer)();
// Called when the host needs to unload the plugin's shared library
typedef void			(*f_destroyer)(WiredPluginInstaller *);

// name of mandatory functions
#define PLUGIN_SYMBOL_INSTALLER (createInstaller)
#define PLUGIN_SYMBOL_DESTROYER (destroyInstaller)

/**
 * Loads/Unloads Wired plugin library.
 */
class				WiredPluginLoader
{
 private:

  /**
   * used to load and get symbol from dynamic library
   */
  wxDynamicLibrary		handle;

  /**
   * function ptr from the plugin
   */
  f_installer			create_installer;
  f_destroyer			destroy_installer;

  /**
   * Class who handle installation of plugin
   */
  WiredPluginInstaller*		installer;

  /**
   *
   */
  WiredDSSIGui			*ExternalPlug;

  /**
   *
   */
  WiredExternalPluginMgr	*PluginMgr;


  /**
   *
   */
  int				IdMenuItem;

 public:

  /**
   *
   */
  WiredPluginLoader(wxString filename);

  /**
   *
   */
  WiredPluginLoader(WiredExternalPluginMgr *PlugMgr, int MenuItemId, WiredPluginStartInfo &info);

  /**
   *
   */
  ~WiredPluginLoader();

  /**
   *
   */
  WiredPlugin			*CreateRack(WiredPluginStartInfo &info);

  /**
   *
   */
  void				Destroy(WiredPlugin *p);

  /**
   *
   */
  bool				IsLoaded();

  /**
   *
   */
  wxString			FileName;

  /**
   *
   */
  int				Id;
};

#endif
