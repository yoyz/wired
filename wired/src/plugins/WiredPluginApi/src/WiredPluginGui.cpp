#include "WiredPluginGui.h"


//WiredPluginGui::WiredPluginGui(WiredPluginStartInfo *parent) { StartInfo = parent; } ;
WiredPluginGui~WiredPluginGui()
{

}

/* Ask the host application to call Update() whenever the main thread can process gui calls  */
void	 WiredPluginGui::UpdatePluginGui()
{
  //StartInfo.HostCallback(this, wiredAskUpdateGui, 0x0);
  _StartInfo->GetCore()->UpdatePluginGui();
}


/* Used to know if a keyboard event occured. No need to overload */
void	 WiredPluginGui::OnKeyEvent(wxKeyEvent &event)
{
  _StartInfo->GetCore()->SendKeyEvent(this, event);
}

/* Used to know if a mouse event occured. No need to overload */
void	WiredPluginGui::OnMouseEvent(wxMouseEvent &event)
{
  _StartInfo->GetCore()->SendMouseEvent(this, event);
}

/* Used to know if a paint event occured. No need to overload */
void	 WiredPluginGui::OnPaintEvent(wxPaintEvent &event)
{
  _StartInfo->GetCore()->SendPaintEvent(this, event);
}

 // User interface events
/* Send help wxString to the Wired help window */
void	 WiredPluginGui::SendHelp(wxString str)
{
  _StartInfo->GetCore()->SendHelp(str);
}

bool	 WiredPluginGui::ShowMidiController()
{
  _StartInfo->GetCore()->ShowMidiController(this);
  if (_StartInfo->GetCore()->GetLastMidiType() == -1)
    return false;
  return true;
}

/* Shows plugin's optional view */
void	 WiredPluginGui::ShowOptionalView()
{
  _StartInfo->GetCore()->ShowOptionalView(this);
}

/* Closes plugin's optional view */
void	 WiredPluginGui::CloseOptionalView()
{
  _StartInfo->GetCore()->CloseOptionalView(this);
}


  /* Opens the Wired file loader with given title, extensions, and if it should read
     AKAI audio cds/files or not. Returns the selected file name or an empty wstring if
     cancelled. If 'exts' is NULL, default audio extensions are used. */
wxString	WiredPluginGui::OpenFileLoader(wxString& title,
					       std::vector<wxString>& exts,
					       bool addExts,
					       bool akai)
{
  return _StartInfo->GetCore()->OpenFileLoader(title, exts, addExts, akai);
}

/* Opens the Wired file loader with given title, extensions, for saving a file.
   Returns the file name or an empty wstring if cancelled */
wxString	WiredPluginGui::SaveFileLoader(wxString& title,
					       std::vector<wxString>& exts,
					       bool addExts)
{
  return _StartInfo->GetCore()->SaveFileLoader(title, exts, addExts);
}

// Sequencer events
/* Create a MIDI pattern containing a list of event in the host's sequencer */
bool		WiredCorePlugins::AddMidiPattern(std::list<SeqCreateEvent *>& midi)
{
  return _StartInfo->GetCore()->AddMidiPattern(midi);
}
