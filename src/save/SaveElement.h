#ifndef _SAVEELEMENT_H_
#define _SAVEELEMENT_H_

#include <wx/string.h>
#include <wx/hashmap.h>
#include <wx/dynarray.h>

class SaveElement;

WX_DEFINE_ARRAY_PTR(SaveElement*, SaveElementArray);
WX_DECLARE_STRING_HASH_MAP(SaveElementArray*, SaveElementsHashMap);
WX_DECLARE_STRING_HASH_MAP(wxString, AttributesHashMap);

class SaveElement
{
 public:
  inline SaveElement() {  }

  inline SaveElement(wxString key, wxString value)
    { 
      _key = key;
      _value = value;
    }

  inline SaveElement(SaveElement &copy):
    _attributes(copy.getAttributes()), _key(copy.getKey()), _value(copy.getValue())
    {      
    }

  inline ~SaveElement(){};

  //accessors
  inline void		setKey(wxString key) { _key = key; }
  inline void		setValue(wxString value) { _value = value; }
  inline void		setPair(wxString key, wxString value) 
    { _key = key; _value = value; }

  inline void		addAttribute(wxString key, wxString value) 
    { _attributes[key] = value; }
  
  inline void		addChildren(SaveElement *children)
    { _children.Add(children); }

  inline wxString	getKey() { return _key; }
  inline wxString	getValue() { return _value; }

  inline SaveElementArray	getChildren() { return _children; }
  
  inline wxString	getAttribute(wxString key)
    {
      if (_attributes.find(key) != _attributes.end())
	return _attributes[key];
      else
	return wxT("");
    }
  
  inline bool		attributeExists(wxString key) 
    {  return ( _attributes.find(key) != _attributes.end() ); }

  inline void		clearAttributes() { _attributes.clear(); }
  inline void		clear() { _key.Clear(); _value.Clear(); clearAttributes(); }

  inline AttributesHashMap	getAttributes() { return _attributes; }

 private:
  wxString			_key;
  wxString			_value;
  AttributesHashMap		_attributes;
  SaveElementArray		_children;
};

#endif /*_SAVEELEMENT_H_ */
