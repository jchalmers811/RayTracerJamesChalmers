#include "Scene.h"

#include "Colour.h"
#include "ImageDisplay.h"
#include "utility.h"

#include <cmath>

Scene::Scene() : backgroundColour(0,0,0), maxRayDepth(3), renderWidth(800), renderHeight(600), filename("render.png"), camera_(), objects_(), lights_() {

}

Scene::~Scene() {

}

void Scene::render() const {
	ImageDisplay display("Render", renderWidth, renderHeight);
	
	std::cout << "Rendering a scene with " << objects_.size() << " objects" << std::endl;
	
	const double w = double(renderWidth);
	const double h = double(renderHeight);

	for (unsigned int v = 0; v < renderHeight; ++v) {
		for (unsigned int u = 0; u < renderWidth; ++u) {
			double cu = -1 + (u + 0.5)*(2.0 / w);
			double cv = -h/w + (v + 0.5)*(2.0 / w);
			Ray ray = camera_->castRay(cu, cv);
			display.set(u, v, computeColour(ray, maxRayDepth));
		}
		display.refresh();
	}

	display.save(filename);
	display.pause(5);
}

RayIntersection Scene::intersect(const Ray& ray) const {
	RayIntersection firstHit;
	firstHit.distance = infinity;	
	for (auto& obj : objects_) {
		for (auto& hit : obj->intersect(ray)) {
			if (hit.distance > epsilon && hit.distance < firstHit.distance) {
				firstHit = hit;
			}
		}
	}	return firstHit;
}

Colour Scene::computeColour(const Ray& ray, unsigned int rayDepth) const {
	RayIntersection hitPoint = intersect(ray);
	if (hitPoint.distance == infinity) {
		return backgroundColour;
	}

	Colour hitColour(0, 0, 0);
		
	// Code to do better lighting, shadows, and reflections goes here.
    for (auto light: lights_) {
        // Compute the influence of this light on the appearance of the hit object.
		if (light->getDistanceToLight(hitPoint.point) < 0) {
			// An ambient light, ignore shadows and add appropriate colour
			hitColour += light->getIlluminationAt(hitPoint.point) * hitPoint.material.ambientColour;
        } else {
            
            
            //get direction to light source and normalise
            Vector lightDirection = -1 * light->getLightDirection(hitPoint.point);
            Vector unitLightDirection = lightDirection / lightDirection.norm();
            
            //get unit normal vector from hitpoint
            Vector unitNormalFromHitPoint = hitPoint.normal / hitPoint.normal.norm();
            
            //reflection about normal for specular lighting
            Vector reflectionAboutNormal = 2*(unitNormalFromHitPoint.dot(unitLightDirection))*unitNormalFromHitPoint - unitLightDirection;
            Vector unitReflectionAboutNormal = reflectionAboutNormal/reflectionAboutNormal.norm();
            
            // get view direction and normalise for sepcular lighting
            Vector viewDirection = -1 * ray.direction;
            Vector unitViewDirection = viewDirection/viewDirection.norm();
           
            //cast shadow ray from hitpoint toward light source
            Ray shadowRay;
            shadowRay.point = hitPoint.point;
            shadowRay.direction = lightDirection;
            
            //only light if first intersection is at or after the light source
            if (intersect(shadowRay).distance >= light->getDistanceToLight(hitPoint.point)) {
            
                //diffuse lighting
                if (unitLightDirection.dot(unitNormalFromHitPoint) > 0) {
                    
                    //calculate diffuse lighting
                    hitColour += (light->getIlluminationAt(hitPoint.point) * hitPoint.material.diffuseColour) * (unitLightDirection.dot(unitNormalFromHitPoint));
                }
                
                //specular lighting
                if (unitReflectionAboutNormal.dot(unitViewDirection) > 0 || hitPoint.material.specularExponent == 0) {
                    
                    //calculate specular lighting
                    hitColour += (light->getIlluminationAt(hitPoint.point) * hitPoint.material.specularColour) * pow((unitReflectionAboutNormal.dot(unitViewDirection)), hitPoint.material.specularExponent);
                    
                }
            
            }
        }
        
        
    }

    //mirror calculations here
    
    //get unit normal vector from hitpoint
    Vector unitNormalFromHitPoint = hitPoint.normal / hitPoint.normal.norm();
    
    //get view direction and normalise
    Vector viewDirection = -1 * ray.direction;
    Vector unitViewDirection = viewDirection/viewDirection.norm();
    
    //cast mirror ray
    Ray mirrorRay;
    mirrorRay.point = hitPoint.point;
    mirrorRay.direction = 2*(unitNormalFromHitPoint.dot(unitViewDirection)) * unitNormalFromHitPoint - unitViewDirection;
    
    //call computeColour recursively to calculate reflections
    hitColour += hitPoint.material.mirrorColour * computeColour(mirrorRay, rayDepth - 1);
    
	hitColour.clip();
	return hitColour;
}

    
bool Scene::hasCamera() const {
	return bool(camera_);
}
