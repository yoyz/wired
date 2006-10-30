#include <wx/menu.h>
#include <wx/string.h>

#include "Settings.h"

#include "PluginLoader.h"
#include "PluginCenter.h"

#include "WiredCorePlugins.h"

#ifdef __DSSI__
# include "WiredExternalPluginMgr.h"
#endif

PluginCenter::PluginCenter()
{
  _StartInfo._Core = new WiredCorePlugins();
  _StartInfo._Version = wxT(PACKAGE_VERSION);
  _StartInfo._Parent = RackPanel;

#ifdef __DSSI__
  LoadedExternalPlugins = new WiredExternalPluginMgr();
#endif

  menuInstruments = new wxMenu;
  menuEffects = new wxMenu;

  menus.push_back(menuInstruments, _("&Instruments"));
  menus.push_back(menuEffects, _("Effec&ts"));
}

PluginCenter::~PluginCenter()
{

}

int		PluginCenter::LoadPlugin(wxString& filename)
{
  return (0);
}

int		PluginCenter::LoadPluginDirectory(wxFilename& path)
{
  return (0);
}

void		PluginCenter::LoadPlugins()
{
  wxString	str;
  PluginLoader	*p;

  if (!PluginsConfFile.Open(WiredSettings->PlugConfFile))
    {
      cerr << "Could not load " << WiredSettings->PlugConfFile.mb_str() << endl;
      return;
    }
  PluginMenuIndexCount = PLUG_MENU_INDEX_START;
  for (str = PluginsConfFile.GetFirstLine(); !PluginsConfFile.Eof();
       str = PluginsConfFile.GetNextLine())
    {
      if ((str.length() > 0) && (str.at(0) != '#'))
	{
	  p = new PluginLoader(str);
	  if (p->IsLoaded())
	    {
	      LoadedPluginsList.push_back(p);

	      p->Id = PluginMenuIndexCount++;
	      if (p->InitInfo.Type == ePlugTypeInstrument)
		{
		  menuInstruments->Append(p->Id, p->InitInfo.Name);
		  Connect(p->Id, wxEVT_COMMAND_MENU_SELECTED,
			  (wxObjectEventFunction)(wxEventFunction)
			  (wxCommandEventFunction)&PluginCenter::OnCreateRackClick);
		}
	      else if (p->InitInfo.Type == ePlugTypeEffect)
		{
		  menuEffects->Append(p->Id, p->InitInfo.Name);
		  Connect(p->Id, wxEVT_COMMAND_MENU_SELECTED,
			  (wxObjectEventFunction)(wxEventFunction)
			  (wxCommandEventFunction)&PluginCenter::OnCreateEffectClick);
		}
	      else
		cout << "[MAINWIN] Plugin type unknown" << endl;
	      cout << "[MAINWIN] Plugin " << p->InitInfo.Name.mb_str() << " is working" << endl;
	    }
	  else
	    delete p;
	}
    }
}

void					PluginCenter::LoadExternalPlugins()
{
//  map<int, wstring>				PluginsList;
  list<wxString>					PluginsList;
  //  map<int, wstring>::iterator	IterPluginsList;
  list<wxString>::iterator		IterPluginsList;
  int							PluginInfo;
  int							PluginId;
  wxString						PluginName, Sep(wxT("#"));

  CreateDSSIInstrMenu = NULL;
  CreateLADSPAInstrMenu = NULL;
  CreateDSSIEffectMenu = NULL;
  CreateLADSPAEffectMenu = NULL;
  LoadedExternalPlugins->LoadPLugins(TYPE_PLUGINS_DSSI | TYPE_PLUGINS_LADSPA);
  LoadedExternalPlugins->SetStartInfo(StartInfo);
  PluginsList = LoadedExternalPlugins->GetSortedPluginsList(Sep);

  for (IterPluginsList = PluginsList.begin(); IterPluginsList != PluginsList.end(); IterPluginsList++)
    {
      if ((*IterPluginsList).find_last_of(Sep.c_str()) > 0)
  	{
	  PluginName = (*IterPluginsList).substr(0, (*IterPluginsList).find_last_of(Sep));
	  PluginId = atoi(wxString((*IterPluginsList).substr((*IterPluginsList).find_last_of(Sep) + 1).c_str(), *wxConvCurrent).mb_str(*wxConvCurrent));
  	}
      //  	PluginInfo = LoadedExternalPlugins->GetPluginType(IterPluginsList->first);
      PluginInfo = LoadedExternalPlugins->GetPluginType(PluginId);

      //  	LoadedExternalPlugins->SetMenuItemId(IterPluginsList->first,
      //  		AddPluginMenuItem(PluginInfo, PluginInfo & TYPE_PLUGINS_EFFECT, IterPluginsList->second));
      LoadedExternalPlugins->SetMenuItemId(PluginId,
					   AddPluginMenuItem(PluginInfo, PluginInfo & TYPE_PLUGINS_EFFECT, PluginName));
    }
}

