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
#include "CImg/CImg.h"

// Libraries being used
#include <cmath>

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
		 * Creates a GradientMapRGB from the given xml
		 *
		 * @param xml the xml representing the colormap
		 */
		GradientMapRGB::GradientMapRGB(pugi::xml_node xml):
		ColorMapRGB(),
		m_start(xml.child("start").text().as_uint()),
		m_gradient(xml.child("start").text().as_uint(),
				   xml.child("end").text().as_uint()) {}

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

		/**
		 * Creates a default RainbowMapRGB
		 */
		RainbowMapRGB::RainbowMapRGB(): ColorMapRGB(),
		m_phaseR(DEFAULT_PHASE_R), m_phaseG(DEFAULT_PHASE_G), m_phaseB(DEFAULT_PHASE_B),
		m_freqR(DEFAULT_FREQ_R),   m_freqG(DEFAULT_FREQ_G),   m_freqB(DEFAULT_FREQ_B) {}

		/**
		 * Creates a RainbowMapRGB with the given phase shifts, frequencies, center, and width
		 *
		 * @param phaseR the phase shift of red
		 * @param phaseG the phase shift of green
		 * @param phaseB the phase shift of blue
		 * @param freqR  the frequency of red
		 * @param freqG  the frequency of green
		 * @param freqB  the frequency of blue
		 */
		RainbowMapRGB::RainbowMapRGB(
			double phaseR, double phaseG, double phaseB,
			double freqR, double freqG, double freqB): 
		ColorMapRGB(),
		m_phaseR(phaseR), m_phaseG(phaseG), m_phaseB(phaseB),
		m_freqR(freqR),   m_freqG(freqG),   m_freqB(freqB) {}

		/**
		 * Creates a RainbowMapRGB from the given xml
		 *
		 * @param xml the xml representing the colormap
		 */
		RainbowMapRGB::RainbowMapRGB(pugi::xml_node xml):
		ColorMapRGB()
		{
			// Parse phase xml
			if (xml.child("phase"))
			{
				m_phaseR = xml.child("phase").attribute("r").as_double();
				m_phaseG = xml.child("phase").attribute("g").as_double();
				m_phaseB = xml.child("phase").attribute("b").as_double();
			}
			else
			{
				m_phaseR = DEFAULT_PHASE_R;
				m_phaseG = DEFAULT_PHASE_G;
				m_phaseB = DEFAULT_PHASE_B;
			}

			// Parse freq xml
			if (xml.child("freq"))
			{
				m_freqR = xml.child("freq").attribute("r").as_double();
				m_freqG = xml.child("freq").attribute("g").as_double();
				m_freqB = xml.child("freq").attribute("b").as_double();
			}
			else
			{
				m_freqR = DEFAULT_FREQ_R;
				m_freqG = DEFAULT_FREQ_G;
				m_freqB = DEFAULT_FREQ_B;
			}
		}

		/**
		 * Maps the given number of iterations to a given color
		 *
		 * @param iterations the iterations being mapped
		 *
		 * @return the color calculated from the iterations
		 */
		ColorRGB RainbowMapRGB::color(unsigned iterations) const
		{
			// Change iterations space to radians
			double angle = iterations / 256.0 * (2*M_PI);

			// Generate color
			return ColorRGB(
				(short)(WIDTH * sin(m_freqR * angle + m_phaseR) + CENTER),
				(short)(WIDTH * sin(m_freqG * angle + m_phaseG) + CENTER),
				(short)(WIDTH * sin(m_freqB * angle + m_phaseB) + CENTER)
			);
		}
	}
}