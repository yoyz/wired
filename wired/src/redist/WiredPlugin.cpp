// Copyright (C) 2004-2006 by Wired Team
// Under the GNU General Public License Version 2, June 1991

#include "WiredPlugin.h"

using namespace std;

/* DO NOT MODIFY THIS FILE FOR MAKING A PLUGIN. JUST DERIVE FROM THAT CLASS */

WiredPlugin::WiredPlugin(WiredPluginStartInfo* start)
  : wxWindow(start.Rack, -1, start.Pos, start.Size)
{
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
//   //  Connect(wxID_ANY, wxEVT_PAINT, (wxObjectEventFunction)(wxEventFunction)
//   //	 &Plugin::OnPaintEvent);
}

WiredPlugin::~WiredPlugin()
{
  CloseOptionalView();
}

 /* Returns the host product name */
wxString	WiredPlugin::GetProductName()
{
  return StartInfo->GetCore()->GetProductName();
}

/* Returns the host product version */
wxString	WiredPlugin::GetProductVersion()
{
  return StartInfo->GetCore()->GetProductVersion();
}
