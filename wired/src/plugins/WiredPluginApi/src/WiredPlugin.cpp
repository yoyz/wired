// Copyright (C) 2004-2006 by Wired Team
// Under the GNU General Public License Version 2, June 1991

#include "WiredPlugin.h"

#include "WiredCorePlugins.h"
#include "WiredPluginStartInfo.h"

using namespace std;

/* DO NOT MODIFY THIS FILE FOR MAKING A PLUGIN. JUST DERIVE FROM THAT CLASS */

WiredPlugin::WiredPlugin(WiredPluginInstaller* creator,
			 WiredPluginStartInfo* start) :
  wxWindow(start->GetRack(), -1, start->GetPos(), start->GetSize()),
  WiredPluginGui(start),
  WiredPluginAudio(start)
{
  _StartInfo = start;
  _CreatorInfo = creator;


  if (!start || !creator)
    throw ;

//   if (InitInfo)
//   	InitInfo->UniqueExternalId = 0;
//   Connect(wxID_ANY, wxEVT_KEY_DOWN, (wxObjectEventFunction)(wxEventFunction)
//           &Plugin::OnKeyEvent);
//   Connect(wxID_ANY, wxEVT_MOUSEWHEEL, (wxObjectEventFunction)(wxEventFunction)
//           &Plugin::OnMouseEvent);
//   Connect(wxID_ANY, wxEVT_LEFT_DOWN, (wxObjectEventFunction)(wxEventFunction)
//           &Plugin::OnMouseEvent);
//   Connect(wxID_ANY, wxEVT_LEFT_UP, (wxObjectEventFunction)(wxEventFunction)
//           &Plugin::OnMouseEvent);
//   Connect(wxID_ANY, wxEVT_MOTION, (wxObjectEventFunction)(wxEventFunction)
// 	 &Plugin::OnMouseEvent);
//   Connect(wxID_ANY, wxEVT_RIGHT_DOWN, (wxObjectEventFunction)(wxEventFunction)
// 	 &Plugin::OnMouseEvent);
  //  Connect(wxID_ANY, wxEVT_PAINT, (wxObjectEventFunction)(wxEventFunction)
  //	 &Plugin::OnPaintEvent);
}

WiredPlugin::~WiredPlugin()
{
  CloseOptionalView();
}


/**
 * Private
 */
WiredPluginStartInfo*	WiredPlugin::GetStartInfo()
{
  return _StartInfo;
}


/**
 * Public
 */
wxString&	WiredPlugin::GetName()
{
  return (_CreatorInfo->GetName());
}

/**
 * Gui: Ask the host application to call Update() whenever the main thread can process gui calls
 */
void	 WiredPlugin::UpdatePluginGui()
{
  _StartInfo->GetCore()->UpdatePluginGui(this);
}

/**
 * Audio: Used to know if a keyboard event occured. No need to overload
*/
void	 WiredPlugin::OnKeyEvent(wxKeyEvent* event)
{
  _StartInfo->GetCore()->SendKeyEvent(this, event);
}

/**
 * Audio: Used to know if a mouse event occured. No need to overload
*/
void	WiredPlugin::OnMouseEvent(wxMouseEvent* event)
{
  _StartInfo->GetCore()->SendMouseEvent(this, event);
}

/**
 *Audio: Used to know if a paint event occured. No need to overload
*/
void	 WiredPlugin::OnPaintEvent(wxPaintEvent* event)
{
  _StartInfo->GetCore()->SendPaintEvent(this, event);
}

/**
 * Gui
 */
bool	 WiredPlugin::ShowMidiController()
{
  _StartInfo->GetCore()->ShowMidiController(this);
  if (_StartInfo->GetCore()->GetLastMidiType() == -1)
    return false;
  return true;
}

/**
 * Audio: Shows plugin's optional view
*/
void	 WiredPlugin::ShowOptionalView()
{
  _StartInfo->GetCore()->ShowOptionalView(this);
}

/**
 * Audio: Closes plugin's optional view
*/
void	 WiredPlugin::CloseOptionalView()
{
  _StartInfo->GetCore()->CloseOptionalView(this);
}

/**
 * Audio: Create a MIDI pattern containing a list of event in the host's sequencer
*/
void	WiredPlugin::AddMidiPattern(std::list<SeqCreateEvent *>* midi)
{
  _StartInfo->GetCore()->AddMidiPattern(this, midi);
}
