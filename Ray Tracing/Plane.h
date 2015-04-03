//
//  Plane.h
//  Ray Tracing
//
//  Created by Jon Atkins on 11/19/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#include <stdio.h>
#include "Intersectable.h"

class Plane : public Intersectable {
    //normal vector
    float3 planeNormal;
    //point on plane
    float3 x0;
public:
    
    Plane(float3 n, float3 x0, Material* material):
    Intersectable(material),
    planeNormal(n),
    x0(x0)
    {
    }
    
    Hit intersect(const Ray& ray) {
        
        float numer = (x0 - ray.origin).dot(planeNormal);
        float denom = ray.dir.dot(planeNormal);
        
        Hit h;
        
        if (denom == 0)
            h.t = -1;
        
        else
            h.t = numer/denom;
        h.material = material;
        h.position = ray.origin + ray.dir * h.t;
        h.normal = planeNormal;
        h.normal.normalize();
        
        return h;
    }
    
};