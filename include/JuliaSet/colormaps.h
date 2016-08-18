//-----------------------------------------------------------------------------------
// Program: JuliaSet
// 
// Generates Julia set images
//
// Author:  Anshul Kharbanda
// Created: 8 - 14 - 2016
//-----------------------------------------------------------------------------------

#ifndef _COLORMAPS_H_
#define _COLORMAPS_H_

// Headers being used
#include "colormap.h"

// Libraries being used
#include <string>
#include <vector>

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
		 * Initializes colormaps
		 */
		void initColorMap();

		/**
		 * Returns a vector of all colormaps
		 *
		 * @return a vector of all colormaps
		 */
		std::vector<std::string> getColorMaps();

		/**
		 * Returns true if the given name is a colormap
		 *
		 * @param name the name of the colormap to check
		 *
		 * @return true if the given name is a colormap
		 */
		bool hasColorMap(std::string name);

		/**
		 * Returns the colormap with the given name
		 *
		 * @param name the name of the colormap to retrieve
		 *
		 * @return the colormap with the given name
		 */
		ColorMapRGB* getColorMap(std::string name);
	}
}

#endif