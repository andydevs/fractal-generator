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
#include "colormaps.h"
#include "CImg/CImg.h"

// Libraries being used
#include <complex>

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
 * Computes the JuliaSet color map of the given complex number
 *
 * @param z the complex number to check
 * @param c the constant complex number
 * @param i the iteration buffer to increment
 * @param m the colormap to use 
 * 
 * @return the JuliaSet color map of the given complex number
 */
unsigned juliaSetColorMap(std::complex<double>& z, const std::complex<double>& c, int& i, colormap m);

/**
 * Sets the pixel in the given image at the given x/y coords
 * to the given color value.
 *
 * @param img the CImg to set
 * @param x   the x coord of the pixel
 * @param y   the y coord of the pixel
 * @param col the col value to set the pixel to
 */
void setColor(cimg_library::CImg<char>& image, const unsigned& x, const unsigned& y, const unsigned& col);

#endif