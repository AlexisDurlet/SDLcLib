#include "sdlclib.h"
#include "sdlclib_window.h"
#include "sdlclib_dbginfo.h"
#include <cstdarg>
#include<cstring>
#include <vector>

TSDLcTextSprite::TSDLcTextSprite():
m_pFont(nullptr),
m_pText(nullptr),
m_tSpriteRect({0,0,0,0}),
m_eTextRenderMode(ESDLcTextRenderMode_Solid),
m_iLinesNumber(0),
m_pLinesTextRect(nullptr),
m_bTextChanged(false)
{

}

TSDLcTextSprite::~TSDLcTextSprite()
{
	Destroy();
}

void TSDLcTextSprite::LoadFont(const char * pFontFile, const int iFontPtSize)
{
	SDLcAssert(m_pFont == nullptr, "Trying to load font on an already created TextSprite!");
	m_iFontPtSize = iFontPtSize;
	m_pFont = TTF_OpenFont(pFontFile, m_iFontPtSize);
	SDLcAssert(m_pFont != nullptr, "Failed to load font!");

	m_iFontLineSpacing = TTF_FontLineSkip(m_pFont);
	TSDLcDbgInfo::GetInstance().IncrementTextSpriteNb();
}

void TSDLcTextSprite::SetText(const char * pText, ...)
{
	if (m_pText != nullptr)
	{
		for (int i = 0; i < m_iLinesNumber; i++)
		{
			delete[]m_pText[i];
			m_pText[i] = nullptr;
		}

		delete[]m_pText;
		m_pText = nullptr;
		delete[]m_pLinesTextRect;
		m_pLinesTextRect = nullptr;

		m_tSpriteRect = { 0, 0, 0, 0 };
		m_iLinesNumber = 0;
	}
	m_bTextChanged = true;
	va_list args;
	va_start(args, pText);

	char * pTextVsPrinted = new char[MAX_TXTSPRITE_PRINT_CHAR];
	vsprintf(pTextVsPrinted, pText, args);

	const char * pNewLine = nullptr;
	const char * pLinebegin = &pTextVsPrinted[0];
	std::vector<int> tLinesSize;

	do
	{
		m_iLinesNumber++;
		pNewLine = strchr(pLinebegin, '\n');
		if (pNewLine != nullptr)
		{
			int iNewLineSize = pNewLine - pLinebegin;
			pLinebegin = pNewLine + 1;
			tLinesSize.push_back(iNewLineSize);
		}
		else
		{
			int iNewLineSize = &pTextVsPrinted[strlen(pTextVsPrinted)] - pLinebegin;
			tLinesSize.push_back(iNewLineSize);
		}

	} while (pNewLine != nullptr);

	m_pText = new char*[m_iLinesNumber];
	m_pLinesTextRect = new SDL_Rect[m_iLinesNumber];

	int iIndex = 0;
	for (int i = 0; i < m_iLinesNumber; i++)
	{
		m_pText[i] = new char[tLinesSize[i] + 1];
		strncpy(m_pText[i], &pTextVsPrinted[iIndex], tLinesSize[i]);
		m_pText[i][tLinesSize[i]] = '\0';

		m_pLinesTextRect[i].x = 0;
		m_pLinesTextRect[i].y = 0;
		TTF_SizeText(m_pFont, m_pText[i], &m_pLinesTextRect[i].w, &m_pLinesTextRect[i].h);
		m_tSpriteRect.w < m_pLinesTextRect[i].w ? m_tSpriteRect.w = m_pLinesTextRect[i].w : m_tSpriteRect.w;
		m_tSpriteRect.h += m_pLinesTextRect[i].h;

		iIndex += tLinesSize[i] + 1;
	}

	delete[]pTextVsPrinted;
	va_end(args);
}

void TSDLcTextSprite::ClearText()
{
	if (m_pText != nullptr)
	{
		for (int i = 0; i < m_iLinesNumber; i++)
		{
			delete[]m_pText[i];
			m_pText[i] = nullptr;
		}
		delete[]m_pText;
		m_pText = nullptr;
		if (m_pLinesTextRect != nullptr)
		{
			delete[]m_pLinesTextRect;
			m_pLinesTextRect = nullptr;
		}

		m_tTexture.Destroy();

		m_tSpriteRect = { 0, 0, 0, 0 };
		m_iLinesNumber = 0;
	}
}

