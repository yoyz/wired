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

void	SaveCenter::SaveFile(WiredDocument *doc, wxString file)
{
  doc->Save();
  WriteFile(file, doc->getDocFile(file)); 
}

bool	SaveCenter::SaveDocument(WiredDocument *currentNode, WiredXml *xmlFile)
{
  WiredDocumentArray			childrenOfCurrentNode;
  int					i;
  SaveElementsHashMap			saveElements;
  SaveElementArray			toWrite;
  SaveElementsHashMap::iterator		saveElementsIt;

  //Get our children
  childrenOfCurrentNode = currentNode->getChildren();

  //Save Document
  currentNode->Save();
  
  //get my SaveElements
  saveElements = currentNode->getDocData();

  //write our SaveElements...
  //...start with our name...
  xmlFile->StartElememt(currentNode->getName());
  
  //Write references
  WriteReferences(saveElements, xmlFile);

  //get elements to write in the conf file
  toWrite = saveElements[WIRED_PROJECT_FILE]->second();

  //...then write the elements
  for (i = 0; i < toWrite.getCount(); i++)
    WriteElement(toWrite[i], xmlFile);
  
  //Write the other files
  for (saveElementsIt = saveElements.begin();
       saveElementsIt != saveElements.end();
       saveElementsIt++)
    if(saveElementsIt->first() != WIRED_PROJECT_FILE)
      WriteFile(saveElementsIt->first(), saveElementsIt->second());

  //call recursively on our children
  for (i = 0; i < childrenOfCurrentNode.getCount(); i++)
    SaveDocument(childrenOfCurrentNode[i], xmlFile);
  
  //...finish by closing things
  xmlFile->EndElement();    
}

void	SaveCenter::AddReferences(SaveElementsHashMap &saveElements, 
				  WiredXml *xmlFile)
{
  SaveElementsHashMap::iterator	saveElementsIt;
  SaveElement			ref;

  //for each entry of the hash map....
  for (saveElementsIt = saveElements.begin();
       saveElementsIt != saveElements.end();
       saveElementsIt++)
    //if it is not the one to write in the project file
    if(saveElementsIt->first() != WIRED_PROJECT_FILE)
      {
	//fill a SaveElement
	ref.clear();
	ref.AddPair(wxT("reference"), SaveElementsIt->first());
	//and write it.
	WriteElement(ref, xmlFile);
      }
}

void	SaveCenter::WriteElement(SaveElement elem, WiredXml *xmlFile)
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

void		SaveCenter::WriteFile(wxString filename, SaveElementArray elements)
{
  wxString	rootTag;
  WiredXml	*xmlFile = new WiredXml();
  int		i;

  xmlFile->CreateDocument(filename);

  rootTag = filename.afterLast('/');
  rootTag = rootTag.beforeLast('.');

  xmlFile->StartElement(rootTag);

  for (i = 0; i < elements.getCount(); i++)
    WriteElement(elements[i], xmlFile);
  
  xmlFile->EndElement();
  delete xmlFile;
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
