//
//  main.cpp
//  RayTracingPractical
//
//  Created by Kevin Nguyen on 11/13/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//
//
//  main.cpp
//  RayTracing
//
//  Created by Kevin Nguyen on 11/13/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
// Needed on MsWindows
#define NOMINMAX
#include <windows.h>
#endif // Win32 platform

#include <iostream>
// Download glut from: http://www.opengl.org/resources/libraries/glut/
#include <GLUT/glut.h>
#include "float.h"
#include <map>


#include "float2.h"
#include "float3.h"
#include "float4.h"
#include "float4x4.h"
#include <vector>
#include <algorithm>
#include "Material.h"
#include "Hit.h"
#include "Camera.h"
#include "perlin.h"
#include "LightSource.h"
#include "Ray.h"
#include "Intersectable.h"

// use of it in TexturedMaterial
extern "C" unsigned char* stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);

#include "TexturedMaterial.h"
#include "Object.h"
#include "Teapot.h"
#include "Mesh.h"
#include "holeSnowMan.h"
#include "Cone.h"
#include "Quadric.h"
#include "Plane.h"
#include "ClippedQuadric.h"
#include "parabloidsExperiment.h"
#include "Parabloids.h"
#include "MeshInstance.h"
#include "Bouncer.h"
#include "Ground.h"
#include "Billboard.h"
#include "Scene.h"



using namespace std;

// For procedural texturing
Perlin perlin;
// for quadrics, so that we do not need a float4.cpp
const float4x4 float4x4::identity(
                                  1, 0, 0, 0,
                                  0, 1, 0, 0,
                                  0, 0, 1, 0,
                                  0, 0, 0, 1);



////////////////////////////////////////////////////////////////////////////////////////////////////////
// global application data


std::vector<bool> keysPressed;

// screen resolution
const int screenWidth = 600;
const int screenHeight = 600;
// image to be computed by ray tracing
float3 image[screenWidth*screenHeight];

Scene scene;

//bool computeImage()
//{
//    static unsigned int iPart = 0;
//    int depth = 5;
//    
//    if(iPart >= 64)
//        return false;
//    for(int j = iPart; j < screenHeight; j+=64)
//    {
//        for(int i = 0; i < screenWidth; i++)
//        {
//            float3 pixelColor = float3(0, 0, 0);
//            float2 ndcPixelCentre( (2.0 * i - screenWidth) / screenWidth, (2.0 * j - screenHeight) / screenHeight );
//            
//            Camera& camera = scene.getCamera();
//            Ray ray = Ray(camera.getEye(), camera.rayDirFromNdc(ndcPixelCentre));
//            
//            image[j*screenWidth + i] = scene.trace(ray, depth);
//        }
//    }
//    iPart++;
//    return true;
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL starts here. In the ray tracing example, OpenGL just outputs the image computed to the array.

// display callback invoked when window needs to be redrawn
// Displays the image.
void onDisplay( ) {
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear screen
    
    scene.draw();
    
    glutSwapBuffers(); // drawing finished
}

void onIdle() {
    double t = glutGet(GLUT_ELAPSED_TIME) * 0.001;
    static double lastTime = 0.0;
    double dt = t - lastTime;
    lastTime = t;
    
    scene.getCamera().move(dt, keysPressed);
    scene.control(keysPressed);
    scene.move(t,dt);
    glutPostRedisplay();
}

void onKeyboard(unsigned char key, int x, int y) {
    keysPressed.at(key) = true;
}

void onKeyboardUp(unsigned char key, int x, int y) {
    keysPressed.at(key) = false;
}

void onMouse(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON)
        if(state == GLUT_DOWN)
            scene.getCamera().startDrag(x, y);
        else
            scene.getCamera().endDrag();
}

void onMouseMotion(int x, int y) {
    scene.getCamera().drag(x, y);
}

void onReshape(int winWidth, int winHeight) {
    glViewport(0, 0, winWidth, winHeight);
    scene.getCamera().setAspectRatio(
                                     (float)winWidth/winHeight);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);						// initialize GLUT
    glutInitWindowSize(screenWidth, screenHeight);				// startup window size
    glutInitWindowPosition(100, 100);           // where to put window on screen
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);    // 8 bit R,G,B,A + double buffer + depth buffer
    
    glutCreateWindow("OpenGL teapots");				// application window is created and displayed
    
    glViewport(0, 0, screenWidth, screenHeight);
    
    glutKeyboardFunc(onKeyboard);
    glutKeyboardUpFunc(onKeyboardUp);
    for(int i=0; i<256; i++)
        keysPressed.push_back(false);
    
    glutDisplayFunc(onDisplay);					// register callback
    glutMouseFunc(onMouse);
    glutMotionFunc(onMouseMotion);
    // not working?
    glutIdleFunc(onIdle);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    // reshapefunc or reshapewindow func?
    glutReshapeFunc(onReshape);
    scene.initialize();
    
    glutMainLoop();								// launch event handling loop
    
    return 0;
}