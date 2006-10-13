// Copyright (C) 2004-2006 by Wired Team
// Under the GNU General Public License Version 2, June 1991

#ifndef _WIREDEXTERNALPLUGIN_H_
#define _WIREDEXTERNALPLUGIN_H_

#include "dssi.h"
#include "WiredExternalPluginLADSPA.h"

#include <wx/dynlib.h>
#include <map>

#define STR_DSSI_DESCRIPTOR_FUNCTION_NAME wxT("dssi_descriptor")
#define STR_LADSPA_DESCRIPTOR_FUNCTION_NAME wxT("ladspa_descriptor")

/**
 * Class who handle DSSI and LADSPA plugin.
 * It manage Load and Unload of external dynamic library (not using Wired API)
 */
class	WiredExternalPlugin
{
 public:
  /**
   * Default constructor
   */
  WiredExternalPlugin();
  ~WiredExternalPlugin();

  /**
   * Constructor from another instance of class
   * \param copy Copy all private value into the new class
   */
  WiredExternalPlugin(const WiredExternalPlugin& copy);

  /**
   * Same as WiredExternalPlugin(const WiredExternalPlugin& copy);
   */
  WiredExternalPlugin		operator=(const WiredExternalPlugin& right);

  /**
   * Load an external plugin DSSI or LADSPA.
   * \param FileName Name of the file. We advice without extension, but it works with.
   * \param FirstIndex Index of new plugin. It'll be incremented if successfully loaded.
   * \return True if loaded and false overwise.
   */
  bool				Load(const wxString& FileName, int& FirstIndex);

  /**
   * Unload previously loaded plugin
   */
  void				UnLoad();

  /**
   * Get a map of plugins previously loaded. The key is FirstIndex from Load() and
   * value is the name of Plugin.
   * If the current plugin is a LADSPA, it return all LADSPA loaded plugins.
   * It return all DSSI loaded plugins overwise.
   */
  std::map<int, wxString>	GetPluginsList();

  /**
   * Return type of plugin 
   * \param  PluginId id gave from plugin creation (FirstIndex).
   * \return Xor of TYPE_PLUGINS_DSSI or TYPE_PLUGINS_LADSPA and TYPE_PLUGINS_INSTR or TYPE_PLUGINS_EFFECT
   */
  int				GetPluginType(int PluginId);

  /**
   * Return if a plugin was insered or not.
   * \param  PluginId id gave from plugin creation (FirstIndex).
   * \return true if a plugin was previously insered or false overwise.
   */
  bool				Contains(int PluginId);

  /**
   * Create an instance of Plugin for previsously loaded Plugin.
   * \param PluginId id gave from plugin creation (FirstIndex).
   * \param Plugin Instance of plugin (LADSPA or DSSI)
   * \return true if plugin is successfully created.
   */
  bool				CreatePlugin(int PluginId, WiredLADSPAInstance *Plugin);

  /**
   * \param PluginUniqueId Use ID from plugin instead PluginId.
   * \see Contains(int PluginId);
   */
  bool				Contains(unsigned long PluginUniqueId);

  /**
   * Same as GetPluginsList() but return PluginUniqueId instead PluginId.
   * \see GetPluginsList()
   */ 
  std::map<int, unsigned long>	GetPluginsListUniqueId();

 private:
  wxString				_FileName;
  wxDynamicLibrary			_Handle;
  DSSI_Descriptor_Function		_DSSIDescriptorFunction;

  //Key == PluginId; Value == PluginDescriptor
  std::map<int, const DSSI_Descriptor*>	_DSSIDescriptors;
  LADSPA_Descriptor_Function		_LADSPADescriptorFunction;

  //Key == PluginId; Value == PluginDescriptor
  std::map<int, const LADSPA_Descriptor*>	_LADSPADescriptors;
  std::map<int, int>						_PluginsInfo;
};


#endif //_WIREDEXTERNALPLUGIN_H_
