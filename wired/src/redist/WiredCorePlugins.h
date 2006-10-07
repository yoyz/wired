#ifndef __WIREDCOREPLUGINS_H__
#define __WIREDCOREPLUGINS_H__

class	WiredCorePlugins
{
 private:
  int		_MidiType;
  int		_MidiController;
  int		_MidiValue;

 public:

  WiredCorePlugins::WiredCorePlugins();
  WiredCorePlugins::~WiredCorePlugins();


  /**
   * Event related
   */
  void		SendMouseEvent(WiredPlugin *plug, wxMouseEvent *event);


  void		SendKeyEvent(WiredPlugin *plug, wxKeyEvent *event);


  void		SendPaintEvent(WiredPlugin *plug, wxPaintEvent *event);


  void		UpdatePluginGui(WiredPlugin *plug);


  /**
   * Basic info
   */

  wxString	GetProductName();


  wxString	GetProductVersion();


  // long		GetBufferSize();
  //

  /**
   * Audio info
   */

  // double		GetSamplingRate();
  //

  float		GetBPM();


  int		GetSigDenominator();


  int		GetSigNumerator();


  double	GetSamplesPerMeasure();


  double	GetMeasurePerSample();


  long		GetCurAudioPos();


  double	GetCurrentPos();


  /**
   * Gui related
   */

  wxString	OpenFileLoader(wxString& title,
			       std::vector<wxString>& extensions,
			       bool akai);


  wxString	SaveFileLoader(wxString& title,
			       std::vector<wxString>& extensions);


  void		SendHelp(wxString& value);


  void		ShowOptionalView(WiredPlugin *plug);


  void		CloseOptionalView(WiredPlugin *plug);

  /**
   * Midi related
   */

  void		AddMidiPattern(WiredPlugin *plug,
			       list<SeqCreateEvent*> midi);


  void		ShowMidiController(WiredPlugin *plug);


  int		GetLastMidiType();


  int		GetLastMidiController();


  int		GetLastMidiValue();


};

#endif // __WIREDCOREPLUGINS_H__
