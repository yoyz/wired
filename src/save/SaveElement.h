#ifndef _SAVEELEMENT_H_
#define _SAVEELEMENT_H_

WX_DEFINE_ARRAY_PTR(SaveElement *, SaveElementArray);
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
  
  inline wxString	getKey() { return _key; }
  inline wxString	getValue() { return _value; }

  inline wxString	getAttribute(wxString key)
    {
      if (_attributes.find(key) != _attributes.end())
	return _attributes[key];
      else
	return wxT("");
    }
  
  inline bool		attributeExists(wxString key) 
    {  return ( _attributes[key] != _attributes.end() ); }

  inline void		clearAttributes() { _attributes.clear(); }
  inline void		clear() { _key.Clear(); _value.Clear(); clearAttributes(); }

  //I don't really know how to do it, but it would be cool if only the SaveCenter
  //could access this...
 protected:
  inline AttributesHashMap	getAttributes() { return _attributes; }

 private:
  wxString			_key;
  wxSring			_value;
  AttributesHashMap		_attributes;
};

#endif /*_SAVEELEMENT_H_ */
