// Copyright (C) 2004 by Wired Team
// Under the GNU General Public License

#include <wx/filename.h>
#include <wx/treectrl.h>
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

const struct s_combo_choice		SortSelectChoices[NB_SORTSELECT_CHOICES + 1] =
{
  { wxT("filename")		,	1	},
  { wxT("filetype")		,	2	},
  { wxT("filesize")		,	4	},
  { wxT("Modified")		,	8	},
  { wxT("")			,	4242	}
};

MediaLibrary::MediaLibrary(wxWindow *parent, const wxPoint &pos, const wxSize &size, long style)
  : wxPanel(parent, -1, pos, size, style)
{
  wxString	sortselect_choices[NB_SORTSELECT_CHOICES];
  long		c;

  this->SetVisible();
  this->SetDocked();
  SetBackgroundColour(ML_BACKGROUND);
  SetForegroundColour(ML_FOREGROUND);

  TopToolbar = new wxToolBar(this, -1, wxPoint(-1, -1), wxSize(1000, 46), wxTB_3DBUTTONS);
  TopToolbar->AddTool(MediaLibrary_Add, _("Add"), wxBitmap(wxString(WiredSettings->DataDir + wxString(MEDIALIBRARY_ADDUP_IMG)), wxBITMAP_TYPE_PNG), wxBitmap(wxString(WiredSettings->DataDir + wxString(MEDIALIBRARY_ADDDO_IMG)), wxBITMAP_TYPE_PNG), wxITEM_NORMAL, _("Add a file"), _("Add a file"), NULL);
  TopToolbar->AddTool(MediaLibrary_Remove, _("Remove"), wxBitmap(wxString(WiredSettings->DataDir + wxString(MEDIALIBRARY_REMOVEUP_IMG)), wxBITMAP_TYPE_PNG), wxBitmap(wxString(WiredSettings->DataDir + wxString(MEDIALIBRARY_REMOVEDO_IMG)), wxBITMAP_TYPE_PNG), wxITEM_NORMAL, _("Remove file"), _("Remove file"), NULL);
  TopToolbar->AddTool(MediaLibrary_Edit, _("Edit"), wxBitmap(wxString(WiredSettings->DataDir + wxString(MEDIALIBRARY_EDITUP_IMG)), wxBITMAP_TYPE_PNG), wxBitmap(wxString(WiredSettings->DataDir + wxString(MEDIALIBRARY_EDITDO_IMG)), wxBITMAP_TYPE_PNG), wxITEM_NORMAL, _("Edit file"), _("Edit file"), NULL);
  TopToolbar->AddTool(MediaLibrary_Insert, _("Insert"), wxBitmap(wxString(WiredSettings->DataDir + wxString(MEDIALIBRARY_INSERTUP_IMG)), wxBITMAP_TYPE_PNG), wxBitmap(wxString(WiredSettings->DataDir + wxString(MEDIALIBRARY_INSERTDO_IMG)), wxBITMAP_TYPE_PNG), wxITEM_NORMAL, _("Insert file"), _("Insert file in a new track"), NULL);
  TopToolbar->Realize();

  CreateTree();
  SetTreeCollapsed();

  BottomToolbar = new wxToolBar(this, -1, wxPoint(-1, this->GetSize().y - 50), wxSize(1000, 46), wxTB_3DBUTTONS);
  BottomToolbar->AddTool(MediaLibrary_Preview, _("Preview"), wxBitmap(wxString(WiredSettings->DataDir + wxString(MEDIALIBRARY_ADDUP_IMG)), wxBITMAP_TYPE_PNG), wxBitmap(wxString(WiredSettings->DataDir + wxString(MEDIALIBRARY_ADDDO_IMG)), wxBITMAP_TYPE_PNG), wxITEM_NORMAL, _("Preview file"), _("Preview a file"), NULL);
  BottomToolbar->AddTool(MediaLibrary_TreeCollapse, _("Expand/Collapse"), wxBitmap(wxString(WiredSettings->DataDir + wxString(MEDIALIBRARY_REMOVEUP_IMG)), wxBITMAP_TYPE_PNG), wxBitmap(wxString(WiredSettings->DataDir + wxString(MEDIALIBRARY_REMOVEDO_IMG)), wxBITMAP_TYPE_PNG), wxITEM_NORMAL, _("Expand/Collapse all"), _("Expand or Collapse all tree branches"), NULL);
  for (c = 0; c < NB_SORTSELECT_CHOICES; c++)
    sortselect_choices[c] = SortSelectChoices[c].s;
  SortSelect = new wxComboBox(BottomToolbar, MediaLibrary_SortSelect, DEFAULT_SORTSELECT_VALUE, wxPoint(-1, -1), wxSize(100, -1), 4, sortselect_choices, wxCB_READONLY);
  BottomToolbar->AddControl(SortSelect);
  BottomToolbar->Realize();

  FiltersToolbar = new wxToolBar(this, -1, wxPoint(-1, this->GetSize().y - 100), wxSize(1000, 46), wxTB_3DBUTTONS);
  FiltersToolbar->AddCheckTool(MediaLibrary_FilterAudio, _("FAudio"), wxBitmap(wxString(WiredSettings->DataDir + wxString(MEDIALIBRARY_ADDUP_IMG)), wxBITMAP_TYPE_PNG), wxBitmap(wxString(WiredSettings->DataDir + wxString(MEDIALIBRARY_ADDDO_IMG)), wxBITMAP_TYPE_PNG), _("Show/Hide Audio files"), _("Show or hide audio files from the Media Library"), NULL);
  FiltersToolbar->AddCheckTool(MediaLibrary_FilterMIDI, _("FMIDI"), wxBitmap(wxString(WiredSettings->DataDir + wxString(MEDIALIBRARY_REMOVEUP_IMG)), wxBITMAP_TYPE_PNG), wxBitmap(wxString(WiredSettings->DataDir + wxString(MEDIALIBRARY_REMOVEDO_IMG)), wxBITMAP_TYPE_PNG), _("Show/Hide MIDI files"), _("Show or hide MIDI files from the Media Library"), NULL);
  FiltersToolbar->AddCheckTool(MediaLibrary_FilterVideo, _("FVideo"), wxBitmap(wxString(WiredSettings->DataDir + wxString(MEDIALIBRARY_EDITUP_IMG)), wxBITMAP_TYPE_PNG), wxBitmap(wxString(WiredSettings->DataDir + wxString(MEDIALIBRARY_EDITDO_IMG)), wxBITMAP_TYPE_PNG), _("Show/Hide Video files"), _("Show or hide video files from the Media Library"), NULL);
  FiltersToolbar->AddCheckTool(MediaLibrary_FilterEffects, _("FEffects"), wxBitmap(wxString(WiredSettings->DataDir + wxString(MEDIALIBRARY_INSERTUP_IMG)), wxBITMAP_TYPE_PNG), wxBitmap(wxString(WiredSettings->DataDir + wxString(MEDIALIBRARY_INSERTDO_IMG)), wxBITMAP_TYPE_PNG), _("Show/Hide Effects Files"), _("Show or hide effects from the Media Library"), NULL);
  FiltersToolbar->ToggleTool(MediaLibrary_FilterAudio, 3);
  FiltersToolbar->ToggleTool(MediaLibrary_FilterMIDI, 3);
  FiltersToolbar->ToggleTool(MediaLibrary_FilterVideo, 3);
  FiltersToolbar->ToggleTool(MediaLibrary_FilterEffects, 3);
  FiltersToolbar->Realize();

  TopSizer = new wxBoxSizer(wxVERTICAL);
  TopSizer->Add(TopToolbar, 0, wxALL | wxEXPAND, 0);
  TopSizer->Add(Tree, 0, wxALL | wxEXPAND, 0);
  TopSizer->Add(BottomToolbar, 0, wxALL | wxEXPAND, 0);
  TopSizer->Add(FiltersToolbar, 0, wxALL | wxEXPAND, 0);
  SetSizer(TopSizer);

}

