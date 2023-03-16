This library was built to read, manipulate, and write textfiles that represent three dimensional geometries.
The geometry is represented by an nx by ny by nz array of numbers (for example 0 for void space, 1 for material 1, 2 for material 2, etc.).
Geometries are stored in a text file with the following format:
	- Header specifying nx, ny, and nz
	- nz blocks of dimension ny by nx of material markers

Example: 5x3x2 geometry
nx= 5
ny= 3
nz= 2
0 1 2 3 4
1 2 3 4 0
2 3 4 0 1

4 3 2 1 0
3 2 1 0 4
2 1 0 4 3

This code was designed to pre-process geometries for HybGe-Flow3D and contains a class HybgeParam3D to write parameter files for this program.
If you are using this code for other reasons, use the Geometry3D class.


Instalation setup: extract include, src, and Makefile to some folder ROOT

ROOT/
	include
		- .hpp files
	src
		- .cpp files
	Makefile

Call make from the terminal shell to compile the CellGeometry library.

	shell$ make

ROOT/
	include
		- *.hpp files
	src
		- *.cpp files
	lib
		- libcellgeometry.a
	obj
		- *.o files
	Makefile



HybGe-Flow3D information:
Costa, T., "HybGe-Flow3D", Package Version 3.0.0,
http://github.com/numsol/HybGe-Flow3D.
