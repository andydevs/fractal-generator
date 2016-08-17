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
static map<string, ColorMapRGB*> index;

/**
 * Initializes colormaps
 */
void initColorMap()
{
	// Populate
	index["noir"]        = new GradientMapRGB(0x000000, 0xffffff);
	index["ink"]         = new GradientMapRGB(0xffffff, 0x000000);
	index["lightning"]   = new GradientMapRGB(0x000000, 0x99ddff);
	index["greenlight"]  = new GradientMapRGB(0x061700, 0x52c234);
	index["redlight"]    = new GradientMapRGB(0x000000, 0xe74c3c);
	index["shadownight"] = new GradientMapRGB(0x000000, 0x774b9b);
	index["drexel"]      = new GradientMapRGB(0x002f6c, 0xffc600);
	index["ironman"]     = new GradientMapRGB(0x771414, 0xbeba46);
}

/**
 * Returns true if the given name is a colormap
 *
 * @param name the name of the colormap to check
 *
 * @return true if the given name is a colormap
 */
bool hasColorMap(std::string name)
{
	map<string, ColorMapRGB*>::iterator it = index.find(name);
	return it != index.end();
}

/**
 * Returns the colormap with the given name
 *
 * @param name the name of the colormap to retrieve
 *
 * @return the colormap with the given name
 */
ColorMapRGB* getColorMap(string name)
{
	// Return colormap
	return index[name];
}