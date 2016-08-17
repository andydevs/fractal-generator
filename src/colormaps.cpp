//-----------------------------------------------------------------------------------
// Program: JuliaSet
// 
// Generates Julia set images
//
// Author:  Anshul Kharbanda
// Created: 8 - 14 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "JuliaSet/colormaps.h"

// Libraries being used
#include <map>

// Namespaces being used
using namespace std;

// Init map
static map<string, ColorMapRGB*> colormapIndex;

/**
 * Returns the colormap with the given name
 *
 * @param name the name of the colormap to retrieve
 *
 * @return the colormap with the given name
 */
ColorMapRGB* getColorMap(string name)
{
	// Populate
	colormapIndex["black2white"] = new GradientMapRGB(0x000000, 0xffffff);
	colormapIndex["white2black"] = new GradientMapRGB(0xffffff, 0x000000);
	colormapIndex["drexel"]      = new GradientMapRGB(0x002f6c, 0xffc600);

	// Return index
	return colormapIndex[name];
}