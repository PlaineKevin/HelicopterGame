//
//  Scene.h
//  RayTracingPractical
//
//  Created by Kevin Nguyen on 11/19/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#ifndef RayTracingPractical_Scene_h
#define RayTracingPractical_Scene_h
using namespace std;

#include "Helicopter.h"
#include "HelicopterParts.h"

class Scene
{
    Camera camera;
    std::vector<LightSource*> lightSources;
    std::vector<Object*> objects;
    std::vector<Material*> materials;
    std::vector<Billboard*> billboards;
public:

    
    Scene()
    {
        // BUILD YOUR SCENE HERE
        lightSources.push_back(
                               new DirectionalLight(
                                                    float3(0, 1, 0),
                                                    float3(1, 0.5, 1)));
        lightSources.push_back(
                               new PointLight(
                                              float3(-1, -1, 1),
                                              float3(0.2, 0.1, 0.1)));
        Material* yellowDiffuseMaterial = new Material();
        materials.push_back(yellowDiffuseMaterial);
        yellowDiffuseMaterial->kd = float3(1, 1, 0);
        materials.push_back(new Material());
        materials.push_back(new Material());
        materials.push_back(new Material());
        materials.push_back(new Material());
        materials.push_back(new Material());
        materials.push_back(new Material());
        
//        
//        objects.push_back( (new Teapot( yellowDiffuseMaterial))->translate(float3(2, 0, 0)) );
//        objects.push_back( (new Teapot( materials.at(1) )     )->translate(float3(0, -1, 2))->scale(float3(0.6, 0.6, 0.6)) );
//        objects.push_back( (new Teapot( materials.at(2) )     )->translate(float3(0, 1.2, 0.5))->scale(float3(1.3, 1.3, 1.3)) );
        
    }
    ~Scene()
    {
        for (std::vector<LightSource*>::iterator iLightSource = lightSources.begin(); iLightSource != lightSources.end(); ++iLightSource)
            delete *iLightSource;
        for (std::vector<Material*>::iterator iMaterial = materials.begin(); iMaterial != materials.end(); ++iMaterial)
            delete *iMaterial;
        for (std::vector<Object*>::iterator iObject = objects.begin(); iObject != objects.end(); ++iObject)
            delete *iObject;
    }
    
    void control(std::vector<bool>& keysPressed)
    {
        std::vector<Object*> spawn;
        for (unsigned int iObject=0; iObject<objects.size(); iObject++)
            objects.at(iObject)->control(
                                         keysPressed, spawn, objects);
//        if(keysPressed['r']) {
//            objects.pop_back();
//        }
    }
    
    void move(double t, double dt){
        float3 tempVel = float3(0,0,0);
        for(int i = 0; i < objects.size(); i++) {
            if(objects[i]->getType() == 1) {
                tempVel = objects[i]->velocity;
            }
            if(objects[i]->getType() == 2) {
                objects[i]->moveHelper(tempVel);
            }
            objects[i]->move(t, dt);
        }
    }
    
    void initialize() {
        Mesh *trigObject = new Mesh("/Users/KevinN/Downloads/heli/heli.obj");
        TexturedMaterial *helText = new TexturedMaterial("/Users/KevinN/Downloads/heli/heliait.png");
        
        Mesh *partsObject = new Mesh("/Users/KevinN/Downloads/heli/mainrotor.obj");
        
        Helicopter *newMeshIns = new Helicopter(trigObject, helText);
        Ground *newGround = new Ground(helText);
        newMeshIns->translate(float3(0,0,0));
        HelicopterParts *newMeshPart = new HelicopterParts(partsObject,helText,*newMeshIns);
        newMeshPart->translate(float3(0,15,0));
        
        objects.push_back(newGround);
        objects.push_back(newMeshIns);
        objects.push_back(newMeshPart);
    }
    
public:
    
    
    Camera& getCamera()
    {
        return camera;
    }
    
    void draw()
    {
        camera.apply();
        unsigned int iLightSource=0;
        for (; iLightSource<lightSources.size(); iLightSource++)
        {
            glEnable(GL_LIGHT0 + iLightSource);
            lightSources.at(iLightSource)->apply(GL_LIGHT0 + iLightSource);
        }
        for (; iLightSource<GL_MAX_LIGHTS; iLightSource++)
            glDisable(GL_LIGHT0 + iLightSource);
        
        for (unsigned int iObject=0; iObject<objects.size(); iObject++)
            objects.at(iObject)->draw();
    }
};


#endif
