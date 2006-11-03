// Copyright (C) 2004-2006 by Wired Team
// Under the GNU General Public License Version 2, June 1991

#include "WiredPluginLoader.h"
#include "config.h"

WiredPluginLoader::WiredPluginLoader()
{
  FileName = wxT("");
  installer = NULL;
  create_installer = NULL;
  destroy_installer = NULL;

  // TODO: init to NULL all used vars.
}

WiredPluginLoader::~WiredPluginLoader()
{
  Unload();
}

bool	WiredPluginLoader::IsLoaded()
{
  return (handle.IsLoaded());
}

void	WiredPluginLoader::Unload()
{
  // freeing class plugin
  if (installer && destroy_installer)
    destroy_installer(installer);

  // unload shared library
  if (IsLoaded())
    handle.Unload();
}

#if USE_DSSI
void	WiredPluginLoader::Load(WiredExternalPluginMgr *PlugMgr, unsigned long UniqueId)
{
	PluginMgr = PlugMgr;
	//IdMenuItem = MenuItemId;
	ExternalPlug = PluginMgr->CreatePlugin(UniqueId);
	ExternalPlug->SetInfo(&InitInfo);
}
#endif
#if USE_DSSI
void	WiredPluginLoader::Load(WiredExternalPluginMgr *PlugMgr, int MenuItemId, PlugStartInfo &info)
{
  External = true;
  PluginMgr = PlugMgr;
  IdMenuItem = MenuItemId;
  ExternalPlug = PluginMgr->CreatePlugin(IdMenuItem, info);
  ExternalPlug->SetInfo(&InitInfo);
  //ExternalPlug->SetVirtualSize(400, 100);
}
#endif

void	WiredPluginLoader::Load(wxString& filename)
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

WiredPlugin	*WiredPluginLoader::CreateRack(WiredPluginStartInfo &info)
{
  if (installer)
    return (installer->Create(&info));
#if USE_DSSI
  ExternalPlug->SetStartInfo(&info);
  return (WiredPlugin*) ExternalPlug;
#else
  return (NULL);
#endif
}

void		WiredPluginLoader::Destroy(WiredPlugin *todel)
{
  if (installer)
    installer->Destroy(todel);
  else
    {
      // it's delete only one instance, and not plugin library itself.
#if USE_DSSI
      PluginMgr->DestroyPlugin(ExternalPlug);
      ExternalPlug = NULL;
#endif
    }
}
