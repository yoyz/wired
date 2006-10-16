#ifndef _SAVEELEMENT_H_
#define _SAVEELEMENT_H_

WX_DEFINE_ARRAY_PTR(SaveElement *, WiredSaveElementArray);
WX_DECLARE_STRING_HASH_MAP(wxString, AttributesHashMap);

class SaveElement
{
 public:
  SaveElement();
  SaveElement(wxString key, wxString value);
  ~SaveElement();

  //accessors
  void		setKey(wxString key);
  void		setValue(wxString value);
  void		setPair(wxString key, wxString value);
  void		addAttribute(wxString key, wxString value);
  
  wxString	getKey();
  wxString	getValue();
  wxString	getAttribute(wxString key);
  
  bool		attributeExists(wxString key);
  void		clearAttributes();

  //I don't really know how to do it, but it would be cool if only the SaveCenter
  //could access this...
 protected:
  AttributesHashMap	getAttributes();

 private:
  wxString			_key;
  wxSring			_value;
  AttributesHashMap		_attributes;
};

#endif /*_SAVEELEMENT_H_ */
