//-----------------------------------------------------------------------------------
// Program: JuliaSet
// 
// Generates Julia set images
//
// Author:  Anshul Kharbanda
// Created: 8 - 14 - 2016
//-----------------------------------------------------------------------------------

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

// Headers being used
#include "colormap.h"
#include "CImg/CImg.h"

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
	const double DEFAULT_ROATION = 0;

	/**
	 * Image transform parameters
	 *
	 * @author  Anshul Kharbanda
	 * @created 8 - 16 - 2016
	 */
	struct Transform
	{
		/**
		 * The zoom scale of the image
		 */
		double zoom;

		/**
		 * The offset of the image
		 */
		std::complex<double> offset;

		/**
		 * The angle of rotation of the image
		 * (in degrees)
		 */
		double rotation;

		/**
		 * Creates a transform with the given parameters
		 *
		 * @param z the zoom scale of the image
		 * @param x the x offset of the image
		 * @param y the y offset of the image
		 * @param a the rotation angle of the image
		 */
		Transform(double z, double x, double y, double a);
	};

	/**
	 * Returns the complex number at the given pixel on the image
	 *
	 * @param x     the x coord of the pixel
	 * @param y     the y coord of the pixel
	 * @param image the image being processed
	 * @param cfg   the image configuration
	 *
	 * @return the complex number at the given pixel on the image
	 */
	std::complex<double> getComplex(const double& x, const double& y, cimg_library::CImg<char>& image, Transform& cfg);

	/**
	 * Computes the Julia set algorithm of the given complex numbers
	 *
	 * @param z the complex number to check
	 * @param c the constant complex number
	 * 
	 * @return the number of the iterations before infinity
	 */
	unsigned juliaSetAlgorithm(std::complex<double>& z, const std::complex<double>& c);

	/**
	 * Computes the Mandelbrot set algorithm of the given complex numbers
	 *
	 * @param c the complex number to check
	 * 
	 * @return the number of the iterations before infinity
	 */
	unsigned mandelbrotSetAlgorithm(std::complex<double>& c);

	/**
	 * Generates a Julia set image in the given object with the given complex constant
	 *
	 * @param image the image object to generate the Julia set in
	 * @param c     the complex constant being used
	 * @param trans the image configuration
	 * @param map   the colormap being used
	 *
	 * @return total number of iterations that were calculated
	 */
	unsigned generateJuliaSetImage(cimg_library::CImg<char>& image, const std::complex<double>& c, Transform& trans, const juliaset::colormap::ColorMapRGB* map);

	/**
	 * Generates a Mandelbrot set image in the given object with the given complex constant
	 *
	 * @param image the image object to generate the Mandelbrot set in
	 * @param trans the image configuration
	 * @param map   the colormap being used
	 *
	 * @return total number of iterations that were calculated
	 */
	unsigned generateMandelbrotSetImage(cimg_library::CImg<char>& image, Transform& trans, const juliaset::colormap::ColorMapRGB* map);
}

#endif