#include "SpotLightSource.h"

#include "utility.h"

SpotLightSource::SpotLightSource(const Colour& colour, const Point& location, const Direction& direction, double angle) :
	LightSource(colour), location_(location), direction_(direction), angle_(angle) {

}




SpotLightSource::SpotLightSource(const SpotLightSource& lightSource) :
LightSource(lightSource),  location_(lightSource.location_), direction_(lightSource.direction_), angle_(lightSource.angle_) {

}


SpotLightSource::~SpotLightSource() {

}

const SpotLightSource& SpotLightSource::operator=(const SpotLightSource& lightSource) {
	if (this != &lightSource) {
		LightSource::operator=(lightSource);
		location_ = lightSource.location_;
		direction_ = lightSource.direction_;
		angle_ = lightSource.angle_;
	}
	return *this;
}

Colour SpotLightSource::getIlluminationAt(const Point& point) const {
    Colour colour(0,0,0);
    
	
    double distance = (location_ - point).norm();
    
    //make sure distance is above or equal to episilon
    if (distance < epsilon) distance = epsilon;
    
    //get and normalise direction of light and direction from light
    Direction directionOfLight = direction_/direction_.norm();
    Direction directionFromLight = getLightDirection(point)/getLightDirection(point).norm();
  
    //only add lighting if within set angle
    if (directionOfLight.dot(directionFromLight) >= cos(deg2rad(angle_))) {
        colour = (1.0 / (distance*distance)) * colour_;
    }
    
    return colour;
}

double SpotLightSource::getDistanceToLight(const Point& point) const {

    //same calculation as point light
	return (location_ - point).norm();
}

Direction SpotLightSource::getLightDirection(const Point& point) const {


    //same calculation as point light
	return point - location_;
}

