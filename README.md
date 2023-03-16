## Installation ##

Installation setup: extract include, src, and Makefile to some folder ROOT

ROOT/include: *.hpp files

ROOT/src: *.cpp files

ROOT/Makefile


Call make from the terminal shell to compile the CellGeometry library. This will add ROOT/lib and ROOT/obj folders.

	shell$ make

ROOT/lib/libcellgeometry.a

ROOT/obj: *.o files

## Example ##
After instalation run the following commands to compile and run the example code.

	shell$ cd ROOT/example
	shell$ make
	shell$ ./example

## Citation ##
	Hilliard, Z., "CellGeometry", Package Version 0.1
	https://github.com/zachhill222/CellGeometry.git
