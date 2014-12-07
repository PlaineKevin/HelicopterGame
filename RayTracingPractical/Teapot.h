//
//  Teapot.h
//  RayTracingPractical
//
//  Created by Kevin Nguyen on 11/27/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#ifndef RayTracingPractical_Teapot_h
#define RayTracingPractical_Teapot_h
class Teapot : public Object
{
public:
    Teapot(Material* material):Object(material){}
    void drawModel()
    {
        glutSolidTeapot(1.0f);
    }
};

#endif
