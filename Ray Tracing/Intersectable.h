//
//  Intersectable.h
//  Ray Tracing
//
//  Created by Jon Atkins on 11/19/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#pragma once

#include <stdio.h>
#include "Hit.h"
#include "Ray.h"
#include "float4x4.h"

enum QuadricType { ellipsoid, parabaloid, cone, cylinder };

// Object abstract base class.
class Intersectable
{
protected:
    Material* material;
public:
    Intersectable(Material* material):material(material) {}
    virtual Hit intersect(const Ray& ray)=0;
};