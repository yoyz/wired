#include "SaveCenter.h"

SaveCenter::SaveCenter(wxString docName,
		       wxString projectName,  
		       wxString projectPath = wxT(""),
		       WiredDocument *docParent = NULL)
  : WiredDocument(docName, docParent)
{
  setProjectPath(projectPath);
  setProjectName(projectName);
  _audioDir << _projectPath << wxT("/audio/");

}

SaveCenter::~SaveCenter()
{
  //Nothing to do yet in here...
}

//Implemetation of WiredDocument
void	SaveCenter::Save()
{
  //return project specific infos ?
}
 
void	SaveCenter::Load()
{
  //load project specific infos ?
}

void	SaveCenter::SaveProject()
{
  wxString	fileName;
  WiredXml	*xmlFile = new WiredXml();
  
  std::cerr << "[Save] SaveCenter::SaveProject" << std::endl;

  fileName << _projectPath << _projectName << wxT(".xml");
  std::cerr << "[Save] filename = " << fileName.mb_str() << std::endl;

  xmlFile->CreateDocument(fileName);

  std::cerr << "[Save] xmlFile created" << std::endl;

  SaveDocument((WiredDocument *)this, xmlFile);

  xmlFile->EndDocumentWriter();
  delete xmlFile;
}

void	SaveCenter::SaveFile(WiredDocument *doc, wxString file)
{
  doc->Save();
  WriteFile(file, doc->getDocFile(file)); 
}

void	SaveCenter::SaveDocument(WiredDocument *currentNode, WiredXml *xmlFile)
{
  WiredDocumentArray			childrenOfCurrentNode;
  int					i;
  SaveElementsHashMap			saveElements;
  SaveElementArray			*toWrite;
  SaveElementsHashMap::iterator		saveElementsIt;

  std::cerr << "[SaveCenter] SaveCenter::SaveDocument" << std::endl;

  //Get our children
  childrenOfCurrentNode = currentNode->getChildren();

  std::cerr << "[SaveCenter] childrenOfCurrentNode" << std::endl;

  //Save Document
  currentNode->Save();
  
  std::cerr << "[SaveCenter] Save" << std::endl;

  //get my SaveElements
  saveElements = currentNode->getDocData();

  std::cerr << "[SaveCenter] getNodeData" << std::endl;

  //write our SaveElements...
  //...start with our name...
  xmlFile->StartElement(currentNode->getName());

  std::cerr << "[SaveCenter] startelement : node name = " << currentNode->getName().mb_str() << std::endl;
  
  //Write references
  AddReferences(saveElements, xmlFile);

  std::cerr << "[SaveCenter] references added" << std::endl;

  std::cerr << "[SaveCenter] saveElements.count(WIRED_PROJECT_FILE) = " << saveElements.count(WIRED_PROJECT_FILE) << std::endl;

  //get elements to write in the conf file
  if(saveElements.count(WIRED_PROJECT_FILE))
    {      
      toWrite = saveElements[WIRED_PROJECT_FILE];
      std::cerr << "[SaveCenter] toWrite" << std::endl;
      
      //...then write the elements
      for (i = 0; i < toWrite->GetCount(); i++)
	WriteElement(toWrite->Item(i), xmlFile);

      std::cerr << "[SaveCenter] Elements written" << std::endl;
    }
  //Write the other files
  for (saveElementsIt = saveElements.begin();
       saveElementsIt != saveElements.end();
       saveElementsIt++)
    if(saveElementsIt->first != WIRED_PROJECT_FILE)
      WriteFile(saveElementsIt->first, saveElementsIt->second);

  std::cerr << "[SaveCenter] other files written" << std::endl;

  //call recursively on our children
  for (i = 0; i < childrenOfCurrentNode.GetCount(); i++)
    SaveDocument(childrenOfCurrentNode[i], xmlFile);
  
  //...finish by closing things
  xmlFile->EndElement();
}

void	SaveCenter::AddReferences(SaveElementsHashMap &saveElements, 
				  WiredXml *xmlFile)
{
  SaveElementsHashMap::iterator	saveElementsIt;
  SaveElement			*ref;

  //for each entry of the hash map....
  for (saveElementsIt = saveElements.begin();
       saveElementsIt != saveElements.end();
       saveElementsIt++)
    //if it is not the one to write in the project file
    if(saveElementsIt->first != WIRED_PROJECT_FILE)
      {
	//fill a SaveElement
	ref->clear();
	ref->setPair(wxT("reference"), saveElementsIt->first);
	//and write it.
	WriteElement(ref, xmlFile);
      }
}

void	SaveCenter::WriteElement(SaveElement *elem, WiredXml *xmlFile)
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
    xmlFile->WriteAttribute(attributesIt->first, attributesIt->second, true);
  
  xmlFile->EndElement();
}

void		SaveCenter::WriteFile(wxString filename, SaveElementArray *elements)
{
  wxString	rootTag;
  WiredXml	*xmlFile = new WiredXml();
  int		i;

  xmlFile->CreateDocument(filename);

  rootTag = filename.AfterLast('/');
  rootTag = rootTag.BeforeLast('.');

  xmlFile->StartElement(rootTag);

  for (i = 0; i < elements->GetCount(); i++)
    WriteElement(elements->Item(i), xmlFile);
  
  xmlFile->EndElement();
  delete xmlFile;
}

//Accessors
wxString	SaveCenter::getProjectPath()
{
  return _projectPath;
}

wxString	SaveCenter::getAudioDir()
{
  return _audioDir;
}

void		SaveCenter::setAudioDir(wxString audioDir)
{
  _audioDir = audioDir;
}

void		SaveCenter::setProjectPath(wxString projectPath)
{

  _projectPath = projectPath;

  //make some checks : 
  //the path must end with a /
  if(!_projectPath.Matches(wxT("*/")))
    _projectPath << wxT("/");

  //Do we have to handle the ~, bash style ? 

}

wxString	SaveCenter::getProjectName()
{
  return _projectName;
}

void		SaveCenter::setProjectName(wxString projectName)
{
  _projectName = projectName;

  //make some checks :
  //empty name is not good. Let's put a default value...
  //could be greatly enhanced because we won't handle 
  //2 default project in the same directory
  if(_projectName.IsEmpty())
    _projectName << wxT("WiredProject");

}

void	SaveCenter::LoadProject(wxString filename)
{

}
