class WiredDocument
{
 private:
  WiredDocument(WiredDocument *parent = NULL);


 public:
  virtual vector<SaveElement>	Save() = 0;
  virtual void			Load() = 0;

  vector<WiredDocument *>	getChildren();
  wxString			getName();
  void				Register(WiredDocument *children);
  

 private:
  vector<WiredDocument *>	_children;
  wxString			_name;
};
