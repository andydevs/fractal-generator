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
#include "JuliaSet/colormaps.h"

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
	// -----------------------------ARGUMENTS-----------------------------

	// Error if approppriate number of arguments is not given
	if (argc < 5)
	{
		cout << "ERROR: Expected 4 program arguments. Got: ";
		cout << (argc - 1) << endl;
		return 1;
	}

	// Parse arguments
	double real    = atof(argv[1]); // Constant real component
	double imag    = atof(argv[2]); // Constant imaginary component
	unsigned img_x = atoi(argv[3]); // Image width
	unsigned img_y = atoi(argv[4]); // Image height
	
	// Parse optional arguments
	double zoom = argc > 5 ? atof(argv[5]) : 1.0; // Zoom
	double offx = argc > 6 ? atof(argv[6]) : 0.0; // Offset x
	double offy = argc > 7 ? atof(argv[7]) : 0.0; // Offset y
	double rot  = argc > 8 ? atof(argv[8]) : 0.0; // Rotation

	// -----------------------------CONSTANTS-----------------------------

	// Complex values
	const complex<double> c(real, imag); 	  // Constant
	const complex<double> off(offx, offy); // Offset

	// Image (with 3 color channels)
	CImg<char> jimage(img_x, img_y, 1, 3);

	// -----------------------------ALGORITHM-----------------------------

	// Print dimensions
	cout << "Generating: " << jimage.width() << "x" << jimage.height() << endl;

	// Start clock
	double time = clock();

	// Generate julia set image
	int iter = generateJuliasetImage(jimage, c, zoom, off, rot, &BLUE_TO_YELLOW);

	// End clock
	time = (clock() - time) / CLOCKS_PER_SEC;

	// ----------------------------SAVE AND END---------------------------

	// Save image
	cout << "Saving..." << endl;
	jimage.save(DEFAULT_IMAGE_NAME);

	// Print end information
	cout << "Iterations: "     << iter << endl;
	cout << "Time (seconds): " << time << endl;

	// End program
	return 0;
}