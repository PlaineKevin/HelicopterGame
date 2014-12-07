#pragma once

#include "float3.h"

class Perlin
{
	static float fade(float t)
	{ 
		return t * t * t * (t * (t * 6 - 15) + 10);
	}

	static float lerp(float t, float a, float b) { 
		return a + t * (b - a);
	}

	static float grad(int hash, float x, float y, float z) {
		int h = hash & 15;
		// CONVERT LO 4 BITS OF HASH CODE
		float u = h<8||h==12||h==13 ? x : y, // INTO 12 GRADIENT DIRECTIONS.
			v = h < 4||h == 12||h == 13 ? y : z;
		return ((h & 1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
	}

public:
	int p[512];
	Perlin(void);

	float noise(float3 pos);

	float marble(float3 pos);

};

