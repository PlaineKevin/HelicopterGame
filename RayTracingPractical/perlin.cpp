#include "perlin.h"

Perlin::Perlin() 
{ 
	static int permutation[] = { 151,160,137,91,90,15,
	131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
	190,6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
	88,237,149,56,87,174,20,125,136,171,168,68,175,74,165,71,134,139,48,27,166,
	77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
	102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208,89,18,169,200,196,
	135,130,116,188,159,86,164,100,109,198,173,186,3,64,52,217,226,250,124,123,
	5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
	23,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167,43,172,9,
	129,22,39,253,19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
	251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,235,249,14,239,107,
	49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127,4,150,254,
	138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
	};

	for (int i=0; i < 256 ; i++) {
		p[256+i] = p[i] = permutation[i];
	}
}


float Perlin::noise(float3 pos) {
	int X = (int)floor(pos.x) & 255, // FIND UNIT CUBE THAT
		Y = (int)floor(pos.y) & 255, // CONTAINS POINT.
		Z = (int)floor(pos.z) & 255;
	float x = pos.x - floor(pos.x);                   // FIND RELATIVE X,Y,Z
	float y = pos.y - floor(pos.y);                   // OF POINT IN CUBE.
	float z = pos.z - floor(pos.z);
	float u = fade(x),              // COMPUTE FADE CURVES
		v = fade(y),              // FOR EACH OF X,Y,Z.
		w = fade(z);
	int A =  p[X]+Y,    // HASH COORDINATES OF
		AA = p[A]+Z,   // THE 8 CUBE CORNERS,
		AB = p[A+1]+Z, 
		B =  p[X+1]+Y, 
		BA = p[B]+Z, 
		BB = p[B+1]+Z;

	return 
		lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z),      // AND ADD  
		grad(p[BA], x-1, y, z)),    // BLENDED
		lerp(u, grad(p[AB], x, y-1, z),     // RESULTS
		grad(p[BB], x-1, y-1, z))), // FROM 8
		lerp(v, lerp(u, grad(p[AA+1], x, y, z-1),   // CORNERS
		grad(p[BA+1], x-1, y, z-1)),// OF CUBE
		lerp(u, grad(p[AB+1], x, y-1, z-1 ),
		grad(p[BB+1], x-1, y-1, z-1 ))));
}

float Perlin::marble(float3 pos)
{
	float noiseCoef = 0;
	for (int level = 1; level < 20; level ++)
	{
		noiseCoef +=  (1.0f / level) 
			* fabsf(float(noise(
			float3(
				level * 0.5 * pos.x, 
				level * 0.5 * pos.y, 
				level * 0.5 * pos.z))));
	};
//	noiseCoef = 
//		0.5f * sinf( (pos.x + pos.y) * 0.05f + noiseCoef) + 0.5f;
	return noiseCoef;
}

