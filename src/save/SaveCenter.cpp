#include "SaveCenter.h"

SaveCenter::SaveCenter(wxFileName  projectPath,
		       WiredDocument *docParent)
  : WiredDocument(wxT("savecenter"), docParent, true)
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

void	SaveCenter::SaveProject()
{
  std::cerr << "[SaveCenter] SaveProject" << std::endl;

  wxString	fileName;
  WiredXml	*xmlFile = new WiredXml();

  if(!_projectPath.DirExists())
    _projectPath.Mkdir();
    
  fileName << _projectPath.GetPath(wxPATH_GET_SEPARATOR | wxPATH_GET_VOLUME) << wxT("wired.xml");

  xmlFile->CreateDocument(fileName);

  SaveDocument((WiredDocument *)this, xmlFile);

  xmlFile->EndDocumentWriter();
  delete xmlFile;

  std::cerr << "[SaveCenter] END SaveProject" << std::endl;

}

void	SaveCenter::SaveFile(WiredDocument *doc, wxString file)
{
  std::cerr << "[SaveCenter] SaveFile" << std::endl;

  doc->SaveMe();
  WriteFile(file, doc->getDocFile(file)); 

  std::cerr << "[SaveCenter] END SaveFile" << std::endl;
}

void	SaveCenter::SaveDocument(WiredDocument *currentNode, WiredXml *xmlFile)
{
  WiredDocumentArray			childrenOfCurrentNode;
  int					i;
  SaveElementsHashMap			saveElements;
  SaveElementArray			*toWrite;
  SaveElementsHashMap::iterator		saveElementsIt;

  std::cerr << "[SaveCenter] SaveDocument" << std::endl;

  //Get our children
  childrenOfCurrentNode = currentNode->getChildren();

  //Save Document
  currentNode->SaveMe();
  
  //get my SaveElements
  saveElements = currentNode->getDocData();

  //write our SaveElements...
  //...start with our name...
  xmlFile->StartElement(WIRED_TAG_WIREDDOC);
  xmlFile->WriteAttribute(wxT("id"), currentNode->getName());

  //Write references
  AddReferences(saveElements, xmlFile);

  //get elements to write in the conf file
  if(saveElements.count(WIRED_PROJECT_FILE))
    {      
      toWrite = saveElements[WIRED_PROJECT_FILE];

      //...then write the elements
      for (i = 0; i < toWrite->GetCount(); i++)
	WriteElement(toWrite->Item(i), xmlFile);
    }
  //Write the other files
  for (saveElementsIt = saveElements.begin();
       saveElementsIt != saveElements.end();
       saveElementsIt++)
    if(saveElementsIt->first != WIRED_PROJECT_FILE)
      WriteFile(saveElementsIt->first, saveElementsIt->second);

  //call recursively on our children
  for (i = 0; i < childrenOfCurrentNode.GetCount(); i++)
    SaveDocument(childrenOfCurrentNode[i], xmlFile);
  
  //...finish by closing things
  xmlFile->EndElement();

  std::cerr << "[SaveCenter] END SaveDocument" << std::endl;

}

void	SaveCenter::AddReferences(SaveElementsHashMap &saveElements, 
				  WiredXml *xmlFile)
{
  std::cerr << "[SaveCenter] AddReferences" << std::endl;

  SaveElementsHashMap::iterator	saveElementsIt;
  SaveElement			*ref = new SaveElement();
  wxFileName			relativePath;

  //for each entry of the hash map....
  for (saveElementsIt = saveElements.begin();
       saveElementsIt != saveElements.end();
       saveElementsIt++)
    //if it is not the one to write in the project file
    if(saveElementsIt->first != WIRED_PROJECT_FILE)
      {
	//fill a SaveElement
	ref->clear();
	std::cerr << "[SaveCenter] trying to make path relative..." << std::endl;
	std::cerr << "[SaveCenter] source :" << saveElementsIt->first.mb_str() << std::endl;	
	relativePath.Assign(getPathFromRelativeTag(saveElementsIt->first));
	std::cerr << "[SaveCenter] relativePath = " << relativePath.GetFullPath().mb_str() << std::endl;
	relativePath.MakeRelativeTo(getProjectPath().GetPath());
	std::cerr << "[SaveCenter] relativePath, once relative = " << relativePath.GetFullPath().mb_str() << std::endl;
	ref->setPair(wxT("reference"), relativePath.GetFullPath());
	//and write it.
	WriteElement(ref, xmlFile);
      }

  delete ref;
  std::cerr << "[SaveCenter] END AddReferences" << std::endl;
}

