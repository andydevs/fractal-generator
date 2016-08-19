//-----------------------------------------------------------------------------------
// Program: JuliaSet
// 
// Generates Julia set images
//
// Author:  Anshul Kharbanda
// Created: 8 - 14 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "JuliaSet/colormap.h"

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
		 * Creates an empty ColorMapRGB
		 */
		ColorMapRGB::ColorMapRGB() {}

		/**
		 * Destroys the ColorMapRGB
		 */
		ColorMapRGB::~ColorMapRGB() {}

		/**
		 * Creates a GradientMapRGB between the two given colors
		 *
		 * @param start the start color
		 * @param end   the end color
		 */
		GradientMapRGB::GradientMapRGB(unsigned start, unsigned end):
		ColorMapRGB(),
		m_start(start),
		m_gradient(start, end)
		{}

		/**
		 * Destroys the GradientMapRGB
		 */
		GradientMapRGB::~GradientMapRGB() {}

		/**
		 * Maps the given number of iterations to a given color
		 *
		 * @param iterations the iterations being mapped
		 *
		 * @return the color calculated from the iterations
		 */
		ColorRGB GradientMapRGB::color(unsigned iterations) const
		{
			return m_start + m_gradient*iterations;
		}
	}
}