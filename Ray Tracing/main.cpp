//
//  main.cpp
//  Ray Tracing
//
//  Created by Jon Atkins on 11/13/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>

#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#include <float.h>
#include "float2.h"
#include "float3.h"
#include "float4.h"
#include "float4x4.h"
#include <vector>
#include <algorithm>

#include "perlin.h"
#include "Lightsource.h"
#include "Material.h"
#include "Scene.h"
#include "Camera.h"

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

// screen resolution
const int screenWidth = 600;
const int screenHeight = 600;
// image to be computed by ray tracing
float3 image[screenWidth*screenHeight];

Scene scene;

bool computeImage()
{
    static unsigned int iPart = 0;
    
    if(iPart >= 64)
        return false;
    for(int j = iPart; j < screenHeight; j+=64)
    {
        for(int i = 0; i < screenWidth; i++)
        {
            float3 pixelColor = float3(0, 0, 0);
            float2 ndcPixelCentre( (2.0 * i - screenWidth) / screenWidth, (2.0 * j - screenHeight) / screenHeight );
            
            Camera& camera = scene.getCamera();
            Ray ray = Ray(camera.getEye(), camera.rayDirFromNdc(ndcPixelCentre));
            
            image[j*screenWidth + i] = scene.trace(ray, 0);
        }
    }
    iPart++;
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL starts here. In the ray tracing example, OpenGL just outputs the image computed to the array.

// display callback invoked when window needs to be redrawn
void onDisplay( ) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear screen
    
    if(computeImage())
        glutPostRedisplay();
    glDrawPixels(screenWidth, screenHeight, GL_RGB, GL_FLOAT, image);
    
    glutSwapBuffers(); // drawing finished
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);						// initialize GLUT
    glutInitWindowSize(600, 600);				// startup window size 
    glutInitWindowPosition(100, 100);           // where to put window on screen
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);    // 8 bit R,G,B,A + double buffer + depth buffer
    
    glutCreateWindow("Ray Tracing");				// application window is created and displayed
    
    glViewport(0, 0, screenWidth, screenHeight);
    
    glutDisplayFunc(onDisplay);					// register callback
    
    glutMainLoop();								// launch event handling loop
    
    return 0;
}

