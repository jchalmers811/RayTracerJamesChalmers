#pragma once

#ifndef LIGHT_SOURCE_H_INCLUDED
#define LIGTH_SOURCE_H_INCLUDED

#include "Colour.h"
#include "Ray.h"

/**
 * \file 
 * \brief LightSource class header file.
 */

/**
 * \brief Abstract base class for LightSources.
 *
 * LightSources provide illumination to the scene. All light sources have a Colour, 
 * but other properties may vary. 
 *
 * As an abstract base class, you cannot create a LightSource directly.
 * Instead one of its concrete subclasses must be created.
 */
class LightSource {

public:

	/** \brief Determine how much light reaches a Point from this LightSource.
	 *
	 * The amount of light emitted by a LightSource is determined by its colour property,
	 * but this generally varies across the Scene. This method returns a scaling factor to
	 * apply to the colour of the light at a given Point in the Scene.
	 *
	 * \param point The Point at which light is measured.
	 * \return The illumination that reaches the Point.
	 */
	virtual Colour getIlluminationAt(const Point& point) const = 0;

	/** \brief Compute the distance from a Point to this LightSource
	 *
	 * \param point The Point from which the distance is measrued.
	 * \return The distance from the Point to the LightSource
	 */
	virtual double getDistanceToLight(const Point& point) const = 0;

	/** \brief Determine the direction from which light from this LightSource falls
	 *
	 * \param point The Point at which to measure the direction.
	 * \return The direction from which light falls on the Point.
	 */
	virtual Direction getLightDirection(const Point& point) const = 0;

protected:

	/** \brief LightSource constructor.
	 *
	 * \param colour The Colour of this LightSource's illumination.
	 */
	LightSource(const Colour& colour);
	
	/** \brief LightSource copy constructor. 
	 *
	 * \param lightSource The LightSource to copy.
	 */
	LightSource(const LightSource& lightSource);
	
	/** \brief LightSource destructor. */
	virtual ~LightSource();
	
	/** \brief LightSource assignment operator. 
	 *
	 * \param lightSource The LightSource to assign to \c this.
	 * \return A reference to \c this to allow for chaining of assignment.
	 */
	const LightSource& operator=(const LightSource& lightSource);

	Colour colour_;  //!< The Colour of this LightSource's illumination.
};

#endif // LIGHT_SOURCE_H_INCLUDED