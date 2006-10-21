// Copyright (C) 2004-2006 by Wired Team
// Under the GNU General Public License Version 2, June 1991

#ifndef __WIREDAUDIOFILE_H__
#define __WIREDAUDIOFILE_H__


/////////////////////////////////////////////
//  class WiredAudioFile
/////////////////////////////////////////////

/**
 * Manages wave files.
 * With this, it's possible to easily manipulate wave file like read, write...
 */
class WiredAudioFile
{
 public:
  virtual WaveFile() = 0;
  virtual ~WaveFile() = 0;

  /**
   * Dumps audio file's informations.
   */
  void	DumpAudio();

  /**
   * Duplicates the static WaveFile object.
   * \return returns a new instantiated WaveFile object.
   */
  WaveFile *Clone()
    {
      cout << "ERROR ERROR Wired will fail miserably" << endl;

      WaveFile		*aNewWaveFile;

      aNewWaveFile = new WaveFile(*this);
      if (LoadedInMem)
	{
	  aNewWaveFile->Data = new float *[sfinfo.channels];
	  for (int channelsCompt = 0; channelsCompt < sfinfo.channels; channelsCompt++)
	    {
	      aNewWaveFile->Data[channelsCompt] = new float[NumberOfFrames];

	      for (int framesCompt = 0; framesCompt < NumberOfFrames; framesCompt++)
		aNewWaveFile->Data[channelsCompt][framesCompt] = Data[channelsCompt][framesCompt];
	    }
	  return aNewWaveFile;
	}
    }

  /**
   * Gets the channels' number.
   * \return returns a long. It's the channels' number.
   */
  virtual long	GetNumberOfChannels() = 0;

  /**
   * Gets the frames' number.
   * \return returns a long. It's the frames' number.
   */
  virtual long	GetNumberOfFrames() = 0;

  /**
   * Sets a new cursor's position.
   * \param position an int. the new position.
   * By default it's setted to 0.
   * \return returns an int. It's the current position.
   */
  virtual int	SetCurrentPosition (int position = 0) = 0;

  /**
   * Sets a new frames' number.
   * \param frames_nbr an int. the new frames' number.
   */
  virtual void	SetNumberOfFrames( int frames_nbr ) = 0;

  /**
   * Gets the file's samplerate.
   * \return returns an int, the file's samplerate.
   */
  virtual int	GetSampleRate() const = 0;

  /**
   * Reads the file and get the content in the WiredBuffer buffer.
   * \param
   * \return returns an long, the read size, or < 0 if failed.
   */
  virtual long	Read(WiredBuffer& buffer, long size) = 0;

  /**
   * Sets the file's pitch.
   * \param p a float, the new pitch.
   */
  virtual void	SetPitch(float p) = 0;

  /**
   * Sets the invert status.
   * \param inv a bool, a new invert status.
   */
  virtual void	SetInvert(bool inv) = 0;

  /**
   * Return opened filename.
   */
  virtual wxString	GetFilename() = 0;

  /**
   * Return extension of opened filename (the last word after the last dot)
   */
  virtual wxString	GetExtension() = 0;
};

#endif // __WIREDAUDIOFILE_H__
