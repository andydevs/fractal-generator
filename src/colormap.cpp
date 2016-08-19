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
		m_freqR(DEFAULT_FREQ_R), m_freqG(DEFAULT_FREQ_G), m_freqB(DEFAULT_FREQ_B),
		m_width(DEFAULT_WIDTH), m_center(DEFAULT_CENTER) {}

		/**
		 * Creates a RainbowMapRGB with the given phase shifts, frequencies, center, and width
		 *
		 * @param phaseR the phase shift of red
		 * @param phaseG the phase shift of green
		 * @param phaseB the phase shift of blue
		 * @param freqR  the frequency of red
		 * @param freqG  the frequency of green
		 * @param freqB  the frequency of blue
		 * @param width  the width of the sine wave
		 * @param center the center of the sine wave
		 */
		RainbowMapRGB::RainbowMapRGB(
			double phaseR, double phaseG, double phaseB,
			double freqR, double freqG, double freqB,
			double width, double center): 
		ColorMapRGB(),
		m_phaseR(phaseR), m_phaseG(phaseG), m_phaseB(phaseB),
		m_freqR(freqR),   m_freqG(freqG),   m_freqB(freqB),
		m_width(width),   m_center(center) {}

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
				(short)(m_width * sin(m_freqR * angle + m_phaseR) + m_center),
				(short)(m_width * sin(m_freqG * angle + m_phaseG) + m_center),
				(short)(m_width * sin(m_freqB * angle + m_phaseB) + m_center)
			);
		}
	}
}