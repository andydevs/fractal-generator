//-----------------------------------------------------------------------------------
// Program: JuliaSet
// 
// Generates Julia set images
//
// Author:  Anshul Kharbanda
// Created: 8 - 14 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "JuliaSet/transform.h"

// Libraries being used
#include <cmath>

// Libraries being used
using namespace std;

/**
 * Contains functions and structs used by JuliaSet algorithm
 * 
 * @author  Anshul Kharbanda
 * @created 8 - 17 - 2016
 */
namespace juliaset
{
	/**
	 * Creates an empty transform
	 */
	Transform::Transform():
	width(0),height(0),
	zoom(DEFAULT_ZOOM),
	offset(DEFAULT_OFFSET),
	shift(0.5,0.5),
	rotation(1.0,0) {}

	/**
	 * Creates a default transform with the given parameters
	 *
	 * @param w the width of the image
	 * @param h the height of the image
	 */
	Transform::Transform(unsigned w, unsigned h):
	width(w),height(h),
	zoom(DEFAULT_ZOOM),
	offset(DEFAULT_OFFSET),
	shift(0.5,0.5),
	rotation(1.0,0) {}

	/**
	 * Creates a config with the given parameters
	 *
	 * @param w the width of the image
	 * @param h the height of the image
	 * @param z the zoom scale of the image
	 * @param x the x offset of the image
	 * @param y the y offset of the image
	 * @param a the rotation angle of the image
	 */
	Transform::Transform(unsigned w, unsigned h, double z, double x, double y, double a):
	width(w),
	height(h),
	zoom(z),
	offset(x, y),
	shift(0.5*w, 0.5*h),
	rotation(polar(1.0, a * M_PI / 180)) {}

	/**
	 * Creates a transform with the given dimension xml
	 *
	 * @param dimension the dimension xml
	 */
	Transform::Transform(pugi::xml_node dimension):
	width(dimension.attribute("x").as_uint()),
	height(dimension.attribute("y").as_uint()),
	shift(0.5*dimension.attribute("x").as_uint(),0.5*dimension.attribute("y").as_uint()) {}

	/**
	 * Creates a transform with the given dimension and transform xml
	 *
	 * @param dimension the dimension xml
	 * @param transform the transform xml
	 */
	Transform::Transform(pugi::xml_node dimension, pugi::xml_node transform):
	width(dimension.attribute("x").as_uint()),
	height(dimension.attribute("y").as_uint()),
	shift(0.5*dimension.attribute("x").as_uint(),0.5*dimension.attribute("y").as_uint())
	{
		// Get zoom
		if (transform.attribute("zoom"))
			zoom = transform.attribute("zoom").as_double();
		else
			zoom = DEFAULT_ZOOM;

		// Get angle
		if (transform.attribute("angle"))
			rotation = polar(1.0, transform.attribute("angle").as_double());
		else
			rotation = complex<double>(1,0);

		// Get offset
		offset = DEFAULT_OFFSET;
		if (transform.attribute("offx"))
			offset += transform.attribute("offx").as_double();
		if (transform.attribute("offy"))
			offset += complex<double>(0,transform.attribute("offy").as_double());
	}

	/**
	 * Copy constructor for transform
	 *
	 * @param other the other transform to copy
	 */
	Transform::Transform(const Transform& other):
	width(other.width), height(other.height),
	zoom(other.zoom), offset(other.offset),
	shift(other.shift), rotation(other.rotation) {}

	/**
	 * Returns the complex number mapped at the given pixel by the transform
	 *
	 * @param x the x coord of the pixel
	 * @param y the y coord of the pixel
	 *
	 * @return the complex number mapped at the given pixel by the transform
	 */
	complex<double> Transform::operator()(const double& x, const double& y)
	{
		return (SCALE / height / zoom) * (complex<double>(x,y) - shift) * rotation + offset;
	}
}