MediaLibrary::~MediaLibrary()
{
  
}

void				MediaLibrary::CreateTree()
{

  cout << "*** [MEDIALIBRARY] Tree Creation" << this->GetSize().x << endl;
  Tree = new wxTreeCtrl((wxWindow*)this, -1, wxPoint(10, 50), wxSize(300, this->GetSize().y - 100), wxTR_DEFAULT_STYLE | wxTR_EDIT_LABELS | wxTR_MULTIPLE, wxDefaultValidator, "Tree");
  Tree->SetIndent(5);

  /* Set the Root node with the project's name in label */
  wxTreeItemId root = Tree->AppendItem(Tree->GetRootItem(), "Project's name");
  Tree->SetItemBold(root);

  /* Starting the nodes construction */
  wxTreeItemId Soundchild = Tree->AppendItem(root, "Sound Files");
  wxTreeItemId child2 = Tree->AppendItem(Soundchild, "child2");
  wxTreeItemId child3 = Tree->AppendItem(Soundchild, "child3");

  wxTreeItemId MIDIchild = Tree->AppendItem(root, "MIDI Files");
  wxTreeItemId child5 = Tree->AppendItem(MIDIchild, "child2");
  wxTreeItemId child6 = Tree->AppendItem(MIDIchild, "child3");

  wxTreeItemId Videochild = Tree->AppendItem(root, "Video Files");
  wxTreeItemId child7 = Tree->AppendItem(Videochild, "child2");
  wxTreeItemId child8 = Tree->AppendItem(Videochild, "child3");

  wxTreeItemId Effectschild = Tree->AppendItem(root, "Effects Files");
  wxTreeItemId child9 = Tree->AppendItem(Effectschild, "child2");
  wxTreeItemId child10 = Tree->AppendItem(Effectschild, "child2");

  Tree->Expand(root);
}

