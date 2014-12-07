//
//  Camera.h
//  RayTracingPractical
//
//  Created by Kevin Nguyen on 11/19/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#ifndef RayTracingPractical_Camera_h
#define RayTracingPractical_Camera_h
// Skeletal Camera class. Feel free to add custom initialization, set aspect ratio to fit viewport dimensions, or animation.
class Camera
{
    float3 eye;
    
    float3 lookAt;
    float3 right;
    float3 up;
    
    float3 ahead;
    
    float2 lastMousePos;
    float2 mouseDelta;
    
    float fov;
    float aspect;
    
public:
    float3 getEye()
    {
        return eye;
    }
    Camera()
    {
        eye = float3(0, 0, 5);
        ahead = float3(0, 0, -1);
        right = float3(1, 0, 0);
        up = float3(0, 1, 0);
        fov = 1.5;
        aspect = 1;
    }
    
    float3 rayDirFromNdc(const float2 ndc) {
        return (lookAt - eye
                + right * ndc.x
                + up    * ndc.y
                ).normalize();
    }
    
    void startDrag(int x, int y) {
        lastMousePos = float2(x, y);
    }
    void drag(int x, int y){
        float2 mousePos(x, y);
        mouseDelta = mousePos - lastMousePos;
        lastMousePos = mousePos;
    }
    void endDrag(){
        mouseDelta = float2(0, 0);
    }
    void move(float dt, std::vector<bool>& keysPressed) {
        if(keysPressed.at('w'))
            eye += ahead * dt * 20;
        if(keysPressed.at('s'))
            eye -= ahead * dt * 20;
        if(keysPressed.at('a'))
            eye -= right * dt * 20;
        if(keysPressed.at('d'))
            eye += right * dt * 20;
        if(keysPressed.at('q'))
            eye -= float3(0,1,0) * dt * 20;
        if(keysPressed.at('e'))
            eye += float3(0,1,0) * dt * 20;
        //to be continued here
        float yaw = atan2f( ahead.x, ahead.z );
        float pitch = -atan2f( ahead.y,
                              sqrtf(ahead.x * ahead.x + ahead.z * ahead.z) );
        
        yaw -= mouseDelta.x * 0.02f;
        pitch += mouseDelta.y * 0.02f;
        if(pitch > 3.14/2) pitch = 3.14/2;
        if(pitch < -3.14/2) pitch = -3.14/2;
        
        mouseDelta = float2(0, 0);
        
        ahead = float3(sin(yaw)*cos(pitch), -sin(pitch),
                       cos(yaw)*cos(pitch) );
        right = ahead.cross(float3(0, 1, 0)).normalize();
        up = right.cross(ahead);
        lookAt = eye + ahead;
    }
    
    void setAspectRatio(float ar)  {
        aspect = ar;
    }
    
    void apply()
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(fov / 3.14 * 180, aspect, 0.1, 200);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(eye.x, eye.y, eye.z, eye.x+ahead.x, eye.y+ahead.y, eye.z+ahead.z, 0.0, 1.0, 0.0);
    }
};

#endif
