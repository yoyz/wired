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
  /** Main save function.
   * This function will be called by the SaveCenter when a save of the document
   * is asked.<br>
   * Memory management is handled by the SaveCenter, just fill in the blanks.<br>
   * There are two WiredSaveElementArray pointers. The first will be dumped in the
   * project file, the second can be used to have a separate file for data.<br>
   * Feel free to use only one of them but try to be consistent.
   * \param conf The configuration SaveElements that will be stored into the project
   *             file.
   * \param data The data SaveElements that will be saved in a separate file.
   * \param filename The path to the data file. If no filename is given or if it is 
   * unvalid, it will be defaulted to the return of the getName() method. If it 
   * does not start with a '/', it will be relative to the project root.
   */ 
  virtual void	Save(WiredSaveElementArray *conf,
	       	     WiredSaveElementArray *data,
		     wxString *filename) = 0;

  /** Main Load function.
   * It will be called by the SaveCenter when a load is asked.<br>
   * Never assume the two arrays are correctly filled. Always check your data...
   * \param conf the set of SaveElements written in the project file.
   * \param data the set of SaveElements written in a separate file. 
   */
  virtual void	Load(WiredSaveElementArray conf,
		     WiredSaveElementArray data) = 0;

  WiredDocumentArray		getChildren();
  wxString			getName();
  void				Register(WiredDocument *children);
  

 private:
  WiredDocumentArray		_children;
  wxString			_name;
};

#endif /*_WIREDDOCUMENT_H */
