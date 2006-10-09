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

 private:
  wxString			_key;
  wxSring			_value;
  map<wxString, wxString>	_attributes;
};
