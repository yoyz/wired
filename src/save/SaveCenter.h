#ifndef _SAVECENTER_H_
#define _SAVECENTER_H_

#include "WiredDocument.h"
#include "WiredXml.h"

class SaveCenter : public WiredDocument
{
 public:
  SaveCenter(wxString docName,
	     wxString projectName,  
	     WiredDocument *docParent,
	     wxString projectPath);
  ~SaveCenter();

  /** Main Save function, implementation of WiredDocument.
   * The SaveCenter is a WiredDocument. This function is used to save 
   * projectwide infos
   * \param conf Please, refer to the WiredDocument class documentation.
   * \param data Please, refer to the WiredDocument class documentation.
   * \param filename Please, refer to the WiredDocument class documentation.
   */
  void		Save();
  
  /** Main Load function, implementation of WiredDocument.
   * The SaveCenter is a WiredDocument. This function is used to load 
   * projectwide infos
   * \param conf Please, refer to the WiredDocument class documentation.
   * \param data Please, refer to the WiredDocument class documentation.
   * \param filename Please, refer to the WiredDocument class documentation.
   */
  void		Load();
  
  /** Returns the project path. */
  wxString	getProjectPath();

  /** Sets the project path
   * \param projectPath the new project path.
   */
  void		setProjectPath(wxString projectPath);

  /** Returns the project name. */
  wxString	getProjectName();

  /** Sets the project name
   * \param projectName the new project name.
   */
  void		setProjectName(wxString projectName);
  
  /** Saves the whole project.
   * This function should only be called when clicking on the save menu...
   * Initialize some elements and calls SaveDocument on the SaveCenter.
   * Make sure the project path and name are set.
   */
  void		SaveProject();
  
  /** Only saves the file designated by file of the WiredDocument designated by doc.
   * This method should be used, for example, to save a plugin patch.<br>
   * It only calls Save() on the WiredDocument and then writes the file with WriteFile.
   * \param doc The WiredDocument containing the file we want to save.
   * \param file The name of the file we want to save
   */
  void		SaveFile(WiredDocument *doc, wxString file);


 private:
   /** Writes an element in the xmlfile.
    * \param elem the element to write.
    * \param xmlFile the WiredXml object to write in.
    */
  void		WriteElement(SaveElement elem, WiredXml *xmlFile);

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


  //TODO
  bool		checkFilePath(wxString filePath);


 private:
  wxString		_projectName;
  wxString		_projectPath;
};

#endif /*_SAVECENTER_H_ */
