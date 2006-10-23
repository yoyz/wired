#include "WiredCorePlugins.h"


WiredCorePlugins::WiredCorePlugins()
{

}

WiredCorePlugins::~WiredCorePlugins()
{

}

void		WiredCorePlugins::SendMouseEvent(WiredPlugin* plugin, wxMouseEvent* event)
{
  RackPanel->HandleMouseEvent(plugin, event);
}

void		WiredCorePlugins::SendKeyEvent(WiredPlugin* plugin, wxKeyEvent* event)
{
  RackPanel->HandleKeyEvent(plugin, event);
}

void		WiredCorePlugins::SendPaintEvent(WiredPlugin* plugin, wxPaintEvent* event)
{
  RackPanel->HandlePaintEvent(plugin, event);
}

void		WiredCorePlugins::UpdatePluginGui(WiredPlugin* plugin)
{
  MainWin->AddUpdatePlugin(plugin);
}

wxString	WiredCorePlugins::GetProductName()
{
  return (wxT(PACKAGE));
}

wxString	WiredCorePlugins::GetProductVersion()
{
  return (wxT(PACKAGE_VERSION));
}

// long		WiredCorePlugins::GetBufferSize()
// {

// }

// double	WiredCorePlugins::GetSamplingRate()
// {

// }

float		WiredCorePlugins::GetBpm()
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
						 std::vector<wxString>* extensions,
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

void		WiredCorePlugins::ShowOptionalView(WiredPlugin* plugin)
{
  OptPanel->ShowPlug(plugin);
}

void		WiredCorePlugins::CloseOptionalView(WiredPlugin* plugin)
{
  OptPanel->ClosePlug(plugin);

}

void		WiredCorePlugins::AddMidiPattern(WiredPlugin* plugin,
						 list<SeqCreateEvent*>* midi)
{
  Seq->AddMidiPattern(midi, plugin);
}

void		WiredCorePlugins::ShowMidiController(WiredPlugin* plugin)
{
  MidiController*	Controller;

  // lock mutex
  MidiMutex.Lock();
  Controller = new MidiController(plugin->GetStartInfo()->GetRack());
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
