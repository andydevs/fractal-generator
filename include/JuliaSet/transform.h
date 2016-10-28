//-----------------------------------------------------------------------------------
// Program: JuliaSet
// 
// Generates Julia set images
//
// Author:  Anshul Kharbanda
// Created: 8 - 14 - 2016
//-----------------------------------------------------------------------------------

#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

// Libraries being used
#include <pugixml-1.7/src/pugixml.hpp>
#include <complex>

/**
 * Contains functions and structs used by JuliaSet algorithm
 * 
 * @author  Anshul Kharbanda
 * @created 8 - 17 - 2016
 */
namespace juliaset
{
	/**
	 * The complex space scale value
	 */
	const double SCALE = 4.0;

	/**
	 * Default zoom
	 */
	const double DEFAULT_ZOOM = 1.0;

	/**
	 * Default offset
	 */
	const std::complex<double> DEFAULT_OFFSET(0,0);

	/**
	 * Default rotation
	 */
	const double DEFAULT_ANGLE = 0;

	/**
	 * Image transform parameters
	 *
	 * @author  Anshul Kharbanda
	 * @created 8 - 16 - 2016
	 */
	struct Transform
	{
		/**
		 * The width of the image
		 */
		unsigned width;

		/**
		 * The height of the image
		 */
		unsigned height;

		/**
		 * The zoom scale of the image
		 */
		double zoom;

		/**
		 * The offset of the image
		 */
		std::complex<double> offset;

		/**
		 * The shift complex
		 */
		std::complex<double> shift;

		/**
		 * The rotation complex
		 */
		std::complex<double> rotation;

		/**
		 * Creates an empty transform
		 */
		Transform();

		/**
		 * Creates a default transform with the given parameters
		 *
		 * @param w the width of the image
		 * @param h the height of the image
		 */
		Transform(unsigned w, unsigned h);

		/**
		 * Creates a transform with the given parameters
		 *
		 * @param w the width of the image
		 * @param h the height of the image
		 * @param z the zoom scale of the image
		 * @param x the x offset of the image
		 * @param y the y offset of the image
		 * @param a the rotation angle of the image
		 */
		Transform(unsigned w, unsigned h, double z, double x, double y, double a);

		/**
		 * Creates a transform with the given dimension xml
		 *
		 * @param dimension the dimension xml
		 */
		Transform(pugi::xml_node dimension);

		/**
		 * Creates a transform with the given dimension and transform xml
		 *
		 * @param dimension the dimension xml
		 * @param transform the transform xml
		 */
		Transform(pugi::xml_node dimension, pugi::xml_node transform);

		/**
		 * Copy constructor for transform
		 *
		 * @param other the other transform to copy
		 */
		Transform(const Transform& other);

		/**
		 * Returns the complex number mapped at the given pixel by the transform
		 *
		 * @param x the x coord of the pixel
		 * @param y the y coord of the pixel
		 *
		 * @return the complex number mapped at the given pixel by the transform
		 */
		std::complex<double> operator()(const double& x, const double& y);
	};
}

#endif