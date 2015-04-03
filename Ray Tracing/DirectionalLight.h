//
//  DirectionalLight.h
//  Ray Tracing
//
//  Created by Jon Atkins on 11/13/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#include "Lightsource.h"

class DirectionalLight : public LightSource {
    float3 direction; // direction vector
    float3 powerdensity; // RGB vector
public:
    DirectionalLight(float3 direction, float3 powerdensity) {
        this->direction = direction;
        this->powerdensity = powerdensity;
    }
    float3 getPowerDensityAt(float3) {
        return powerdensity;
    }
    float3 getLightDirAt(float3) {
        return direction;
    }
    float  getDistanceFrom(float3) {
        return FLT_MAX;
    }
};