void	SaveCenter::WriteElement(SaveElement *elem, WiredXml *xmlFile)
{
  std::cerr << "[SaveCenter] WriteElement" << std::endl;

  int				i;
  AttributesHashMap		attributes;
  AttributesHashMap::iterator	attributesIt;
  SaveElementArray		children;

  attributes = elem->getAttributes();
  std::cerr << "[SaveCenter] elem->getAttributes()" << std::endl;

  xmlFile->StartElement(elem->getKey());  
  std::cerr << "[SaveCenter] startElement" << std::endl;

  for(attributesIt = attributes.begin();
      attributesIt != attributes.end();
      attributesIt++)
    {
      xmlFile->WriteAttribute(attributesIt->first, attributesIt->second, true);
      std::cerr << "[SaveCenter] attribute iteration" << std::endl;
    }
  xmlFile->WriteString(elem->getValue());
  std::cerr << "[SaveCenter] Write value" << std::endl;
  
  children = elem->getChildren();
  std::cerr << "[SaveCenter] get children (" << children.GetCount() << ")" << std::endl;
  
  for(int j = 0; j < children.GetCount(); j++)
    {
      std::cerr << "[SaveCenter] children iteration" << std::endl;
      if(children.Item(j) == NULL)
	std::cerr << "[SaveCenter] children[j] == NULL" << std::endl;
      WriteElement(children.Item(j), xmlFile);
    }  
  xmlFile->EndElement();
  
  std::cerr << "[SaveCenter] END WriteElement" << std::endl;
}

wxFileName	SaveCenter::getPathFromRelativeTag(wxString tag)
{
  wxFileName	ret;

  while(tag.Find('/') != -1)
    {
      ret.AppendDir(tag.BeforeFirst('/'));
      tag = tag.AfterFirst('/');
    }
  tag = tag.BeforeFirst('.');
  ret.SetName(tag);
  ret.SetExt(wxT("xml"));

  return ret;
}

void		SaveCenter::WriteFile(wxString relativeFileName, 
				      SaveElementArray *elements)
{
  std::cerr << "[SaveCenter] WriteFile" << std::endl;

  wxFileName	filename;
  wxFileName	relativePath;
  wxArrayString	dirs;

  WiredXml	*xmlFile = new WiredXml();
  int		i;
  
  std::cerr << "[SaveCenter] WriteFile : " << relativeFileName.mb_str() << std::endl;

  filename.Assign(getProjectPath());
  relativePath = getPathFromRelativeTag(relativeFileName);
  dirs = relativePath.GetDirs();

  for(int j = 0; j < dirs.GetCount(); j++)
    filename.AppendDir(dirs[j]);

  filename.SetName(relativePath.GetName());
  filename.SetExt(relativePath.GetExt());
  
  filename.MakeAbsolute();
  
  if(!wxFileName::DirExists(filename.GetPath(wxPATH_GET_SEPARATOR | wxPATH_GET_VOLUME)))
    wxFileName::Mkdir(filename.GetPath(wxPATH_GET_SEPARATOR | wxPATH_GET_VOLUME),
		      0777, wxPATH_MKDIR_FULL);

  xmlFile->CreateDocument(filename.GetFullPath());
  
  xmlFile->StartElement(relativeFileName);
  
  for (i = 0; i < elements->GetCount(); i++)
    WriteElement(elements->Item(i), xmlFile);
  
  xmlFile->EndElement();
  delete xmlFile;

  std::cerr << "[SaveCenter] END WriteFile" << std::endl;
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
      _projectPath.AssignDir(projectPath.GetFullPath());
      
      _projectName = GetProjectNameFromProjectPath(_projectPath);
    }

}

