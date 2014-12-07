//
//  Material.h
//  RayTracingPractical
//
//  Created by Kevin Nguyen on 11/19/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#ifndef RayTracingPractical_Material_h
#define RayTracingPractical_Material_h
// Skeletal Material class. Feel free to add methods e.g. for illumination computation (shading).
class Material
{
    
public:
    float3 kd;
    float3 ks;        // specular reflection coefficient
    float shininess; // specular exponent
    bool reflective;
    bool refractive;
    bool textured;
    float3 minReflectance;		// Fresnel coefficient
    float refractiveIndex;			// index of refraction
    
    
    Material()
    {
        reflective = false;
        refractive = false;
        textured = false;
        minReflectance = float3(0.93, 0.85, 0.4);
        refractiveIndex = 1;
        kd = float3(0.5, 0.5, 0.5) + kd * 0.5;
        ks = float3(1, 1, 1);
        shininess = 15;
    }
    
    Material(bool reflective, bool refractive, bool textured, float3 minReflectance, float refractiveIndex, float3 kd, float3 ks, float shininess)
    {
        this->reflective = reflective;
        this->refractive = refractive;
        this->textured = textured;
        this->minReflectance =  minReflectance;
        this->refractiveIndex = refractiveIndex;
        this->kd = kd;
        this->ks = ks;
        this->shininess = shininess;
    }
    
    virtual void apply()
        {
            float aglDiffuse[] = {kd.x, kd.y, kd.z, 1.0f};
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, aglDiffuse);
            float aglSpecular[] = {kd.x, kd.y, kd.z, 1.0f};
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, aglSpecular);
            if(shininess <= 128)
                glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
            else
                glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128.0f);
        }

    
    float3 reflect(float3 inDir, float3 normal) {
        return inDir - normal * normal.dot(inDir) * 2;
    }
    float3 refract(float3 inDir, float3 normal) {
        float ri = refractiveIndex;
        float cosa = -normal.dot(inDir);
        if(cosa < 0) { cosa = -cosa; normal = -normal; ri = 1 / ri; }
        float disc = 1 - (1 - cosa * cosa) / ri / ri;
        if(disc < 0) return reflect(inDir, normal);
        return inDir * (1.0 / ri) + normal * (cosa / ri - sqrt(disc));
    }
    float3 getReflectance(float3 inDir, float3 normal) {
        float cosa = fabs(normal.dot(inDir));
        return minReflectance + (float3(1, 1, 1) - minReflectance) * pow(1 - cosa, 5);
    }
    
    virtual float3 shade(
                         float3 position,
                         float3 normal,
                         float3 viewDir,
                         float3 lightDir,
                         float3 lightPowerDensity)
    {
        float cosTheta = normal.dot(lightDir);
        if(cosTheta < 0) {
            return float3(0,0,0);
        }
        float3 halfway = (viewDir+lightDir).normalize();
        float cosDelta = normal.dot(halfway);
        if(cosDelta < 0) {
            return kd * lightPowerDensity * cosTheta;
        }
        return kd * lightPowerDensity * cosTheta + lightPowerDensity * ks * pow(cosDelta,shininess);
    }
};

#endif
