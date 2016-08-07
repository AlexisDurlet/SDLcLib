#include "sdlclib.h"

TSDLcAudioMusic::TSDLcAudioMusic() :
m_pCurrentMusic(nullptr),
m_pMusicsPath(nullptr)
{}

TSDLcAudioMusic::~TSDLcAudioMusic()
{
	if (m_pMusicsPath != nullptr)
	{
		delete[] m_pMusicsPath;
	}
}

void TSDLcAudioMusic::CheckMusicLoad(const int iIndex)
{
	SDLcAssert(iIndex < m_iMusicsNumber, "Music index out of range!");
	SDLcAssert(m_pMusicsPath != nullptr, "Music file path not initialized!");
}

void TSDLcAudioMusic::LoadMusic(const int iIndex)
{
	CheckMusicLoad(iIndex);

	if (m_pCurrentMusic != nullptr)
	{
		Mix_FreeMusic(m_pCurrentMusic);
	}

	m_pCurrentMusic = Mix_LoadMUS(m_pMusicsPath[iIndex]);
	SDLcAssert(m_pCurrentMusic != nullptr, "Failed to load music!");
}

void TSDLcAudioMusic::Initialize(const char ** pMusicsPath, const int iMusicsNumber)
{
	m_iMusicsNumber = iMusicsNumber;
	m_pMusicsPath = new const char *[m_iMusicsNumber];
	for (int i = 0; i < m_iMusicsNumber; i++)
	{
		m_pMusicsPath[i] = pMusicsPath[i];
	}
}

void TSDLcAudioMusic::Play(const int iIndex, const int iLoops)
{
	LoadMusic(iIndex);
	Mix_PlayMusic(m_pCurrentMusic, iLoops);
}

void TSDLcAudioMusic::Play(const int iIndex, const int iLoops, const int iFadeInTimeMs)
{
	LoadMusic(iIndex);
	Mix_FadeInMusic(m_pCurrentMusic, iLoops, iFadeInTimeMs);
}

void TSDLcAudioMusic::Pause()
{
	if (IsPlaying() && !IsPaused())
	{
		Mix_PauseMusic();
	}
}

void TSDLcAudioMusic::Stop()
{
	if (Mix_PlayingMusic())
	{
		Mix_HaltMusic();
	}
}

void TSDLcAudioMusic::Stop(const int iFadeOutTimeMs)
{
	if (Mix_PlayingMusic())
	{
		switch (GetFadingState())
		{
			case MIX_NO_FADING:
				Mix_FadeOutMusic(iFadeOutTimeMs);
				break;

			default:
				SDL_Log("Warning : music could not start to fade out, music is already in fading state");
				break;
		}
	}

}

void TSDLcAudioMusic::Resume()
{
	Mix_ResumeMusic();
}

void TSDLcAudioMusic::Rewind()
{
	Mix_RewindMusic();
}

void TSDLcAudioMusic::SetVolume(const int iVolume)
{
	switch (GetFadingState())
	{
		case MIX_NO_FADING:
			Mix_VolumeMusic(iVolume);
			break;

		default:
			SDL_Log("Warning : music volume could not be set, music is currently in fading state");
			break;
	}
}

int TSDLcAudioMusic::GetVolume()
{
	return Mix_VolumeMusic(-1);
}

Mix_Fading TSDLcAudioMusic::GetFadingState()
{
	return Mix_FadingMusic();
}

bool TSDLcAudioMusic::IsPlaying()
{
	return static_cast<bool>(Mix_PlayingMusic());
}

bool TSDLcAudioMusic::IsPaused()
{
	return static_cast<bool>(Mix_PausedMusic());
}

bool TSDLcAudioMusic::IsStopped()
{
	return  !IsPlaying();
}
