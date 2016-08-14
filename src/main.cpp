//-----------------------------------------------------------------------------------
// Program: JuliaSet
// 
// Generates Julia set images
//
// Author:  Anshul Kharbanda
// Created: 8 - 14 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "CImg/CImg.h"

// Libraries being used
#include <iostream>
#include <complex>
#include <ctime>

// Namespaces being used
using namespace std;
using namespace cimg_library;

/**
 * Computes the JuliaSet color map of the given complex number
 *
 * @param z the complex number to check
 * @param c the constant complex number
 * @param i the iteration buffer to increment 
 * 
 * @return the JuliaSet color map of the given complex number
 */
unsigned juliaSetColorMap(complex<double> z, complex<double> c, int& i);

/**
 * Sets the pixel in the given image at the given x/y coords
 * to the given color value.
 *
 * @param img the CImg to set
 * @param x   the x coord of the pixel
 * @param y   the y coord of the pixel
 * @param col the col value to set the pixel to
 */
void setColor(CImg<char>& image, const unsigned& x, const unsigned& y, const unsigned& col);

/**
 * The main function of the program
 *
 * @param argc the number of command line arguments
 * @param argv the command line arguments
 *
 * @return exit code
 */
int main(int argc, char const *argv[])
{
	// Read arguments (to be implemented later)
		// First argument is constant real component
		// Second argument is constant imaginary component
		// Third argument is image x size
		// Fourth argument is image y size

	// Default arguments
	complex<double> c(0, 0); 		   	 // Complex constant
	unsigned img_x = 1920, img_y = 1080; // Image dimensions

	// Init iterations buffer and start clock
	int iterations = 0;
	int time0 = clock();

	// Print dimensions
	cout << "Generating: " << img_x << "x" << img_y << endl;

	// Load image (with 3 color channels)
	CImg<char> jimage(img_x, img_y, 1, 3);

	// For each pixel location in image
	cimg_forXY(jimage, x, y) {
		// Compute complex number at location
		// Compute JuliaSet map at complex number
		// Add color as pixel map to pixel at location

		// Color everything blue for now
		setColor(jimage, x, y, 0x00aaff);

		// Increment iterations
		iterations++;
	}

	// End clock
	double time = (double)(clock() - time0) / CLOCKS_PER_SEC;

	// Save image
	cout << "Saving..." << endl;
	jimage.save("./juliasetimage.jpg");

	// Print end information
	cout << "Iterations: " << iterations << endl;
	cout << "Time (seconds): " << time << endl;

	// End program
	return 0;
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
void setColor(CImg<char>& image, const unsigned& x, const unsigned& y, const unsigned& col)
{
	// Set each channel
	image(x, y, 0) = (col & 0xFF0000) >> 16;
	image(x, y, 1) = (col & 0x00FF00) >> 8;
	image(x, y, 2) = (col & 0x0000FF);
}