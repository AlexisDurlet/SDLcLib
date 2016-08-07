#include "sdlclib.h"
#include "sdlclib_dbginfo.h"

TSDLcAudioChunck::~TSDLcAudioChunck()
{
	Destroy();
}

void TSDLcAudioChunck::Load(const char * pFile)
{
	SDLcAssert(m_pChunck == nullptr, "trying to load file on already loaded chunck!");
	m_pChunck = Mix_LoadWAV(pFile);
	SDLcAssert(m_pChunck != nullptr, "unable to load audio file!");
	TSDLcDbgInfo::GetInstance().IncrementAudioChunckNb();
}

void TSDLcAudioChunck::Destroy()
{
	if (m_pChunck != nullptr)
	{
		Mix_FreeChunk(m_pChunck);
		m_pChunck = nullptr;
		TSDLcDbgInfo::GetInstance().DecrementAudioChunckNb();
	}
}

