WiredDocument::WiredDocument(wxString name, WiredDocument *parent = NULL)
{
  if (!parent)
    parent = saveCenter;

  parent->Register(this);

  _name = name;

}

void		WiredDocument::Register(WiredDocument *child)
{
  _children->push_back(child);
}


vector<WiredDocument *>	WiredDocument::getChildren()
{
  return _children;
}

wxString	WiredDocument::getName()
{
  return _name;
}
