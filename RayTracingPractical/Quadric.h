//
//  Quadric.h
//  RayTracingPractical
//
//  Created by Kevin Nguyen on 11/19/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#ifndef RayTracingPractical_Quadric_h
#define RayTracingPractical_Quadric_h
class Quadric : public Intersectable
{
    float4x4 A;
public:
    Quadric(Material* material):
    Intersectable(material)
    { // ellipsoid hardwired here
        // you should add methods
        // to set up different quadrics
        A = float4x4::identity;
        A._11 = 8;
        A._33 = -4;
    }
    
    // e is the ray origin
    // t
    // d is the ray direction
    //
    void rotate(const float3 &axis, float angle) {
        A = float4x4::rotation(axis, angle) * A * float4x4::rotation(axis, -angle);
    }
    
    void scale(const float3 &factors) {
        float3 scaledFactors = float3(1/factors.x, 1/factors.y, 1/factors.z);
        A = float4x4::scaling(scaledFactors) * A * float4x4::scaling(scaledFactors);
    }
    
    void translate(const float3 &offset) {
        A = float4x4::translation(offset) * A * float4x4::translation(offset).transpose();
    }
    
    Hit intersect(const Ray& ray) {
        // ray in homo coords
        float4 e = float4(ray.origin.x,
                          ray.origin.y, ray.origin.z, 1);
        float4 d = float4(ray.dir.x,
                          ray.dir.y, ray.dir.z, 0);
        
        // quadratic coeffs.
        double a = d.dot( A * d );
        double b = e.dot( A * d )
        + d.dot( A * e );
        double c = e.dot( A * e );
        
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
        
        // homo position
        float4 hPos = float4(h.position.x,
                             h.position.y, h.position.z, 1);

        // homo normal per quadric normal formula
        float4 hNormal = A * hPos +  hPos * A;
        
        // Cartesian normal
        h.normal = float3(hNormal.x, hNormal.y, hNormal.z).normalize();
        h.position = float3(hPos.x,hPos.y,hPos.z);
        
        h.normal.normalize();
    

        
        return h;
    }
};

#endif
