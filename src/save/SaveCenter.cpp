#include "SaveCenter.h"

SaveCenter::SaveCenter(wxFileName  projectPath,
		       WiredDocument *docParent)
  : WiredDocument(wxT("savecenter"), docParent)
{
  setProjectPath(projectPath);
  _audioDir = _projectPath;
  _audioDir.AppendDir(wxT("audio"));
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
 
void	SaveCenter::Load(SaveElementArray)
{
  //load project specific infos ?
}

void	SaveCenter::SaveProject(bool saveAs)
{
  wxString	fileName;
  WiredXml	*xmlFile = new WiredXml();
  wxDirDialog	dirDialog(NULL, _("Select a project folder"),
			  _projectPath.GetPath());

  std::cerr << "[Save] SaveCenter::SaveProject" << std::endl;

  if(!_saved || saveAs)
    {
      //call fileloader to select the location
      if(dirDialog.ShowModal() == wxID_OK)
	{
	  _projectPath.Clear();
	  _projectPath.AssignDir(dirDialog.GetPath());
	  std::cerr << "dirDialog.GetPath() = " << dirDialog.GetPath().mb_str() << std::endl;
	  _saved = true;
	}
      else
	return ;
    }

  if(!_projectPath.DirExists())
    _projectPath.Mkdir();
    
  fileName << _projectPath.GetPath(wxPATH_GET_SEPARATOR | wxPATH_GET_VOLUME) << wxT("wired.xml");

  std::cerr << "fileName = " << fileName.mb_str() << std::endl;

  xmlFile->CreateDocument(fileName);

  std::cerr << "[Save] xmlFile created" << std::endl;

  SaveDocument((WiredDocument *)this, xmlFile);

  xmlFile->EndDocumentWriter();
  delete xmlFile;
}

void	SaveCenter::SaveFile(WiredDocument *doc, wxString file)
{
  doc->SaveMe();
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
  currentNode->SaveMe();
  
  std::cerr << "[SaveCenter] Save" << std::endl;

  //get my SaveElements
  saveElements = currentNode->getDocData();

  std::cerr << "[SaveCenter] getNodeData" << std::endl;

  //write our SaveElements...
  //...start with our name...
  xmlFile->StartElement(WIRED_TAG_WIREDDOC);
  xmlFile->WriteAttribute(wxT("id"), currentNode->getName());

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

  xmlFile->WriteString(elem->getValue());
  
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
wxFileName	SaveCenter::getProjectPath()
{
  return _projectPath;
}

wxString	SaveCenter::getAudioDir()
{
  return _audioDir.GetLongPath();
}

void		SaveCenter::setAudioDir(wxString audioDir)
{
  _audioDir = audioDir;
}

void		SaveCenter::setProjectPath(wxFileName projectPath)
{
  if(!projectPath.IsOk())
    {
      _saved = false;
      _projectPath.AssignDir(wxGetCwd());
      _projectName = GetDefaultProjectName(projectPath);
      _projectPath.AppendDir(_projectName);
    }
  else
    {
      _saved = true;
      _projectPath = projectPath;
      
      _projectName = GetProjectNameFromProjectPath(_projectPath);
    }

}

wxString	SaveCenter::getProjectName()
{
  return _projectName;
}

void		SaveCenter::setProjectName(wxString projectName)
{
  _projectName = projectName;

  _projectPath.RemoveLastDir();
  _projectPath.AppendDir(_projectName);

}

void	SaveCenter::LoadProject(wxString filename)
{
  //infos about the node we are reading
  WiredXml	*xmlFile = new WiredXml();
  wxString	nodeName;
  int		nodeType;

  //the things we are storing (code readability)
  //It's just used as a reference. No new, no delete on this pointer.
  SaveElement		*saveElem = NULL;

  //we store the whole path to the current document.
  //Please refer to the technical documentation for more infos.
  //used only to make the code readable
  wxString		currentDoc;
  SaveElementArray	*currentArray;
  
  //a big hashmap to store everything
  SaveElementArrayHashMap	dataLoaded;

  wxArrayString			pathToCurrentDoc;

  std::cerr << "[SaveCenter] Load file : " << filename.mb_str() << std::endl;

  //read the xml file and fill in a big hash map
  xmlFile->OpenDocument(filename);
  
  while(xmlFile->Read())
    {
      nodeType = xmlFile->GetNodeType();

      if(nodeType == XML_READER_TYPE_ELEMENT)
	{
	  std::cerr << "[SaveCenter] start tag : " << std::endl;
 
	  nodeName = xmlFile->GetNodeName();
	  std::cerr << "[SaveCenter] Node Name : " << nodeName.mb_str() << std::endl;
	  std::cerr << "[SaveCenter] Node Value : " << xmlFile->GetNodeValue().mb_str() << std::endl;

	  if(nodeName == WIRED_TAG_WIREDDOC)
	    {
	      currentDoc = xmlFile->GetAttribute(wxT("id"));
	      std::cerr << "[SaveCenter] currentDoc = " << currentDoc.mb_str();
	      pathToCurrentDoc.Add(currentDoc);
	      if(dataLoaded.find(currentDoc) == dataLoaded.end())
		dataLoaded[currentDoc]->Add(new SaveElementArray());
	      //may look hazardous, but last() returns the last item we added...
	      currentArray = dataLoaded[currentDoc]->Last();
	    }
	  else
	    {
	      currentArray->Add(new SaveElement);
	      saveElem = currentArray->Last();

	      saveElem->setKey(nodeName);
	      saveElem->setValue(xmlFile->GetNodeValue());

	      //attributes handling
	      for(int i = 0; i < xmlFile->GetAttributeCount(); i++)
		saveElem->addAttribute(xmlFile->GetAttributeName(i),
				       xmlFile->GetAttributeValue(i));

	    }
	}
      else if(nodeType == XML_READER_TYPE_END_ELEMENT)
	{
	  std::cerr << "[SaveCenter] end tag : " << xmlFile->GetNodeName().mb_str() << std::endl;
	  
	  pathToCurrentDoc.Remove(nodeName);
	  currentDoc = pathToCurrentDoc.Last();
	}
    }

  //un petit dump de la table de hash pour le debug ?

  //redistribute the elements of the hash
  //In a separated method for readability and for logic
  //check technical documentation for more informations.
  RedistributeHash(dataLoaded);

 
}


void		SaveCenter::RedistributeHash(SaveElementArrayHashMap dataLoaded)
{
  WiredDocumentArray				children;
  wxString					currentName;
  WiredDocumentArrayHashMap::iterator		it;
  WiredDocumentArrayHashMap			toProcess;
  WiredDocument					*currentDoc;

  int						i, j;

  //init the whole process with the SaveCenter on top
  currentName = getName();
  toProcess[currentName] = new WiredDocumentArray();
  toProcess[currentName]->Add(this);
  

  while(!toProcess.empty())
    {
      it = toProcess.begin();
      if(it->second->empty())
	{
	  delete it->second;
	  toProcess.erase(it->first);
	}
      else
	{
	  //load the document
	  currentDoc = it->second->Item(0);
	  currentDoc->Load(* (dataLoaded[it->first]->Item(0)) );
	  //get infos before removing it
	  children = currentDoc->getChildren();
	  //add his children to the list
	  for(i = 0; i < children.GetCount(); i++)
	    {
	      currentName = children[i]->getName();
	      if(toProcess.find(currentName) == toProcess.end())
		toProcess[currentName] = new WiredDocumentArray();
	      toProcess[currentName]->Add(children[i]);
	    }
	  //remove it from the list
	  it->second->Remove(0);
	}
    }
  
}

wxString	SaveCenter::GetDefaultProjectName(wxFileName cwd)
{
  wxString ret(WIRED_DEFAULT_PROJECT_NAME);
  wxString fullPath;
  int i = 0;

  do
    {
      fullPath.Clear();
      i++;
      fullPath << cwd.GetPath(wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR) << ret << i;
    }
  while(wxDirExists(fullPath));

  ret << i;

  return ret;
}

wxString	SaveCenter::GetProjectNameFromProjectPath(wxFileName path)
{
  wxString		ret;
  wxArrayString		dirs;
  
  dirs = path.GetDirs();

  ret = dirs[dirs.GetCount() - 1];

  return ret;
}
