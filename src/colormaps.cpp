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
#include <cstring>
#include <map>

// Namespaces being used
using namespace std;

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
		// Init map
		static map<string, ColorMapRGB*> preset;

		/**
		 * Returns the colormap parsed by the given xml
		 *
		 * @param xml the xml object being parsed
		 * 
		 * @return the colormap parsed by the given xml
		 */
		ColorMapRGB* parseColorMap(pugi::xml_node xml) 
		{
			// Return preset if set
			if (xml.attribute("preset"))
				return preset[xml.attribute("preset").value()];

			// Get type 
			const char* type = xml.attribute("type").value();

			// Parse colormap according to type
			if (!strcmp(type, "rainbow"))
				return new RainbowMapRGB(xml);
			else if (!strcmp(type, "gradient"))
				return new GradientMapRGB(xml);
			else
				return NULL;
		}

		/**
		 * Initializes colormaps
		 *
		 * @return error code if colormap is not parsed correctly
		 */
		int initColorMap()
		{
			// Read colormap xml
			pugi::xml_document cmapdoc;
			cmapdoc.load_file("juliaset_colormaps.xml");

			// Buffers
			ColorMapRGB* colormap;
			string name;

			// Default preset
			preset["rainbow"] = new RainbowMapRGB();

			// For every entry in the colormap doc
			for (pugi::xml_node entry = cmapdoc.child("entry"); 
				 entry; entry = entry.next_sibling("entry"))
			{
				// Get name and colormap
				name     = string(entry.child("name").text().get());
				colormap = parseColorMap(entry.child("colormap"));
				
				// Set name in preset to colormap
				preset[name] = colormap;
			}

			// Delete final colormap
			delete colormap;
			
			// Return success
			return 0;
		}

		/**
		 * Returns a vector of all colormaps
		 *
		 * @return a vector of all colormaps
		 */
		vector<string> getColorMaps()
		{
			vector<string> maps;
			for (map<string, ColorMapRGB*>::iterator it = preset.begin();
				it != preset.end(); it++)
			{
				maps.push_back(it->first);
			}
			return maps;
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
			map<string, ColorMapRGB*>::iterator it = preset.find(name);
			return it != preset.end();
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
			return preset[name];
		}
	}
}