//
//  Bouncer.h
//  RayTracingPractical
//
//  Created by Kevin Nguyen on 12/4/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#ifndef RayTracingPractical_Bouncer_h
#define RayTracingPractical_Bouncer_h

class Bouncer : public MeshInstance
{
public:
    float3 velocity{0,0,0};
    float angularVelocity{0};
    float restitution{1};
    float angularAcceleration{0};
    float3 acceleration;
    
    
    Bouncer(Mesh* meshPointer, Material* matPointer) : MeshInstance(meshPointer, matPointer) {
        MeshInstance::drawModel();
    }
    
    // the else if cases make it so that only one of these are possible at a time.
    bool control(std::vector<bool>& keysPressed, std::vector<Object*>& spawn, std::vector<Object*>& objects)
    {
        if(keysPressed['h'] == true) {
            angularAcceleration = 100;
        } else if(keysPressed['k']) {
            angularAcceleration = -100;
        } else if(keysPressed['u']) {
            acceleration = float3(-cos(orientationAngle)*10, -10, sin(orientationAngle) *10);
        } else if(keysPressed['j']) {
            acceleration = float3(cos(orientationAngle) *10, -10, -sin(orientationAngle) *10);
        } else {
            angularAcceleration = 0;
            acceleration = float3(0,-10,0);
        }
        
        return true;
    }
    
    void move(double t, double dt) {
        velocity += acceleration * dt;
        translate(velocity*dt);
        angularVelocity += angularAcceleration*dt;
        angularVelocity *= pow(.8,dt);
//        velocity *= pow(.8,dt);
        rotate(angularVelocity*dt);
        
        if(this->getPosition().y < 0) {
            velocity.y *= -restitution;
            this->position.y = 0;
        }
        
    }
};

#endif
