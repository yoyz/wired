#include "WiredPluginGui.h"

#include "WiredCorePlugins.h"



WiredPluginGui::~WiredPluginGui()
{

}

// User interface events
/* Send help wxString to the Wired help window */
void	 WiredPluginGui::SendHelp(wxString str)
{
  _StartInfo->GetCore()->SendHelp(str);
}


  /* Opens the Wired file loader with given title, extensions, and if it should read
     AKAI audio cds/files or not. Returns the selected file name or an empty wstring if
     cancelled. If 'exts' is NULL, default audio extensions are used. */
wxString	WiredPluginGui::OpenFileLoader(wxString& title,
					       std::vector<wxString>* exts,
					       bool addExts,
					       bool akai)
{
  return _StartInfo->GetCore()->OpenFileLoader(title, exts, addExts, akai);
}

/* Opens the Wired file loader with given title, extensions, for saving a file.
   Returns the file name or an empty wstring if cancelled */
wxString	WiredPluginGui::SaveFileLoader(wxString& title,
					       std::vector<wxString>* exts,
					       bool addExts)
{
  return _StartInfo->GetCore()->SaveFileLoader(title, exts, addExts);
}
