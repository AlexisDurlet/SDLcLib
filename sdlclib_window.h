#ifndef	SDLCLIB_WINDOW_H_INCLUDED
#define	SDLCLIB_WINDOW_H_INCLUDED

class TSDLcWindow
{
	private:
	
		TSDLcWindow();
	
		SDL_Window * m_pWindow;
		SDL_Surface * m_pScreenSurface;
		SDL_Renderer * m_pRenderer;
	
		int m_iWindowWidth;
		int m_iWindowHeight;
	
		bool m_bInitialized;
	
	public:
	
		static TSDLcWindow & GetInstance()
		{
			static TSDLcWindow * pWindow;
			if (pWindow == nullptr)
			{
				pWindow = new TSDLcWindow;
			}
			return *pWindow;
		}
	
		SDL_Window * GetWindow()
		{
			return m_pWindow;
		}
		SDL_Renderer * GetRenderer()
		{
			return m_pRenderer;
		}
		int GetWindowWidth()
		{
			return m_iWindowWidth;
		}
		int GetWindowHeight()
		{
			return m_iWindowHeight;
		}
		bool GetInitialization()
		{
			return m_bInitialized;
		}
	
		void Initialize();
};


#endif
