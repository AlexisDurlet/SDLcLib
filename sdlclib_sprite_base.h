#ifndef SDLC_SPRITE_BASE_H_INCLUDED
#define	SDLC_SPRITE_BASE_H_INCLUDED

class TSDLcBaseSprite
{
	protected:
	
		TSDLcTexture m_tTexture;
		SDL_Point m_tPivot;
		SDL_RendererFlip m_tFlipState;
		float m_fAngle;
		float m_fScaleX;
		float m_fScaleY;
	
		Uint8 m_iRColor;
		Uint8 m_iGColor;
		Uint8 m_iBColor;
		Uint8 m_iAColor;
	
		TSDLcBaseSprite();

	public:
	
	
		virtual void SetPosition(const int iX, const int iY) = 0;
		virtual void SetPosition(const float fXPercent, const float fYPercent) = 0;
		virtual void SetPivot(const int iX, const int iY)
		{
			m_tPivot.x = iX; m_tPivot.y = iY;
		}
		virtual void SetScale(const float fScaleX, const float fScaleY)
		{
			m_fScaleX = fScaleX; m_fScaleY = fScaleY;
		}
		virtual void Flip(const SDL_RendererFlip tFlip)
		{
			m_tFlipState = tFlip;
		}
		virtual void SetAngle(const float fAngle)
		{
			m_fAngle = fAngle;
		}
		virtual void Rotate(const float fAngle)
		{
			m_fAngle += fAngle;
		}
		void SetColor(const Uint8 iRColor, const Uint8 iGColor, const Uint8 iBColor, const Uint8 iAColor)
		{
			m_iRColor = iRColor; m_iGColor = iGColor; m_iBColor = iBColor; m_iAColor = iAColor;
		}
	
		virtual void Render() = 0;
};



#endif
