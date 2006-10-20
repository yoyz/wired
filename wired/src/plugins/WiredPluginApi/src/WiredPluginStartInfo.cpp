#include "WiredPluginStartInfo.h"


WiredPluginStartInfo::WiredPluginStartInfo()
{

}

WiredPluginStartInfo::~WiredPluginStartInfo()
{

}


WiredCorePlugins	WiredPluginStartInfo::GetCore()
{
  return core;
}

wxString		WiredPluginStartInfo::GetVersion()
{
  return Version;
}

wxWindow*		WiredPluginStartInfo::GetRack()
{
  return Rack;
}

wxPoint			WiredPluginStartInfo::GetPos()
{
  return Pos;
}

wxSize			WiredPluginStartInfo::GetSize()
{
  return Size;
}

