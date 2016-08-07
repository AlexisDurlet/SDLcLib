#ifndef SDLCLIB_SPRITE_H
#define	SDLCLIB_SPRITE_H


class TSDLcSprite : public TSDLcBaseSprite
{
	private:
	
		SDL_Rect m_tCutoutRect;
		SDL_Rect m_tSpriteRect;

	public:
	
		TSDLcSprite();
		~TSDLcSprite();
	
		void Create(TSDLcTexture & pTexture);
		void Destroy();
		void SetCutout(const int iCutoutX, const int iCutoutY, const int iCutoutW, const int iCutoutH);

		virtual void SetPosition(const int iX, const int iY);
		virtual void SetPosition(const float fXPercent, const float fYPercent);
		virtual void SetScale(const float fScaleX, const float fScaleY);

		virtual void Render();
};




#endif
