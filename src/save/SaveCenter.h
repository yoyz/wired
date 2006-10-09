
class SaveCenter
{
 public:
  SaveCenter();
  ~SaveCenter();

  void		Register(WiredDocument *children);

 private:
  bool		WriteElement(SaveElement elem);
  bool		WriteXml();

  bool		ReadXml();

 private:
  vector<WiredDocument *>	_children;
}
