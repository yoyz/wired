// Copyright (C) 2004 by Wired Team
// Under the GNU General Public License

#ifndef __MLTREE_H__
#define __MLTREE_H__

#include <wx/wx.h>
#include <vector>

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
  //vector<wxTreeItemId>		Folders;

  bool				IsTreeCollapsed();
  void				SetTreeCollapsed();
  void				SetTreeExpanded();
  void				OnAdd();
  void				OnRemove();
  void				OnCollapse();
  //DECLARE_EVENT_TABLE()
};


/* enum */
/* { */
/*    MediaLibrary_Add = 1, */
/*    MediaLibrary_Remove, */
/*    MediaLibrary_Edit, */
/*    MediaLibrary_Insert, */
/*    MediaLibrary_Preview, */
/*    MediaLibrary_TreeCollapse, */
/*    MediaLibrary_SortSelect, */
/*    MediaLibrary_FilterAudio, */
/*    MediaLibrary_FilterMIDI, */
/*    MediaLibrary_FilterVideo, */
/*    MediaLibrary_FilterEffects, */
/* }; */

#endif
