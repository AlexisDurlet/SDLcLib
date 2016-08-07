#include "sdlclib.h"
#include "sdlclib_window.h"
#include "sdlclib_dbginfo.h"

TSDLcSprite::TSDLcSprite() 
{}
TSDLcSprite::~TSDLcSprite()
{
	Destroy();
}

void TSDLcSprite::Create(TSDLcTexture & pTexture)
{
	m_tTexture = pTexture;

	int w, h;
	SDL_QueryTexture(m_tTexture.GetTexture(), nullptr, nullptr, &w, &h);

	m_tSpriteRect.x = 0;
	m_tSpriteRect.y = 0;
	m_tSpriteRect.w = w;
	m_tSpriteRect.h = h;

	m_tCutoutRect.x = 0;
	m_tCutoutRect.y = 0;
	m_tCutoutRect.w = w;
	m_tCutoutRect.h = h;

	m_tPivot.x = 0;
	m_tPivot.y = 0;

	TSDLcDbgInfo::GetInstance().IncrementSpriteNb();
}

void TSDLcSprite::Destroy()
{
	m_tTexture.Destroy();
	TSDLcDbgInfo::GetInstance().DecrementSpriteNb();
}

void TSDLcSprite::SetPosition(const int iX, const int iY)
{
	m_tSpriteRect.x = iX - m_tPivot.x;
	m_tSpriteRect.y = iY - m_tPivot.y;
}

void TSDLcSprite::SetPosition(const float fXPercent, const float fYPercent)
{
	m_tSpriteRect.x = static_cast<int>(fXPercent * GetResWH().x - m_tPivot.x);
	m_tSpriteRect.y = static_cast<int>(fYPercent * GetResWH().y - m_tPivot.y);
}

void TSDLcSprite::SetCutout(const int iCutoutX, const int iCutoutY, const int iCutoutW, const int iCutoutH)
{
	m_tCutoutRect.x = iCutoutX;
	m_tCutoutRect.y = iCutoutY;
	m_tCutoutRect.w = iCutoutW;
	m_tCutoutRect.h = iCutoutH;
	m_tSpriteRect.w = iCutoutW;
	m_tSpriteRect.h = iCutoutH;
}

void TSDLcSprite::SetScale(const float fScaleX, const float fScaleY)
{
	m_fScaleX = fScaleX;
	m_fScaleY = fScaleY;

	m_tSpriteRect.w = SDLcROUND(m_tCutoutRect.w * m_fScaleX);
	m_tSpriteRect.h = SDLcROUND(m_tCutoutRect.h * m_fScaleY);
}

void TSDLcSprite::Render()
{
	SDLcAssert(m_tTexture.GetTexture() != nullptr, "Trying to render null texture sprite!");
	SDLcAssert(m_tTexture.GetTexture() != nullptr, "Trying to render null texture sprite!");
	SDL_SetTextureColorMod(m_tTexture.GetTexture(), m_iRColor, m_iGColor, m_iBColor);
	SDL_SetTextureAlphaMod(m_tTexture.GetTexture(), m_iAColor);

	SDL_RenderCopyEx(TSDLcWindow::GetInstance().GetRenderer(), m_tTexture.GetTexture(), &m_tCutoutRect, &m_tSpriteRect, m_fAngle, &m_tPivot, m_tFlipState);

	SDL_SetTextureColorMod(m_tTexture.GetTexture(), SDLcColorRGB_White);
	SDL_SetTextureAlphaMod(m_tTexture.GetTexture(), SDLcAlpha_Opaque);
}
