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
	// Real and imaginary
	double real = 4.0 * (x / img_x) - 2.0;
	double imag = 4.0 * (y / img_y) - 2.0;

	// Return complex value
	return complex<double>(real, imag);
}

/**
 * Computes the JuliaSet color map of the given complex number
 *
 * @param z the complex number to check
 * @param c the constant complex number
 * @param i the iteration buffer to increment
 * @param m the colormap to use
 * 
 * @return the JuliaSet color map of the given complex number
 */
unsigned juliaSetColorMap(complex<double>& z, const complex<double>& c, int& i, colormap m)
{
	// Iterations in this map
	unsigned n;

	// Try 255 iterations
	for (n = 0; n < 255; n++, i++)
	{
		// Iteration function
		z = pow(z, 2) + c;

		// Break if z goes to infinity (beyond 2)
		if (norm(z) >= 4.0) break;
	}

	// Return color map
	return m(n);
}

/**
 * Sets the pixel in the given image at the given x/y coords
 * to the given color value.
 *
 * @param img the CImg to set
 * @param x   the x coord of the pixel
 * @param y   the y coord of the pixel
 * @param col the col value to set the pixel to
 */
void setColor(CImg<char>& img, const unsigned& x, const unsigned& y, const unsigned& col)
{
	// Set each channel
	img(x, y, 0) = (col & 0xFF0000) >> 16;
	img(x, y, 1) = (col & 0x00FF00) >> 8;
	img(x, y, 2) = (col & 0x0000FF);
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
int generateJuliasetImage(cimg_library::CImg<char>& image, const std::complex<double>& c, colormap map)
{
	// Image dimensions
	int imgx = image.width(), imgy = image.height();

	// Initialize buffers
	complex<double> z; // Z Complex buffer
	unsigned color;	   // Color value buffer
	int iter = 0;      // Total number of iterations

	// For each pixel location in image
	cimg_forXY(image, x, y) {
		// Compute JuliaSet map at pixel location
		z = getComplex(x, y, imgx, imgy);   	   // Complex number z at pixel
		color = juliaSetColorMap(z, c, iter, map); // Compute color map
		setColor(image, x, y, color);      		   // Set color map
	}
}