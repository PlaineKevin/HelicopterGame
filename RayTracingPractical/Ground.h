//
//  Ground.h
//  RayTracingPractical
//
//  Created by Kevin Nguyen on 12/4/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#ifndef RayTracingPractical_Ground_h
#define RayTracingPractical_Ground_h
class Ground: public Object
{
public:
    float3 velocity;
    
    Ground(Material* matPointer): Object(matPointer){};
    
    int getType() {
        return 0;
    }
    
    void drawModel() {
        glBegin(GL_QUADS);
            glColor3d(0, 1, 0);
            glVertex4d(1000,0,1000,1);
            glVertex4d(-1000,0,1000,1);
            glVertex4d(-1000,0,-1000,1);
            glVertex4d(1000,0,-1000,1);
        glEnd();
    }
};

#endif
