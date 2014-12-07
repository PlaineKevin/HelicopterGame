//
//  Billboard.h
//  RayTracingPractical
//
//  Created by Kevin Nguyen on 12/7/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#ifndef RayTracingPractical_Billboard_h
#define RayTracingPractical_Billboard_h

class Billboard
{
public:
    friend class Camera;
    float3 position;
    
    Billboard(float3 position) : position(position){}
    
    void draw(Camera& camera) {
        
    }
};

#endif
