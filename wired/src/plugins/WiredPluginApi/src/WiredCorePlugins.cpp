#include "WiredCorePlugins.h"

WiredCorePlugins::WiredCorePlugins()
{

}

WiredCorePlugins::~WiredCorePlugins()
{

}

void		WiredCorePlugins::SendMouseEvent(WiredPlugin *plug, wxMouseEvent *event)
{
  RackPanel->HandleMouseEvent(plug, event);
}

void		WiredCorePlugins::SendKeyEvent(WiredPlugin *plug, wxKeyEvent *event)
{
  RackPanel->HandleKeyEvent(plug, event);
}

void		WiredCorePlugins::SendPaintEvent(WiredPlugin *plug, wxPaintEvent *event)
{
  RackPanel->HandlePaintEvent(plug, event);
}

void		WiredCorePlugins::UpdatePluginGui(WiredPlugin *plug)
{
  MainWin->AddUpdatePlugin(plug);
}

wxString	WiredCorePlugins::GetProductName()
{
  return (wxT(WIRED_NAME));
}

wxString	WiredCorePlugins::GetProductVersion()
{
  return (wxT(WIRED_VERSION));
}

// long		WiredCorePlugins::GetBufferSize()
// {

// }

// double		WiredCorePlugins::GetSamplingRate()
// {

// }

float		WiredCorePlugins::GetBPM()
{
  return (Seq->BPM);
}

int		WiredCorePlugins::GetSigDenominator()
{
  return (Seq->SigDenominator);
}

int		WiredCorePlugins::GetSigNumerator()
{
  return (Seq->SigNumerator);
}

long		WiredCorePlugins::GetCurAudioPos()
{
  return (Seq->CurAudioPos);
}

double		WiredCorePlugins::GetSamplesPerMeasure()
{
  return (Seq->SamplesPerMeasure);
}

double		WiredCorePlugins::GetMeasurePerSample()
{
  return (Seq->MeasurePerSample);
}

double		WiredCorePlugins::GetCurrentPos()
{
  return (Seq->CurrentPos);
}

wxString	WiredCorePlugins::OpenFileLoader(wxString& title,
						 std::vector<wxString>* extensions,
						 bool addExts,
						 bool akai)
{
  wxString	selected;
  FileLoader*	dlg = new FileLoader(MainWin, MainWin_FileLoader,
				     title,
				     akai,
				     false,
				     extensions,
				     addExts);

  if (dlg->ShowModal() == wxID_OK)
    selected = dlg->GetSelectedFile();
  dlg->Destroy();
}

wxString	WiredCorePlugins::SaveFileLoader(wxString& title,
						 std::vector<wxString>& extensions,
						 bool addExts)
{
  wxString	selected;
  FileLoader*	dlg = new FileLoader(MainWin, MainWin_FileLoader,
				     title,
				     false,
				     true,
				     extensions,
				     addExts);

  if (dlg->ShowModal() == wxID_OK)
    selected = dlg->GetSelectedFile();
  dlg->Destroy();
}

void		WiredCorePlugins::SendHelp(wxString& value)
{
  if (HelpWin->IsShown())
    HelpWin->Help->Load_Text(value);
}

void		WiredCorePlugins::ShowOptionalView(WiredPlugin *plug)
{
  OptPanel->ShowPlug(plug);
}

void		WiredCorePlugins::CloseOptionalView(WiredPlugin *plug)
{
  OptPanel->ClosePlug(plug);

}

void		WiredCorePlugins::AddMidiPattern(WiredPlugin *plug,
						 list<SeqCreateEvent*>& midi)
{
  Seq->AddMidiPattern(midi, plug);
}

void		WiredCorePlugins::ShowMidiController(WiredPlugin *plug)
{
  MidiController*	Controller;

  // lock mutex
  MidiMutex.Lock();
  Controller = new MidiController(plug)
  MidiMutex.Unlock();

  // get information from user and stock them
  Controller->ShowModal();
  _MidiType = Controller->Type;
  _MidiController = Controller->Controller;
  _MidiValue = Controller->Value;

  // lock mutex, and delete object
  MidiMutex.Lock();
  delete Controller;
  MidiMutex.Unlock();
}

int		WiredCorePlugins::GetLastMidiType()
{
  return (_MidiType);
}

int		WiredCorePlugins::GetLastMidiController()
{
  return (_MidiController);
}

int		WiredCorePlugins::GetLastMidiValue()
{
  return (_MidiValue);
}
