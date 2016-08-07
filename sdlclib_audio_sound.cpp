#include "sdlclib.h"


TSDLcAudioSound * TSDLcAudioSound::m_pChannels[];

TSDLcAudioSound::TSDLcAudioSound() :
m_pSound(nullptr),
m_iCurrentChannel(-2),
m_bActive(false)
{}

TSDLcAudioSound::~TSDLcAudioSound()
{
	Destroy();
}

void TSDLcAudioSound::PlayCheck()
{
	SDLcAssert(m_pSound != nullptr, "trying to play uninitialized sound!");
}

void TSDLcAudioSound::ChannelCheck()
{
	SDLcAssert(m_iCurrentChannel >= 0, "trying to manipulate uninitialized or unplayed sound!");
}


void TSDLcAudioSound::Create(TSDLcAudioChunck * pSound)
{
	m_pSound = pSound;
}

void FinishedCallBack(int iChannel)
{
	if (iChannel >= 0)
	{
		TSDLcAudioSound ** pChanels = TSDLcAudioSound::GetChannels();
		pChanels[iChannel]->SetInactive();
		pChanels[iChannel] = nullptr;
	}
}

void TSDLcAudioSound::Play(const int iLoops)
{
	PlayCheck();
	if (!m_bActive)
	{
		m_iCurrentChannel = Mix_PlayChannel(-1, m_pSound->GetChunck(), iLoops);
	}
	else
	{
		Mix_HaltChannel(m_iCurrentChannel);
		Mix_PlayChannel(m_iCurrentChannel, m_pSound->GetChunck(), iLoops);
	}

	if (m_iCurrentChannel >= 0)
	{
		m_pChannels[m_iCurrentChannel] = this;

		m_bActive = true;
		Mix_ChannelFinished(&FinishedCallBack);
	}
	else
	{
		SDL_Log("WARNING : Sound couldn't be played, no more channels available");
	}
}

void TSDLcAudioSound::Play(const int iLoops, const int iFadeIn)
{
	PlayCheck();
	if (!m_bActive)
	{
		Mix_FadeInChannel(-1, m_pSound->GetChunck(), iLoops, iFadeIn);
	}
	else
	{
		Mix_HaltChannel(m_iCurrentChannel);
		Mix_FadeInChannel(-1, m_pSound->GetChunck(), iLoops, iFadeIn);
	}

	if (m_iCurrentChannel >= 0)
	{
		m_pChannels[m_iCurrentChannel] = this;

		m_bActive = true;
		Mix_ChannelFinished(&FinishedCallBack);
	}
	else
	{
		SDL_Log("WARNING : Sound couldn't be played, no more channels available");
	}
}

void TSDLcAudioSound::Pause()
{
	ChannelCheck();
	if (m_bActive)
	{
		Mix_Pause(m_iCurrentChannel);
	}
}

void TSDLcAudioSound::Resume()
{
	ChannelCheck();
	if (m_bActive)
	{
		Mix_Resume(m_iCurrentChannel);
	}
}

void TSDLcAudioSound::Stop()
{
	ChannelCheck();
	if (m_bActive)
	{
		Mix_HaltChannel(m_iCurrentChannel);
	}
}

void TSDLcAudioSound::Stop(const int iFadeout)
{
	ChannelCheck();
	if (m_bActive)
	{
		Mix_FadeOutChannel(m_iCurrentChannel, iFadeout);
	}
}

void TSDLcAudioSound::Destroy()
{
	m_pSound = nullptr;
	m_iCurrentChannel = -2;
}

