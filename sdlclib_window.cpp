#include "sdlclib.h"
#include "sdlclib_window.h"
#include <cstring>

TSDLcWindow::TSDLcWindow() :
m_pWindow(nullptr),
m_pScreenSurface(nullptr),
m_pRenderer(nullptr),
m_bInitialized(false)
{}
void TSDLcWindow::Initialize()
{
	//Set resolution
	const char * pPlatform = SDL_GetPlatform();
	if (strcmp(pPlatform, "Android") == 0)
	{
		SDL_DisplayMode tDisplayInfo;
		int iDisplayErrorCheck = SDL_GetCurrentDisplayMode(0, &tDisplayInfo);
		if (iDisplayErrorCheck < 0)
		{
			SDLcAssert(false, "Failed to retreive display mode!");
		}

		m_iWindowWidth = tDisplayInfo.w;
		m_iWindowHeight = tDisplayInfo.h;
	}
	else
	{
		m_iWindowWidth = DEFAULT_RES_W;
		m_iWindowHeight = DEFAULT_RES_H;
	}

	//Create window
	m_pWindow = SDL_CreateWindow("SDL Custom Lib Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_iWindowWidth, m_iWindowHeight, SDL_WINDOW_SHOWN);
	if (m_pWindow == nullptr)
	{
		SDLcAssert(false, "Failed to create window!");
	}
	else
	{
		//Create renderer
		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (m_pRenderer == nullptr)
		{
			SDLcAssert(false, "Renderer could not be created!");
		}
		else
		{
			SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
		}


		m_bInitialized = true;
	}

}