void				MediaLibrary::SetTreeExpanded()
{
  collapsed = false;
}

void				MediaLibrary::SetTreeCollapsed()
{
  collapsed = true;
}

bool				MediaLibrary::IsTreeCollapsed()
{
  return (collapsed);
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
  cout << "[MEDIALIBRARY] Resize (OnSize) : X = " << this->GetSize().x << "; Y = " << this->GetSize().y << endl;

  BottomToolbar->Move(0, this->GetSize().y - 100);
  FiltersToolbar->Move(0, this->GetSize().y - 50);
}

void				MediaLibrary::OnAdd(wxCommandEvent &WXUNUSED(event))
{
  cout << "[MEDIALIBRARY] Add File (OnAdd)" << endl;
  wxString FileToAdd = wxFileSelector("Add a file to the Media Library", "", "", "", "All supported files (*.*)|*.*", wxOPEN);
  if (!FileToAdd.empty())
    {
      wxFileName	*File = new wxFileName(FileToAdd);
      
      if (File->FileExists() == true)
	{
	  cout << "[MEDIALIBRARY] File added : " << FileToAdd <<  " Extention is : " << File->GetExt() << endl;
	}
    }
}

void				MediaLibrary::OnRemove(wxCommandEvent &WXUNUSED(event))
{
  //  cout << "[MEDIALIBRARY] Remove File (OnRemove)" << endl;
  wxArrayTreeItemIds		selection;
  int				selection_length;
  int				i;

  selection_length = Tree->GetSelections(selection);  
  for (i = 0; i < selection_length; i++)
    {
      if (Tree->GetItemParent(selection[i]) != Tree->GetRootItem() && selection[i] != Tree->GetRootItem())
	{
	  Tree->DeleteChildren(selection[i]);
	  Tree->Delete(selection[i]);
	}
    }
}

void				MediaLibrary::OnEdit(wxCommandEvent &WXUNUSED(event))
{
  cout << "[MEDIALIBRARY] Edit fille (OnEdit)" << endl;
}