int						PluginCenter::AddPluginMenuItem(int Type, bool IsEffect, const wxString& MenuName)
{
  int					Id = PluginMenuIndexCount++;
  wxMenuItem			*NewItem;

  if (IsEffect == true)
    {
      if (Type & TYPE_PLUGINS_DSSI)
	{
	  if (!CreateDSSIEffectMenu)
	    {
	      CreateDSSIEffectMenu = new wxMenu();
	      CreateEffectMenu->Append(Id, wxT("DSSI"), CreateDSSIEffectMenu);
	      Id = PluginMenuIndexCount++;
	    }
	  NewItem = CreateDSSIEffectMenu->Append(Id, MenuName.c_str());
	}
      else if (Type & TYPE_PLUGINS_LADSPA)
	{
	  if (!CreateLADSPAEffectMenu)
	    {
	      CreateLADSPAEffectMenu = new wxMenu();
	      CreateEffectMenu->Append(Id, wxT("LADSPA"), CreateLADSPAEffectMenu);
	      Id = PluginMenuIndexCount++;
	    }
	  NewItem = CreateLADSPAEffectMenu->Append(Id, MenuName.c_str());
	}
    }
  else
    {
      if (Type & TYPE_PLUGINS_DSSI)
	{
	  if (!CreateDSSIInstrMenu)
	    {
	      CreateDSSIInstrMenu = new wxMenu();
	      CreateInstrMenu->Append(Id, wxT("DSSI"), CreateDSSIInstrMenu);
	      Id = PluginMenuIndexCount++;
	    }
	  NewItem = CreateDSSIInstrMenu->Append(Id, MenuName.c_str());
	}
      else if (Type & TYPE_PLUGINS_LADSPA)
	{
	  if (!CreateLADSPAInstrMenu)
	    {
	      CreateLADSPAInstrMenu = new wxMenu();
	      CreateInstrMenu->Append(Id, wxT("LADSPA"), CreateLADSPAInstrMenu);
	      Id = PluginMenuIndexCount++;
	    }
	  NewItem = CreateLADSPAInstrMenu->Append(Id, MenuName.c_str());
	}
    }
  if (NewItem)
    Connect(Id, wxEVT_COMMAND_MENU_SELECTED,
	    (wxObjectEventFunction)(wxEventFunction)
	    (wxCommandEventFunction)&PluginCenter::OnCreateExternalPlugin);
  return Id;
}

void					PluginCenter::OnCreateExternalPlugin(wxCommandEvent &event)
{
  if (LoadedExternalPlugins)
    {
      PluginLoader 	*NewPlugin = new PluginLoader(LoadedExternalPlugins, event.GetId(), StartInfo);

      LoadedPluginsList.push_back(NewPlugin);
      cout << "[MAINWIN] Creating rack for plugin: " << NewPlugin->InitInfo.Name.mb_str() << endl;
      cActionManager::Global().AddEffectAction(&StartInfo, NewPlugin, true);
    }
}

void					PluginCenter::OnCreateRackClick(wxCommandEvent& event)
{
  int					id = event.GetId();
  vector<PluginLoader *>::iterator	i;
  PluginLoader				*p = 0x0;

  for (i = LoadedPluginsList.begin(); i != LoadedPluginsList.end(); i++)
    if ((*i)->Id == id)
      {
	p = *i;
	break;
      }
  if (p)
    {
      cout << "[MAINWIN] Creating rack for plugin: " << p->InitInfo.Name.mb_str() << endl;
      cCreateRackAction* action = new cCreateRackAction(&StartInfo,  p);
      action->Do();
    }
}

void					PluginCenter::OnCreateEffectClick(wxCommandEvent& event)
{
  int					id = event.GetId();
  vector<PluginLoader *>::iterator	i;
  PluginLoader				*p = 0x0;

  for (i = LoadedPluginsList.begin(); i != LoadedPluginsList.end(); i++)
    if ((*i)->Id == id)
      {
	p = *i;
	break;
      }
  if (p)
    {
      cout << "[MAINWIN] Creating rack for plugin: " << p->InitInfo.Name.mb_str() << endl;
      cActionManager::Global().AddEffectAction(&StartInfo, p, true);
      CreateUndoRedoMenus(EditMenu);
    }
}
