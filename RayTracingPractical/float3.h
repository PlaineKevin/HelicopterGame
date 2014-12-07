#pragma once

#include <math.h>
#include <stdlib.h>

class float3
{
public:
	float x;
	float y;
	float z;

	float3()
	{
		x = ((float)rand() / RAND_MAX) * 2 - 1;
		y = ((float)rand() / RAND_MAX) * 2 - 1;
		z = ((float)rand() / RAND_MAX) * 2 - 1;
	}

	float3(float x, float y, float z):x(x),y(y),z(z){}

	float3 operator-() const
	{
		return float3(-x, -y, -z);
	}


	float3 operator+(const float3& addOperand) const
	{
		return float3(x + addOperand.x, y + addOperand.y, z + addOperand.z);
	}

	float3 operator-(const float3& operand) const
	{
		return float3(x - operand.x, y - operand.y, z - operand.z);
	}

	float3 operator*(const float3& operand) const
	{
		return float3(x * operand.x, y * operand.y, z * operand.z);
	}
	
	float3 operator*(float operand) const
	{
		return float3(x * operand, y * operand, z * operand);
	}

	void operator-=(const float3& a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
	}

	void operator+=(const float3& a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
	}

	void operator*=(const float3& a)
	{
		x *= a.x;
		y *= a.y;
		z *= a.z;
	}

	void operator*=(float a)
	{
		x *= a;
		y *= a;
		z *= a;
	}

	float norm() const
	{
		return sqrtf(x*x+y*y+z*z);
	}

	float norm2() const
	{
		return x*x+y*y+z*z;
	}

	float3 normalize()
	{
		float oneOverLength = 1.0f / norm();
		x *= oneOverLength;
		y *= oneOverLength;
		z *= oneOverLength;
		return *this;
	}
	
	float3 cross(const float3& operand) const
	{
		return float3(
			y * operand.z - z * operand.y,
			z * operand.x - x * operand.z,
			x * operand.y - y * operand.x);

	}

	float dot(const float3& operand) const
	{
		return x * operand.x + y * operand.y + z * operand.z;
	}

};