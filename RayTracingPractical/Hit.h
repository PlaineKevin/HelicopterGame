//
//  Hit.h
//  RayTracingPractical
//
//  Created by Kevin Nguyen on 11/19/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#ifndef RayTracingPractical_Hit_h
#define RayTracingPractical_Hit_h
// Hit record structure. Contains all data that describes a ray-object intersection point.
class Hit
{
public:
    Hit()
    {
        t = -1;
    }
    // we can compare which ray hit was closer
    float t;
    float3 position;
    float3 normal;
    Material* material;
};

#endif
