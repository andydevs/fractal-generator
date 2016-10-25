# JuliaSet

A program that generates Julia Set images.

![Julia Set Image](fimage.jpg)

## The Algorithm

This algorithm generates images that represent the interesting behaviour of complex numbers.

### The imaginary number (i)

The square root of -1 is defined as `i`. This number doesn't exist naturally, but it is used often for it's unique properties. When multiplied by a real constant, say `b`, the result is an imaginary number `bi`, the square of which will be negative the square of the constant, or `-b^2`, since `i^2 = -1`.

### Complex Numbers

A complex number can be defined as the sum of a real number with an imaginary number `a + bi`. The sum of two complex numbers is simply the sums of the real components plus the sums of the imaginary components

	(a + bi) + (c + di) = (a + b) + (c + d)i

The product of two complex numbers is more interesting. The components must be distributed with each other, but since `i^2 = -1`, the product of the two imaginary components is a _negative_ real number, rather than positive. So the real of the product is the difference of the two real product terms.

	(a + bi)(c + di) = (ac - bd) + (ad + bc)i

Consider two complex numbers represented as shown:

	A = r*(cos(a) + sin(a)i)
	B = s*(cos(b) + sin(b)i)

The product of these two numbers reveals a new property of complex numbers:

	A*B = r*(cos(a) + sin(a)i) * s*(cos(b) + sin(b)i)
		= r*s*((cos(a)cos(b) - sin(a)sin(b)) + (cos(a)sin(b) + sin(a)cos(b))i)

		= r*s*(cos(a + b) + sin(a + b)i)

Complex numbers can be represented as vectors on an xy grid, where the x component of the vector represents the real component, and the y component of the vector represents the imaginary component. The product of two complex numbers, then, can be represented by the vector whose magnitude is the product of the magnitudes of the two complex vectors and whose angle is the sum of the angles of the two complex vectors. Naturally, then, the square of a complex number, will be a complex vector with a magnitude equal to the square of the original magnitude, and an angle equal to twice the original angle.

### Iteration

Consider a complex function `f(z) = z^2 + c`, where `c` is a constant.

## Usage

### Installation (Clone and build)

NOTE: Project can only be built on bash-based platform.

Make sure that you have make and g++ installed. Both of these can be acquired using `apt-get`. Clone the git repository into your local machine using `git clone` and entering the remote repository. You can then build and install using `make install`. This will build the project and install the binary in `/usr/bin`.

### Command line interface

The program uses CImg option parsing to retrieve command line arguments. To set options, type the name of the option, followed by the value of the option: `$ juliaset -[name] [value] ...`. If the value is a boolean, you can just type the name of the option to set it to true: `$ juliaset -[boolean-option]`. Options do not have to be put in any order.

Here are a list of options:

|    Option     |                                 Description                                 |  Defaults  |
|:-------------:|:---------------------------------------------------------------------------:|:----------:|
|     -cr       | The real component of the complex constant                                  | 0.0        |
|     -ci       | The imaginary component of the complex constant                             | 0.0        |
|     -mbrot    | Generates the mandelbrot set image (overrides -cr and -ci)                  | false      |
|     -imgx     | The width of the image                                                      | 1920       |
|     -imgy     | The height of the image                                                     | 1080       |
|     -zoom     | The zoom scale of the image                                                 | 1.0        |
|     -offx     | The x offset of the image                                                   | 0.0        |
|     -offy     | The y offset of the image                                                   | 0.0        |
|     -rot      | The angle of rotation of the image                                          | 0.0        |
|     -save     | The filename to save to                                                     | jimage.jpg |
|     -cmap     | The colormapping used (see gallery to look at colormaps)                    | rainbow    |
|     -cmaps    | Lists all of the colormaps and returns (overrides all options)              | false      |
|     -test     | Generates a 400x300 test image (saved to the savename) for the set colormap | false      |
| -help (or -h) | Prints the help message                                                     | false      |