wxString	SaveCenter::getProjectName()
{
  return _projectName;
}

void		SaveCenter::setProjectName(wxString projectName)
{
  std::cerr << "[SaveCenter] setProjectName : " << projectName << std::endl;

  _projectName = projectName;

  _projectPath.RemoveLastDir();
  _projectPath.AppendDir(_projectName);

}

//This method really looks like LoadProject... maybe we could do something...
SaveElementArray	SaveCenter::LoadFile(wxString filename)
{
  WiredXml		*xmlFile = new WiredXml();
  wxString		rootTag;
  SaveElementArray	ret;

  wxString	nodeName;
  int			nodeType;

  SaveElement		*currSaveElem;

  rootTag = filename.AfterLast('/');
  rootTag = filename.BeforeLast('.');

  xmlFile->OpenDocument(filename);

  while(xmlFile->Read())
    {
      nodeType = xmlFile->GetNodeType();
      if(nodeType == XML_READER_TYPE_ELEMENT)
	{
	  nodeName = xmlFile->GetNodeName();
	  if(nodeName != rootTag)
	    {
	      ret.Add(new SaveElement());
	      currSaveElem = ret.Last();
	      currSaveElem->setKey(nodeName);
	      
	      //attributes handling
	      for(int i = 0; i < xmlFile->GetAttributeCount(); i++)
		currSaveElem->addAttribute(xmlFile->GetAttributeName(i),
					   xmlFile->GetAttributeValue(i));
	    }
	}
      else if(nodeType == XML_READER_TYPE_TEXT)
	{
	  currSaveElem->setValue(xmlFile->GetNodeValue());
	}
    }
  return ret;
}


void	SaveCenter::LoadProject()
{
  //infos about the node we are reading
  WiredXml	*xmlFile = new WiredXml();
  wxString	filename;
  wxString	nodeName;
  int		nodeType;

  //the things we are storing (code readability)
  //It's just used as a reference. No new, no delete on this pointer.
  SaveElement		*currentSaveElem = NULL;

  //we store the whole path to the current document.
  //Please refer to the technical documentation for more infos.
  //used only to make the code readable
  wxString		currentDoc;
  SaveElementArray	*currentArray;
  
  //a big hashmap to store everything
  SaveElementArrayHashMap	dataLoaded;

  wxArrayString			pathToCurrentDoc;

  filename.Clear();
  filename << getProjectPath().GetPath(wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR);
  filename << wxT("wired.xml");

  std::cerr << "[SaveCenter] Load file : " << filename.mb_str() << std::endl;

  //read the xml file and fill in a big hash map
  xmlFile->OpenDocument(filename);
  
  while(xmlFile->Read())
    {
      nodeType = xmlFile->GetNodeType();

      if(nodeType == XML_READER_TYPE_ELEMENT)
	{
	  nodeName = xmlFile->GetNodeName();

	  if(nodeName == WIRED_TAG_WIREDDOC)
	    {
	      currentDoc = xmlFile->GetAttribute(wxT("id"));
	      pathToCurrentDoc.Add(currentDoc);

	      //if it is the first doc of this type
	      if(dataLoaded.find(currentDoc) == dataLoaded.end())
		{
		  //we add create the key and its array
		  dataLoaded[currentDoc] = new SaveElementArrayArray();
		}
	      //we add a new array to it
	      dataLoaded[currentDoc]->Add(new SaveElementArray());
	      //may look hazardous, but last() returns the last item we added...
	      currentArray = dataLoaded[currentDoc]->Last();
	    }
	  else
	    {
	      currentArray->Add(new SaveElement);
	      currentSaveElem = currentArray->Last();

	      currentSaveElem->setKey(nodeName);

	      //attributes handling
	      for(int i = 0; i < xmlFile->GetAttributeCount(); i++)
		currentSaveElem->addAttribute(xmlFile->GetAttributeName(i),
					      xmlFile->GetAttributeValue(i));

	    }
	}
      else if(nodeType == XML_READER_TYPE_TEXT)
	{
	  currentSaveElem->setValue(xmlFile->GetNodeValue());
	}
      else if(nodeType == XML_READER_TYPE_END_ELEMENT)
	{
	  pathToCurrentDoc.Remove(nodeName);
	  currentDoc = pathToCurrentDoc.Last();
	}
    }
  
 
  //DumpSaveElementArrayHashMap(dataLoaded);

  //redistribute the elements of the hash
  //In a separated method for readability and for logic
  //check technical documentation for more informations.
  
  RedistributeHash(dataLoaded);

 
}

