//-----------------------------------------------------------------------------------
// Program: JuliaSet
// 
// Generates Julia set images
//
// Author:  Anshul Kharbanda
// Created: 8 - 14 - 2016
//-----------------------------------------------------------------------------------

#ifndef _COLOR_H_
#define _COLOR_H_

// Headers being used
#include "CImg/CImg.h"

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
		 * Represents a linear gradient between two 
		 * end colors over a space of 256 units
		 *
		 * @author  Anshul Kharbanda
		 * @created 8 - 16 - 2016
		 */
		struct ColorGradientRGB;

		/**
		 * Represents a color with red, green, and blue values
		 *
		 * @author  Anshul Kharbanda
		 * @created 8 - 16 - 2016
		 */
		struct ColorRGB
		{
			/**
			 * The red value
			 */
			short red;

			/**
			 * The green value
			 */
			short green;

			/**
			 * The blue value
			 */
			short blue;

			/**
			 * Creates an empty ColorRGB
			 */
			ColorRGB();

			/**
			 * Creates a ColorRGB with the given red, green and blue values
			 *
			 * @param r the red value
			 * @param g the green value
			 * @param b the blue value
			 */
			ColorRGB(short r, short g, short b);

			/**
			 * Creates a ColorRGB with the given integer color value
			 *
			 * @param color an RGB color integer
			 */
			ColorRGB(unsigned color);

			/**
			 * Returns the result of the color shifted by the given gradient value
			 *
			 * @param other the gradient to shift the color by
			 */
			ColorRGB operator+(ColorGradientRGB other) const;
		};

		/**
		 * Represents a linear gradient between two 
		 * end colors over a space of 256 units
		 *
		 * @author  Anshul Kharbanda
		 * @created 8 - 16 - 2016
		 */
		struct ColorGradientRGB
		{
			/**
			 * The red value
			 */
			double red;

			/**
			 * The green value
			 */
			double green;

			/**
			 * The blue value
			 */
			double blue;

			/**
			 * Creates an empty ColorGradientRGB
			 */
			ColorGradientRGB();

			/**
			 * Creates a ColorGradientRGB with the given red, green and blue values
			 *
			 * @param r the red value
			 * @param g the green value
			 * @param b the blue value
			 */
			ColorGradientRGB(double r, double g, double b);

			/**
			 * Computes the ColorGradientRGB between the given start and end colors
			 *
			 * @param start the start color
			 * @param end   the end color
			 */
			ColorGradientRGB(ColorRGB start, ColorRGB end);

			/**
			 * Computes the gradient value at the given point in the space
			 *
			 * @param point the point in the gradient space
			 */
			ColorGradientRGB operator*(unsigned point) const;
		};
	}
}

#endif