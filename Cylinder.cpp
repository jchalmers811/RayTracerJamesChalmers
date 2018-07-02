#include "Cylinder.h"

#include "utility.h"

Cylinder::Cylinder() : Object() {

}

Cylinder::Cylinder(const Cylinder& cylinder) : Object(cylinder) {

}

Cylinder::~Cylinder() {

}

const Cylinder& Cylinder::operator=(const Cylinder& cylinder) {
	if (this != &cylinder) {
		Object::operator=(cylinder);
	}
	return *this;
}

std::vector<RayIntersection> Cylinder::intersect(const Ray& ray) const {

	std::vector<RayIntersection> result;

	/*********************************************************
	 * Code to compute Ray-Cylinder intersections goes here. *
	 *********************************************************/
    
    //inverse ray instead of image
    Ray inverseRay = transform.applyInverse(ray);
    
    const Point& p = inverseRay.point;
    const Direction& d = inverseRay.direction;
   
    //get direction and origin of the z component of the ray
    double dz = inverseRay.direction(2);
    double z0 = inverseRay.point(2);
    
    //get direction and origin of the y component of the ray
    double dy = inverseRay.direction(1);
    double y0 = inverseRay.point(1);
    
    //get direction and origin of the x component of the ray
    double dx = inverseRay.direction(0);
    double x0 = inverseRay.point(0);
    
    
    double a = dx*dx + dy*dy;
    double b = 2 * dx * x0 + 2 * dy * y0;
    double c = x0*x0 + y0*y0 - 1;
    
    RayIntersection hit;
    hit.material = material;
    
    double b2_4ac = b*b - 4*a*c;
    double t;
    switch (sign(b2_4ac)) {
        case -1:
            // No intersections
            break;
        case 0:
            // One intersection
            t = -b/(2*a);
            if (t > 0) {
                // Intersection is in front of the ray's start point
                double zLimit = z0 + t * dz;
                // Make cylinder finite along Z axis
                if (abs(zLimit) <= 1) {
                    hit.point = transform.apply(Point(p + t*d));
                    
                    //get normal for sphere and make z component 0
                    Normal cylinderNormal = p + t*d;
                    cylinderNormal(2) = 0;
                    hit.normal = transform.apply(cylinderNormal);
                    
                    if (hit.normal.dot(ray.direction) > 0) {
                        hit.normal = -hit.normal;
                    }
                    hit.distance = (hit.point - ray.point).norm();
                    result.push_back(hit);
                }
                
            }
            break;
        case 1:
            // Two intersections
            t = (-b + sqrt(b*b - 4*a*c))/(2*a);
            if (t > 0) {
                // Intersection is in front of the ray's start point
                
                double zLimit = z0 + t * dz;
                
                // Make cylinder finite along Z axis
                if (abs(zLimit) <= 1) {
                    hit.point = transform.apply(Point(p + t*d));
                    
                    //get normal for sphere and make z component 0
                    Normal cylinderNormal = p + t*d;
                    cylinderNormal(2) = 0;
                    hit.normal = transform.apply(cylinderNormal);
                  
                    if (hit.normal.dot(ray.direction) > 0) {
                        hit.normal = -hit.normal;
                    }
                    hit.distance = (hit.point - ray.point).norm();
                    result.push_back(hit);
                }
            }
            
            t = (-b - sqrt(b*b - 4*a*c))/(2*a);
            if (t > 0) {
                // Intersection is in front of the ray's start point
                
                double zLimit = z0 + t * dz;
                
                // Make cylinder finite along Z axis
                if (abs(zLimit) <= 1) {
                    hit.point = transform.apply(Point(p + t*d));
                    
                    //get normal for sphere and make z component 0
                    Normal cylinderNormal = p + t*d;
                    cylinderNormal(2) = 0;
                    hit.normal = transform.apply(cylinderNormal);
                    
                    if (hit.normal.dot(ray.direction) > 0) {
                        hit.normal = -hit.normal;
                    }
                    hit.distance = (hit.point - ray.point).norm();
                    result.push_back(hit);
                }
            }
            break;
        default:
            // Shouldn't be possible, but just in case
            std::cerr << "Something's wrong - sign(x) should be -1, +1 or 0" << std::endl;
            exit(-1);
            break;
    }
    
    
    //calculations for top and bottom caps of cylinder
    
    //check for devision by zero (or very small number, epsilon) before calculating t
    if (std::abs(dz) > epsilon) {
        double tFront = -(z0 - 1)/ dz;
        double tBack = -(z0 + 1)/ dz;
        
        if (tFront > epsilon) {
            //hit is in front of ray
    
            hit.point = inverseRay.point + tFront*inverseRay.direction;
            //checking bounds in X and Y to ensure in range (-1, 1)
            if (hit.point(0)*hit.point(0) + hit.point(1)*hit.point(1) <= 1 ) {
                // In square region -- Compute hit point details
                hit.point = transform.apply(hit.point);
            
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
            
            hit.point = inverseRay.point + tBack*inverseRay.direction;
            
            //checking bounds in X and Y to ensure in range (-1, 1)
            if (hit.point(0)*hit.point(0) + hit.point(1)*hit.point(1) <= 1 ) {
                // In square region -- Compute hit point details
                hit.point = transform.apply(hit.point);
               
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
        
        
    
	return result;
}
