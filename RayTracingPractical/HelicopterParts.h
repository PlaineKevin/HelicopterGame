//
//  HelicopterParts.h
//  RayTracingPractical
//
//  Created by Kevin Nguyen on 12/7/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#ifndef RayTracingPractical_HelicopterParts_h
#define RayTracingPractical_HelicopterParts_h
class HelicopterParts : public MeshInstance
{
    friend class Scene;
    
public:
    float3 velocity{0,0,0};
    float angularVelocity{0};
    float restitution{1};
    float3 acceleration;
    float3 upwardVelocity;
    
    int getType() {
        return 2;
    }

    
    HelicopterParts(Mesh* meshPointer, Material* matPointer, Helicopter helicopter) : MeshInstance(meshPointer, matPointer), velocity(helicopter.velocity){
        this->angularVelocity = 100;
    }

    
    void moveHelper(float3 velocity) {
        this->velocity = velocity;
    }
    
    void move(double t, double dt) {
        translate(velocity*dt);
        
        
        rotate(angularVelocity);
        
        if(this->getPosition().y < 0) {
            //            velocity.y *= -restitution;
            this->position.y = 15;
        }
        
    }
    

    
    
};

#endif
