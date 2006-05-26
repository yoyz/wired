// Copyright (C) 2004 by Wired Team
// Under the GNU General Public License

#ifndef __MLTREE_H__
#define __MLTREE_H__

#include <wx/wx.h>
#include <vector>
#include <list>

using std::string;
using std::vector;

#define EXT_FILE		wxT("wired_exts.conf")

class				MLTree : public wxPanel
{
 public:
  MLTree(wxWindow *MediaLibraryPanel);
  ~MLTree();

 protected:
  friend class			MediaLibrary;

  wxTreeCtrl			*Tree;
  bool				collapsed;
  wxTreeItemId			root;
  wxString			filters;
  vector<wxString>		Exts;

  // temp
  wxTreeItemId			Soundchild;
  //

  bool				IsTreeCollapsed();
  void				SetTreeCollapsed();
  void				SetTreeExpanded();
  void				OnAdd();
  void				OnRemove();
  void				ExpandAll(wxTreeCtrl *Tree, const wxTreeItemId& id, bool shouldExpand, int toLevel);
  void				OnCollapse();
  bool				LoadKnownExtentions();

  void				OnRightClick(wxTreeEvent &WXUNUSED(event));
  void				OnContextMenu(wxMouseEvent &WXUNUSED(event));
  void				OnSelChange(wxTreeEvent &WXUNUSED(event));

  DECLARE_EVENT_TABLE()
};


enum
{
   MLTree_Add = 53028,
   MLTree_RightClick = 2913,
   MLTree_SelChange,
};

#endif
