//-----------------------------------------------------------------------------------
// Program: JuliaSet
// 
// Generates Julia set images
//
// Author:  Anshul Kharbanda
// Created: 8 - 14 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "JuliaSet/juliaset.h"

// Libraries being used
#include <cmath>

// Libraries being used
using namespace std;
using namespace cimg_library;
using namespace juliaset::colormap;

/**
 * Contains functions and structs used by JuliaSet algorithm
 * 
 * @author  Anshul Kharbanda
 * @created 8 - 17 - 2016
 */
namespace juliaset
{
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
	angle(a) {}

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
		// Downscale pixel value by image height
		complex<double> downScale(x / height, y / height);

		// Rotation complex
		complex<double> rotation = polar(1.0, angle * M_PI / 180);

		// Shift complex (scale by image aspect ratio)
		complex<double> shift(0.5*width/height, 0.5);

		// Perform Operation
		return (SCALE / zoom) * (downScale - shift) * rotation + offset;
	}

	/**
	 * Computes the JuliaSet algorithm of the given complex numbers
	 *
	 * @param z the complex number to check
	 * @param c the constant complex number
	 * 
	 * @return the number of the iterations before infinity
	 */
	unsigned juliaSetAlgorithm(complex<double>& z, const complex<double>& c)
	{
		// Iterations at this point
		unsigned n;

		// Try 256 iterations
		for (n = 0; n < 256; n++)
		{
			// Iteration function
			z = pow(z, 2) + c;

			// Break if z goes to infinity (beyond space)
			if (norm(z) >= pow(SCALE/2, 2)) break;
		}

		// Return number of iterations
		return n;
	}

	/**
	 * Computes the Mandelbrot set algorithm of the given complex numbers
	 *
	 * @param c the complex number to check
	 * 
	 * @return the number of the iterations before infinity
	 */
	unsigned mandelbrotSetAlgorithm(std::complex<double>& c)
	{
		// Iterations at this point
		unsigned n;

		// Zero z
		complex<double>z;

		// Try 256 iterations
		for (n = 0; n < 256; ++n)
		{
			// Iteration function
			z = pow(z, 2) + c;

			// Break if z goes to infinity (beyond space)
			if (norm(z) >= pow(SCALE/2, 2)) break;
		}

		// Return iterations
		return n;
	}

	/**
	 * Generates a Juliaset Image in the given object with the given complex constant
	 *
	 * @param image the image object to generate the Juliaset in
	 * @param c     the complex constant being used
	 * @param trans the image configuration
	 * @param map   the colormap being used
	 *
	 * @return total number of iterations that were calculated
	 */
	unsigned generateJuliaSetImage(cimg_library::CImg<char>& image, const complex<double>& c, Transform& trans, const ColorMapRGB* map)
	{
		// Initialize buffers
		complex<double> z;     // Z Complex buffer
		ColorRGB color;	       // Color value buffer
		int result, total = 0; // Tterations buffer

		// For each pixel location in image
		cimg_forXY(image, x, y) 
		{
			// Compute JuliaSet map at pixel location
			z      = trans(x,y); 			  // Complex number z at pixel
			result = juliaSetAlgorithm(z, c); // Julia set algorithm
			color  = map->color(result);      // Compute color map
			
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

	/**
	 * Generates a Mandelbrot set image in the given object with the given complex constant
	 *
	 * @param image the image object to generate the Mandelbrot set in
	 * @param trans the image configuration
	 * @param map   the colormap being used
	 *
	 * @return total number of iterations that were calculated
	 */
	unsigned generateMandelbrotSetImage(cimg_library::CImg<char>& image, Transform& trans, const ColorMapRGB* map)
	{
		// Initialize buffers
		complex<double> c;     // C Complex buffer
		ColorRGB color;	       // Color value buffer
		int result, total = 0; // Tterations buffer

		// For each pixel location in image
		cimg_forXY(image, x, y) 
		{
			// Compute JuliaSet map at pixel location
			c      = trans(x, y);			    // Complex number c at pixel
			result = mandelbrotSetAlgorithm(c); // Mandelbrot set algorithm
			color  = map->color(result);		// Compute color map
			
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
}