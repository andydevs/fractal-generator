//-----------------------------------------------------------------------------------
// Program: Fractal
// 
// Generates Julia and Mandelbrot Set fractal images
//
// Author:  Anshul Kharbanda
// Created: 8 - 14 - 2016
//-----------------------------------------------------------------------------------

#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

// Libraries being used
#include <pugixml-1.7/src/pugixml.hpp>
#include <complex>

/**
 * Contains functions and structs used by Fractal generator
 * 
 * @author  Anshul Kharbanda
 * @created 8 - 17 - 2016
 */
namespace fractal
{
	/**
	 * The complex space scale value
	 */
	const double SCALE = 4.0;

	/**
	 * Default zoom
	 */
	const double DEFAULT_ZOOM = 1.0;

	/**
	 * Default offset
	 */
	const std::complex<double> DEFAULT_OFFSET(0,0);

	/**
	 * Default rotation
	 */
	const double DEFAULT_ANGLE = 0;

	/**
	 * Parses rectangle complex from XML
	 * 
	 * @param xml the rectangle complex xml
	 * 
	 * @return complex parsed from XML
	 */
	std::complex<double> rectFromXML(pugi::xml_node xml);

	/**
	 * Parses polar complex from XML
	 * 
	 * @param xml the polar complex xml
	 * 
	 * @return complex parsed from XML
	 */
	std::complex<double> polarFromXML(pugi::xml_node xml);

	/**
	 * Image size (height and width)
	 *
	 * @author  Anshul Kharbanda
	 * @created 10 - 29 - 2016
	 */
	struct ImgSize
	{
		/**
		 * The width of the image
		 */ 
		unsigned width;

		/**
		 * The height of the image
		 */
		unsigned height;

		/**
		 * Creates an empty ImgSize
		 */
		ImgSize();

		/**
		 * Creates a ImgSize with the given width and height
		 *
		 * @param w the width of the image
		 * @param h the height of the image
		 */
		ImgSize(unsigned w, unsigned h);

		/**
		 * Copy constructor for ImgSize
		 *
		 * @param other the other ImgSize to copy
		 */
		ImgSize(const ImgSize& other);

		/** 
		 * Creates a ImgSize with the given xml
		 *
		 * @param xml the image xml
		 */
		ImgSize(pugi::xml_node xml);

		/**
		 * Returns the area of the image
		 *
		 * @return the area of the image
		 */
		unsigned area();
	};

	/**
	 * Image transform parameters
	 *
	 * @author  Anshul Kharbanda
	 * @created 8 - 28 - 2016
	 */
	struct Transform
	{
		/**
		 * The image size
		 */
		ImgSize size;

		/**
		 * The zoom scale of the image
		 */
		double zoom;

		/**
		 * The offset of the image
		 */
		std::complex<double> offset;

		/**
		 * The shift complex
		 */
		std::complex<double> shift;

		/**
		 * The rotation complex
		 */
		std::complex<double> rotation;

		/**
		 * Creates an empty transform
		 */
		Transform();

		/**
		 * Creates a default transform with the given size
		 *
		 * @param s the size of the image
		 */
		Transform(ImgSize s);

		/**
		 * Creates a transform with the given parameters
		 *
		 * @param s the size of the image
		 * @param z the zoom scale of the image
		 * @param x the x offset of the image
		 * @param y the y offset of the image
		 * @param a the rotation angle of the image
		 */
		Transform(ImgSize s, double z, double x, double y, double a);

		/**
		 * Creates a transform with the given s and xml
		 *
		 * @param s   the size of the image
		 * @param xml the transform xml
		 */
		Transform(ImgSize s, pugi::xml_node xml);

		/**
		 * Copy constructor for transform
		 *
		 * @param other the other transform to copy
		 */
		Transform(const Transform& other);

		/**
		 * Returns the complex number mapped at the given pixel by the transform
		 *
		 * @param x the x coord of the pixel
		 * @param y the y coord of the pixel
		 *
		 * @return the complex number mapped at the given pixel by the transform
		 */
		std::complex<double> operator()(const double& x, const double& y);
	};
}

#endif