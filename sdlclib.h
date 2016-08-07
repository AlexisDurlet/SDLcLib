#ifndef SDLCLIB_H_INCLUDED
#define SDLCLIB_H_INCLUDED

// ** SDL and subsystems **
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#pragma warning(disable:4996)//vsprintf_s not recognized by android compiler, need to use unsafe version vsprintf
#pragma warning(disable:4800) //conversion from int to bool nedded because test methods from SDL_mixer return 0 or 1 integer

// ** TYPES **
	//singleton
class TSDLcInput;
class TSDLcAudioMusic;
	//instanciable
class TSDLcTime;
class TSDLcTexture;
class TSDLcBaseSprite;
class TSDLcSprite;
class TSDLcDrawSprite;
class TSDLcTextSprite;
class TSDLcAudioChunck;
class TSDLcAudioSound;

// ** CORE **
void SDLcCallbacks(void(*pInitialize)(), void(*pUpdate)(), void(*pRender)(), void(*pFinalize)() = 0);
SDL_Point GetResWH();

// ** DBG **
void SDLcAssert(const bool bExpectedTrue, const char * pMessage);

// ** COLORS **
#define SDLcColorRGB_White 255, 255, 255  
#define SDLcColorRGB_Black 0, 0, 0  
#define SDLcColorRGB_Red   255, 0, 0  
#define SDLcColorRGB_Green 0, 255, 0  
#define SDLcColorRGB_Blue  0, 0, 255 
#define SDLcAlpha_Opaque 255
#define SDLcAlpha_Transparent 0

Uint32 SDLcSetRGBA(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a);
void SDLcGetRGBA(const Uint32 iColor, Uint8 * r, Uint8 * g, Uint8 * b, Uint8 * a);

// ** CONST **
const int DEFAULT_RES_W = 480;
const int DEFAULT_RES_H = 320;
static const char * DEFAULT_FONT = "sdlclib_data/cour.ttf";
const int MAX_TXTSPRITE_PRINT_CHAR = 512;
const int AUDIO_FREQUENCY = 44100;
const int AUDIO_FORMAT = MIX_DEFAULT_FORMAT;
const int AUDIO_CHANNELS = 2;
const int AUDIO_CHUNK_SIZE = 4096;
const int AUDIO_MIXING_CHANNELS_NUMBER = 16;

// ** MACROS **
#define SDLcROUND(x) static_cast<int>(round(x))

// ** INCLUDES **
#include "sdlclib_math.h"
#include "sdlclib_texture.h"
#include "sdlclib_sprite_base.h"
#include "sdlclib_sprite.h"
#include "sdlclib_sprite_draw.h"
#include "sdlclib_sprite_text.h"
#include "sdlclib_input.h"
#include "sdlclib_time.h"
#include"sdlclib_audio_music.h"
#include "sdlclib_audio_chunck.h"
#include "sdlclib_audio_sound.h"


#endif
