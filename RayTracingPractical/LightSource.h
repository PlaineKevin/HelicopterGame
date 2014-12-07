//
//  LightSource.h
//  RayTracingPractical
//
//  Created by Kevin Nguyen on 11/13/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//
#pragma once

#ifndef RayTracingPractical_LightSource_h
#define RayTracingPractical_LightSource_h
#include <math.h>
class LightSource
{
public:
    virtual float3 getpowerDensityAt  ( float3 x )=0;
    virtual float3 getLightDirAt  ( float3 x )=0;
    virtual float  getDistanceFrom( float3 x )=0;
    virtual void   apply( GLenum openglLightName )=0;
};

class DirectionalLight : public LightSource
{
    float3 dir;
    float3 powerDensity;
public:
    DirectionalLight(float3 dir, float3 powerDensity)
    :dir(dir), powerDensity(powerDensity){}
    float3 getpowerDensityAt  ( float3 x ){return powerDensity;}
    float3 getLightDirAt  ( float3 x ){return dir;}
    float  getDistanceFrom( float3 x ){return 900000000;}
    void   apply( GLenum openglLightName )
    {
        float aglPos[] = {dir.x, dir.y, dir.z, 0.0f};
        glLightfv(openglLightName, GL_POSITION, aglPos);
        float aglZero[] = {0.0f, 0.0f, 0.0f, 0.0f};
        glLightfv(openglLightName, GL_AMBIENT, aglZero);
        float aglIntensity[] = {powerDensity.x, powerDensity.y, powerDensity.z, 1.0f};
        glLightfv(openglLightName, GL_DIFFUSE, aglIntensity);
        glLightfv(openglLightName, GL_SPECULAR, aglIntensity);
        glLightf(openglLightName, GL_CONSTANT_ATTENUATION, 1.0f);
        glLightf(openglLightName, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(openglLightName, GL_QUADRATIC_ATTENUATION, 0.0f);
    }
};

class PointLight : public LightSource
{
    float3 pos;
    float3 power;
public:
    PointLight(float3 pos, float3 power)
    :pos(pos), power(power){}
    float3 getpowerDensityAt  ( float3 x ){return power*(1/(x-pos).norm2()*4*3.14);}
    float3 getLightDirAt  ( float3 x ){return (pos-x).normalize();}
    float  getDistanceFrom( float3 x ){return (pos-x).norm();}
    void   apply( GLenum openglLightName )
    {
        float aglPos[] = {pos.x, pos.y, pos.z, 1.0f};
        glLightfv(openglLightName, GL_POSITION, aglPos);
        float aglZero[] = {0.0f, 0.0f, 0.0f, 0.0f};
        glLightfv(openglLightName, GL_AMBIENT, aglZero);
        float aglIntensity[] = {power.x, power.y, power.z, 1.0f};
        glLightfv(openglLightName, GL_DIFFUSE, aglIntensity);
        glLightfv(openglLightName, GL_SPECULAR, aglIntensity);
        glLightf(openglLightName, GL_CONSTANT_ATTENUATION, 0.0f);
        glLightf(openglLightName, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(openglLightName, GL_QUADRATIC_ATTENUATION, 0.25f / 3.14f);
    }
};


#endif
