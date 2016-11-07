//-----------------------------------------------------------------------------------
// Program: Fractal
// 
// Generates Julia and Mandelbrot Set fractal images
//
// Author:  Anshul Kharbanda
// Created: 8 - 14 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "Fractal/error.h"

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
	 * Creates an Error with the given message
	 *
	 * @param message the message to store
	 */
	Error::Error(const char* message): exception(), m_message(message)
	{}

	/**
	 * Creates an Error with the given message
	 *
	 * @param message the message to store
	 */
	Error::Error(string message): exception(), m_message(message)
	{}

	/**
	 * Copy constructor for Error
	 *
	 * @param other the other Error to copy
	 */
	Error::Error(const Error& other): exception(other), m_message(other.m_message)
	{}

	/**
	 * Destroys the error
	 */
	Error::~Error() throw() {}

	/**
	 * Returns the message of the Error
	 *
	 * @return the message of the Error
	 */
	const char* Error::what() const throw()
	{
		return m_message.c_str();
	}
}