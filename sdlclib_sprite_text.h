#ifndef SDLCLIB_SPRITE_TEXT_H_INCLUDED
#define	SDLCLIB_SPRITE_TEXT_H_INCLUDED

enum ESDLcTextRenderMode
{
	ESDLcTextRenderMode_Solid,
	ESDLcTextRenderMode_Blended
};

class TSDLcTextSprite : public TSDLcBaseSprite
{
	private:

		TTF_Font * m_pFont;
		char ** m_pText;

		SDL_Rect m_tSpriteRect;
		ESDLcTextRenderMode m_eTextRenderMode;
		int m_iFontPtSize;
		int m_iFontLineSpacing;
		int m_iLinesNumber;
		SDL_Rect * m_pLinesTextRect;
		Uint32 m_iColor;
		bool m_bTextChanged;

		

	public:

		TSDLcTextSprite();
		~TSDLcTextSprite();

		void LoadFont(const char * pFontFile, const int iFontPtSize);
		void SetText(const char * pText, ...);
		void SetRenderMode(const ESDLcTextRenderMode eRenderMode)
		{
			m_eTextRenderMode = eRenderMode;
		}
		void ClearText();
		void Destroy();

		virtual void SetPosition(const int iX, const int iY);
		virtual void SetPosition(const float fXPercent, const float fYPercent);
		
		virtual void Render();
};


#endif
