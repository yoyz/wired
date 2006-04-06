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

class				MediaLibrary : public wxPanel
{
 public:
  MediaLibrary(wxWindow *parent, const wxPoint &pos, const wxSize &size, long style);
  ~MediaLibrary();


 protected:
  friend class			MainWindow;
  int				size_x;
  int				size_y;
  bool				visible;
  bool				floating;

  void				OnSize(wxSizeEvent &event);
  void				SetSize(int x, int y);
  int				GetXSize();
  int				GetYSize();
  bool				IsVisible();
  void				SetInvisible();
  void				SetVisible();
  bool			        IsFloating();
  void				SetFloating();
  void				SetDocked();
  DECLARE_EVENT_TABLE()
};

enum    

{
  
};


#endif
