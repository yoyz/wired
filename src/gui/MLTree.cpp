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

//IMPLEMENT_CLASS(MLTree, wxTreeCtrl)

s_nodeInfo		SetStructInfos(s_nodeInfo infos, wxString label, wxString extention, wxString length)
{
  
  infos.label = label;
  infos.extention = extention;
  infos.length = length;
  /* add more... */
  return(infos);
}

MLTree::MLTree(wxWindow *MediaLibraryPanel)
{

  Tree = new wxTreeCtrl((wxWindow*)MediaLibraryPanel, -1, wxPoint(10, 50),
			wxSize(300, MediaLibraryPanel->GetSize().y - 100),
			wxTR_DEFAULT_STYLE | wxTR_EDIT_LABELS | wxTR_MULTIPLE,
			wxDefaultValidator, _("Tree"));
  Tree->SetIndent(10);  
  /* Set the Root node with the project's name in label */
  root = Tree->AppendItem(Tree->GetRootItem(), _("Project's name"));
  Tree->SetItemBold(root);
  /* Create basic nodes */
  s_nodeInfo	infos;
  infos = SetStructInfos(infos, _("Sounds"), _(""), _(""));
  nodes[Tree->AppendItem(root, _("Sound Files"))] = infos;

  s_nodeInfo	infos1;
  infos1 = SetStructInfos(infos1, _("MIDI"), _(""), _(""));
  nodes[Tree->AppendItem(root, _("MIDI Files"))] = infos1;

  s_nodeInfo	infos2;
  infos2 = SetStructInfos(infos2, _("Videos"), _(""), _(""));
  nodes[Tree->AppendItem(root, _("Videos Files"))] = infos2;

  s_nodeInfo	infos3;
  infos3 = SetStructInfos(infos3, _("Effects"), _(""), _(""));
  nodes[Tree->AppendItem(root, _("Effects Files"))] = infos3;

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

void				MLTree::AddFile(wxTreeItemId ParentNode, wxString FileToAdd, s_nodeInfo infos)
{  
  nodes[Tree->AppendItem(ParentNode, FileToAdd)] = infos;
}

wxTreeItemId			MLTree::GetTreeItemIdFromLabel(wxString label)
{
  wxTreeItemId			ItemToReturn;
  map<wxTreeItemId, s_nodeInfo>::iterator theIterator;

  for(theIterator = nodes.begin(); theIterator != nodes.end(); theIterator++ ) 
    {
      s_nodeInfo temp;
      temp = (*theIterator).second;
      if (temp.label.Cmp(label) == 0)
	{
	  ItemToReturn = (*theIterator).first;
	}
    }
  return (ItemToReturn);
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
		  s_nodeInfo		infos;

		  SetStructInfos(infos, FileToAdd, File->GetExt(), _(""));
		  this->AddFile(GetTreeItemIdFromLabel(_("Sounds")),FileToAdd, infos);
		}
	    }
	}
    }
}


wxString			MLTree::getSelection()
{
  wxArrayTreeItemIds		selection;
  int				selection_length;
  int				i;
  
  selection_length = Tree->GetSelections(selection);
  for (i = 0; i < selection_length; i++)
    {
      if (Tree->GetItemParent(selection[i]) != Tree->GetRootItem() && selection[i] != Tree->GetRootItem())
	{
	  return (Tree->GetItemText(selection[i]));
	}
    }
  return (_(""));
}

void				MLTree::OnRemove()
{
  wxArrayTreeItemIds		selection;
  int				selection_length;
  int				i;

  selection_length = Tree->GetSelections(selection);
  for (i = 0; i < selection_length; i++)
    {
      if (Tree->GetItemParent(selection[i]) != Tree->GetRootItem() && selection[i] != Tree->GetRootItem())
	{
	  //nodes.erase(Tree->GetItemText(selection[i]));
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

void				MLTree::OnItemRightClick(wxTreeEvent& event)
{
  cout << "[MEDIALIBRARY] RightClick" << endl;
        wxMenu* myMenu = new wxMenu();
//         myMenu->Append(idMenuNewDir, wxT("New Directory"), wxT("New Directory"));
//         myMenu->Append(idMenuNewSnip, wxT("New Snippet"), wxT("New Snippet"));
        myMenu->AppendSeparator();
//         myMenu->Append(idMenuDelete, wxT("Delete"), wxT("Delete"));
        PopupMenu(myMenu);
        delete myMenu;
}


void				MLTree::OnTreeRightClick(wxTreeEvent& event)
{
  cout << "[MEDIALIBRARY] RightClick tarass" << endl;
        wxMenu* myMenu = new wxMenu();
//         myMenu->Append(idMenuNewDir, wxT("New Directory"), wxT("New Directory"));
        PopupMenu(myMenu);
        delete myMenu;
}

BEGIN_EVENT_TABLE(MLTree, wxTreeCtrl)
        EVT_TREE_ITEM_RIGHT_CLICK(0, MLTree::OnItemRightClick)
        EVT_TREE_ITEM_MENU(MLTree_Menu, MLTree::OnTreeRightClick)
END_EVENT_TABLE()
