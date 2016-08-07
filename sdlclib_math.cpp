#include "sdlclib.h"
#include <math.h>

float SDLcDegToRad(const float fAngle)
{
	return (static_cast<float>(M_PI) * fAngle) / 180.0f;
}

void SDLcRotate2D(SDL_Point & tPoint, const float fAngle)
{
	float fRadAngle = SDLcDegToRad(fAngle);
	float fSin = sin(fRadAngle);
	float fCos = cos(fRadAngle);
	SDL_Point tPrevPoint = tPoint;

	tPoint.x = SDLcROUND(tPrevPoint.x * fCos - tPrevPoint.y * fSin);
	tPoint.y = SDLcROUND(tPrevPoint.x * fSin + tPrevPoint.y * fCos);
}
