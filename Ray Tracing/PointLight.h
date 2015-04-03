//
//  PointLight.h
//  Ray Tracing
//
//  Created by Jon Atkins on 11/13/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#include <stdio.h>

class PointLight : public LightSource {
    float3 position; // position vector
    float3 power; // RGB vector
    
public:
    PointLight(float3 position, float3 power) {
        this->position = position;
        this->power = power;
    }
    float3 getPowerDensityAt(float3 x) {
        return power * 1 / (4 * M_PI * ((position - x).dot(position - x)));
    }
    float3 getLightDirAt(float3 x) {
        return (position - x).normalize();
    }
    float getDistanceFrom(float3 x) {
        return (position - x).norm();
    }
};
