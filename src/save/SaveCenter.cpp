#include "SaveCenter.h"

SaveCenter::SaveCenter(wxString projectName, wxString projectPath = wxT(""))
{
  setProjectPath(projectPath);
  setProjectName(projectName);

}

SaveCenter::~SaveCenter()
{
  //Nothing to do yet in here...
}

//Implemetation of WiredDocument
WiredSaveElementArray	SaveCenter::Save()
{
  WiredSaveElementArray	ret;

  return ret;
}
 
void			SaveCenter::Load(WiredSaveElementArray)
{

}

bool	SaveCenter::SaveProject()
{
  wxString	fileName;
  
  filename << _projectPath << _projectName << wxT(".xml");

  SaveDocument(fileName, this);
}

bool	SaveCenter::SaveDocument(wxString fileName, WiredDocument *doc)
{
  WiredXml	*xmlFile = new WiredXml();

  xmlFile->CreateDocument(fileName);
  
  WriteDocument(doc, xmlFile);

  xmlFile->EndDocumentWriter();
  delete xmlFile;
}

bool	SaveCenter::WriteDocument(WiredDocument *currentNode, WiredXml *xmlFile)
{
  WiredSaveElementArray			toWrite;
  WiredDocumentArray			childrenOfCurrentNode;
  int					i;

  //get our children
  childrenOfCurrentNode = currentNode->getChildren();

  //get our SaveElements
  toWrite = currentNode->Save();

  //write our SaveElements...
  //...start with our name...
  xmlFile->StartElememt(currentNode->getName());
  
  //...then the elements
  for (i = 0; i < toWrite.getCount(); i++)
    WriteElement(toWrite[i]);
  
  //call recursively on our children
  for (i = 0; i < childrenOfCurrentNode.getCount(); i++)
    WriteDocument(childrenOfCurrentNode[i], xmlFile);      
  
  //...finish by closing things
  xmlFile->EndElement();    
}

bool	SaveCenter::WriteElement(SaveElement elem, WiredXml *xmlFile)
{
  int i;

  //XML bullshit
  xmlFile->StartElement(elem->getKey());

  for(i = 0; i < 
}


//Accessors
wxString	SaveCenter::getProjectPath()
{
  return _projectPath;
}

void		SaveCenter::setProjectPath(wxString projectPath)
{

  _projectPath = projectPath;

  //make some checks : 
  //the path must end with a /
  if(!_projectPath.Matches("*/"))
    _projectPath << wxT("/");

  //Do we have to handle the ~, bash style ? 

}

wxString	SaveCenter::getProjectName()
{
  return _projectName;
}

void		SaveCenter::setProjectname(wxString projectName)
{
  _projectName = projectName;

  //make some checks :
  //empty name is not good. Let's put a default value...
  //could be greatly enhanced because we won't handle 
  //2 default project in the same directory
  if(_projectName.isEmpty())
    _projectName << wxT("WiredProject");

}
