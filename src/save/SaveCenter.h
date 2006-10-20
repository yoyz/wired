#ifndef _SAVECENTER_H_
#define _SAVECENTER_H_

#include "WiredDocument.h"

class SaveCenter : public WiredDocument
{
 public:
  SaveCenter(wxString projectName, wxString projectPath = wxT(""));
  ~SaveCenter();

  //Implemetation of WiredDocument
  WiredSaveElementArray	Save();
  void			Load(WiredSaveElementArray);

  wxString	getProjectPath();
  void		setProjectPath(wxString projectPath);

  wxString	getProjectName();
  void		setProjectname(wxString projectName);
  
  void		SaveProject();
  void		SaveDocument(wxString fileName, WiredDocument *doc);

 private:
  bool		WriteElement(SaveElement elem, WiredXml *xmlFile);
  bool		WriteDocument(WiredDocument *currentNode, WiredXml *xmlFile);

  bool		ReadXml();

 private:
  wxString		_projectName;
  wxString		_projectPath;
}

#endif /*_SAVECENTER_H_ */
