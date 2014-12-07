//
//  Scene.h
//  RayTracingPractical
//
//  Created by Kevin Nguyen on 11/19/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#ifndef RayTracingPractical_Scene_h
#define RayTracingPractical_Scene_h
class Scene
{
    Camera camera;
    std::vector<LightSource*> lightSources;
    std::vector<Intersectable*> objects;
    std::vector<Material*> materials;
public:
    Scene()
    {
        lightSources.push_back(new PointLight(float3(1,0,0),float3(1,0,0)));
        //        lightSources.push_back(new PointLight(float3(0,1.5,0),float3(0,1,0)));
        //        lightSources.push_back(new PointLight(float3(-.5,-0.5,-2),float3(0,0,1)));
        
        lightSources.push_back(new DirectionalLight(float3(1,0,0),float3(0,1,0)));
        //        lightSources.push_back(new DirectionalLight(float3(-.5,-0.5,-2),float3(1,0,0)));
        lightSources.push_back(new DirectionalLight(float3(-.5,1.5,0),float3(0,0,1)));
        
        materials.push_back(new Material(false,false,false,float3(0.85, 0.85, .85), .8,float3(0.5, 0.5, 0.5) + float3(.6,.7,.8) * 0.5, float3(1,1,1), 10));
        
        materials.push_back(new Material(false,false,false,float3(0.6, 0.7, .4), .5,float3(0.4, 0.5, 0.3) + float3(.1,.2,.3) * 0.5, float3(1,1,1), 6));
        
        materials.push_back(new Material(false,false,false,float3(0.4, 0.5, .6), .7,float3(0.6, 0.1, 0.5) + float3(.4,.2,.7) * 0.5, float3(.5,1,1), 3));
        
        // why are my materials not working?
        objects.push_back(new Sphere(float3(1,0,0),1,materials[0]));
        objects.push_back(new Sphere(float3(-.5,1.5,0),1, materials[1]));
        objects.push_back(new Sphere(float3(-.5,-0.5,-2),1,materials[2]));
        
        objects.push_back(new Plane(float3(0,1,0),float3(.5,.5,.5)));
        
        
        
        //        for(int i = 0; i< objects.size(); i++) {
        //            objects[i]->material = materials[i];
        //        }
        
        
    }
    ~Scene()
    {
        for (std::vector<LightSource*>::iterator iLightSource = lightSources.begin(); iLightSource != lightSources.end(); ++iLightSource)
            delete *iLightSource;
        for (std::vector<Material*>::iterator iMaterial = materials.begin(); iMaterial != materials.end(); ++iMaterial)
            delete *iMaterial;
        for (std::vector<Intersectable*>::iterator iObject = objects.begin(); iObject != objects.end(); ++iObject)
            delete *iObject;
    }
    
public:
    Camera& getCamera()
    {
        return camera;
    }
    
    // IMPLEMENTED FOR YOUR CONVENIENCE, CALL THIS WHEN APPROPRIATE
    Hit firstIntersect(const Ray& ray)
    {
        Hit bestHit;
        bestHit.t = FLT_MAX;
        for(int oi=0; oi < objects.size(); oi++)
        {
            Hit hit = objects[oi]->intersect(ray);
            if(hit.t > 0 && hit.t < bestHit.t)
                bestHit = hit;
        }
        if(bestHit.t == FLT_MAX)
            return Hit();
        return bestHit;
    }
    
    // why are my shadows not working correctly?
    float3 trace(const Ray& ray)
    {
        Hit hit = firstIntersect(ray);
        //        float3 kd(1,1,1);
        
        if(hit.t < 0)
            return float3(0,0,0);
        
        float3 outRadiance = float3(0, 0, 0);
        float3 sum(0,0,0);
        for(int i = 0; i< lightSources.size();i++) {
            // light source provides li , Mi , |x - yi|
            // l is direction and i is the specific light source
            // y is the position of the light source
            Ray shadowRay(hit.position + hit.normal*float3(0.001f,0.001f,0.001f), lightSources[i]->getLightDirAt(hit.position));
            
            Hit shadowHit = firstIntersect(shadowRay);
            
            if(shadowHit.t > 0 && shadowHit.t < (lightSources[i]->getDistanceFrom(hit.position))) {
                continue;
            }
            
            outRadiance += hit.material->shade(hit.position, hit.normal, -ray.dir, lightSources[i]->getLightDirAt(hit.position) ,lightSources[i]->getPowerDensityAt(hit.position));
            
        }
        
        if(hit.material->reflective){
            float3 reflectionDir = hit.material->reflect(ray.dir, hit.normal);
            Ray reflectedRay(hit.position + hit.normal*float3(0.01f,0.01f,0.01f), reflectionDir );
            outRadiance += trace(reflectedRay)
            * hit.material->reflect(ray.dir, hit.normal);
        }
        if(hit.material->refractive) {
            float3 refractionDir = hit.material->refract(ray.dir, hit.normal);
            Ray refractedRay(hit.position - hit.normal*float3(0.01f,0.01f,0.01f), refractionDir );
            outRadiance += trace(refractedRay)
            * hit.material->refract(ray.dir, hit.normal);
        }
        
        
        return outRadiance;
    }
};

#endif
