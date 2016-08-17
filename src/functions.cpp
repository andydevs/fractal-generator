//-----------------------------------------------------------------------------------
// Program: JuliaSet
// 
// Generates Julia set images
//
// Author:  Anshul Kharbanda
// Created: 8 - 14 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "JuliaSet/functions.h"

// Libraries being used
using namespace std;
using namespace cimg_library;

/**
 * Returns the complex number at the given pixel on the image
 *
 * @param x     the x coord of the pixel
 * @param y     the y coord of the pixel
 * @param img_x the width of the image
 * @param img_y the height of the image
 *
 * @return the complex number at the given pixel on the image
 */
complex<double> getComplex(const double& x, const double& y, const double& img_x, const double& img_y)
{
	// Return complex value
	return SCALE * complex<double>(x / img_x, y / img_y) - SHIFT;
}

/**
 * Computes the JuliaSet algorithm of the given complex numbers
 *
 * @param z the complex number to check
 * @param c the constant complex number
 * 
 * @return the number of the iterations before infinity
 */
int juliaSetAlgorithm(std::complex<double>& z, const std::complex<double>& c)
{
	// Iterations in this map
	unsigned n;

	// Try 256 iterations
	for (n = 0; n < 256; n++)
	{
		// Iteration function
		z = pow(z, 2) + c;

		// Break if z goes to infinity (beyond space)
		if (norm(z) >= pow(SCALE, 2)) break;
	}

	// Return number of iterations
	return n;
}

/**
 * Generates a Juliaset Image in the given object with the given complex constant
 *
 * @param image the image object to generate the Juliaset in
 * @param c     the complex constant being used
 * @param map   the colormap being used
 *
 * @return number of iterations that were calculated
 */
int generateJuliasetImage(cimg_library::CImg<char>& image, const std::complex<double>& c, const ColorMapRGB* map)
{
	// Image dimensions
	int imgx = image.width(), imgy = image.height();

	// Initialize buffers
	complex<double> z;     // Z Complex buffer
	ColorRGB color;	       // Color value buffer
	int result, total = 0; // Tterations buffer

	// For each pixel location in image
	cimg_forXY(image, x, y) 
	{
		// Compute JuliaSet map at pixel location
		z      = getComplex(x, y, imgx, imgy); // Complex number z at pixel
		result = juliaSetAlgorithm(z, c);      // Julia set algorithm
		color  = map->color(result);		   // Compute color map
		
		// Set Color
		image(x, y, 0) = color.red;
		image(x, y, 1) = color.green;
		image(x, y, 2) = color.blue;

		// Add to total
		total += result;
	}

	// Return total
	return total;
}