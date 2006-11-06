// Copyright (C) 2004-2006 by Wired Team
// Under the GNU General Public License Version 2, June 1991

#include <wx/colour.h>
#include "Track.h"
#include "Sequencer.h"
#include "Mixer.h"
#include "Pattern.h"
#include "AudioPattern.h"
#include "MidiPattern.h"
#include "SeqTrack.h"
#include "SeqTrackPattern.h"
#include "MixerGui.h"

wxColour				PatternColours[MAX_AUTO_COLOURS] = 
  {  
    // blue
    wxColour( 50, 166, 211),				
    wxColour( 75, 133, 204),
    wxColour( 15,  98, 198),
    // purple
    wxColour(134, 112, 175),				
    wxColour(133,  96, 204),
    wxColour( 96,  47, 188),
    // orange
    wxColour(247, 186, 111),				
    wxColour(237, 134,  66),
    wxColour(239, 104,  75),
    // green
    wxColour(182, 226,  99),				
    wxColour(130, 206,  95),
    wxColour( 97, 183, 166),

    wxColour( 50, 166, 211),				
    wxColour( 75, 133, 204),
    wxColour( 15,  98, 198),
    wxColour( 15,  98, 198)    
  };

Track::Track(WiredDocument* parentDoc, trackType type,
	     wxPoint& pos, wxSize& size, wxWindow* TrackView) : 
  WiredDocument(wxT("track"), parentDoc)
{
  // basic initialization
  Wave = 0x0;
  Midi = 0x0;
  Index = 0;
  Type = type;

  ColourIndex = (AudioTrackCount + MidiTrackCount - 1) % MAX_AUTO_COLOURS;

  // relative to the header of track (mostly GUI)
  TrackOpt = new SeqTrack(Seq->Tracks.size() + 1, TrackView,
			  pos, size, type, this);

  // list of patterns in the track
  TrackPattern = new SeqTrackPattern();

  // mixer output 
  if (IsAudioTrack())
    Output = Mix->AddStereoOutputChannel(true);
  else
    Output = 0x0;

  // mixer output GUI
  if (type == eAudioTrack)
    {
      ChanGui = MixerPanel->AddChannel(Output, TrackOpt->Text->GetValue());
      ChanGui->SetOpt(TrackOpt);
      TrackOpt->SetChannelGui(ChanGui);
    }
  else
    ChanGui = NULL;


  // add itself to sequencer management
  Seq->AddTrack(this);
}

Track::~Track() 
{ 
  SeqMutex.Lock();

  // delete track's patterns
  if (GetTrackPattern())
    {
      vector<Pattern*>::iterator	it;

      for (it = TrackPattern->Patterns.begin();
	   it != TrackPattern->Patterns.end(); it++)
	{
	  if (GetType() == eAudioTrack)
	    delete (AudioPattern*)*it;
	  else if (GetType() == eAudioTrack)
	    delete (MidiPattern*)*it;
	}
      delete TrackPattern;
    } 

  // delete mixer related
  if (TrackOpt->ChanGui)
    MixerPanel->RemoveChannel(TrackOpt->ChanGui);
  if (Output)
    Mix->RemoveChannel(Output);

  // delete track's options
  if (TrackOpt)
    delete TrackOpt;
  SeqMutex.Unlock();
}

void		Track::Dump()
{
  cout << "===Track " << this << "dump begin===" << endl;
  cout << "TrackOpt Ptr : {" << TrackOpt << "}" << endl;
  cout << "TrackPattern Ptr : {" << TrackPattern << "}" << endl;
  cout << "Wave Ptr : {" << Wave << "}" << endl;
  cout << "Midi Ptr : {" << Midi << "}" << endl;
  cout << "Index : {" << Index << "}" << endl;
  cout << "Output Ptr : {" << Output << "}" << endl;
  cout << "Type : {" << Type << "}" << endl;
  cout << "ColourIndex : {" << ColourIndex << "}" << endl;
  cout << "===Track dump end===" << endl;
}

Track			Track::operator=(const Track& right)
{
  cerr << "WARNING : Soon, Wired will miserably fail" << endl;

  // Classes are copied, but they doesn't handle operator= correctly.
	if (this != &right)
	{
		TrackOpt = right.TrackOpt;
		TrackPattern = right.TrackPattern;
		Wave = right.Wave;
		Midi = right.Midi;
		Index = right.Index;
		Output = right.Output;
		Type = right.Type;
		ColourIndex = right.ColourIndex;
	}
	return *this;
}

