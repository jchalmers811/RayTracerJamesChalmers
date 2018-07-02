#include "DirectionalLightSource.h"
#include "utility.h"

DirectionalLightSource::DirectionalLightSource(const Colour& colour, const Direction& direction) :
	LightSource(colour), direction_(direction) {

}

DirectionalLightSource::DirectionalLightSource(const DirectionalLightSource& lightSource) :
	LightSource(lightSource), direction_(lightSource.direction_) {

}

DirectionalLightSource::~DirectionalLightSource() {

}

const DirectionalLightSource& DirectionalLightSource::operator=(const DirectionalLightSource& lightSource) {
	if (this != &lightSource) {
		LightSource::operator=(lightSource);
		direction_ = lightSource.direction_;
	}
	return *this;
}


Colour DirectionalLightSource::getIlluminationAt(const Point& point) const {
    
    //illumination is completely even
	return colour_;
}


double DirectionalLightSource::getDistanceToLight(const Point& point) const {

    //distance approximated to infinity
	return infinity;
}

Direction DirectionalLightSource::getLightDirection(const Point& point) const {

    //direction already set
	return direction_;
}
