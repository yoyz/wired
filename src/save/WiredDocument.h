#ifndef _WIREDDOCUMENT_H_
#define _WIREDDOCUMENT_H_

#include <wx/dynarray.h>

#include "SaveElement.h"

WX_DEFINE_ARRAY_PTR(WiredDocument *, WiredDocumentArray);

class WiredDocument
{
 private:
  WiredDocument(wxString name, WiredDocument *parent = NULL);


 public:
  virtual WiredSaveElementArray	Save() = 0;
  virtual void			Load(WiredSaveElementArray) = 0;

  WiredDocumentArray		getChildren();
  wxString			getName();
  void				Register(WiredDocument *children);
  

 private:
  WiredDocumentArray		_children;
  wxString			_name;
};

#endif /*_WIREDDOCUMENT_H */
