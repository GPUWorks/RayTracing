//
//  Hit.h
//  Ray Tracing
//
//  Created by Jon Atkins on 11/19/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#pragma once
#include <stdio.h>

// Hit record structure. Contains all data that describes a ray-object intersection point.
class Hit
{
public:
    Hit()
    {
        t = -1;
    }
    float t;
    float3 position;
    float3 normal;
    Material* material;
};

