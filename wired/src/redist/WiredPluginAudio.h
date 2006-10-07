#ifndef __WIREDPLUGINAUDIO_H__
#define __WIREDPLUGINAUDIO_H__


#include <wx/wxprec.h>
#ifndef WX_PRECOMP
   #include <wx/wx.h>
#endif

#include "WiredPluginStartInfo.h"
#include "WiredPluginEvent.h"

class WiredPluginStartInfo;
class WiredEvent;

////
// Current version of API
//
// this number increment only when methods or function of API are modified
//
#define WIRED_CURRENT_VERSION_API (2)


class		WiredPluginAudio
{
 private:
  WiredPluginStartInfo*	_StartInfo;

 public:
  WiredPluginAudio(WiredPluginStartInfo* parent) { StartInfo = parent; } ;
  ~WiredPluginAudio();

  /* Called when the host starts to play */
  virtual void	 Play() {}
  /* Called when the host stopped the sequencer */
  virtual void	 Stop() {}

  /* Called by the host when the signature changes */
  virtual void   SetSignature(int numerator, int denominator) {}

  /**
   * This is were you do your processing. 'input' is the data you have to process (or
   * not if you are making an instrument) and 'output' whre you should place the
   * processed or generated. 'input' and 'output' contains 'n' buffers (2 for stereo) which
   * contains 'sample_length' elements
   */
  typedef float**	WiredBuffer;
  virtual void	 Process(WiredBuffer& input, WiredBuffer& output, long sample_length)
    {
      long i;
      for (i = 0; i < sample_length; i++)
	{
	  output[0][i] = input[0][i];
	  output[1][i] = input[1][i];
	}
    }

  /* Is plugin supporting audio data to be sent to it ? */
  virtual bool	 IsAudio() = 0;
  /* Is plugin supporting MIDI data to be sent to it ? */
  virtual bool   IsMidi() = 0;

  // Time events
  /* Returns current BPM (tempo) */
  float		GetBpm();
  /* Returns the signature numerator */
  int		GetSigNumerator();
  /* Returns the signature denominator */
  int		GetSigDenominator();
  /* Returns the position in sample in the sequencer */
  unsigned long	GetCurAudioPos();
  /* Returns the number of samples per bar */
  double	GetSamplesPerMeasure();
  /* Returns the number of bars per sample */
  double	GetMeasuresPerSample();
  /* Returns the position in Bars of the sequencer */
  double	GetCurrentPos();

  /* Called when the plugin receives an event such as MIDI */
  virtual void	 ProcessEvent(WiredEvent &event) {}

};

#endif // __WIREDPLUGINAUDIO_H__
