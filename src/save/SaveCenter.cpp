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
void	SaveCenter::Save(WiredSaveElementArray *conf
			 WiredSaveElementArray *data, 
			 wxString *filename)
{
  //return project specific infos ?
}
 
void	SaveCenter::Load(WiredSaveElementArray conf, WiredSaveElementArray data)
{
  //load project specific infos ?
}

bool	SaveCenter::SaveProject()
{
  wxString	fileName;
  WiredXml	*xmlFile = new WiredXml();
  

  filename << _projectPath << _projectName << wxT(".xml");

  xmlFile->CreateDocument(fileName);

  SaveDocument(this, xmlFile);

  xmlFile->EndDocumentWriter();
  delete xmlFile;

  return true;
}

bool	SaveCenter::SaveDocument(WiredDocument *currentNode, WiredXml *confFile = NULL)
{
  WiredSaveElementArray			confToWrite;
  WiredSaveElementArray			dataToWrite;
  wxString				dataFileName;
  WiredDocumentArray			childrenOfCurrentNode;
  int					i;
  WiredXml				*dataFile;

  //get our children
  childrenOfCurrentNode = currentNode->getChildren();

  //get our SaveElements
  currentNode->Save(&confToWrite, &dataToWrite, &dataFileName);

  //if we have a project file to write in...
  if(confFile)
    {
      //write our conf SaveElements...
      //...start with our name...
      confFile->StartElememt(currentNode->getName());
      
      //...then the elements
      for (i = 0; i < toWrite.getCount(); i++)
	WriteElement(toWrite[i], confFile);
    }

  //if we got a filename and data to write, let's write it.
  if(!dataFileName.isEmpty() && !dataToWrite.isEmpty())
    {
      dataFile = new WiredXml();
      
      checkFilePath(dataFileName);

      dataFile->CreateDocument(dataFileName);

      for (i = 0; i < toWrite.getCount(); i++)
	WriteElement(toWrite[i], dataFile);

      dataFile->EndDocumentWriter();
      delete dataFile;
    }
  
  //call recursively on our children
  for (i = 0; i < childrenOfCurrentNode.getCount(); i++)
    SaveDocument(childrenOfCurrentNode[i], confFile);      
  
  //...still if we have a project to file to write in...
  //...finish by closing things
  if(confFile)
    confFile->EndElement();    
}

bool	SaveCenter::WriteElement(SaveElement elem, WiredXml *xmlFile)
{
  int				i;
  AttributesHashMap		attributes;
  AttributesHashMap::iterator	attributesIt;

  attributes = elem->getAttributes();

  //XML bullshit
  xmlFile->StartElement(elem->getKey());
  

  for(attributesIt = attributes.begin();
      attributesIt != attributes.end();
      attributesIt++)
    xmlFile->WriteAttribute(it->first, it->second, true);
  
  xmlFile->EndElement();
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
