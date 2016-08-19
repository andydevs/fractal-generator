//-----------------------------------------------------------------------------------
// Program: JuliaSet
// 
// Generates Julia set images
//
// Author:  Anshul Kharbanda
// Created: 8 - 14 - 2016
//-----------------------------------------------------------------------------------

#ifndef _COLORMAP_H_
#define _COLORMAP_H_

// Headers being used
#include "color.h"

/**
 * Contains functions and structs used by JuliaSet algorithm
 * 
 * @author  Anshul Kharbanda
 * @created 8 - 17 - 2016
 */
namespace juliaset
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
		 * Maps a given number of iterations made by the JuliaSet algorithm
		 * to a color to assign the pixel in question to
		 *
		 * @author  Anshul Kharbanda
		 * @created 8 - 16 - 2016
		 */
		class ColorMapRGB
		{
		public:
			/**
			 * Creates an empty ColorMapRGB
			 */
			ColorMapRGB();

			/**
			 * Destroys the ColorMapRGB
			 */
			~ColorMapRGB();

			/**
			 * Maps the given number of iterations to a given color
			 *
			 * @param iterations the iterations being mapped
			 *
			 * @return the color calculated from the iterations
			 */
			virtual ColorRGB color(unsigned iterations) const = 0;
		};

		/**
		 * Maps a given number of iterations to a color using a linear
		 * gradient between two colors
		 *
		 * @author  Anshul Kharbanda
		 * @created 8 - 16 - 2016
		 */
		class GradientMapRGB : public ColorMapRGB
		{
		private:
			/**
			 * The start color
			 */
			ColorRGB m_start;

			/**
			 * The color gradient
			 */
			ColorGradientRGB m_gradient;
		public:
			/**
			 * Creates a GradientMapRGB between the two given colors
			 *
			 * @param start the start color
			 * @param end   the end color
			 */
			GradientMapRGB(unsigned start, unsigned end);

			/**
			 * Destroys the GradientMapRGB
			 */
			~GradientMapRGB();

			/**
			 * Maps the given number of iterations to a given color
			 *
			 * @param iterations the iterations being mapped
			 *
			 * @return the color calculated from the iterations
			 */
			ColorRGB color(unsigned iterations) const;
		};
	}
}

#endif