void		SaveCenter::DumpSaveElementArrayHashMap(SaveElementArrayHashMap dataLoaded)
{
  //un petit dump de la table de hash pour le debug
  std::cerr << "[SaveCenter] dataLoaded Big Dump" << std::endl;
  //iterate on the keys of the hash map
  for(SaveElementArrayHashMap::iterator myIt = dataLoaded.begin();
      myIt != dataLoaded.end();
      myIt++)
    //iterate on the elements of the ArrayArray
    for(int z = 0; z < myIt->second->GetCount(); z++)
      //iterate on the elements of the Array
      for(int y = 0; y < myIt->second->Item(z)->GetCount(); y++)
	{
	  std::cerr << "SaveElementArrayHashMap[" << myIt->first << "]";
	  std::cerr << "[" << z << "][" << y << "]->getKey() = ";
	  std::cerr << dataLoaded[myIt->first]->Item(z)->Item(y)->getKey().mb_str() << std::endl;
	}
}

void		SaveCenter::DumpWiredDocumentArrayHashMap(WiredDocumentArrayHashMap toProcess)
{
  for(WiredDocumentArrayHashMap::iterator it = toProcess.begin();
      it != toProcess.end();
      it ++)
    for(int i = 0; i < it->second->GetCount(); i++)
      {
	std::cerr << "WiredDocumentArrayHashMap[" << it->first << "]";
	std::cerr << "[" << i << "]->getName() = ";
	std::cerr << toProcess[it->first]->Item(i)->getName().mb_str() << std::endl;
      }
}


void		SaveCenter::RedistributeHash(SaveElementArrayHashMap dataLoaded)
{
  WiredDocumentArray				children;
  wxString					childName;
  wxString					currentName;
  WiredDocumentArrayHashMap::iterator		it;
  WiredDocumentArrayHashMap			toProcess;
  WiredDocument					*currentDoc;

  int						i;

  //init the whole process with the SaveCenter on top
  currentName = getName();
  toProcess[currentName] = new WiredDocumentArray();
  toProcess[currentName]->Add(this);
  
  while(!toProcess.empty() && !dataLoaded.empty())
    {
      it = toProcess.begin();
      currentName = it->first;

      //load the document
      currentDoc = it->second->Item(0); 
      currentDoc->Load(* (dataLoaded[currentName]->Item(0)) );
      //get infos before removing it
      children = currentDoc->getChildren();
      //add his children to the list
      for(i = 0; i < children.GetCount(); i++)
	{
	  childName = children[i]->getName();
	  if(toProcess.find(childName) == toProcess.end())
	    toProcess[childName] = new WiredDocumentArray();
	  toProcess[childName]->Add(children[i]);
	}

      //remove the doc from the doc HashMap
      it->second->RemoveAt(0);

      //remove the data from dataLoaded
      delete dataLoaded[currentName]->Item(0);
      dataLoaded[currentName]->RemoveAt(0);

      
      //make things clean... remove unused entries of both hash maps.
      if(it->second->IsEmpty())
	{
	  delete it->second;
	  toProcess.erase(currentName);
	}
      if(dataLoaded[currentName]->IsEmpty())
	{
	  delete dataLoaded[currentName];
	  dataLoaded.erase(currentName);
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

bool		SaveCenter::getSaved()
{
  return _saved;
}
