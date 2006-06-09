// Copyright (C) 2004 by Wired Team
// Under the GNU General Public License

#ifndef __MLTREE_H__
#define __MLTREE_H__

#include <wx/wx.h>
#include <vector>
#include <list>
#include <map>

using std::string;
using std::vector;
using std::map;

#define EXT_FILE		wxT("wired_exts.conf")

struct				s_nodeInfo
{
  wxString			label;
  wxString			extention;
  wxString			length;

};

class				MLTree : public wxTreeCtrl
{
 public:
  MLTree(wxWindow *dad, wxPoint p, wxSize s, long style);
  ~MLTree();

 protected:
  friend class			MediaLibrary;

  wxTreeCtrl			*Tree;
  bool				collapsed;
  wxTreeItemId			root;
  wxString			filters;
  vector<wxString>		Exts;
  map<wxTreeItemId, s_nodeInfo>	nodes;

  // temp
  wxTreeItemId			Soundchild;
  //

  bool				IsTreeCollapsed();
  void				SetTreeCollapsed();
  void				SetTreeExpanded();
  wxTreeItemId			GetTreeItemIdFromLabel(wxString label);
  wxString			getSelection();
  void				AddFile(wxTreeItemId ParentNode, wxString FileToAdd, s_nodeInfo infos);
  void				OnAdd();
  void				OnRemove();
  void				ExpandAll(wxTreeCtrl *Tree, const wxTreeItemId& id, bool shouldExpand, int toLevel);
  void				OnCollapse();
  bool				LoadKnownExtentions();

  void				AddIcon(wxImageList *images, wxIcon icon);
  void				OnRightClick(wxMouseEvent &WXUNUSED(event));
  void				OnContextMenu(wxMouseEvent &WXUNUSED(event));
  void				OnSelChange(wxTreeEvent &WXUNUSED(event));
  void				OnTreeRightClick(wxTreeEvent& event);
  void				OnItemRightClick(wxTreeEvent& event);


  DECLARE_EVENT_TABLE()
};


enum
{
   MLTree_RightClick = 165238,
   MLTree_Menu,
   MLTree_Selected,
};

#endif
