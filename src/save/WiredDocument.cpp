#include "WiredDocument.h"

#include <iostream>
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

void		WiredDocument::SaveMe()
{
  clearDocData();

  Save();
}

void		WiredDocument::saveDocData(wxString file, SaveElement *data)
{
  SaveElementsHashMap::iterator	it;

  if(!_dataSave.count(file))
      _dataSave[file] = new SaveElementArray();

  //Should check if key already exists and delete it before overwriting it.
  _dataSave[file]->Add(data);

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
