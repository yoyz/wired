// Copyright (C) 2004 by Wired Team
// Under the GNU General Public License

#include <wx/filename.h>
#include <wx/treectrl.h>
#include "MediaLibrary.h"
#include "MLTree.h"
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


MLTree::MLTree(wxWindow *MediaLibraryPanel)
{
  //  cout << "*** [MEDIALIBRARY] Tree Creation" << MediaLibraryPanel->GetSize().x << endl;

  Tree = new wxTreeCtrl((wxWindow*)MediaLibraryPanel, -1, wxPoint(10, 50),
			wxSize(300, MediaLibraryPanel->GetSize().y - 100),
			wxTR_DEFAULT_STYLE | wxTR_EDIT_LABELS | wxTR_MULTIPLE,
			wxDefaultValidator, _("Tree"));
  Tree->SetIndent(5);
  
  /* Set the Root node with the project's name in label */
  root = Tree->AppendItem(Tree->GetRootItem(), _("Project's name"));
  Tree->SetItemBold(root);

  /* Starting the nodes construction */
  Soundchild = Tree->AppendItem(root, _("Sound Files"));
  wxTreeItemId child2 = Tree->AppendItem(Soundchild, _("child2"));
  wxTreeItemId child3 = Tree->AppendItem(Soundchild, _("child3"));

  wxTreeItemId MIDIchild = Tree->AppendItem(root, _("MIDI Files"));
  wxTreeItemId child5 = Tree->AppendItem(MIDIchild, _("child2"));
  wxTreeItemId child6 = Tree->AppendItem(MIDIchild, _("child3"));

  wxTreeItemId Videochild = Tree->AppendItem(root, _("Video Files"));
  wxTreeItemId child7 = Tree->AppendItem(Videochild, _("child2"));
  wxTreeItemId child8 = Tree->AppendItem(Videochild, _("child3"));

  wxTreeItemId Effectschild = Tree->AppendItem(root, _("Effects Files"));
  wxTreeItemId child9 = Tree->AppendItem(Effectschild, _("child2"));
  wxTreeItemId child10 = Tree->AppendItem(Effectschild, _("child2"));

  Tree->Expand(root);

  LoadKnownExtentions();
}

MLTree::~MLTree()
{
 
}

bool				MLTree::LoadKnownExtentions()
{
  wxTextFile			file(WiredSettings->ConfDir + EXT_FILE);
  wxString			l;
  wxString			*itemdata = NULL;

  filters = wxT("");  

   if (file.Open())
     {
      for (l = file.GetFirstLine(); ; l = file.GetNextLine())
	{
	  l.Trim(false);
	  l = l.BeforeFirst('#');
	  if (!l.IsEmpty())
	    {
	      itemdata = new wxString(l.BeforeFirst('\t'));
	      Exts.push_back(*itemdata);
	      filters += *itemdata + wxT(";");
	    }
 	  if (file.Eof())
 	    break;
	}
      file.Close();
     }
   else
     {
       cout << "[MEDIALIBRARY] Could not open ext file" << endl;
     }
   //    cout << "[MEDIALIBRARY] known extentions : " << filters << endl;
  
    for (vector<wxString>::iterator iter = Exts.begin(); iter != Exts.end(); iter++)
      {

	cout << "[MEDIALIBRARY] : " << *iter << endl;
      }

   return (true);
}

void				MLTree::SetTreeExpanded()
{
  collapsed = false;
}

void				MLTree::SetTreeCollapsed()
{
  collapsed = true;
}

bool				MLTree::IsTreeCollapsed()
{
  return (collapsed);
}

void				MLTree::OnAdd()
{
  cout << "[MEDIALIBRARY] Add File (OnAdd)" << endl;
  wxString FileToAdd = wxFileSelector(_("Add a file to the Media Library"), _(""), _(""), _(""), _("All supported files (*.*)|*.*"), wxOPEN);
  if (!FileToAdd.empty())
    {
      wxFileName	*File = new wxFileName(FileToAdd);

      if (File->FileExists() == true)
	{
	  cout << "[MEDIALIBRARY] File added : " << FileToAdd <<  " Extention is : " << File->GetExt() << endl;
	  
	  for (vector<wxString>::iterator iter = Exts.begin(); iter != Exts.end(); iter++)
	    {
	     
	      if (iter->Contains(File->GetExt()) == true)
		{
		  wxTreeItemId child2 = Tree->AppendItem(Soundchild, _(FileToAdd));
		}
	    }
	}
    }
}

void				MLTree::OnRemove()
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

void				MLTree::ExpandAll(wxTreeCtrl *Tree, const wxTreeItemId& id, bool shouldExpand, int toLevel)
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

void				MLTree::OnCollapse()
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

void				MLTree::OnRightClick(wxTreeEvent &WXUNUSED(event))
{
  cout << "[MEDIALIBRARY] RightClick" << endl;

        wxMenu* myMenu = new wxMenu();
    //     myMenu->Append(idMenuNewDir, wxT("New Directory"), wxT("New Directory"));
//         myMenu->Append(idMenuNewSnip, wxT("New Snippet"), wxT("New Snippet"));
        myMenu->AppendSeparator();
//         myMenu->Append(idMenuDelete, wxT("Delete"), wxT("Delete"));
        PopupMenu(myMenu);
        delete myMenu; 
}

void				MLTree::OnContextMenu(wxMouseEvent &WXUNUSED(event))
{
  cout << "[MEDIALIBRARY] ContextMenu" << endl;
}

void				MLTree::OnSelChange(wxTreeEvent &WXUNUSED(event))
{
    cout << "[MEDIALIBRARY] Selection Change" << endl;
}

BEGIN_EVENT_TABLE(MLTree, wxPanel)
  //  EVT_CONTEXT_MENU(MLTree::OnContextMenu)
//   EVT_RIGHT_DOWN(MLTree::OnContextMenu)
//   EVT_TREE_ITEM_MENU(MLTree_RightClick, MLTree::OnRightClick)

//   EVT_TREE_ITEM_RIGHT_CLICK(MLTree_RightClick, MLTree::OnRightClick)
//   EVT_TREE_SEL_CHANGED(MLTree_SelChange, MLTree::OnSelChange)
END_EVENT_TABLE()
