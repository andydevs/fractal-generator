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
#include "JuliaSet/functions.h"

// Libraries being used
#include <iostream>
#include <ctime>

// Namespaces being used
using namespace std;
using namespace cimg_library;

// Constants being used
const char* DEFAULT_IMAGE_NAME = "jimage.jpg"; // The default image name

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
	complex<double> c(0, 0); 		     // Complex constant
	unsigned img_x = 1920, img_y = 1920; // Image dimensions

	// Init buffers
	int iter = 0;      // Total number of iter
	complex<double> z; // Z Complex buffer
	unsigned color;	   // Color buffer

	// Create image (with 3 color channels)
	CImg<char> jimage(img_x, img_y, 1, 3);

	// Print dimensions
	cout << "Generating: " << img_x << "x" << img_y << endl;

	// Start clock
	double time0 = clock();

	// For each pixel location in image
	cimg_forXY(jimage, x, y) {
		// Compute complex number at location
		z = getComplex(x, y, img_x, img_y);
		// Compute JuliaSet map at complex number
		color = juliaSetColorMap(z, c, iter);
		// Add color as pixel map to pixel at location
		setColor(jimage, x, y, color);
	}

	// End clock
	double time = (clock() - time0) / CLOCKS_PER_SEC;

	// Save image
	cout << "Saving..." << endl;
	jimage.save(DEFAULT_IMAGE_NAME);

	// Print end information
	cout << "Iterations: "     << iter << endl;
	cout << "Time (seconds): " << time << endl;

	// End program
	return 0;
}