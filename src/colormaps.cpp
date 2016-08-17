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
	colormapIndex["noir"]        = new GradientMapRGB(0x000000, 0xffffff);
	colormapIndex["ink"]         = new GradientMapRGB(0xffffff, 0x000000);
	colormapIndex["greenlight"]  = new GradientMapRGB(0x061700, 0x52c234);
	colormapIndex["redlight"]    = new GradientMapRGB(0x000000, 0xe74c3c);
	colormapIndex["shadownight"] = new GradientMapRGB(0x000000, 0x774b9b);
	colormapIndex["drexel"]      = new GradientMapRGB(0x002f6c, 0xffc600);
	colormapIndex["ironman"]     = new GradientMapRGB(0x771414, 0xbeba46);

	// Return index
	return colormapIndex[name];
}