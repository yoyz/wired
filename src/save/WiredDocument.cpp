#include "WiredDocument.h"

WiredDocument::WiredDocument(wxString name, WiredDocument *parent = NULL)
{
  //uncomment when savecenter is instanciated
//   if (!parent)
//     parent = saveCenter;

  if(parent)
    parent->Register(this);

  _name = name;

}

void		WiredDocument::Register(WiredDocument *child)
{
  _children.Add(child);
}


WiredDocumentArray	WiredDocument::getChildren()
{
  return _children;
}

wxString	WiredDocument::getName()
{
  return _name;
}

void		WiredDocument::saveDocData(wxString file, SaveElement *data)
{
  SaveElement	*toAdd;

  toAdd = new SaveElement(*data);

  _dataSave[file]->Add(toAdd);
}

void		WiredDocument::clearDocData()
{
  SaveElementsHashMap::iterator	dataSaveIt;

  for (dataSaveIt = _dataSave.begin();
       dataSaveIt != _dataSave.end();
       dataSaveIt++)
    rmDocDataFile(dataSaveIt->first);

  _dataSave.clear();
}

void		WiredDocument::rmDocDataFile(wxString file)
{
  int	i;

  if(_dataSave.find(file) != _dataSave.end())
    for (i = 0; i < _dataSave[file]->GetCount(); i++)
      if(_dataSave[file]->Item(i) != NULL)
	delete(_dataSave[file]->Item(i));

  _dataSave.erase(file);
}

SaveElementsHashMap	WiredDocument::getDocData()
{
  return _dataSave;
}

SaveElementArray	*WiredDocument::getDocFile(wxString file)
{
  return _dataSave[file];
}
