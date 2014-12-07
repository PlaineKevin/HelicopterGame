#pragma once

#include <math.h>

class float4
{
public:
	union{
		struct {
			float x;
			float y;
			float z;
			float w;
		};
		
		float v[4];
	};

	float4():x(0.0f),y(0.0f),z(0.0f),w(0.0f){}

	float4(float f):x(f),y(f),z(f),w(f){}

	float4(float x, float y, float z, float w):x(x),y(y),z(z),w(w){}

	float4& operator+=(const float4& o)
	{
		x += o.x;
		y += o.y;
		z += o.z;
		w += o.w;
		return *this;
	}

	float4& operator-=(const float4& o)
	{
		x -= o.x;
		y -= o.y;
		z -= o.z;
		w -= o.w;
		return *this;
	}

	float4& operator*=(const float4& o)
	{
		x *= o.x;
		y *= o.y;
		z *= o.z;
		w *= o.w;
		return *this;
	}

	float4& operator/=(const float4& o)
	{
		x /= o.x;
		y /= o.y;
		z /= o.z;
		w /= o.w;
		return *this;
	}

	float4& operator%=(const float4& o)
	{
		x = fmodf(x, o.x);
		y = fmodf(y, o.y);
		z = fmodf(z, o.z);
		w = fmodf(w, o.w);
		return *this;
	}

	float4 operator+(const float4& o) const
	{
		return float4(x + o.x, y + o.y, z + o.z, w + o.w);
	}

	float4 operator-(const float4& o) const
	{
		return float4(x - o.x, y - o.y, z - o.z, w - o.w);
	}

	float4 operator*(const float4& o) const
	{
		return float4(x * o.x, y * o.y, z * o.z, w * o.w);
	}

	float4 operator/(const float4& o) const
	{
		return float4(x / o.x, y / o.y, z / o.z, w / o.w);
	}

	float4 operator%(const float4& o) const
	{
		return float4(fmodf(x, o.x), fmodf(y, o.y), fmodf(z, o.z), fmodf(w, o.w));
	}


	float4 operator+() const
	{
		return float4(+x, +y, +z, +w);
	}

	float4 operator-() const
	{
		return float4(-x, -y, -z, -w);
	}

	float4 operator!() const
	{
		return float4(-x, -y, -z, +w);
	}

	float distance(const float4& o) const
	{
		return (*this - o).norm();
	}

	float dot(const float4& o) const
	{
		return x * o.x + y * o.y + z * o.z + w * o.w;
	}

	float norm() const
	{
		return sqrtf( this->dot(*this));
	}

	float norm2() const
	{
		return this->dot(*this);
	}

	float4 normalize() const
	{
		return *this / norm();
	}

};

