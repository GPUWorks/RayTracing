//
//  Scene.h
//  Ray Tracing
//
//  Created by Jon Atkins on 11/19/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#pragma once

#include <stdio.h>
#include "Camera.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Intersectable.h"
#include "Ray.h"
#include "Hit.h"
#include "Sphere.h"
#include "Plane.h"
#include "Quadric.h"
#include "ClippedQuadric.h"
#include "assert.h"

#define SNOW_MATERIAL false, false, false, float3(0.93, 0.85, 0.4), 1, float3(0.3, 0.3, 0.3), float3(1.0, 1.0, 1.0), 15
#define COPPER_MATERIAL false, false, false, float3(0.93, 0.85, 0.4), 1, float3(0.3, 0.3, 0.3), float3(1.0, 1.0, 1.0), 15
#define CARROT_MATERIAL false, false, false, float3(0.93, 0.85, 0.4), 1, float3(0.3, 0.3, 0.3), float3(1.0, 1.0, 1.0), 15
#define WATER_MATERIAL false, false, false, float3(0.93, 0.85, 0.4), 1, float3(0.3, 0.3, 0.3), float3(1.0, 1.0, 1.0), 15

const float SNOWMAN_DISTANCE = -15;
const int NUM_ICICLES = 25;
const float3 EPSILON = float3(.001, .001, .001);
const int MAX_DEPTH = 5;

class Scene
{
    Camera camera;
    std::vector<LightSource*> lightSources;
    std::vector<Intersectable*> objects;
    std::vector<Material*> materials;
public:
    Scene()
    {   
        // LIGHT SOURCES
    
        lightSources.push_back(new DirectionalLight(float3(4, 10, 10).normalize(), float3(1, 1, 1)));
        lightSources.push_back(new DirectionalLight(float3(-4, 10, 10).normalize(), float3(1, 1, 1)));
//        lightSources.push_back(new DirectionalLight(float3(1, 0, 0).normalize(), float3(1, 1, 1)));
        lightSources.push_back(new PointLight(float3(0, 8, 3), float3(1000, 1000, 1000)));
        
        // MATERIALS
        Material* snow = new Material(false, false, false, float3(0.93, 0.85, 0.4), 1, float3(0.9, 0.9, 0.9), float3(1.0, 1.0, 1.0), 40);
        materials.push_back(snow);
        Material* copper = new Material(false, false, false, float3(0.93, 0.85, 0.4), 1, float3(.722, .451, .200), float3(1.0, 1.0, 1.0), 15);
        materials.push_back(copper);
        Material* carrot = new Material(false, false, false, float3(0.93, 0.85, 0.4), 1, float3(.921, .537, .129), float3(0, 0, 0), 15);
        materials.push_back(carrot);
        Material* blackMatte = new Material(false, false, false, float3(0.93, 0.85, 0.4), 1, float3(0, 0, 0), float3(0, 0, 0), 20);
        materials.push_back(blackMatte);
        Material* redMatte = new Material(false, false, false, float3(0.93, 0.85, 0.4), 1, float3(1, 0, 0), float3(0, 0, 0), 50);
        materials.push_back(redMatte);
        Material* ice = new Material(false, true, false, float3(0.93, 0.85, 0.4), .2, float3(.9, .9, .9), float3(.5, .5, .5), 100);
        materials.push_back(ice);
        
        // OBJECTS
        
        Quadric* legs = new Quadric(snow, ellipsoid);
        Quadric* torso = new Quadric(snow, ellipsoid);
        Quadric* head = new Quadric(snow, ellipsoid);
        ClippedQuadric* hatPot = new ClippedQuadric(copper, cylinder);
        ClippedQuadric* hatHandle = new ClippedQuadric(blackMatte, cylinder);
        ClippedQuadric* nose = new ClippedQuadric(carrot, cone);
        Quadric* leftEye = new Quadric(blackMatte, ellipsoid);
        Quadric* rightEye = new Quadric(blackMatte, ellipsoid);
        Quadric* button1 = new Quadric(redMatte, ellipsoid);
        Quadric* button2 = new Quadric(redMatte, ellipsoid);
        Quadric* button3 = new Quadric(redMatte, ellipsoid);
        
        legs->scale(float3(.8, .8, .8));
        legs->translate(float3(0, -.7, SNOWMAN_DISTANCE));
        objects.push_back(legs);
        
        torso->scale(float3(.6, .6, .6));
        torso->translate(float3(0, 1.4, SNOWMAN_DISTANCE));
        objects.push_back(torso);
        
        head->scale(float3(.4, .4, .4));
        head->translate(float3(0, 2.9, SNOWMAN_DISTANCE));
        objects.push_back(head);
        
        hatPot->rotate(float3(0, 0, 1), 11*M_PI/24);
        hatPot->rotate(float3(0, 0, 0), M_PI/24);
        hatPot->scale(float3(.065, .065, .083));
        hatPot->translate(float3(.1, 3.85, SNOWMAN_DISTANCE));
        objects.push_back(hatPot);
        
        hatHandle->scale(float3(.07, .005, .005));
        hatHandle->rotate(float3(0, 0, 1), -M_PI/24);
        hatHandle->rotate(float3(0, 1, 0), M_PI/6);
        hatHandle->translate(float3(.3, 3.7, SNOWMAN_DISTANCE-.05));
        objects.push_back(hatHandle);
        
        nose->rotate(float3(0, 1, 0), M_PI/2);
        nose->scale(float3(.03, .03, 1));
        nose->translate(float3(0, 2.9, SNOWMAN_DISTANCE + 1.8));
        objects.push_back(nose);
        
        leftEye->scale(float3(.02, .02, .02));
        leftEye->translate(float3(.3, 3.15, SNOWMAN_DISTANCE + 1.54));
        objects.push_back(leftEye);
        
        rightEye->scale(float3(.02, .02, .02));
        rightEye->translate(float3(-.3, 3.15, SNOWMAN_DISTANCE + 1.54));
        objects.push_back(rightEye);
        
        button1->scale(float3(.03, .03, .03));
        button1->translate(float3(0, 1.8, SNOWMAN_DISTANCE + 1.2));
        objects.push_back(button1);
        
        button2->scale(float3(.03, .03, .03));
        button2->translate(float3(0, 1.55, SNOWMAN_DISTANCE + 1.2));
        objects.push_back(button2);
        
        button3->scale(float3(.03, .03, .03));
        button3->translate(float3(0, 1.3, SNOWMAN_DISTANCE + 1.2));
        objects.push_back(button3);
        
        Quadric* icicles[NUM_ICICLES];
        for (int i = 0; i < NUM_ICICLES; i++) {
            icicles[i] = new Quadric(ice, parabaloid);
            icicles[i]->rotate(float3(1, 0, 0), M_PI/2);
            icicles[i]->scale(float3(.2, 1, .2));
            
            float3 translation = float3();
            // -3 <= x <= 3
            translation.x = fmodf(translation.x * 53, 6) - 3;
            // 0 <= y <= 3
            translation.y = fmodf(translation.y * 53, 3);
            if(translation.y < 0)
                translation.y *= -1;
            translation.z = 0;
            //check if the icicle is blocking the view of the screen
            icicles[i]->translate(translation);
            if ((translation.x >= 1.5 || translation.x <= -1.5) || translation.y > 1.5)
                objects.push_back(icicles[i]);
        }
        
        objects.push_back(new Plane(float3(0, 1, 0.1), float3(0, -3, 0), snow));
        
    }
        
