//
//  ClippedQuadric.h
//  Ray Tracing
//
//  Created by Jon Atkins on 11/21/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#pragma once

#include <stdio.h>
#include "Intersectable.h"

class ClippedQuadric : public Intersectable {
    float4x4 A;
    float4x4 B;
    
public:
    ClippedQuadric(Material* material, QuadricType type): Intersectable(material) {
        //figure out Quadric Type
        switch (type) {
            case ellipsoid:
                A = float4x4::identity;
                A._11 = 1;
                A._33 = -4;
                break;
            case parabaloid:
                fprintf(stderr, "type == parabaloid");
                exit(1);
                break;
            case cone:
                A = float4x4::identity;
                A._00 = -1;
                A._33 = 0;
                
                B = float4x4::identity;
                B._30 = -2;
                B._33 = 0;
                break;
            case cylinder:
                A = float4x4::identity;
                A._00 = 0;
                A._33 = -1;
                
                //centered sphere
                B = float4x4::identity;
                B._33 = -2;
                break;
            default:
                fprintf(stderr, "type not recognized");
                exit(1);
                break;
        }

        // sphere or radius 2 hardwired

    }
    
    Hit intersect(const Ray& ray) {
        //ray in homo coords
        float4 e = float4(ray.origin.x, ray.origin.y, ray.origin.z, 1);
        float4 d = float4(ray.dir.x, ray.dir.y, ray.dir.z, 0);
        
        //quadratic coeffs
        double a = d.dot(A * d);
        double b = e.dot(A * d) + d.dot(A * e);
        double c = e.dot(A * e);
        
        double discr = b * b - 4.0 * a * c;
        if ( discr < 0 )
            return Hit();
        double sqrt_discr = sqrt( discr );
        double t1 = (-b + sqrt_discr)/2.0/a;
        double t2 = (-b - sqrt_discr)/2.0/a;
        
        // get t1, t2 for quadric A
        
        float4 hit1 = e + d * t1;
        if(hit1.dot(B * hit1) > 0) // if not in B
            t1 = -1;            // invalidate
        float4 hit2 = e + d * t2;
        if(hit2.dot(B * hit2) > 0) // if not in B
            t2 = -1; 			// invalidate
  
        float t = (t1<t2)?t1:t2;
        if(t < 0)
            t = (t1<t2)?t2:t1;
        if (t < 0)
            return Hit();
        
        Hit h;
        h.t = t;
        h.material = material;
        h.position = ray.origin + ray.dir * t;
        // homo position
        float4 hPos = float4(h.position.x,
                             h.position.y, h.position.z, 1);
        // homo normal per quadric normal formula
        float4 hNormal = A * hPos +  hPos * A;
        // Cartesian normal
        h.normal = float3(hNormal.x, hNormal.y, hNormal.z).normalize();
        
        h.normal.normalize();
        
        return h;
    }
    
    void rotate(float3 axis, float angle) {
        A = float4x4::rotation(axis, -angle) * A * float4x4::rotation(axis, angle);
        B = float4x4::rotation(axis, -angle) * B * float4x4::rotation(axis, angle);
    }
    
    void translate(const float3 offset) {
        float4x4 translation = float4x4::translation(-offset);
        translation.invert();
        A = translation * A * translation.transpose();
        B = translation * B * translation.transpose();
    }
    
    void scale(const float3 factors) {
        A = float4x4::scaling(factors.invert()) * A;
        B = float4x4::scaling(factors.invert()) * B;
    }
    
    
    
};

