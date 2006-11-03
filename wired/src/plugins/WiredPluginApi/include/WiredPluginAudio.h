#ifndef __WIREDPLUGINAUDIO_H__
#define __WIREDPLUGINAUDIO_H__


#include <wx/wxprec.h>
#ifndef WX_PRECOMP
   #include <wx/wx.h>
#endif

//#include "WiredPluginStartInfo.h"


class WiredPluginStartInfo;
class WiredMidiEvent;

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
  WiredPluginAudio(WiredPluginStartInfo* parent) { _StartInfo = parent; };
  ~WiredPluginAudio();

  /* Called when the host starts to play */
  virtual void	 Play() {};
  /* Called when the host stopped the sequencer */
  virtual void	 Stop() {};

  /* Called by the host when the buffersize changes */
  virtual void   SetBufferSize(long size) {};

  /* Called by the host when the samplingrate changes */
  virtual void   SetSamplingRate(double rate) {};

  /* Called by the host when the signature changes */
  virtual void   SetSignature(int numerator, int denominator) {};

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
    };


  int	GetLastMidiType();
  int	GetLastMidiController();
  int	GetLastMidiValue();


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
  virtual void	 ProcessEvent(WiredMidiEvent& event) {};

  /* Returns the number of bars per sample */
  double	GetBarsPerSample();


};

#endif // __WIREDPLUGINAUDIO_H__
