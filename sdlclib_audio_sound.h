#ifndef SDLCLIB_AUDIO_SOUND_H_INCLUDED
#define SDLCLIB_AUDIO_SOUND_H_INCLUDED

class TSDLcAudioSound
{
	private:
		static TSDLcAudioSound * m_pChannels[AUDIO_MIXING_CHANNELS_NUMBER];

		TSDLcAudioChunck * m_pSound;
		int m_iCurrentChannel;
		bool m_bActive;

		void PlayCheck();
		void ChannelCheck();

	public:

		TSDLcAudioSound();
		~TSDLcAudioSound();

		void Create(TSDLcAudioChunck * pSound);
		void Play(const int iLoops = 0);
		void Play(const int iLoops, const int iFadeIn);
		void Pause();
		void Resume();
		void Stop();
		void Stop(const int iFadeout);
		void Destroy();  

		bool IsActive() const
		{
			return m_bActive;
		}
		void SetInactive()
		{
			m_bActive = false;
		}
		static TSDLcAudioSound ** GetChannels()
		{
			return m_pChannels;
		}
};


#endif
