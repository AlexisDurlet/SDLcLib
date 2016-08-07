#include "sdlclib_vec2.h"
#include"sdlclib.h"
#include <math.h>

SDLcVec2::SDLcVec2() :
x(0),
y(0)
{}

SDLcVec2::SDLcVec2(float x, float y) :
x(x),
y(y)
{}


bool operator == (const SDLcVec2 & t0, const SDLcVec2 & t1)
{
	return (t0.x == t1.x && t0.y == t1.y);
}

bool operator != (const SDLcVec2 & t0, const SDLcVec2 & t1)
{
	return (t0.x != t1.x || t0.y != t1.y);
}

SDLcVec2 operator + (const SDLcVec2 & t0)
{
	return t0;
}

SDLcVec2 operator - (const SDLcVec2 & t0)
{
	return SDLcVec2(-t0.x, -t0.y);
}

SDLcVec2 operator + (const SDLcVec2 & t0, const SDLcVec2 & t1)
{
	return SDLcVec2(t0.x + t1.x, t0.y + t1.y);
}

SDLcVec2 operator - (const SDLcVec2 & t0, const SDLcVec2 & t1)
{
	return SDLcVec2(t0.x - t1.x, t0.y - t1.y);
}

SDLcVec2 operator * (const SDLcVec2 & t0, const SDLcVec2 & t1)
{
	return SDLcVec2(t0.x * t1.x, t0.y * t1.y);
}

SDLcVec2 operator / (const SDLcVec2 & t0, const SDLcVec2 & t1)
{
	SDLcAssert(t1.x != 0.0f && t1.y != 0.0f, "Dividing by zero!");
	return SDLcVec2(t0.x / t1.x, t0.y / t1.y);
}

SDLcVec2 & operator += (SDLcVec2 & t0, const SDLcVec2 & t1)
{

	t0.x += t1.x;
	t0.y += t1.y;
	return t0;
}

SDLcVec2 & operator -= (SDLcVec2 & t0, const SDLcVec2 & t1)
{

	t0.x -= t1.x;
	t0.y -= t1.y;
	return t0;
}

SDLcVec2 operator * (const SDLcVec2 & t0, float f1)
{

	return SDLcVec2(t0.x * f1, t0.y * f1);
}

SDLcVec2 operator * (float f0, const SDLcVec2 & t1)
{

	return SDLcVec2(f0 * t1.x, f0 * t1.y);
}

SDLcVec2 operator / (const SDLcVec2 & t0, float f1)
{

	SDLcAssert(f1 != 0.0f, "Dividing by zero!");
	return SDLcVec2(t0.x / f1, t0.y / f1);
}

SDLcVec2 & operator *= (SDLcVec2 & t0, float f1)
{

	t0.x *= f1;
	t0.y *= f1;
	return t0;
}

SDLcVec2 & operator /= (SDLcVec2 & t0, float f1)
{

	SDLcAssert(f1 != 0.0f, "Dividing by zero!");
	t0.x /= f1;
	t0.y /= f1;
	return t0;
}

float SDLcVec2::DotProduct(const SDLcVec2 & t1) const
{

	return (x * t1.x + y * t1.y);
}

float SDLcVec2::SquaredLength() const
{

	return DotProduct(*this);
}

float SDLcVec2::Length() const
{

	return sqrt(SquaredLength());
}

SDLcVec2 SDLcVec2::Normalize() const
{

	const float fLen = Length();
	SDLcAssert(fLen > 0.0f, "Dividing by zero!");
	return (*this / fLen);
}

SDLcVec2 SDLcVec2::Rotate(float f1) const
{

	const float sin_f1 = sin(f1);
	const float cos_f1 = cos(f1);
	return SDLcVec2(x * cos_f1 - y * sin_f1, y * cos_f1 + x * sin_f1);
}

SDLcVec2 SDLcVec2::Rotate90() const
{
	return SDLcVec2(-y, x);
}

SDLcVec2 SDLcVec2::Rotate180() const
{
	return SDLcVec2(-x, -y);
}

SDLcVec2 SDLcVec2::Rotate270() const
{
	return SDLcVec2(y, -x);
}