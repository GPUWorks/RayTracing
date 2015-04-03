//
//  Lightsource.h
//  Ray Tracing
//
//  Created by Jon Atkins on 11/13/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#pragma once

#include <stdio.h>

class LightSource
{
public:
    virtual float3 getPowerDensityAt ( float3 x )=0;
    virtual float3 getLightDirAt     ( float3 x )=0;
    virtual float  getDistanceFrom   ( float3 x )=0;
};