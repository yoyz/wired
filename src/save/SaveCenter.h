#ifndef _SAVECENTER_H_
#define _SAVECENTER_H_

#include "WiredDocument.h"
#include "WiredXml.h"

//For the DirDialog
#include <wx/dirdlg.h>
#include <wx/generic/dirdlgg.h>

#define WIRED_DEFAULT_PROJECT_NAME wxT("WiredProject")

class SaveCenter : public WiredDocument
{
 public:
  /** Constructor.
   * \param projectName
   * \param docParent
   * \param projectPath
   */
  SaveCenter(wxString docName,
	     wxFileName projectPath = wxT(""),
	     WiredDocument *docParent = NULL);
  ~SaveCenter();

  /** Main Save function, implementation of WiredDocument.
   * The SaveCenter is a WiredDocument. This function is used to save 
   * projectwide infos
   */
  void		Save();
  
  /** Main Load function, implementation of WiredDocument.
   * The SaveCenter is a WiredDocument. This function is used to load 
   * projectwide infos
   */
  void		Load();
  
  /** Returns the project path. */
  wxFileName	getProjectPath();

  /** Sets the project path
   * \param projectPath the new project path.
   */
  void		setProjectPath(wxFileName projectPath);

  /** Returns the project name. */
  wxString	getProjectName();

  wxString	getAudioDir();
  void		setAudioDir(wxString audioDir);

  /** Sets the project name
   * \param projectName the new project name.
   */
  void		setProjectName(wxString projectName);
  
  /** Saves the whole project.
   * This function should only be called when clicking on the save menu...
   * Initialize some elements and calls SaveDocument on the SaveCenter.
   * Make sure the project path and name are set.
   */
  void		SaveProject(bool saveAs = false);
  
  /** Only saves the file designated by file of the WiredDocument designated by doc.
   * This method should be used, for example, to save a plugin patch.<br>
   * It only calls Save() on the WiredDocument and then writes the file with WriteFile.
   * \param doc The WiredDocument containing the file we want to save.
   * \param file The name of the file we want to save
   */
  void		SaveFile(WiredDocument *doc, wxString file);

  void		LoadProject(wxString filename);

 private:
   /** Writes an element in the xmlfile.
    * \param elem the element to write.
    * \param xmlFile the WiredXml object to write in.
    */
  void		WriteElement(SaveElement *elem, WiredXml *xmlFile);

  /** Saves a WiredDocument.
   * This function calls itself recursively, so the whole WiredDocument tree is
   * parsed.
   * If the confFile is NULL, no project file will be written (only data...)
   * \param doc the 
   */ 
  void		SaveDocument(WiredDocument *doc, WiredXml *xmlFile);

  /** Writes a SaveElementArray in a separate file.
   * The filename is relative to the project root path.
   * \param filename the path to the file to write.
   * \param elements the SaveElementArray to write.
   */
  void		WriteFile(wxString filename, SaveElementArray *elements);

  void		AddReferences(SaveElementsHashMap &saveElements, 
			      WiredXml *xmlFile);

  bool		ReadXml();

  wxString	GetDefaultProjectName(wxFileName cwd);
  wxString	GetProjectNameFromProjectPath(wxFileName path);


 private:
  wxFileName		_projectPath;
  wxString		_projectName;
  wxFileName		_audioDir;
  bool			_saved;
};

#endif /*_SAVECENTER_H_ */