AudioPattern					*Track::AddPattern(WaveFile *w, double pos)
{
  AudioPattern					*a;

#ifdef __DEBUG__
  printf("Track::AddPattern(%d, %f) -- START (AUDIO) Index=%d\n", w, pos, Index);
#endif
  a = new AudioPattern(this, pos, w, Index);
  a->SetDrawColour(PatternColours[ColourIndex]);

  SeqMutex.Lock();
  if (a->GetEndPosition() > Seq->EndPos)
    Seq->EndPos = a->GetEndPosition();
  SeqMutex.Unlock();

  a->Update();
#ifdef __DEBUG__
  printf("Track::AddPattern(%d, %f) -- OVER (AUDIO)\n", w, pos);
#endif
  return (a);
}

void						Track::DelPattern(Pattern *p)
{
#ifdef __DEBUG__
  printf("Track::DelPattern(%d) -- START (PATTERN)\n", p);
#endif
  SeqMutex.Lock();
  vector<Pattern *>::iterator		iter;
  
  for (iter = TrackPattern->Patterns.begin(); *iter != p; iter++)
    ;
  if (iter != TrackPattern->Patterns.end())
    TrackPattern->Patterns.erase(iter);
  SeqMutex.Unlock();
#ifdef __DEBUG__
  printf("Track::DelPattern(%d) -- OVER (PATTERN)\n", p);
#endif
}

void						Track::AddPattern(Pattern *p)
{
#ifdef __DEBUG__
  printf("Track::AddPattern(%d) -- START (PATTERN)\n", p);
#endif
  SeqMutex.Lock();
  TrackPattern->Patterns.push_back(p);
  SeqMutex.Unlock();
#ifdef __DEBUG__
  printf("Track::AddPattern(%d) -- OVER (PATTERN)\n", p);
#endif
}

MidiPattern					*Track::AddPattern(MidiTrack *t)
{
  MidiPattern					*a;

#ifdef __DEBUG__
  printf("Track::AddPattern(%d) -- START (MIDI)\n", t);
#endif
  a = new MidiPattern(this, 0, t, Index);
  a->SetDrawColour(PatternColours[ColourIndex]);
  SeqMutex.Lock();
  a->Update();
  if (a->GetEndPosition() > Seq->EndPos)
    Seq->EndPos = a->GetEndPosition();
  SeqMutex.Unlock();
#ifdef __DEBUG__
  printf("Track::AddPattern(%d) -- OVER (MIDI)\n", t);
#endif
  return (a);
}

void						Track::UpdateIndex(long trackindex)
{  
  vector<Pattern *>::iterator			k;

#ifdef __DEBUG__
  printf("Track::UpdateIndex(%d) -- START\n", trackindex);
#endif
  Index = trackindex;
  for (k = TrackPattern->Patterns.begin(); k != TrackPattern->Patterns.end(); k++)
    (*k)->Modify(-1, -1, trackindex);
#ifdef __DEBUG__
  printf("Track::UpdateIndex(%d) -- OVER\n", trackindex);
#endif
}

void						Track::RefreshFullTrack()
{
  vector<Pattern *>::iterator			p;
  
  TrackOpt->Refresh();
  for (p = TrackPattern->Patterns.begin(); p != TrackPattern->Patterns.end(); p++)
    (*p)->Update();
}  

void						Track::SetMidiPattern(MidiPattern* mp)
{
  Midi = mp;
}

void						Track::SetAudioPattern(AudioPattern* ap)
{
  Wave = ap;
}

// WiredDocument implementation
void						Track::Save()
{
  saveDocData(new SaveElement(wxT("Index"), (int)Index));
  saveDocData(new SaveElement(wxT("ColourIndex"), (int)ColourIndex));
}

void						Track::Load(SaveElementArray data)
{
  int						i;

  for (i = 0; i < data.GetCount(); i++)
    {
      if (data[i]->getKey() == wxT("Index"))
	Index = data[i]->getValueInt();
      else if (data[i]->getKey() == wxT("ColourIndex"))
	ColourIndex = data[i]->getValueInt();
    }
}
