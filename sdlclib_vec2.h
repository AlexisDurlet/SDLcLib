#ifndef  SDLCLIB_VEC2_H_INCLUDED
#define	 SDLCLIB_VEC2_H_INCLUDED


struct SDLcVec2
{
	float x;
	float y;

	SDLcVec2();
	SDLcVec2(float x, float y);

	float DotProduct(const SDLcVec2 & t1) const;
	float SquaredLength() const;
	float Length() const;

	SDLcVec2 Normalize() const;
	SDLcVec2 Rotate(float f1) const;

	SDLcVec2 Rotate90() const;
	SDLcVec2 Rotate180() const;
	SDLcVec2 Rotate270() const;
};

bool operator == (const SDLcVec2 & t0, const SDLcVec2 & t1);
bool operator != (const SDLcVec2 & t0, const SDLcVec2 & t1);

SDLcVec2 operator + (const SDLcVec2 & t0);
SDLcVec2 operator - (const SDLcVec2 & t0);

SDLcVec2 operator + (const SDLcVec2 & t0, const SDLcVec2 & t1);
SDLcVec2 operator - (const SDLcVec2 & t0, const SDLcVec2 & t1);
SDLcVec2 operator * (const SDLcVec2 & t0, const SDLcVec2 & t1);
SDLcVec2 operator / (const SDLcVec2 & t0, const SDLcVec2 & t1);

SDLcVec2 & operator += (SDLcVec2 & t0, const SDLcVec2 & t1);
SDLcVec2 & operator -= (SDLcVec2 & t0, const SDLcVec2 & t1);

SDLcVec2 operator * (const SDLcVec2 & t0, float f1);
SDLcVec2 operator * (float f0, const SDLcVec2 & t1);
SDLcVec2 operator / (const SDLcVec2 & t0, float f1);

SDLcVec2 & operator *= (SDLcVec2 & t0, float f1);
SDLcVec2 & operator /= (SDLcVec2 & t0, float f1);

#endif
