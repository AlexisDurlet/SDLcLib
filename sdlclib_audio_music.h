#ifndef SDLCLIB_AUDIO_MUSIC_H_INCLUDED
#define SDLCLIB_AUDIO_MUSIC_H_INCLUDED

class TSDLcAudioMusic
{
	private:

		TSDLcAudioMusic();
		~TSDLcAudioMusic();

		Mix_Music * m_pCurrentMusic;

		const char ** m_pMusicsPath;
		int m_iMusicsNumber;
		int m_iCurrentIndex;
		int m_iCurrentVolume;

		void CheckMusicLoad(const int iIndex);
		void LoadMusic(const int iIndex);

	public:

		static TSDLcAudioMusic & GetInstance()
		{
			static TSDLcAudioMusic * pMusic;
			if (pMusic == nullptr)
			{
				pMusic = new TSDLcAudioMusic;
			}
			return *pMusic;
		}

		void Initialize(const char ** pMusicsPath, const int iMusicsNumber);

		void Play(const int iIndex, const int iLoops);//iLoops -1 for infinite
		void Play(const int iIndex, const int iLoops, const int iFadeInTimeMs);
		void Pause();//pause music, conserve current fading at resume
		void Stop(); //stop music, disregard current fading at resume
		void Stop(const int iFadeOutTimeMs);
		void Resume();
		void Rewind();

		void SetVolume(const int iVolume);
		int GetVolume();

		Mix_Fading GetFadingState();
		bool IsPlaying();
		bool IsPaused();
		bool IsStopped();

};


#endif
