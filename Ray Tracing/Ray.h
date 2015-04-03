//
//  Ray.h
//  Ray Tracing
//
//  Created by Jon Atkins on 11/19/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#pragma once

#include <stdio.h>
#include "float3.h"

// Ray structure
class Ray
{
public:
    float3 origin;
    float3 dir;
    Ray(float3 o, float3 d)
    {
        origin = o;
        dir = d;
    }
};
