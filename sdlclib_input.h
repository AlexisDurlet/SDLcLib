#ifndef SDLCLIB_INPUT_H_INCLUDED
#define	SDLCLIB_INPUT_H_INCLUDED

enum ESDLcMouseButton
{
	ESDLcMouseButton_LEFT = 1,
	ESDLcMouseButton_MIDDLE,
	ESDLcMouseButton_RIGHT,
	ESDLcMouseButton_X1,
	ESDLcMouseButton_X2
};

class TSDLcInput
{
	private:
	
		Uint32 m_iPreviousMouseState;
		Uint32 m_iCurrentMouseState;
	
		int m_iPreviousMousePosX;
		int m_iPreviousMousePosY;
		int m_iCurrentMousePosX;
		int m_iCurrentMousePosY;
	
		Uint8 * m_pPreviousKeyboardState;
		const Uint8 * m_pCurrentKeyboardState;
		int m_iKeyArraySize;
	
		TSDLcInput();
		~TSDLcInput();
	
	public:
	
		static TSDLcInput & GetInstance()
		{
			static TSDLcInput * pInput;
			if (pInput == nullptr)
			{
				pInput = new TSDLcInput;
			}
			return *pInput;
		}
	
		void Initialize();
		void Update();
		void LateUpdate();
	
		int GetMousePreviousPosX()
		{
			return m_iPreviousMousePosX;
		}
		int GetMousePreviousPosY()
		{
			return m_iPreviousMousePosY;
		}
		int GetMouseCurrentPosX()
		{
			return m_iCurrentMousePosX;
		}
		int GetMouseCurrentPosY()
		{
			return m_iCurrentMousePosY;
		}
	
		bool IsMouseButtonJustPressed(const ESDLcMouseButton eButton);
		bool IsMouseButtonPressed(const ESDLcMouseButton eButton);
		bool IsMouseButtonJustRealeased(const ESDLcMouseButton eButton);
		bool IsKeyJustPressed(const SDL_Scancode tKey);
		bool IsKeyPressed(const SDL_Scancode tKey);
		bool IsKeyJustRealeased(const SDL_Scancode tKey);
};

#endif
