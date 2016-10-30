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
#include "JuliaSet/juliaset.h"
#include "JuliaSet/colormaps.h"

// Libraries being used
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <ctime>

// Namespaces being used
using namespace std;
using namespace cimg_library;
using namespace juliaset;
using namespace juliaset::colormap;
using namespace pugi;

/**
 * Shows a list of the available colormaps
 */
void showCmaps();

/**
 * Generates a 400x300 test image for the given colormap
 * saved to the given sname
 *
 * @param sname the name to save the test image to
 * @param cmap  the colormap to test
 */
void testCmap(string sname, ColorMapRGB* cmap);

/**
 * Generates a juliaset image with the given parameters
 *
 * @param imgx  the width of the image
 * @param imgy  the height of the image
 * @param sname the name to save the image to
 * @param trans the image transform
 * @param cmap  the image colormap
 * @param mbrot true if the mandelbrot set is to be generated
 * @param cons  the juliaset complex constant
 *
 * @return the number of iterations performed
 */
int generate(string sname, Transform trans, 
	ColorMapRGB* cmap, bool mbrot, 
	complex<double> cons);

/**
 * Runs the xml document with the given name
 *
 * @param docname the name of the document to parse
 */
void runXML(string docname);

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
	// ------------------------------CONFIG------------------------------

	// CImg descriptor
	cimg_usage("Generates JuliaSet images.");

	// Image options
	string xml      = cimg_option("-xml",   "",           "Parses the xml file with the given name.");
	double real     = cimg_option("-cr",    0.0,  		  "The constant real component");
	double imag     = cimg_option("-ci",    0.0,  		  "The constant imaginary component");
	bool mandelbrot = cimg_option("-mbrot", false,        "Generates the mandelbrot set");
	unsigned imgx   = cimg_option("-imgx",  1920, 		  "The image width");
	unsigned imgy   = cimg_option("-imgy",  1080, 		  "The image height");
	double zoom     = cimg_option("-zoom",  1.0,  		  "The zoom scale of the image");
	double offx     = cimg_option("-offx",  0.0,  		  "The x offset of the image");
	double offy     = cimg_option("-offy",  0.0,  		  "The y offset of the image");
	double rot      = cimg_option("-rot",   0.0,  		  "The angle of rotation of the image (in degrees)");
	string sname    = cimg_option("-save",  "jimage.jpg", "The file to save the image to");
	string cname    = cimg_option("-cmap",  "rainbow",    "The colormapping to use");
	bool showcmaps  = cimg_option("-cmaps", false,		  "Lists the cmaps");
	bool testcmap   = cimg_option("-test",  false,        "Generates a 400x300 test image (saved to the sname) for the set colormap");
	bool help       = cimg_option("-help",  false,        "Prints the help message")
				   || cimg_option("-h",     false,        "Prints the help message");

	// Initialize colormaps
	initColorMap();

	// -----------------------------FUNCTIONS-----------------------------

	if (help) // If they just wanted help
		printf("\n");
	else if (showcmaps) // Shows all cmaps
		showCmaps();
	else if (testcmap) // Tests one cmap
		testCmap(sname, getColorMap(cname));
	else if (!xml.empty()) // Parse XML document
		runXML(xml);
	else // Command line interface
		generate(sname, 
				Transform(ImgSize(imgx, imgy),zoom,offx,offy,rot), 
				getColorMap(cname), mandelbrot,
				complex<double>(real,imag));

	// End program
	return 0;
}

/**
 * Runs the xml document with the given name
 *
 * @param docname the name of the document to parse
 */
void runXML(string docname)
{
	// Create xml doc
	xml_document jdoc;
	jdoc.load_file(docname.c_str());

	// Parameters to extract
	string sname;
	ImgSize size;
	Transform trans;
	ColorMapRGB* cmap;
	bool mbrot;
	complex<double> cons(0,0);

	// Start clock
	double time = clock();

	// Number of iterations
	unsigned iter = 0;

	// For each jimage object
	for (xml_node jimage = jdoc.child("jimage"); 
		jimage; jimage = jimage.next_sibling("jimage"))
	{
		// Extract parameters
		sname = jimage.attribute("save").as_string();
		size  = ImgSize(jimage.child("size"));
		trans = Transform(size,jimage.child("transform"));
		cmap  = parseColorMap(jimage.child("colormap"));
		mbrot = jimage.attribute("mbrot").as_bool();
		cons  = rectFromXML(jimage.child("complex"));

		// Generate image
		iter += generate(sname, trans, cmap, mbrot, cons);
	}

	// End clock
	time = (clock() - time) / CLOCKS_PER_SEC;

	// Print end information
	cout << "Total Iterations: " << iter << endl;
	cout << "Total Time:       " << time << " seconds" << endl;
}

/**
 * Shows a list of the available colormaps
 */
void showCmaps()
{
	// Get cmaps
	vector<string> v = getColorMaps();

	// Print cmaps
	cout << "Available colormaps:" << endl;
	for (vector<string>::iterator it = v.begin(); it != v.end(); it++)
		cout << "\t" << *it << endl;
}

/**
 * Generates a 400x300 test image for the given colormap
 * saved to the given sname
 *
 * @param sname the name to save the test image to
 * @param cmap  the colormap to test
 */
void testCmap(string sname, ColorMapRGB* cmap)
{
	// 400 x 300 image with 3 color channels
	CImg<char> image(400, 300, 1, 3);

	// Variables
	ColorRGB color;
	
	// For each pixel
	cimg_forXY(image, x, y)
	{
		// Get color
		color = cmap->color(256 * x / image.width());

		// Set color
		image(x, y, 0) = color.red;
		image(x, y, 1) = color.green;
		image(x, y, 2) = color.blue;
	}

	// Save image
	image.save(sname.c_str());
}

/**
 * Generates a juliaset image with the given parameters
 *
 * @param sname the name to save the image to
 * @param trans the image transform
 * @param cmap  the image colormap
 * @param mbrot true if the mandelbrot set is to be generated
 * @param cons  the juliaset complex constant
 *
 * @return the number of iterations performed
 */
int generate(string sname, Transform trans, ColorMapRGB* cmap, bool mbrot, complex<double> cons)
{
	// Image (with 3 color channels)
	CImg<char> jimage(trans.size.width, trans.size.height, 1, 3);

	// -----------------------------ALGORITHM-----------------------------

	// Print dimensions
	cout << "Generating " << sname << "..." << endl;

	// Iterations
	unsigned iter;

	// Start clock
	double time = clock();

	// Generate either mandelbrot or juliaset image
	iter = mbrot ? generateMandelbrotSetImage(jimage, trans, cmap)
				 : generateJuliaSetImage(jimage, cons, trans, cmap);

	// End clock
	time = (clock() - time) / CLOCKS_PER_SEC;

	// --------------------------SAVE AND RETURN--------------------------

	// Save image
	jimage.save(sname.c_str());

	// Print end information
	cout << "	Iterations: " << iter << endl;
	cout << "	Time:       " << time << " seconds" << endl;

	// Return iterations
	return iter;
}