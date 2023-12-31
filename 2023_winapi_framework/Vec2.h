#pragma once
#include<assert.h>
class Vec2
{
public:
	Vec2();
	~Vec2();
	Vec2(float _x, float _y);
	Vec2(int _x, int _y);
	Vec2(POINT _pt);
	Vec2(const Vec2& _vec);
public:
	float Length() { return (float)(sqrt(pow(x, 2) + pow(y, 2))); }
	static float Dot(const Vec2& _vec1, const Vec2& _vec2) {
		return (_vec1.x * _vec2.x) + (_vec1.y * _vec2.y);
	}
	static Vec2 Lerp(Vec2& _from, Vec2& _to, const float& _percent)
	{
		return _from + (_to - _from) * _percent;
	}
	Vec2& Normalize()
	{
		float fLen = Length();
		assert(fLen != 0.f);
		x /= fLen;
		y /= fLen;
		return *this;
	}
	Vec2 Normalized() {
		float fLen = Length();
		assert(fLen != 0.f);
		return Vec2(x / fLen, y / fLen);
	}
	Vec2 operator + (Vec2 _vOther)
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}
	void operator += (Vec2 _vOther) {
		x += _vOther.x;
		y += _vOther.y;
	}
	Vec2 operator - (Vec2 _vOther)
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}
	void operator -= (Vec2 _vOther) {
		x -= _vOther.x;
		y -= _vOther.y;
	}
	Vec2 operator * (Vec2 _vOther)
	{
		return Vec2(x * _vOther.x, y * _vOther.y);
	}
	Vec2 operator * (float _f)
	{
		return Vec2(x * _f, y * _f);
	}
	void operator *= (Vec2 _vOther) {
		x *= _vOther.x;
		y *= _vOther.y;
	}
	void operator *= (float _f) {
		x *= _f;
		y *= _f;
	}
	Vec2 operator / (Vec2 _vOther)
	{
		assert(!(0.f == _vOther.x || 0.f == _vOther.y));
		return Vec2(x / _vOther.x, y / _vOther.y);
	}
	Vec2 operator / (float _f) {
		assert(!_f == 0.f);
		return Vec2(x / _f, y / _f);
	}
	void operator /= (Vec2 _vOther) {
		x /= _vOther.x;
		y /= _vOther.y;
	}
	void operator /= (float _f) {
		x /= _f;
		y /= _f;
	}
	Vec2 operator -() {
		return Vec2(-x, -y);
	}
public:
	float x;
	float y;
};

