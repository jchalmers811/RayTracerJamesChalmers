#include "Plane.h"

#include "utility.h"

Plane::Plane() : Object() {

}

Plane::Plane(const Plane& plane) : Object(plane) {

}

Plane::~Plane() {

}

const Plane& Plane::operator=(const Plane& plane) {
	if (this != &plane) {
		Object::operator=(plane);
	}
	return *this;
}

std::vector<RayIntersection> Plane::intersect(const Ray& ray) const {

	std::vector<RayIntersection> result;

	/******************************************************
	 * Code to compute Ray-Plane intersections goes here. *
	 ******************************************************/
    
    //inverse ray instead of image
    Ray inverseRay = transform.applyInverse(ray);
    
    //get direction and origin of the z component of the ray
    double dz = inverseRay.direction(2);
    double z0 = inverseRay.point(2);
    
    //check for devision by zero (or very small number, epsilon) before calculating t
    if (std::abs(dz) > epsilon) {
        
        double t = -z0 / dz;
        
        //check if hit is in front of ray
        if (t > epsilon) {
            //hit is in front of ray
            RayIntersection hit;
            hit.point = inverseRay.point + t*inverseRay.direction;
            //checking bounds in X and Y to ensure in range (-1, 1)
            if (abs(hit.point(0)) <= 1 && abs(hit.point(1)) <= 1) {
                // In square region -- Compute hit point details
                hit.point = transform.apply(hit.point);
                hit.material = material;
                //normal along Z axis
                hit.normal = transform.apply(Normal(0, 0, 1));
                if (hit.normal.dot(ray.direction) > 0) {
                    hit.normal = -hit.normal;
                }
                hit.distance = (hit.point - ray.point).norm();
                result.push_back(hit);
            }
        }
    }
    
    /******************************************************
     * Added code ends                                    *
     ******************************************************/

	return result;
}
