//-----------------------------------------------------------------------------------
// Program: Fractal
// 
// Generates Julia and Mandelbrot Set fractal images
//
// Author:  Anshul Kharbanda
// Created: 8 - 14 - 2016
//-----------------------------------------------------------------------------------

#ifndef _ERROR_H_
#define _ERROR_H_

// Libraries being used
#include <exception>
#include <string>

/**
 * Contains functions and structs used by Fractal generator
 * 
 * @author  Anshul Kharbanda
 * @created 8 - 17 - 2016
 */
namespace fractal
{
	/**
	 * Thrown upon an error with the program
	 *
	 * @author  Anshul Kharbanda
	 * @created 11 - 7 - 2016
	 */
	class Error: public std::exception
	{
	private:
		/**
		 * The message of the error
		 */
		std::string m_message;
	public:
		/**
		 * Creates an Error with the given message
		 *
		 * @param message the message to store
		 */
		Error(const char* message);

		/**
		 * Creates an Error with the given message
		 *
		 * @param message the message to store
		 */
		Error(std::string message);

		/**
		 * Copy constructor for Error
		 *
		 * @param other the other Error to copy
		 */
		Error(const Error& other);

		/**
		 * Destroys the error
		 */
		~Error() throw();

		/**
		 * Returns the message of the Error
		 *
		 * @return the message of the Error
		 */
		const char* what() const throw();
	};
}

#endif