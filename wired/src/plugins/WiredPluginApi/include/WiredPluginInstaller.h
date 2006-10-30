#ifndef __WIREDPLUGININSTALLER__
#define __WIREDPLUGININSTALLER__

#include "WiredPlugin.h"
#include "WiredPluginStartInfo.h"

/**
 * Determine type of plugin
 * \ePlugTypeUnknown Unknown type
 * \ePlugTypeInstrument Instrument type
 * \ePlugTypeEffect Effect type
 */
enum ePlugType {
  ePlugTypeUnknown = 0,
  ePlugTypeInstrument,
  ePlugTypeEffect
};

class		WiredPluginInstaller
{
 public:
  //  virtual	WiredPluginInstaller();
  //  virtual	~WiredPluginInstaller();

  /**
   * Get Name of plugin
   */
  virtual wxString	GetName();

  /**
   * Get Type of plugin
   * \return ePlugType type enumered, ePlugTypeUnknown, ePlugTypeInstrument, ePlugTypeEffect, ..
   */
  virtual ePlugType	GetType();

  /**
   * Get Width of an instance of plugin in the Rack panel
   * \return int Width in unit of 200 pixels
   */
  virtual int		GetWidth();

  /**
   * Get Height of an instance of plugin in the Rack panel
   * \return int Height in unit of 200 pixels
   */
  virtual int		GetHeight();

  /**
   * Get version of API used by the plugin
   */
  virtual int		GetVersion();

  /**
   * Create an instance of the plugin.
   * For exemple, its called when users add an instrument.
   * \WiredPluginStartInfo informations needed by the constructor of WiredPlugin
   */
  virtual WiredPlugin*	Create(WiredPluginStartInfo* start);

  /**
   * Destroy an instance of the plugin.
   * For exemple, its called when users remove an instrument.
   */
  virtual void		Destroy(WiredPlugin* plugin);

  /**
   * Returns the host product data path
   */
  //wxString	GetDataPath() { return (wxT(INSTALL_PREFIX)); }
};

/**
 * Create a WiredPluginInstaller class
 */
WiredPluginInstaller*	createInstaller();

/**
 * Delete a WiredPluginInstaller class
 */
void			destroyInstaller(WiredPluginInstaller* installer);

#endif // __WIREDPLUGININSTALLER__
