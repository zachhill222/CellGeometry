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

## Contact ##
- Zachary Hilliard, hilliarz@oregonstate.edu or zach.hill222@gmail.com
	
## Contributors ##
- Zachary Hilliard

## Change Log ##
v0.1: Base functionality
- CellGeometry::Geometry3D::read() 		//read geometry files
- CellGeometry::Geometry3D::saveas() 		//write geometry files
- CellGeometry::Geometry3D::swap() 		//change indexing to swap two axes
- CellGeometry::Geometry3D::setaxes() 		//flip axes indexing to specified order
- CellGeometry::Geometry3D::pad() 		//append zeros to first axis (to the front or back of the geometry)
- CellGeometry::Geometry3D::trim() 		//trim entries from first axis (from the front or back)
- CellGeometry::Geometry3D::trimall() 		//trim entries from all sides of geometry
- CellGeometry::Geometry3D::print() 		//print geometry to output file stream
- CellGeometry::Geometry3D::porosity() 		//return the porosity of the geometry counting 0 as void and non-zero as solid
- CellGeometry::Geometry3D::getaxisorder() 	//return the current axis order (default 'xyz', 'zxy' after calling setaxis(2,0,1) )
- CellGeometry::HybgeParam3D::saveas()		//save Parameter.dat file for use with HybGe-Flow3D

## Acknowledgements ##
This library was originally designed to pre-process geometries for HybGe-Flow3D.

	Costa, T., "HybGe-Flow3D", Package Version 3.0.0,
	http://github.com/numsol/HybGe-Flow3D.
