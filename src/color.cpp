//-----------------------------------------------------------------------------------
// Program: Fractal
// 
// Generates Julia and Mandelbrot Set fractal images
//
// Author:  Anshul Kharbanda
// Created: 8 - 14 - 2016
//-----------------------------------------------------------------------------------

// Headers being useds
#include "Fractal/const.h"
#include "Fractal/color.h"

/**
 * Contains functions and structs used by Fractal generator
 * 
 * @author  Anshul Kharbanda
 * @created 8 - 17 - 2016
 */
namespace fractal
{
	/**
	 * Handles colormapping
	 *
	 * @author  Anshul Kharbanda
	 * @created 8 - 17 - 2016
	 */
	namespace colormap
	{
		/**
		 * Creates an empty ColorRGB
		 */
		ColorRGB::ColorRGB(): red(0), green(0), blue(0) {}

		/**
		 * Creates a ColorRGB with the given red, green and blue values
		 *
		 * @param r the red value
		 * @param g the green value
		 * @param b the blue value
		 */
		ColorRGB::ColorRGB(short r, short g, short b):
		red(r), green(g), blue(b) {}

		/**
		 * Creates a ColorRGB with the given integer color value
		 *
		 * @param color an RGB color integer
		 */
		ColorRGB::ColorRGB(unsigned color):
		red((color & 0xff0000) >> 16),
		green((color & 0x00ff00) >> 8),
		blue((color & 0x0000ff)) {}

		/**
		 * Returns the result of the color shifted by the given gradient value
		 *
		 * @param other the gradient to shift the color by
		 */
		ColorRGB ColorRGB::operator+(ColorGradientRGB other) const
		{
			return ColorRGB(
				(short)(red   + other.red),
				(short)(green + other.green),
				(short)(blue  + other.blue)
			);
		}

		/**
		 * Creates an empty ColorGradientRGB
		 */
		ColorGradientRGB::ColorGradientRGB():
		red(0), green(0), blue(0) {}

		/**
		 * Creates a ColorGradientRGB with the given red, green and blue values
		 *
		 * @param r the red value
		 * @param g the green value
		 * @param b the blue value
		 */
		ColorGradientRGB::ColorGradientRGB(double r, double g, double b):
		red(r), green(g), blue(b) {}

		/**
		 * Computes the ColorGradientRGB between the given start and end colors
		 *
		 * @param start the start color
		 * @param end   the end color
		 */
		ColorGradientRGB::ColorGradientRGB(ColorRGB first, ColorRGB last)
		{
			red   = (last.red   - first.red)   / ((double)MAX_ITER);
			green = (last.green - first.green) / ((double)MAX_ITER);
			blue  = (last.blue  - first.blue)  / ((double)MAX_ITER);

		}

		/**
		 * Computes the gradient value at the given point in the space
		 *
		 * @param point the point in the gradient space
		 */
		ColorGradientRGB ColorGradientRGB::operator*(unsigned iterations) const
		{
			return ColorGradientRGB(
				red*iterations,
				green*iterations,
				blue*iterations
			);
		}
	}
}