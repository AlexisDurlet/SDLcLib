#include "sdlclib.h"
#include "sdlclib_dbginfo.h"

Uint32 TSDLcDbgInfo::m_iSDlcAllocations = 0;
Uint32 TSDLcDbgInfo::m_iSDlcDeallocations = 0;
Uint32 TSDLcDbgInfo::m_iUserAllocations = 0;
Uint32 TSDLcDbgInfo::m_iUserDeallocations = 0;

TSDLcDbgInfo::TSDLcDbgInfo():
m_tTextDbg(nullptr)
{
}

TSDLcDbgInfo::~TSDLcDbgInfo()
{
	if (m_tTextDbg != nullptr)
	{
		delete m_tTextDbg;
		m_tTextDbg = nullptr;
	}
}

void TSDLcDbgInfo::Initialize()
{
	m_iTextureNumber = 0;
	m_iSpriteNumber = 0;
	m_iDrawSpriteNumber = 0;
	m_iTextSpriteNumber = 0;
	m_iAudioChunckNumber = 0;
	m_iActiveSoundNumber = 0;

	m_iFrameRate = 0;
	m_iUpdateDuration = 0;
	m_iRenderDuration = 0;

	m_iSDlcAllocations = 0;
	m_iSDlcDeallocations = 0;
	m_iSDlcDeltaAllocations = 0;

	m_iUserAllocations = 0;
	m_iUserDeallocations = 0;
	m_iUserDeltaAllocations = 0;

	m_tTextDbg = new TSDLcTextSprite;
	m_tTextDbg->LoadFont(DEFAULT_FONT, 11);
	m_tTextDbg->SetRenderMode(ESDLcTextRenderMode_Solid);
	m_eDisplayDbg = ESDLcDbgDisplay_Off;
}

void TSDLcDbgInfo::Update()
{
	if (TSDLcInput::GetInstance().IsKeyPressed(SDL_SCANCODE_LCTRL) && TSDLcInput::GetInstance().IsKeyJustPressed(SDL_SCANCODE_F12))
	{
		switch (m_eDisplayDbg)
		{
			case ESDLcDbgDisplay_On:

				m_eDisplayDbg = ESDLcDbgDisplay_Off;
				m_tTextDbg->ClearText();
				break;

			case ESDLcDbgDisplay_Off:

				m_eDisplayDbg = ESDLcDbgDisplay_On;
				break;
		}
	}

	m_iFrameRate = SDLcROUND(1.0f / (TSDLcTime::GetGlobalTime().GetTimeDeltaInSec()));

	m_iActiveSoundNumber = Mix_Playing(-1);

	m_iSDlcDeltaAllocations = m_iSDlcAllocations - m_iSDlcDeallocations;
	m_iUserDeltaAllocations = m_iUserAllocations - m_iUserDeallocations;

	switch (m_eDisplayDbg)
	{
		case ESDLcDbgDisplay_On:

			m_tTextDbg->SetText("%d fps Update %dms Render %dms\nTextures: %d, Sprite : %d, DrawSprite: %d, TextSprite: %d\nAudio Chunck: %d, Active Sounds: %d\nSDLcustom Memory allocation: %d, free: %d, delta: %d\nUser Memory allocation: %d, free: %d, delta: %d",
								m_iFrameRate, m_iUpdateDuration, m_iRenderDuration,
								m_iTextureNumber, m_iSpriteNumber, m_iDrawSpriteNumber, m_iTextSpriteNumber,
								m_iAudioChunckNumber, m_iActiveSoundNumber,
								m_iSDlcAllocations, m_iSDlcDeallocations, m_iSDlcDeltaAllocations,
								m_iUserAllocations, m_iUserDeallocations, m_iUserDeltaAllocations);

			break;

		case ESDLcDbgDisplay_Off:

			break;
	}
}

void TSDLcDbgInfo::Render()
{
	switch (m_eDisplayDbg)
	{
		case ESDLcDbgDisplay_On:

			m_tTextDbg->Render();

			break;

		case ESDLcDbgDisplay_Off:

			break;
	}
}
