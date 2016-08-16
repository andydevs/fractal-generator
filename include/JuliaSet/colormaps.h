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

/**
 * Defines a colormap function
 *
 * @param iterations the number of iterations being denoted
 *
 * @return a color integer
 */
typedef unsigned (*colormap)(unsigned iterations);

/**
 * Black to white colormapping
 *
 * @param iterations the number of iterations being denoted
 *
 * @return a color integer
 */
unsigned blackToWhite(unsigned iterations);

/**
 * White to black colormapping
 *
 * @param iterations the number of iterations being denoted
 *
 * @return a color integer
 */
unsigned whiteToBlack(unsigned iterations);


#endif