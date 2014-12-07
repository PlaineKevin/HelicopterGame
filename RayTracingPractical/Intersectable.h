//
//  Intersectable.h
//  RayTracingPractical
//
//  Created by Kevin Nguyen on 11/19/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#ifndef RayTracingPractical_Intersectable_h
#define RayTracingPractical_Intersectable_h
// Object abstract base class.
class Intersectable
{
protected:
    //    Material* material;
public:
    Material* material;
    Intersectable(Material* material):material(material) {}
    virtual Hit intersect(const Ray& ray)=0;
    
};

// Object realization.
class Sphere : public Intersectable
{
    float3 center;
    float radius;
public:
    Sphere(const float3& center, float radius, Material* material):
    Intersectable(material),
    center(center),
    radius(radius)
    {
    }
    Hit intersect(const Ray& ray)
    {
        float3 diff = ray.origin - center;
        double a = ray.dir.dot(ray.dir);
        double b = diff.dot(ray.dir) * 2.0;
        double c = diff.dot(diff) - radius * radius;
        
        double discr = b * b - 4.0 * a * c;
        if ( discr < 0 )
            return Hit();
        double sqrt_discr = sqrt( discr );
        double t1 = (-b + sqrt_discr)/2.0/a;
        double t2 = (-b - sqrt_discr)/2.0/a;
        
        float t = (t1<t2)?t1:t2;
        if(t < 0)
            t = (t1<t2)?t2:t1;
        if (t < 0)
            return Hit();
        
        Hit h;
        h.t = t;
        h.material = material;
        h.position = ray.origin + ray.dir * t;
        h.normal = h.position - center;
        h.normal.normalize();
        
        return h;
        
    }
};

#endif
