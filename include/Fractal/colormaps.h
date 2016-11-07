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
#include "error.h"

// Libraries being used
#include <pugixml-1.7/src/pugixml.hpp>
#include <string>
#include <vector>

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
		 * The document containing preset colormaps
		 */
		const std::string PRESET_DOCUMENT("fractal_colormaps.xml");

		/**
		 * Returns the colormap parsed by the given xml
		 *
		 * @param xml the xml object being parsed
		 * 
		 * @return the colormap parsed by the given xml
		 */
		ColorMapRGB* parseColorMap(pugi::xml_node xml);

		/**
		 * Initializes presets
		 *
		 * @return error code if preset is not parsed correctly
		 */
		int initPresets();

		/**
		 * Returns a vector of all presets
		 *
		 * @return a vector of all presets
		 */
		std::vector<std::string> getPresets();

		/**
		 * Returns the preset with the given name
		 *
		 * @param name the name of the preset to retrieve
		 *
		 * @return the preset with the given name
		 */
		ColorMapRGB* getPreset(std::string name);
	}
}

#endif