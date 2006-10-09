#include "SaveCenter.h"

SaveCenter::SaveCenter()
{
  //Nothing to do yet in here...
}

SaveCenter::~SaveCenter()
{
  //Nothing to do yet in here...
}

void	SaveCenter::Register(WiredDocument *child)
{
  _children.push_back(child);
}

bool	SaveCenter::WriteXml()
{
  vector<WiredDocument *>::iterator	it;

  //commencer le document avec des headers standards
  
  for(it = _children.begin(); it != _children.end(); it++)
    WriteDocument(*it);

  //finir le document avec des footers standards

}

bool	SaveCenter::WriteDocument(WiredDocument *currentNode)
{
  vector<SaveElement>			toWrite;
  vector<SaveElement>::iterator		itElem;
  vector<WiredDocument *>		childrenOfCurrentNode;
  vector<WiredDocument *>::iterator	itChild;

  //get our children
  childrenOfCurrentNode = currentNode->getChildren();

  //get our SaveElements
  toWrite = currentNode->Save();

  //write our SaveElements...
  //...start with our name...
  startTag(currentNode->getName());
  
  //...then the elements
  for (itElem = toWrite.begin();
       itElem != toWrite.end();
       itElem++)
    WriteElement(elem);
  
  //call recursively on our children
  for (it = childrenOfCurrentNode.begin();
       it != childrenOfCurrentNode.end();
       it ++)
    WriteDocument(*it);      
  
  //...finish by closing things
  endTag(currentNode->getName());    
}

bool	SaveCenter::WriteElement(SaveElement elem)
{
  //XML bullshit
}
