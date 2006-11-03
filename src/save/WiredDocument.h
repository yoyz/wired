#ifndef _WIREDDOCUMENT_H_
#define _WIREDDOCUMENT_H_

#include <wx/dynarray.h>

#include "SaveElement.h"

class WiredDocument;

WX_DEFINE_ARRAY_PTR(WiredDocument *, WiredDocumentArray);

#define WIRED_PROJECT_FILE wxT("WiredProjectFile")

class WiredDocument
{
 public:
  WiredDocument(wxString docName, WiredDocument *parent);

  /** Main save function.
   * This function will be called by the SaveCenter when a save of the document
   * is asked.
   */ 
  virtual void	Save() = 0;

  /** Main Load function.
   * It will be called by the SaveCenter when a load is asked.<br>
   */
  virtual void	Load(SaveElementArray data) = 0;

  void		SaveMe();

  WiredDocumentArray		getChildren();
  void				Register(WiredDocument *children);
  
  SaveElementsHashMap		getDocData();
  SaveElementArray		*getDocFile(wxString file);

  inline wxString		getName() { return _name; }

 protected:
  void				saveDocData(wxString file, SaveElement *data);
  void				clearDocData();
  void				rmDocDataFile(wxString file);

 private:
  WiredDocumentArray		_children;

  wxString			_name;
  SaveElementsHashMap		_dataSave;
};

#endif /*_WIREDDOCUMENT_H */
