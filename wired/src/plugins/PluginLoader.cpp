// Copyright (C) 2004-2006 by Wired Team
// Under the GNU General Public License Version 2, June 1991

#include <iostream>
#include <dlfcn.h>
#include "PluginLoader.h"
#include "config.h"


PluginLoader::PluginLoader()
{
  FileName = wxT("");
  installer = NULL;
  create_installer = NULL;
  destroy_installer = NULL;

  // TODO: init to NULL all used vars.
}

PluginLoader::~PluginLoader()
{
  Unload();
}

bool	PluginLoader::IsLoaded()
{
  return (handle.IsLoaded());
}

void	PluginLoader::Unload()
{
  // freeing class plugin
  if (installer && destroy_installer)
    destroy_installer(installer);

  // unload shared library
  if (IsLoaded())
    handle.Unload();
}

void	PluginLoader::Load(WiredExternalPluginMgr *PlugMgr, unsigned long UniqueId)
{
	PluginMgr = PlugMgr;
	//IdMenuItem = MenuItemId;
	ExternalPlug = PluginMgr->CreatePlugin(UniqueId);
	ExternalPlug->SetInfo(&InitInfo);
}

void	PluginLoader::Load(WiredExternalPluginMgr *PlugMgr, int MenuItemId, PlugStartInfo &info)
{
  External = true;
  PluginMgr = PlugMgr;
  IdMenuItem = MenuItemId;
  ExternalPlug = PluginMgr->CreatePlugin(IdMenuItem, info);
  ExternalPlug->SetInfo(&InitInfo);
  //ExternalPlug->SetVirtualSize(400, 100);
}

void	PluginLoader::Load(wxString& filename)
{
  handle.Load(filename);

  // if failed, try loading filename without PREFIX base
  // (wx load /usr/lib, /usr/local/lib/, ...)
  if (!handle.IsLoaded())
    {
      cout << "[PLUGLOADER] Warning : " <<
	wxString(wxT(INSTALL_PREFIX) + wxString(wxT("/lib/")) + filename).mb_str()
	   << " can't be loaded" << endl;
      handle.Load(filename);
    }

  // check if the library is correctly loaded
  if (handle.IsLoaded())
    {
      // check all mandatory symbols
      cout << "[PLUGLOADER] Loading symbol init..." << endl;

      create_installer = (f_installer) handle.GetSymbol(PLUGIN_SYMBOL_INSTALLER);
      if (!create_installer)
	{
	  cerr << "[PLUGLOADER] Error: Cannot load symbol : " << PLUGIN_SYMBOL_INSTALLER << endl;
	  Unload();
	  return ;
	}

      destroy_installer = (f_destroyer) handle.GetSymbol(PLUGIN_SYMBOL_DESTROYER);
      if (!destroy_installer)
	{
	  cerr << "[PLUGLOADER] Error: Cannot load symbol : " << PLUGIN_SYMBOL_DESTROYER << endl;
	  Unload();
	  return ;
	}

      // get installer from plugin (id, name, version, size, instance creator..)
      installer = create_installer();

      // check version of API
      if (!installer || installer->GetVersion() != WIRED_CURRENT_VERSION_API)
	{
	  cerr << "[PLUGLOADER] Error: Cannot load plugin " << filename.mb_str()
	       << ", it has deprecated version of API " << endl;
	  Unload();
	  return ;
	}
    }
  else
    cerr << "[PLUGLOADER] Error: Cannot open library : " << filename.mb_str() << endl;
}

WiredPlugin	*PluginLoader::CreateRack(WiredPluginStartInfo &info)
{
  if (installer)
    return (installer->Create(&info));

  ExternalPlug->SetStartInfo(&info);
  return (WiredPlugin*) ExternalPlug;
}

void		PluginLoader::Destroy(WiredPlugin *todel)
{
  if (installer)
    installer->Destroy(todel);
  else
    {
      // it's delete only one instance, and not plugin library itself.
      PluginMgr->DestroyPlugin(ExternalPlug);
      ExternalPlug = NULL;
    }
}
