#include "sdlclib.h"

TSDLcInput::TSDLcInput() :
m_pPreviousKeyboardState(nullptr),
m_pCurrentKeyboardState(nullptr)
{}
TSDLcInput::~TSDLcInput()
{
	if (m_pPreviousKeyboardState != nullptr)
	{
		delete m_pPreviousKeyboardState;
	}

	if (m_pCurrentKeyboardState != nullptr)
	{
		delete m_pCurrentKeyboardState;
	}
}
void TSDLcInput::Initialize()
{
	m_iCurrentMouseState = SDL_GetMouseState(&m_iCurrentMousePosX, &m_iCurrentMousePosY);
	m_iPreviousMouseState = m_iCurrentMouseState;
	m_iPreviousMousePosX = m_iCurrentMousePosX;
	m_iPreviousMousePosY = m_iCurrentMousePosY;

	m_pCurrentKeyboardState = SDL_GetKeyboardState(&m_iKeyArraySize);
	m_pPreviousKeyboardState = new Uint8[m_iKeyArraySize];
}
void TSDLcInput::Update()
{
	SDL_PumpEvents();
	m_iCurrentMouseState = SDL_GetMouseState(&m_iCurrentMousePosX, &m_iCurrentMousePosY);
}
void TSDLcInput::LateUpdate()
{
	m_iPreviousMouseState = m_iCurrentMouseState;

	for (int i = 0; i < m_iKeyArraySize; i++)
	{
		m_pPreviousKeyboardState[i] = m_pCurrentKeyboardState[i];
	}
}
bool TSDLcInput::IsMouseButtonJustPressed(const ESDLcMouseButton eButton)
{
	return (m_iCurrentMouseState & SDL_BUTTON(eButton)) && !(m_iPreviousMouseState & SDL_BUTTON(eButton));
}
bool TSDLcInput::IsMouseButtonPressed(const ESDLcMouseButton eButton)
{
	return (m_iCurrentMouseState & SDL_BUTTON(eButton)) == 1;
}
bool TSDLcInput::IsMouseButtonJustRealeased(const ESDLcMouseButton eButton)
{
	return !(m_iCurrentMouseState & SDL_BUTTON(eButton)) && (m_iPreviousMouseState & SDL_BUTTON(eButton));
}
bool TSDLcInput::IsKeyJustPressed(const SDL_Scancode tKey)
{
	return m_pCurrentKeyboardState[tKey] == 1 && m_pPreviousKeyboardState[tKey] == 0;
}
bool TSDLcInput::IsKeyPressed(const SDL_Scancode tKey)
{
	return m_pCurrentKeyboardState[tKey] == 1;
}
bool TSDLcInput::IsKeyJustRealeased(const SDL_Scancode tKey)
{
	return m_pCurrentKeyboardState[tKey] == 0 && m_pPreviousKeyboardState[tKey] == 1;
}
