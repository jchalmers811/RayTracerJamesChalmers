/* $Rev: 250 $ */
#include "Cube.h"

#include "utility.h"

Cube::Cube() : Object() {

}

Cube::Cube(const Cube& cube) : Object(cube) {

}

Cube::~Cube() {

}

const Cube& Cube::operator=(const Cube& cube) {
	if (this != &cube) {
		Object::operator=(cube);
	}
	return *this;
}

std::vector<RayIntersection> Cube::intersect(const Ray& ray) const {

	std::vector<RayIntersection> result;

	/*****************************************************
	 * Code to compute Ray-Cube intersections goes here. *
	 *****************************************************/
    
     //inverse ray instead of image
    Ray inverseRay = transform.applyInverse(ray);
    
    //get direction and origin of the z component of the ray
    double dz = inverseRay.direction(2);
    double z0 = inverseRay.point(2);

    //get direction and origin of the y component of the ray
    double dy = inverseRay.direction(1);
    double y0 = inverseRay.point(1);
 
    //get direction and origin of the x component of the ray
    double dx = inverseRay.direction(0);
    double x0 = inverseRay.point(0);
 
    //check for devision by zero (or very small number, epsilon) before calculating t
    if (std::abs(dz) > epsilon) {
        double tFront = -(z0 - 1)/ dz;
        double tBack = -(z0 + 1)/ dz;
        
        if (tFront > epsilon) {
            //hit is in front of ray
            RayIntersection hit;
            hit.point = inverseRay.point + tFront*inverseRay.direction;
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
        
        if (tBack> epsilon) {
            //hit is in front of ray
            RayIntersection hit;
            hit.point = inverseRay.point + tBack*inverseRay.direction;
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
    
    //check for devision by zero (or very small number, epsilon) before calculating t
    if (std::abs(dy) > epsilon) {
        double tTop = -(y0 - 1) / dy;
        double tBottom = -(y0 + 1) / dy;

      
        if (tTop > epsilon) {
            //hit is in front of ray
            RayIntersection hit;
            hit.point = inverseRay.point + tTop*inverseRay.direction;
            //checking bounds in X and Z to ensure in range (-1, 1)
            if (abs(hit.point(0)) <= 1 && abs(hit.point(2)) <= 1) {
                // In square region -- Compute hit point details
                hit.point = transform.apply(hit.point);
                hit.material = material;
                 //normal along Y axis
                hit.normal = transform.apply(Normal(0, 1, 0));
                if (hit.normal.dot(ray.direction) > 0) {
                    hit.normal = -hit.normal;
                }
                hit.distance = (hit.point - ray.point).norm();
                result.push_back(hit);
            }
        }
        
        if (tBottom> epsilon) {
            //hit is in front of ray
            RayIntersection hit;
            hit.point = inverseRay.point + tBottom*inverseRay.direction;
            //checking bounds in X and Z to ensure in range (-1, 1)
            if (abs(hit.point(0)) <= 1 && abs(hit.point(2)) <= 1) {
                // In square region -- Compute hit point details
                hit.point = transform.apply(hit.point);
                hit.material = material;
                //normal along Y axis
                hit.normal = transform.apply(Normal(0, 1, 0));
                if (hit.normal.dot(ray.direction) > 0) {
                    hit.normal = -hit.normal;
                }
                hit.distance = (hit.point - ray.point).norm();
                result.push_back(hit);
            }
        }
        
        
        
    }
    
    //check for devision by zero (or very small number, epsilon) before calculating t
    if (std::abs(dx) > epsilon) {
        double tSide1 = -(x0 - 1) / dx;
        double tSide2 = -(x0 + 1) / dx;
        
        if (tSide1 > epsilon) {
            //hit is in front of ray
            RayIntersection hit;
            hit.point = inverseRay.point + tSide1*inverseRay.direction;
            //checking bounds in Y and Z to ensure in range (-1, 1)
            if (abs(hit.point(1)) <= 1 && abs(hit.point(2)) <= 1) {
                // In square region -- Compute hit point details
                hit.point = transform.apply(hit.point);
                hit.material = material;
                //normal along X axis
                hit.normal = transform.apply(Normal(1, 0, 0));
                if (hit.normal.dot(ray.direction) > 0) {
                    hit.normal = -hit.normal;
                }
                hit.distance = (hit.point - ray.point).norm();
                result.push_back(hit);
            }
        }
        
        if (tSide2> epsilon) {
            //hit is in front of ray
            RayIntersection hit;
            hit.point = inverseRay.point + tSide2*inverseRay.direction;
            //checking bounds in Y and Z to ensure in range (-1, 1)
            if (abs(hit.point(1)) <= 1 && abs(hit.point(2)) <= 1) {
                // In square region -- Compute hit point details
                hit.point = transform.apply(hit.point);
                hit.material = material;
                //normal along X axis
                hit.normal = transform.apply(Normal(1, 0, 0));
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
