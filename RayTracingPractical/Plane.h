//
//  Plane.h
//  RayTracingPractical
//
//  Created by Kevin Nguyen on 11/19/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#ifndef RayTracingPractical_Plane_h
#define RayTracingPractical_Plane_h

class Plane: public Intersectable
{
    
public:
    float3 normal;
    float3 x0;
    
    Plane(float3 normal, float3 x0, Material *material): normal(normal), x0(x0), Intersectable(material) {}

    Hit intersect(const Ray& ray) {
        float t = (x0-ray.origin).dot(normal)/ray.dir.dot(normal);
        float3 hitPos = ray.origin + ray.dir * t;
        
        Hit actualHit;
        actualHit.position = hitPos;
        actualHit.t = t;
        actualHit.normal = normal;
        actualHit.material = material;
        
        return actualHit;
        
    }
};
#endif
