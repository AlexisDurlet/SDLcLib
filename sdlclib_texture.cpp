#include "sdlclib.h"
#include "sdlclib_window.h"
#include "sdlclib_dbginfo.h"

TSDLcTexture::TSDLcTexture() :
m_pTexture(nullptr)
{}
TSDLcTexture::~TSDLcTexture()
{
	Destroy();
}
void TSDLcTexture::Load(const char * pFileName)
{
	SDLcAssert(m_pTexture == nullptr, "Trying to load image on an already created texture!");
	SDL_Surface * pLoadedSurface = IMG_Load(pFileName);
	if (pLoadedSurface == nullptr)
	{
		SDLcAssert(false, "Failed to load image!");
	}
	else
	{
		Load(pLoadedSurface);

		SDL_FreeSurface(pLoadedSurface);
	}

	TSDLcDbgInfo::GetInstance().IncrementTextureNb();
}

void TSDLcTexture::Load(SDL_Surface * pSurface)
{
	SDLcAssert(m_pTexture == nullptr, "Trying to load surface on an already created texture!");
	m_pTexture = SDL_CreateTextureFromSurface(TSDLcWindow::GetInstance().GetRenderer(), pSurface);
	SDLcAssert(m_pTexture != nullptr, "Failed to create texture!");

	SDL_SetTextureBlendMode(m_pTexture, SDL_BLENDMODE_BLEND);

	TSDLcDbgInfo::GetInstance().IncrementTextureNb();
}

void TSDLcTexture::LoadCombine(const int iOutPutW, const int iOutPutH, const int iSurfacesNumber, SDL_Surface ** pSurfaces, SDL_Rect * pCopyOffsets, SDL_Rect * pPasteOffsets)
{
	SDL_Surface * pCombinedSurface = SDL_CreateRGBSurface(0, iOutPutW, iOutPutH, 32, 0, 0 ,0, 0);

	for (int i = 0; i < iSurfacesNumber; i++)
	{
		int iError = SDL_BlitSurface(pSurfaces[i], &pCopyOffsets[i], pCombinedSurface, &pPasteOffsets[i]);

		if (iError != 0)
		{
			SDLcAssert(false, "Failed to blitt surface!");
		}
	}

	Load(pCombinedSurface);
	SDL_FreeSurface(pCombinedSurface);
}

void TSDLcTexture::Destroy()
{
	if (m_pTexture != nullptr)
	{
		SDL_DestroyTexture(m_pTexture);
		m_pTexture = nullptr;

		TSDLcDbgInfo::GetInstance().DecrementTextureNb();
	}
}