    ~Scene()
    {
        for (std::vector<LightSource*>::iterator iLightSource = lightSources.begin(); iLightSource != lightSources.end(); ++iLightSource)
            delete *iLightSource;
        for (std::vector<Material*>::iterator iMaterial = materials.begin(); iMaterial != materials.end(); ++iMaterial)
            delete *iMaterial;
        for (std::vector<Intersectable*>::iterator iObject = objects.begin(); iObject != objects.end(); ++iObject)
            delete *iObject;
    }
    
Camera& getCamera()
    {
        return camera;
    }
    
    // IMPLEMENTED FOR YOUR CONVENIENCE, CALL THIS WHEN APPROPRIATE
    Hit firstIntersect(const Ray& ray)
    {
        Hit bestHit;
        bestHit.t = FLT_MAX;
        for(int oi=0; oi < objects.size(); oi++)
        {
            Hit hit = objects[oi]->intersect(ray);
            if(hit.t > 0 && hit.t < bestHit.t)
                bestHit = hit;
        }
        if(bestHit.t == FLT_MAX)
            return Hit();
        return bestHit;
    }
    
    float3 trace(const Ray& ray, float depth)
    {
        Hit hit = firstIntersect(ray);
        
        //if nothing hit, return sky color
        if(hit.t < 0 || depth > (float)MAX_DEPTH) {
            return float3(0.648, 0.820, 0.926) + ((hit.normal) * cos(hit.t + 2) * cos(hit.t));
//            return float3(0.648, 0.820, 0.926);
        }
        
        float3 outRadiance = float3(0, 0, 0);
        
        //loop through the light sources and sum the contribution of them
        //sum radiance from reflection models here
        for (int i = 0; i < lightSources.size(); i++) {
            //light source provides Li, Mi, |X - Yi|
            Ray shadowRay(hit.position + (hit.normal * EPSILON), lightSources[i]->getLightDirAt(hit.position));
            Hit shadowHit = firstIntersect(shadowRay);
            
            if ((shadowHit.t > 0) && (shadowHit.t < lightSources[i]->getDistanceFrom(hit.position)))
                continue;
            
            outRadiance += hit.material->shade(hit.position, hit.normal, -ray.dir, lightSources[i]->getLightDirAt(hit.position), lightSources[i]->getPowerDensityAt(hit.position));
        }
        if (hit.material) {
            if (hit.material->reflective) {
                float3 reflectionDir = hit.material->reflect(ray.dir, hit.normal);
                Ray reflectedRay(hit.position + (hit.normal * EPSILON), reflectionDir);
                outRadiance += trace(reflectedRay, depth + 1);
            }
            if (hit.material->refractive) {
                float3 refractionDir = hit.material->refract(ray.dir, hit.normal);
                Ray refractedRay(hit.position + (hit.normal * EPSILON), refractionDir);
                outRadiance += trace(refractedRay, depth + 1) * hit.material->refract(ray.dir, hit.normal);
            }
        }
        
        return outRadiance;
    }
};
