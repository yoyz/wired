// Copyright (C) 2004 by Wired Team
// Under the GNU General Public License

#include <wx/filename.h>
#include "MediaLibrary.h"
#include "Sequencer.h"
#include "SequencerGui.h"
#include "Colour.h"
#include "WiredSession.h"
#include "HelpPanel.h"
#include "DownButton.h"
#include "HoldButton.h"
#include "StaticLabel.h"
#include "VUMCtrl.h"
#include "../engine/Settings.h"
#include "../engine/AudioEngine.h"

extern WiredSession				*CurrentSession;

MediaLibrary::MediaLibrary(wxWindow *parent, const wxPoint &pos, const wxSize &size, long style)
  : wxPanel(parent, -1, pos, size, style)
{
  SetBackgroundColour(CL_RULER_BACKGROUND);
  this->SetVisible();
  this->SetDocked();

  
}

MediaLibrary::~MediaLibrary()
{

}

void				MediaLibrary::SetSize(int x, int y)
{
  size_x = x;
  size_y = y;
}


int				MediaLibrary::GetXSize()
{
  return (size_x);
}

int				MediaLibrary::GetYSize()
{
  return (size_y);
}

bool				MediaLibrary::IsVisible()
{
  return (visible);
}

void				MediaLibrary::SetInvisible()
{
  visible = false;
}

void				MediaLibrary::SetVisible()
{
  visible = true;
}

bool				MediaLibrary::IsFloating()
{
  return (floating);
}

void				MediaLibrary::SetFloating()
{
  floating = true;
}

void				MediaLibrary::SetDocked()
{
  floating = false;
}

void				MediaLibrary::OnSize(wxSizeEvent &event)
{
  cout << "[MEDIALIBRARY] Resize (OnSize)" << endl;
  //this->SetSize(wxSize(100, GetSize().y - 200));
  //  MediaLibraryPanel->SetSize(wxSize(GetSize().x + 4, GetSize().y));
}

BEGIN_EVENT_TABLE(MediaLibrary, wxPanel)
  EVT_SIZE(MediaLibrary::OnSize)
END_EVENT_TABLE()
