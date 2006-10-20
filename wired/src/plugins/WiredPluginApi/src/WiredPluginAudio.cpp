#include "WiredPluginAudio.h"


//WiredPluginAudio::WiredPluginAudio(WiredPluginStartInfo* parent) { StartInfo = parent; };

WiredPluginAudio::~WiredPluginAudio()
{

}

// Time events
/* Returns current BPM (tempo) */
float		WiredPluginAudio::GetBpm()
{
  return StartInfo->GetCore()->GetBpm();
}

/* Returns the signature numerator */
int		WiredPluginAudio::GetSigNumerator()
{
  return StartInfo->GetCore()->GetSigNumerator();
}

/* Returns the signature denominator */
int		WiredPluginAudio::GetSigDenominator()
{
  return StartInfo->GetCore()->GetSigDenominator();
}

/* Returns the position in sample in the sequencer */
unsigned long	WiredPluginAudio::GetCurAudioPos()
{
  return StartInfo->GetCore()->GetCurAudioPos();
}

/* Returns the number of samples per bar */
double		WiredPluginAudio::GetSamplesPerMeasure()
{
  return StartInfo->GetCore()->GetSamplesPerMeasure();
}

/* Returns the number of bars per sample */
double		WiredPluginAudio::GetBarsPerSample()
{
  return StartInfo->GetCore()->GetMeasuresPerSample();
}

/* Returns the position in Bars of the sequencer */
double		WiredPluginAudio::GetCurrentPos()
{
  return StartInfo->GetCore()->GetCurrentPos();
}

int		WiredPluginAudio::GetLastMidiType()
{
  return   _StartInfo->GetCore()->GetLastMidiType();
}

int		WiredPluginAudio::GetLastMidiController()
{
  return   _StartInfo->GetCore()->GetLastMidiController();
}

int		WiredPluginAudio::GetLastMidiValue()
{
  return _StartInfo->GetCore()->GetLastMidiValue();
}
