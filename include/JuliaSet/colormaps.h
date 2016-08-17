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

// Headers being used
#include "colormap.h"

/**
 * Black to White mapping
 */
const GradientMapRGB BLACK_TO_WHITE(0x000000, 0xffffff);

/**
 * White to Black mapping
 */
const GradientMapRGB WHITE_TO_BLACK(0xffffff, 0x000000);

/**
 * Blue to Yellow mapping
 */
const GradientMapRGB BLUE_TO_YELLOW(0x002f6c, 0xffc600);

#endif