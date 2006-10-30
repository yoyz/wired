#include "WiredPluginAudio.h"

#include "WiredCorePlugins.h"

WiredPluginAudio::~WiredPluginAudio()
{

}

// Time events
/* Returns current BPM (tempo) */
float		WiredPluginAudio::GetBpm()
{
  return _StartInfo->GetCore()->GetBpm();
}

/* Returns the signature numerator */
int		WiredPluginAudio::GetSigNumerator()
{
  return _StartInfo->GetCore()->GetSigNumerator();
}

/* Returns the signature denominator */
int		WiredPluginAudio::GetSigDenominator()
{
  return _StartInfo->GetCore()->GetSigDenominator();
}

/* Returns the position in sample in the sequencer */
unsigned long	WiredPluginAudio::GetCurAudioPos()
{
  return _StartInfo->GetCore()->GetCurAudioPos();
}

/* Returns the number of samples per bar */
double		WiredPluginAudio::GetSamplesPerMeasure()
{
  return _StartInfo->GetCore()->GetSamplesPerMeasure();
}

/* Returns the number of bars per sample */
double		WiredPluginAudio::GetBarsPerSample()
{
  return _StartInfo->GetCore()->GetMeasurePerSample();
}

/* Returns the position in Bars of the sequencer */
double		WiredPluginAudio::GetCurrentPos()
{
  return _StartInfo->GetCore()->GetCurrentPos();
}

int		WiredPluginAudio::GetLastMidiType()
{
  return _StartInfo->GetCore()->GetLastMidiType();
}

int		WiredPluginAudio::GetLastMidiController()
{
  return  _StartInfo->GetCore()->GetLastMidiController();
}

int		WiredPluginAudio::GetLastMidiValue()
{
  return _StartInfo->GetCore()->GetLastMidiValue();
}
