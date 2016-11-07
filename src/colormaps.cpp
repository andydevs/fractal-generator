//-----------------------------------------------------------------------------------
// Program: Fractal
// 
// Generates Julia and Mandelbrot Set fractal images
//
// Author:  Anshul Kharbanda
// Created: 8 - 14 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "Fractal/colormaps.h"

// Libraries being used
#include <cstring>
#include <iostream>
#include <sstream>
#include <map>

// Namespaces being used
using namespace std;

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

		int loadDocument(pugi::xml_document& document)
		{
			// Paths to check
			vector<string> paths;
			paths.push_back(string("."));
			paths.push_back(string("/usr/bin"));

			// Go through each path and return if file is found there
			std::string path;
			pugi::xml_parse_result res;
			for (vector<string>::iterator i = paths.begin(); i != paths.end(); ++i)
			{
				path = *i + "/" + PRESET_DOCUMENT;
				res = document.load_file(path.c_str());
				if (res) return 0;
			}

			// Return 1 if not
			return 1;
		}

		/**
		 * Initializes presets
		 *
		 * @return error code if preset is not parsed correctly
		 */
		int initPresets()
		{
			// Default preset
			preset["rainbow"] = new RainbowMapRGB();

			// Colormap xml document
			pugi::xml_document cmapdoc;
			if (loadDocument(cmapdoc)) return 1;

			// Buffers
			ColorMapRGB* colormap;
			string name;

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
		 * Returns a vector of all presetss
		 *
		 * @return a vector of all presetss
		 */
		vector<string> getPresets()
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
		 * Returns the preset with the given name
		 *
		 * @param name the name of the preset to retrieve
		 *
		 * @return the preset with the given name
		 *
		 * @throw Error when name is not a preset
		 */
		ColorMapRGB* getPreset(string name) throw(Error)
		{
			// Find name
			map<string, ColorMapRGB*>::iterator it = preset.find(name);

			// Return preset if found, else throw error
			if (it != preset.end())
				return it->second;
			else
				throw Error("Undefined preset name: " + name + ". See -cmaps for available presets.");
		}
	}
}