void TSDLcTextSprite::Destroy()
{
	if (m_pFont != nullptr)
	{
		TTF_CloseFont(m_pFont);
		m_pFont = nullptr;

		TSDLcDbgInfo::GetInstance().DecrementTextSpriteNb();
	}
	if (m_pText != nullptr)
	{
		for (int i = 0; i < m_iLinesNumber; i++)
		{
			delete[]m_pText[i];
			m_pText[i] = nullptr;
		}
		delete[]m_pText;
		m_pText = nullptr;
	}

	if (m_pLinesTextRect != nullptr)
	{
		delete[]m_pLinesTextRect;
		m_pLinesTextRect = nullptr;
	}

	m_tTexture.Destroy();

	m_tSpriteRect = { 0, 0, 0, 0 };
	m_iLinesNumber = 0;
}

void TSDLcTextSprite::SetPosition(const int iX, const int iY)
{
	m_tSpriteRect.x = iX - m_tPivot.x;
	m_tSpriteRect.y = iY - m_tPivot.y;
}
void TSDLcTextSprite::SetPosition(const float fXPercent, const float fYPercent)
{
	m_tSpriteRect.x = static_cast<int>(fXPercent * GetResWH().x - m_tPivot.x);
	m_tSpriteRect.y = static_cast<int>(fYPercent * GetResWH().y - m_tPivot.y);
}

void TSDLcTextSprite::Render()
{
	SDLcAssert(m_pFont != nullptr && m_pText != nullptr, "Trying to render uninitialized text");

	if (m_bTextChanged)
	{
		m_bTextChanged = false;

		SDL_Color tColor = { m_iRColor, m_iGColor, m_iBColor, m_iAColor };
		SDL_Surface ** pTextSurface = new SDL_Surface*[m_iLinesNumber];
		SDL_Rect * pPasteOffset = new SDL_Rect[m_iLinesNumber];

		for (int i = 0; i < m_iLinesNumber; i++)
		{
			pPasteOffset[i] = m_pLinesTextRect[i];
			pPasteOffset[i].y = i * m_iFontLineSpacing;

			switch (m_eTextRenderMode)
			{
				case ESDLcTextRenderMode_Solid:

					pTextSurface[i] = TTF_RenderUTF8_Solid(m_pFont, m_pText[i], tColor);
					SDLcAssert(pTextSurface[i] != nullptr, "Failed to render text!");
					break;

				case ESDLcTextRenderMode_Blended:

					pTextSurface[i] = TTF_RenderUTF8_Blended(m_pFont, m_pText[i], tColor);
					SDLcAssert(pTextSurface[i] != nullptr, "Failed to render text!");
					break;
			}
		}

		m_tTexture.Destroy();
		m_tTexture.LoadCombine(m_tSpriteRect.w, m_tSpriteRect.h, m_iLinesNumber, pTextSurface, m_pLinesTextRect, pPasteOffset);

		for (int i = 0; i < m_iLinesNumber; i++)
		{
			SDL_FreeSurface(pTextSurface[i]);
		}
		delete[] pTextSurface;
		pTextSurface = nullptr;
		delete[]pPasteOffset;
		pPasteOffset = nullptr;
	}

	SDL_SetTextureColorMod(m_tTexture.GetTexture(), m_iRColor, m_iGColor, m_iBColor);
	SDL_SetTextureAlphaMod(m_tTexture.GetTexture(), m_iAColor);

	SDL_RenderCopyEx(TSDLcWindow::GetInstance().GetRenderer(), m_tTexture.GetTexture(), nullptr, &m_tSpriteRect, m_fAngle, &m_tPivot, m_tFlipState);

	SDL_SetTextureColorMod(m_tTexture.GetTexture(), SDLcColorRGB_White);
	SDL_SetTextureAlphaMod(m_tTexture.GetTexture(), SDLcAlpha_Opaque);
}

