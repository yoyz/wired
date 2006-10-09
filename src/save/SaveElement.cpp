#include "SaveElement.h"

SaveElement::SaveElement(WiredObject *Object)
{
  _object = Object;
}

SaveElement::SaveElement(WiredObject *Object, wxString Key, wxString Value)
{
  _object = Object;
  _key = key;
  _value = value;
}

void		SaveElement::setKey(wxString key)
{
  _key = key;
}

void		SaveElement::setValue(wxString value)
{
  _value = value;
}

void		SaveElement::setPair(wxString key, wxString value)
{
  _key = key;
  _value = value;
}

void		SaveElement::addAttribute(wxString key, wxString value)
{

  //comment on fait pour rajouter un element a la map ?

}

wxString	SaveElement::getKey()
{
  return _key;
}

wxString	SaveElement::getValue()
{
  return _value;
}

wxString	SaveElement::getAttribute(wxString key)
{
  if (_attributes[key].is_set())
    return _attributes[key];
  else
    return wxT("");
}

bool		SaveElement::attributeExists(wxString key)
{
  return _attributes[key].is_set();
}

void		SaveElement::clearAttributes()
{
  _attributes.clear();
}
