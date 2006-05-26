// Copyright (C) 2004 by Wired Team
// Under the GNU General Public License

#ifndef __MEDIALIBRARY_H__
#define __MEDIALIBRARY_H__

#include <wx/wx.h>

class				MainWindow;
class				DownButton;
class				HoldButton;
class				StaticLabel;
class				VUMCtrl;

#define MEDIALIBRARY_ADDUP_IMG		wxT("ihm/toolbar/hand_up.png")
#define MEDIALIBRARY_ADDDO_IMG		wxT("ihm/toolbar/hand_down.png")
#define MEDIALIBRARY_REMOVEUP_IMG	wxT("ihm/toolbar/erase_up.png")
#define MEDIALIBRARY_REMOVEDO_IMG	wxT("ihm/toolbar/erase_down.png")
#define MEDIALIBRARY_EDITUP_IMG		wxT("ihm/toolbar/draw_up.png")
#define MEDIALIBRARY_EDITDO_IMG		wxT("ihm/toolbar/draw_down.png")
#define MEDIALIBRARY_INSERTUP_IMG	wxT("ihm/toolbar/split_up.png")
#define MEDIALIBRARY_INSERTDO_IMG	wxT("ihm/toolbar/split_down.png")

#define ML_BACKGROUND			wxColour(142, 142, 169)
#define ML_FOREGROUND			wxColour(142, 142, 155)

#define NB_SORTSELECT_CHOICES		(4)
#define DEFAULT_SORTSELECT_VALUE	wxT("Sort by...")


//class				MediaLibrary;
class				MLTree;


class				MediaLibrary : public wxPanel
{
 public:
  MediaLibrary(wxWindow *parent, const wxPoint &pos, const wxSize &size, long style);
  ~MediaLibrary();


 protected:
  friend class			MainWindow;
  friend class			MLTree;
  bool				visible;
  bool				floating;
  wxToolBar			*TopToolbar;
  wxToolBar			*BottomToolbar;
  wxToolBar			*FiltersToolbar;
  wxBoxSizer			*TopSizer;
  // A effacer ?
  wxBoxSizer			*TreeSizer;
  wxBoxSizer			*BottomSizer;
  ///////////
  wxComboBox			*SortSelect;
  //wxTreeCtrl			*Tree;
  wxTextCtrl			*mlTextCtrl;
  wxMenu			*PopMenu;
  MLTree			*MLTreeView;

  void				OnSize(wxSizeEvent &event);
  void				OnEdit(wxCommandEvent &WXUNUSED(event));
  void				OnInsert(wxCommandEvent &WXUNUSED(event));

  void				OnPreview(wxCommandEvent &WXUNUSED(event));
  void				OnAdd(wxCommandEvent &WXUNUSED(event));
  void				OnRemove(wxCommandEvent &WXUNUSED(event));
  void				OnCollapse(wxCommandEvent &WXUNUSED(event));
  void				OnSortToggle(wxCommandEvent &WXUNUSED(event));
  void				OnFilterAudio(wxCommandEvent &WXUNUSED(event));
  void				OnFilterMIDI(wxCommandEvent &WXUNUSED(event));
  void				OnFilterVideo(wxCommandEvent &WXUNUSED(event));
  void				OnFilterEffects(wxCommandEvent &WXUNUSED(event));

  //void				CreateTree();
  void				OnRightClick(wxMouseEvent &event);
  void				ShowPopup(wxPoint pos);

 
  bool				IsVisible();
  void				SetInvisible();
  void				SetVisible();
  bool			        IsFloating();
  void				SetFloating();
  void				SetDocked();

  DECLARE_EVENT_TABLE()
};


extern const struct s_combo_choice	SortSelectChoices[NB_SORTSELECT_CHOICES + 1];

enum
{
   MediaLibrary_Add = 1, 
   MediaLibrary_Remove, 
   MediaLibrary_Edit,
   MediaLibrary_Insert,
   MediaLibrary_Preview,
   MediaLibrary_TreeCollapse,
   MediaLibrary_SortSelect,
   MediaLibrary_FilterAudio,
   MediaLibrary_FilterMIDI,
   MediaLibrary_FilterVideo,
   MediaLibrary_FilterEffects,
};


#endif
