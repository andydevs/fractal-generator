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
#include <cstdlib>
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
	// If approppriate number of arguments given
	if (argc > 4)
	{
		// Parse arguments
		double real    = atof(argv[1]); // Constant real component
		double imag    = atof(argv[2]); // Constant imaginary component
		unsigned img_x = atoi(argv[3]); // Image width
		unsigned img_y = atoi(argv[4]); // Image height

		// Complex constant
		const complex<double> c(real, imag);

		// Initialize buffers
		complex<double> z; // Z Complex buffer
		unsigned color;	   // Color value buffer
		int iter = 0;      // Total number of iterations

		// Create image (with 3 color channels)
		CImg<char> jimage(img_x, img_y, 1, 3);

		// Print dimensions
		cout << "Generating: " << img_x << "x" << img_y << endl;

		// Start clock
		double time0 = clock();

		// For each pixel location in image
		cimg_forXY(jimage, x, y) {
			// Compute JuliaSet map at pixel location
			z = getComplex(x, y, img_x, img_y);   // Complex number z at pixel
			color = juliaSetColorMap(z, c, iter); // Compute color map
			setColor(jimage, x, y, color);        // Set color map
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
	else
	{
		// Print error message
		cout << "ERROR: Expected 4 program arguments. Got: " << (argc - 1) << endl;

		// Return error
		return 1;
	}
}