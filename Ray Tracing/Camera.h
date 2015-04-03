//
//  Camera.h
//  Ray Tracing
//
//  Created by Jon Atkins on 11/19/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#pragma once

#include <stdio.h>
#include "float2.h"
#include "float3.h"

// Skeletal Camera class. Feel free to add custom initialization, set aspect ratio to fit viewport dimensions, or animation.
class Camera
{
    float3 eye;
    
    float3 lookAt;
    float3 right;
    float3 up;
    
public:
    float3 getEye()
    {
        return eye;
    }
    Camera()
    {
        eye = float3(0, 0, 20);
        lookAt = float3(0, 0, 2);
        right = float3(3, 0, 0);
        up = float3(0, 3, 0);
    }
    
    float3 rayDirFromNdc(const float2 ndc) {
        return (lookAt - eye
                + right * ndc.x
                + up    * ndc.y
                ).normalize();
    }
};