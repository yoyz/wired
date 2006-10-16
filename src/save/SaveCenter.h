#ifndef _SAVECENTER_H_
#define _SAVECENTER_H_

#include "WiredDocument.h"

class SaveCenter : public WiredDocument
{
 public:
  SaveCenter(wxString projectName, wxString projectPath = wxT(""));
  ~SaveCenter();

  /** Main Save function, implementation of WiredDocument.
   * The SaveCenter is a WiredDocument. This function is used to save 
   * projectwide infos
   * \param conf Please, refer to the WiredDocument class documentation.
   * \param data Please, refer to the WiredDocument class documentation.
   * \param filename Please, refer to the WiredDocument class documentation.
   */
  void		Save(WiredSaveElementArray &conf,
		     WiredSaveElementArray &data,
		     wxString &filename);
  
  /** Main Load function, implementation of WiredDocument.
   * The SaveCenter is a WiredDocument. This function is used to load 
   * projectwide infos
   * \param conf Please, refer to the WiredDocument class documentation.
   * \param data Please, refer to the WiredDocument class documentation.
   * \param filename Please, refer to the WiredDocument class documentation.
   */
  void		Load(WiredSaveElementArray conf,
		     WiredSaveElementArray data);
  
  wxString	getProjectPath();
  void		setProjectPath(wxString projectPath);

  wxString	getProjectName();
  void		setProjectname(wxString projectName);
  
  /** Saves the whole project.
   * This function should only be called when clicking on the save menu...
   * Initialize some elements and calls SaveDocument on the SaveCenter.
   * Make sure the project path and name are set.
   */
  void		SaveProject();

  /** Saves a WiredDocument.
   * This function calls itself recursively, so the whole WiredDocument tree is
   * parsed.
   * If the confFile is NULL, no project file will be written (only data...)
   * \param doc the 
   */ 
  void		SaveDocument(WiredDocument *doc, WiredXml confFile = NULL);

 private:
  bool		WriteElement(SaveElement elem, WiredXml *xmlFile);
  bool		WriteDocument(WiredDocument *currentNode, WiredXml *xmlFile);

  bool		ReadXml();

  //TODO
  bool		checkFilePath(wxString filePath);


 private:
  wxString		_projectName;
  wxString		_projectPath;
}

#endif /*_SAVECENTER_H_ */
