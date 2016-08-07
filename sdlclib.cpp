#include "sdlclib.h"
#include "sdlclib_memory_info.h"
#include "sdlclib_window.h"
#include "sdlclib_dbginfo.h"
#include <cstring>

#include "sdlclib_memory_info.cpp"
#include "sdlclib_window.cpp"
#include "sdlclib_dbginfo.cpp"
#include "sdlclib_math.cpp"
#include "sdlclib_texture.cpp"
#include "sdlclib_sprite_base.cpp"
#include "sdlclib_sprite.cpp"
#include "sdlclib_sprite_draw.cpp"
#include "sdlclib_sprite_text.cpp"
#include "sdlclib_input.cpp"
#include "sdlclib_time.cpp"
#include"sdlclib_audio_music.cpp"
#include "sdlclib_audio_chunck.cpp"
#include "sdlclib_audio_sound.cpp"

// ** CORE **

void InitializeSDL()
{
	SDLcAssert(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) >= 0, "Failed to initialize SDL!");
	SDLcAssert(TTF_Init() != -1, "Failed to initialize TTF!");
	SDLcAssert(Mix_OpenAudio(AUDIO_FREQUENCY, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_CHUNK_SIZE) >= 0, "Failed to initialize SDL_Mixer!");
	Mix_AllocateChannels(AUDIO_MIXING_CHANNELS_NUMBER);
}


void SDLcCallbacks(void(*pInitialize)(), void(*pUpdate)(), void(*pRender)(), void(*pFinalize)())
{
	InitializeSDL();

	bool bQuit = false;
	SDL_Event tEvent;

	if (!TSDLcWindow::GetInstance().GetInitialization())
	{
		TSDLcMemoryInfo::s_bSDLcInternalMem = true;
		TSDLcWindow::GetInstance().Initialize();
		TSDLcTime::GetGlobalTime().Initialize();
		TSDLcInput::GetInstance().Initialize();
		TSDLcDbgInfo::GetInstance().Initialize();
		TSDLcMemoryInfo::s_bSDLcInternalMem = false;
		pInitialize();
	}
	else
	{
		SDLcAssert(false, "Window already initialized!");
	}

	while (!bQuit)
	{
		TSDLcMemoryInfo::s_bSDLcInternalMem = true;
		TSDLcTime::GetGlobalTime().Update();
		TSDLcDbgInfo::GetInstance().Update();
		TSDLcInput::GetInstance().Update();
		TSDLcMemoryInfo::s_bSDLcInternalMem = false;
		pUpdate();
		TSDLcMemoryInfo::s_bSDLcInternalMem = true;
		TSDLcInput::GetInstance().LateUpdate();

		SDL_SetRenderDrawColor(TSDLcWindow::GetInstance().GetRenderer(), SDLcColorRGB_Black, SDLcAlpha_Opaque);
		SDL_RenderClear(TSDLcWindow::GetInstance().GetRenderer());
		TSDLcMemoryInfo::s_bSDLcInternalMem = false;
		pRender();
		TSDLcMemoryInfo::s_bSDLcInternalMem = true;
		TSDLcDbgInfo::GetInstance().Render();

		SDL_RenderPresent(TSDLcWindow::GetInstance().GetRenderer());
		TSDLcMemoryInfo::s_bSDLcInternalMem = false;

		while (SDL_PollEvent(&tEvent) != 0)
		{
			if (tEvent.type == SDL_QUIT)
			{
				bQuit = true;
				if (pFinalize != nullptr)
				{
					pFinalize();
					SDL_DestroyWindow(TSDLcWindow::GetInstance().GetWindow());
					TTF_Quit();
					IMG_Quit();
					Mix_Quit();
					SDL_Quit();
				}
			}
		}
	}
}

SDL_Point GetResWH()
{
	return SDL_Point{TSDLcWindow::GetInstance().GetWindowWidth(), TSDLcWindow::GetInstance().GetWindowHeight()};
}

// ** COLOR **

Uint32 SDLcSetRGBA(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
{
	Uint32 r32 = r << 24;
	Uint32 g32 = g << 16;
	Uint32 b32 = b << 8;
	Uint32 a32 = a;

	Uint32 iColor = r32 + g32 + b32 + a32;

	return iColor;
}

void SDLcGetRGBA(const Uint32 iColor, Uint8 * r, Uint8 * g, Uint8 * b, Uint8 * a)
{
	*r = (iColor & 0xFF000000) >> 24;
	*g = (iColor & 0x00FF0000) >> 16;
	*b = (iColor & 0x0000FF00) >> 8;
	*a = (iColor & 0x000000FF);
}

// ** DBG **

void SDLcAssert(const bool bExpectedTrue, const char * pMessage)
{
	if (!bExpectedTrue)
	{
		SDL_Log("%s\n", pMessage);

		const char * pSDLError = SDL_GetError();
		const char * IMGError = IMG_GetError();
		const char * MIXError = Mix_GetError();
		if (pSDLError != nullptr)
		{
			SDL_Log("SDL Error : %s\n", pSDLError);
		}
		if (IMGError != nullptr)
		{
			SDL_Log("SDL_IMG Error : %s\n", IMGError);
		}
		if (MIXError != nullptr)
		{
			SDL_Log("SDL_Mixer Error : %s\n", MIXError);
		}


		SDL_assert(bExpectedTrue);
	}
}
