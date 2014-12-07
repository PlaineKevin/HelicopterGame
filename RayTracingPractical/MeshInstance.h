//
//  MeshInstance.h
//  RayTracingPractical
//
//  Created by Kevin Nguyen on 11/27/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#ifndef RayTracingPractical_MeshInstance_h
#define RayTracingPractical_MeshInstance_h
class MeshInstance : public Object
{
    
public:
    Mesh* mesh;
    
    MeshInstance(Mesh* meshPointer, Material* matPointer):Object(matPointer), mesh(meshPointer) {}
    
    void drawModel(){
        mesh->draw();
    };
    void move(double t, double dt){}
    bool control(std::vector<bool>& keysPressed, std::vector<Object*>& spawn, std::vector<Object*>& objects){return false;}
    
};

#endif
