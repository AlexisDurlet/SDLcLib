#include "sdlclib.h"
#include "sdlclib_window.h"
#include "sdlclib_dbginfo.h"

TSDLcDrawSprite::TSDLcDrawSprite()
{
	TSDLcDbgInfo::GetInstance().IncrementDrawSpriteNb();
}
TSDLcDrawSprite::~TSDLcDrawSprite()
{
	Clear();
	TSDLcDbgInfo::GetInstance().DecrementDrawSpriteNb();
}

int TSDLcDrawSprite::GetYSign()
{
	int iYSign = 1;
	if (m_bYAxisInverted) iYSign = -1;
	return iYSign;
}

SDL_Point TSDLcDrawSprite::ConvertLocalToWorld(const SDL_Point tP)
{
	SDL_Point a;
	a.x = m_tPivot.x + tP.x;
	a.y = GetYSign() * (m_tPivot.y + tP.y);

	return a;
}

SDL_Point TSDLcDrawSprite::ConvertWorldToLocal(const SDL_Point tP)
{
	SDL_Point a;
	a.x = tP.x - m_tPivot.x;
	a.y = (tP.y  * GetYSign()) - m_tPivot.y;

	return a;
}

SDL_Point TSDLcDrawSprite::ApplyFloatOpperations(const SDL_Point tP)
{
	SDL_Point a;
	a.x = SDLcROUND(tP.x * m_fScaleX);
	a.y = SDLcROUND(tP.y * m_fScaleY);

	a = ConvertWorldToLocal(a);
	SDLcRotate2D(a, m_fAngle);
	a = ConvertLocalToWorld(a);

	return a;
}

void TSDLcDrawSprite::DrawLine(SDL_Point a, SDL_Point b)
{
	a = ConvertLocalToWorld(a);
	b = ConvertLocalToWorld(b);

	m_tPoints.push_back(a);
	m_tPoints.push_back(b);
	m_tColors.push_back(m_iDrawingColor);
}

void TSDLcDrawSprite::DrawRectangle(const SDL_Rect tRect)
{
	SDL_Point upr;
	upr.x = tRect.x + tRect.w/2;
	upr.y = tRect.y + tRect.h/2;
	SDL_Point upl;
	upl.x = tRect.x - tRect.w/2;
	upl.y = tRect.y + tRect.h/2;
	SDL_Point downr;
	downr.x = tRect.x + tRect.w / 2;
	downr.y = tRect.y - tRect.w / 2;
	SDL_Point downl;
	downl.x = tRect.x - tRect.w / 2;
	downl.y = tRect.y - tRect.w / 2;

	DrawLine(upr, upl);
	DrawLine(upl, downl);
	DrawLine(downl, downr);
	DrawLine(downr, upr);
}

void TSDLcDrawSprite::DrawCircle(const SDL_Point tPoint, const int iRadius)
{
	const int iSegmentNumber = 2 * SDLcROUND(M_PI) * iRadius;
	const float fAngleStep = 360.0f / iSegmentNumber;
	SDL_Point tStartPoint;
	tStartPoint.x = iRadius;
	tStartPoint.y = 0;

	SDL_Point tStartDrawPoint;
	tStartDrawPoint.x = tPoint.x + tStartPoint.x;
	tStartDrawPoint.y = tPoint.y + tStartPoint.y;

	for (int i = 0; i < iSegmentNumber; i++)
	{
		SDL_Point tNextPoint = tStartPoint;
		SDLcRotate2D(tNextPoint, i * fAngleStep);

		SDL_Point tNextDrawPoint;
		tNextDrawPoint.x = tPoint.x + tNextPoint.x;
		tNextDrawPoint.y = tPoint.y + tNextPoint.y;

		DrawLine(tStartDrawPoint, tNextDrawPoint);

		tStartDrawPoint.x = tNextDrawPoint.x;
		tStartDrawPoint.y = tNextDrawPoint.y;
	}
}

void TSDLcDrawSprite::Flip(const SDL_RendererFlip tFlip)
{
	switch (tFlip)
	{
		case SDL_FLIP_NONE:
			switch (m_tFlipState)
			{
				case SDL_FLIP_NONE:
					break;

				case SDL_FLIP_HORIZONTAL:

					for (unsigned int i = 0; i < m_tPoints.size(); i++)
					{
						m_tPoints[i].x *= -1;
					}

					break;

				case SDL_FLIP_VERTICAL:

					for (unsigned int i = 0; i < m_tPoints.size(); i++)
					{
						m_tPoints[i].y *= -1;
					}

					break;
			}
			break;

		default:
			break;
	}

	TSDLcBaseSprite::Flip(tFlip);

	switch (m_tFlipState)
	{
		case SDL_FLIP_NONE:
			break;

		case SDL_FLIP_HORIZONTAL:

			for (unsigned int i = 0; i < m_tPoints.size(); i++)
			{
				m_tPoints[i].x *= -1;
			}

			break;

		case SDL_FLIP_VERTICAL:

			for (unsigned int i = 0; i < m_tPoints.size(); i++)
			{
				m_tPoints[i].y *= -1;
			}

			break;
	}
}

void TSDLcDrawSprite::SetPosition(const int iX, const int iY)
{
	for (unsigned int i = 0; i < m_tPoints.size(); i++)
	{
		m_tPoints[i] = ConvertWorldToLocal(m_tPoints[i]);
	}

	m_tPivot.x = iX; 
	m_tPivot.y = iY;

	for (unsigned int i = 0; i < m_tPoints.size(); i ++)
	{
		m_tPoints[i] = ConvertLocalToWorld(m_tPoints[i]);
	}
}

void TSDLcDrawSprite::SetPosition(const float fXPercent, const float fYPercent)
{
	for (unsigned int i = 0; i < m_tPoints.size(); i++)
	{
		m_tPoints[i] = ConvertWorldToLocal(m_tPoints[i]);
	}

	m_tPivot.x = static_cast<int>(fXPercent * GetResWH().x);
	m_tPivot.y = static_cast<int>(fYPercent * GetResWH().y);

	for (unsigned int i = 0; i < m_tPoints.size(); i++)
	{
		m_tPoints[i] = ConvertLocalToWorld(m_tPoints[i]);
	}
}

void TSDLcDrawSprite::Render()
{
	for (unsigned int i = 0; i < m_tPoints.size(); i += 2)
	{
		Uint8 r, g, b, a;
		SDLcGetRGBA(m_tColors[i/2], &r, &g, &b, &a);
		SDL_SetRenderDrawColor(TSDLcWindow::GetInstance().GetRenderer(), r,g,b,a);

		SDL_Point p1 = ApplyFloatOpperations(m_tPoints[i]);
		SDL_Point p2 = ApplyFloatOpperations(m_tPoints[i + 1]);


		SDL_RenderDrawLine(TSDLcWindow::GetInstance().GetRenderer(), p1.x, p1.y, p2.x, p2.y);
	}
}

void TSDLcDrawSprite::Clear()
{
	m_tPoints.clear();
	m_tColors.clear();
}
