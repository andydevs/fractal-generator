//-----------------------------------------------------------------------------------
// Program: Fractal
// 
// Generates Julia and Mandelbrot Set fractal images
//
// Author:  Anshul Kharbanda
// Created: 8 - 14 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "Fractal/transform.h"

// Libraries being used
#include <cmath>

// Libraries being used
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
	 * Parses rectangle complex from XML
	 * 
	 * @param xml the rectangle complex xml
	 * 
	 * @return complex parsed from XML
	 */
	complex<double> rectFromXML(pugi::xml_node xml)
	{
		return xml 
			? complex<double>(
				xml.attribute("real").as_double(),
				xml.attribute("imag").as_double())
			: complex<double>(0,0);
	}
	
	/**
	 * Creates an empty ImgSize
	 */
	ImgSize::ImgSize():
	width(0), height(0) {}

	/**
	 * Creates a ImgSize with the given width and height
	 *
	 * @param w the width of the image
	 * @param h the height of the image
	 */
	ImgSize::ImgSize(unsigned w, unsigned h):
	width(w), height(h) {}

	/** 
	 * Creates a ImgSize with the given xml
	 *
	 * @param xml the image xml
	 */
	ImgSize::ImgSize(pugi::xml_node xml):
	width(xml.attribute("width").as_uint()),
	height(xml.attribute("height").as_uint()) {}

	/**
	 * Copy constructor for ImgSize
	 *
	 * @param other the other ImgSize to copy
	 */
	ImgSize::ImgSize(const ImgSize& other):
	width(other.width), height(other.height) {}

	/**
	 * Returns the area of the image
	 *
	 * @return the area of the image
	 */
	unsigned ImgSize::area() 
	{
		return width*height;
	}

	/**
	 * Creates an empty transform
	 */
	Transform::Transform():
	size(ImgSize()),
	zoom(DEFAULT_ZOOM),
	offset(DEFAULT_OFFSET),
	shift(0.5,0.5),
	rotation(1.0,DEFAULT_ANGLE) {}

	/**
	 * Creates a default transform with the given size
	 *
	 * @param s the size of the image
	 */
	Transform::Transform(ImgSize s):
	size(s),
	zoom(DEFAULT_ZOOM),
	offset(DEFAULT_OFFSET),
	shift(0.5*s.width,0.5*s.height),
	rotation(1.0,0) {}

	/**
	 * Creates a transform with the given parameters
	 *
	 * @param s the size of the image
	 * @param z the zoom scale of the image
	 * @param x the x offset of the image
	 * @param y the y offset of the image
	 * @param a the rotation angle of the image
	 */
	Transform::Transform(ImgSize s, double z, double x, double y, double a):
	size(s),
	zoom(z), offset(x, y),
	shift(0.5*s.width, 0.5*s.height),
	rotation(polar(1.0, a * M_PI / 180)) {}

	/**
	 * Creates a transform with the given s and xml
	 *
	 * @param s   the size of the image
	 * @param xml the transform xml
	 */
	Transform::Transform(ImgSize s, pugi::xml_node xml):
	size(s), shift(0.5*size.width, 0.5*size.height)
	{
		zoom     = xml.attribute("zoom").as_double(DEFAULT_ZOOM);
		offset   = rectFromXML(xml.child("offset"));
		rotation = polar(1.0, xml.attribute("angle").as_double(0) * M_PI / 180);
	}

	/**
	 * Copy constructor for transform
	 *
	 * @param other the other transform to copy
	 */
	Transform::Transform(const Transform& other):
	size(other.size), zoom(other.zoom), offset(other.offset),
	shift(other.shift), rotation(other.rotation) {}

	/**
	 * Returns the complex number mapped at the given pixel by the transform
	 *
	 * @param x the x coord of the pixel
	 * @param y the y coord of the pixel
	 *
	 * @return the complex number mapped at the given pixel by the transform
	 */
	complex<double> Transform::operator()(const double& x, const double& y)
	{
		return (SCALE / size.height / zoom) * (complex<double>(x,y) - shift) * rotation + offset;
	}
}