#include "WiredPluginStartInfo.h"


WiredPluginStartInfo::WiredPluginStartInfo()
{

}

WiredPluginStartInfo::~WiredPluginStartInfo()
{

}


WiredCorePlugins*	WiredPluginStartInfo::GetCore()
{
  return _Core;
}

wxString		WiredPluginStartInfo::GetVersion()
{
  return _Version;
}

wxWindow*		WiredPluginStartInfo::GetRack()
{
  return _Parent;
}

wxPoint			WiredPluginStartInfo::GetPos()
{
  return _Pos;
}

wxSize			WiredPluginStartInfo::GetSize()
{
  return _Size;
}

