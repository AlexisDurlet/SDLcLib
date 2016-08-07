#include "sdlclib.h"

void TSDLcTime::Initialize()
{
	m_iTimeNow = SDL_GetTicks();
	m_iTimeBegin = m_iTimeNow;
	m_iTimePrevious = m_iTimeNow;
	m_iTimeFromBegin = 0;
}
void TSDLcTime::Update()
{
	m_iTimeNow = SDL_GetTicks();
	m_iTimeFromBegin = m_iTimeNow - m_iTimeBegin;
	m_iTimeDelta = m_iTimeNow - m_iTimePrevious;
	m_iTimePrevious = m_iTimeNow;
}
