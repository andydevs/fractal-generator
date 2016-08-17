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
#include <complex>

/**
 * The complex space scale value
 */
const double SCALE = 4.0;

/**
 * The complex space shift value
 */
const std::complex<double> SHIFT(2.0, 2.0);

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
std::complex<double> getComplex(const double& x, const double& y, const double& img_x, const double& img_y);

/**
 * Computes the JuliaSet algorithm of the given complex numbers
 *
 * @param z the complex number to check
 * @param c the constant complex number
 * 
 * @return the number of the iterations before infinity
 */
int juliaSetAlgorithm(std::complex<double>& z, const std::complex<double>& c);

/**
 * Generates a Juliaset Image in the given object with the given complex constant
 *
 * @param image the image object to generate the Juliaset in
 * @param c     the complex constant being used
 * @param map   the colormap being used
 *
 * @return total number of iterations that were calculated
 */
int generateJuliasetImage(cimg_library::CImg<char>& image, const std::complex<double>& c, const ColorMapRGB* map);

#endif