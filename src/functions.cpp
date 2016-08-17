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
#include <cmath>

// Libraries being used
using namespace std;
using namespace cimg_library;

/**
 * Creates a config with the given parameters
 *
 * @param z the zoom scale of the image
 * @param x the x offset of the image
 * @param y the y offset of the image
 * @param a the rotation angle of the image
 */
Config::Config(double z, double x, double y, double a): 
zoom(z), 
offset(x, y), 
rotation(a) 
{}

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
std::complex<double> getComplex(const double& x, const double& y, cimg_library::CImg<char>& image, Config& cfg)
{
	// Downscale pixel value by image dimensions
	complex<double> downScale(x / image.width(), y / image.height());

	// Rotation complex
	complex<double> rotation = polar(1.0, cfg.rotation / 180 * M_PI);

	// Perform Operation
	return (SCALE * downScale - SHIFT) * rotation / cfg.zoom + cfg.offset;
}

/**
 * Computes the JuliaSet algorithm of the given complex numbers
 *
 * @param z    the complex number to check
 * @param c    the constant complex number
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
 * @param cfg   the image configuration
 * @param map   the colormap being used
 *
 * @return total number of iterations that were calculated
 */
int generateJuliasetImage(cimg_library::CImg<char>& image, const std::complex<double>& c, Config& cfg, const ColorMapRGB* map)
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
		z      = getComplex(x, y, image, cfg); // Complex number z at pixel
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