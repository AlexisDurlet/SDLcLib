#ifndef SDLCLIB_DRAWSPRITE_H_INCLUDED
#define	SDLCLIB_DRAWSPRITE_H_INCLUDED

#include <vector>

class TSDLcDrawSprite : public TSDLcBaseSprite
{
	private:

		std::vector<SDL_Point> m_tPoints;
		std::vector<Uint32> m_tColors;

		SDL_Point m_tPos;
		Uint32 m_iDrawingColor;

		bool m_bYAxisInverted;

		int GetYSign();
		SDL_Point ConvertLocalToWorld(const SDL_Point tP);
		SDL_Point ConvertWorldToLocal(const SDL_Point tP);
		SDL_Point ApplyFloatOpperations(const SDL_Point tP);

	public:

		TSDLcDrawSprite();
		~TSDLcDrawSprite();

		void DrawLine(SDL_Point a, SDL_Point b);
		void DrawRectangle(SDL_Rect tRect);
		void DrawCircle(SDL_Point tPoint, int iRadius);
		void SetDrawingColor(const Uint32 iColorRGBA)
		{
			m_iDrawingColor = iColorRGBA;
		}
		virtual void SetPosition(const int iX, const int iY); //set the origin and correct all lines positions accordingly 
		virtual void SetPosition(const float fXPercent, const float fYPercent);
		virtual void Flip(const SDL_RendererFlip tFlip);
		virtual void SetInvertYAxis(bool bInverted) //false is screen y orientation, true is inverted
		{
			m_bYAxisInverted = bInverted;
		}

		virtual void Render();
		void Clear();
};


#endif