void				MediaLibrary::OnInsert(wxCommandEvent &WXUNUSED(event))
{
  cout << "[MEDIALIBRARY] Insert File (OnInsert)" << endl;
}

void				MediaLibrary::OnFilterAudio(wxCommandEvent &WXUNUSED(event))
{
  cout << "[MEDIALIBRARY] Filter AudioFile (OnFilterAudio)" << endl;
}

void				MediaLibrary::OnFilterMIDI(wxCommandEvent &WXUNUSED(event))
{
  cout << "[MEDIALIBRARY] Filter MIDIFile (OnFilterMidi)" << endl;
}

void				MediaLibrary::OnFilterVideo(wxCommandEvent &WXUNUSED(event))
{
  cout << "[MEDIALIBRARY] Filter VideoFile (OnFilterVideo)" << endl;
}

void				MediaLibrary::OnFilterEffects(wxCommandEvent &WXUNUSED(event))
{
  cout << "[MEDIALIBRARY] Filter EffectsFile (OnFilterEffects)" << endl;
}

void				MediaLibrary::OnPreview(wxCommandEvent &WXUNUSED(event))
{
  cout << "[MEDIALIBRARY] Preview File (OnPreview)" << endl;
}

void				MediaLibrary::OnSortToggle(wxCommandEvent &WXUNUSED(event))
{
  cout << "[MEDIALIBRARY] Sort Files (OnSortToggle)" << endl;

}

void				ExpandAll(wxTreeCtrl *Tree, const wxTreeItemId& id, bool shouldExpand, int toLevel)
{
  if (toLevel == 0 || !Tree->ItemHasChildren(id)) 
    return;

  bool isExpanded = Tree->IsExpanded(id);

  if (shouldExpand && !isExpanded)
    Tree->Expand(id);
  else if (!shouldExpand && isExpanded)
    Tree->Collapse(id);

  wxTreeItemIdValue cookie = &Tree;
  for (wxTreeItemId child = Tree->GetFirstChild(id, cookie); child.IsOk(); child = Tree->GetNextChild(id, cookie))
    ExpandAll(Tree, child, shouldExpand, toLevel - 1);
}

void				MediaLibrary::OnCollapse(wxCommandEvent &WXUNUSED(event))
{
  cout << "[MEDIALIBRARY] Expand/Collapse Tree (OnCollapse)" << endl;
  if (IsTreeCollapsed() == true)
    {
      ExpandAll(Tree, Tree->GetRootItem(), true, 2);
      SetTreeExpanded();
    }
  else
    {
      wxTreeItemIdValue cookie = &Tree;
      ExpandAll(Tree, Tree->GetRootItem(), false, 2);
      Tree->EnsureVisible(Tree->GetFirstChild(Tree->GetRootItem(), cookie));
      SetTreeCollapsed();
    }
}

BEGIN_EVENT_TABLE(MediaLibrary, wxPanel)
  EVT_SIZE(MediaLibrary::OnSize)
  EVT_TOOL(MediaLibrary_Add, MediaLibrary::OnAdd)
  EVT_TOOL(MediaLibrary_Remove, MediaLibrary::OnRemove)
  EVT_TOOL(MediaLibrary_Edit, MediaLibrary::OnEdit)
  EVT_TOOL(MediaLibrary_Insert, MediaLibrary::OnInsert)
  EVT_TOOL(MediaLibrary_Preview, MediaLibrary::OnPreview)
  EVT_TOOL(MediaLibrary_TreeCollapse, MediaLibrary::OnCollapse)
  EVT_TOOL(MediaLibrary_SortSelect, MediaLibrary::OnSortToggle)
  EVT_TOOL(MediaLibrary_FilterAudio, MediaLibrary::OnFilterAudio)
  EVT_TOOL(MediaLibrary_FilterMIDI, MediaLibrary::OnFilterMIDI)
  EVT_TOOL(MediaLibrary_FilterVideo, MediaLibrary::OnFilterVideo)
  EVT_TOOL(MediaLibrary_FilterEffects, MediaLibrary::OnFilterEffects)
END_EVENT_TABLE()
