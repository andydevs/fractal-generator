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
using namespace pugi;

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
		 *
		 * @throw Error upon error parsing xml
		 */
		ColorMapRGB* parseColorMap(xml_node xml) throw(Error)
		{
			// Return preset if set
			if (xml.attribute("preset"))
				return getPreset(xml.attribute("preset").value());

			// Get type 
			const char* type = xml.attribute("type").value();

			// Parse colormap according to type
			if (!strcmp(type, "rainbow"))
				return new RainbowMapRGB(xml);
			else if (!strcmp(type, "gradient"))
				return new GradientMapRGB(xml);
			else
				throw Error("Undefined colormap type: " + string(type) + " Available types: gradient, rainbow. See README for details.");
		}

		/**
		 * Loads the preset document to the given xml document
		 * 
		 * @param document the xml document to load to
		 *
		 * @return the parse results
		 */
		xml_parse_result loadDocument(xml_document& document)
		{
			// Paths to check
			vector<string> paths;
			paths.push_back(string("."));
			paths.push_back(string("/usr/bin"));

			// Go through each path and break if file is found there
			xml_parse_result result;
			for (vector<string>::iterator i = paths.begin(); i != paths.end(); ++i)
			{
				result = document.load_file((*i + "/" + PRESET_DOCUMENT).c_str());
				if (result) break;
			}

			// Return parse result
			return result;
		}

		/**
		 * Initializes presets
		 *
		 * @throw Error upon error parsing preset document
		 */
		void initPresets() throw (Error)
		{
			// Default preset
			preset["rainbow"] = new RainbowMapRGB();

			// Read cmapdoc (error if fail)
			xml_document cmapdoc;
			xml_parse_result result = loadDocument(cmapdoc);
			if (!result) throw Error("When reading preset document (" + PRESET_DOCUMENT + ") - " + result.description());

			// For every entry in the colormap doc
			string name;
			for (xml_node entry = cmapdoc.child("entry"); entry; entry = entry.next_sibling("entry"))
			{
				// Get name
				name = string(entry.child("name").text().get());

				// Error if name is empty
				if (name.empty())
					throw Error("When reading preset document (" + PRESET_DOCUMENT + ") - Entity does not have defined name");
				
				// Set name in preset to colormap
				preset[name] = parseColorMap(entry.child("colormap"));
			}
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