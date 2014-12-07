//
//  Helicopter.h
//  RayTracingPractical
//
//  Created by Kevin Nguyen on 12/7/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#ifndef RayTracingPractical_Helicopter_h
#define RayTracingPractical_Helicopter_h
class Helicopter : public MeshInstance
{
    friend class Scene;
    
public:
    bool flyMode;
    bool keys[5];
    
    float3 velocity{0,0,0};
    float angularVelocity{0};
    float restitution{1};
    float angularAcceleration{0};
    float upwardAcceleration;
    float3 acceleration;
    float3 upwardVelocity;
    
    int getType() {
        return 1;
    }
    
    
    Helicopter(Mesh* meshPointer, Material* matPointer) : MeshInstance(meshPointer, matPointer) {
        flyMode = false;
        MeshInstance::drawModel();
    }
    
    // the else if cases make it so that only one of these are possible at a time.
    bool control(std::vector<bool>& keysPressed, std::vector<Object*>& spawn, std::vector<Object*>& objects)
    {
        if(keysPressed['h'] or keysPressed['k'] or keysPressed['u'] or keysPressed['j'] or keysPressed['n']) {
            if(keysPressed['h'] == true) {
                angularAcceleration = 100;
            }
            if(keysPressed['k']) {
                angularAcceleration = -100;
            }
            if(keysPressed['u']) {
                acceleration = float3(-cos(orientationAngle)*10, 10, sin(orientationAngle) *10);
            }
            if(keysPressed['j']) {
                acceleration = float3(cos(orientationAngle) *10,-10, -sin(orientationAngle) *10);
            }
            if(keysPressed['n']){
                velocity.y *= -restitution;
            }
            
        } else{
            angularAcceleration = 0;
            acceleration = float3(0,-10,0);
        }
        
        
        return true;
    }
    
    void move(double t, double dt) {
        velocity += acceleration * dt;
        velocity *= pow(.8,dt);
        translate(velocity*dt);
        
        angularVelocity += angularAcceleration*dt;
        angularVelocity *= pow(.8,dt);
        
        rotate(angularVelocity*dt);
        
        if(this->getPosition().y < 0) {
//            velocity.y *= -restitution;
            this->position.y = 0;
        }
        
        
    }
};

#endif
