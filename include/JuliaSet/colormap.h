//-----------------------------------------------------------------------------------
// Program: JuliaSet
// 
// Generates Julia set images
//
// Author:  Anshul Kharbanda
// Created: 8 - 14 - 2016
//-----------------------------------------------------------------------------------

#ifndef _COLORMAP_H_
#define _COLORMAP_H_

// Headers being used
#include "color.h"

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
		 * Maps a given number of iterations made by the JuliaSet algorithm
		 * to a color to assign the pixel in question to
		 *
		 * @author  Anshul Kharbanda
		 * @created 8 - 16 - 2016
		 */
		class ColorMapRGB
		{
		public:
			/**
			 * Creates an empty ColorMapRGB
			 */
			ColorMapRGB();

			/**
			 * Destroys the ColorMapRGB
			 */
			~ColorMapRGB();

			/**
			 * Maps the given number of iterations to a given color
			 *
			 * @param iterations the iterations being mapped
			 *
			 * @return the color calculated from the iterations
			 */
			virtual ColorRGB color(unsigned iterations) const = 0;
		};

		/**
		 * Maps a given number of iterations to a color using a linear
		 * gradient between two colors
		 *
		 * @author  Anshul Kharbanda
		 * @created 8 - 16 - 2016
		 */
		class GradientMapRGB : public ColorMapRGB
		{
		private:
			/**
			 * The start color
			 */
			ColorRGB m_start;

			/**
			 * The color gradient
			 */
			ColorGradientRGB m_gradient;
		public:
			/**
			 * Creates a GradientMapRGB between the two given colors
			 *
			 * @param start the start color
			 * @param end   the end color
			 */
			GradientMapRGB(unsigned start, unsigned end);

			/**
			 * Maps the given number of iterations to a given color
			 *
			 * @param iterations the iterations being mapped
			 *
			 * @return the color calculated from the iterations
			 */
			ColorRGB color(unsigned iterations) const;
		};

		/**
		 * Maps a given number of iterations to a color
		 * using a rainbow gradient (using sine waves)
		 *
		 * @author  Anshul Kharbanda
		 * @created 8 - 19 - 2016
		 */
		class RainbowMapRGB: public ColorMapRGB
		{
		public:
			/**
			 * The center of the sine wave
			 */
			static const double CENTER  = 128;

			/**
			 * The width of the sine wave
			 */
			static const double WIDTH   = 127;

			/**
			 * The default phase shift of red
			 */
			static const double DEFAULT_PHASE_R = 2.0;

			/**
			 * The default phase shift of green
			 */
			static const double DEFAULT_PHASE_G = 0.0;

			/**
			 * The default phase shift of blue
			 */
			static const double DEFAULT_PHASE_B = 4.0;

			/**
			 * The default frequency of red
			 */
			static const double DEFAULT_FREQ_R  = 1.0;

			/**
			 * The default frequency of green
			 */
			static const double DEFAULT_FREQ_G  = 1.0;

			/**
			 * The default frequency of blue
			 */
			static const double DEFAULT_FREQ_B  = 1.0;
		private:
			/**
			 * The phase shift of red
			 */
			double m_phaseR;

			/**
			 * The phase shift of green
			 */
			double m_phaseG;

			/**
			 * The phase shift of blue
			 */
			double m_phaseB;

			/**
			 * The frequency of red
			 */
			double m_freqR;

			/**
			 * The frequency of green
			 */
			double m_freqG;

			/**
			 * The frequency of blue
			 */
			double m_freqB;

			/**
			 * The width of the sine wave
			 */
			double m_width;

			/**
			 * The center of the sine wave
			 */
			double m_center;
		public:
			/**
			 * Creates a default RainbowMapRGB
			 */
			RainbowMapRGB();

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
			RainbowMapRGB(double phaseR, double phaseG, double phaseB, double freqR, double freqG, double freqB);

			/**
			 * Maps the given number of iterations to a given color
			 *
			 * @param iterations the iterations being mapped
			 *
			 * @return the color calculated from the iterations
			 */
			ColorRGB color(unsigned iterations) const;
		};
	}
}

#endif