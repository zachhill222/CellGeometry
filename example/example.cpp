#include "cellgeometry.hpp"
#include <iostream>

#include <string>

int main()
{
	CellGeometry::HybgeParam3D param("Geometry.dat");
	std::cout << "Read geometry file\n";

	param.geometry.trim_all(1);
	std::cout << "Trimmed 1 cell from all sides\n";

	std::cout << "Changed axis order from " << param.geometry.getaxisorder();
	param.geometry.setaxes(1,0,2);
	std::cout << " to " << param.geometry.getaxisorder() << std::endl;

	param.geometry.pad(2);
	std::cout << "Padded 2 cells to the first axis\n";

	param.geometry.saveas("AlteredGeometry.dat");
	std::cout << "Saved geometry\n";

	param.saveas("Parameters.dat");
	std::cout << "Saved parameters\n";
	return 0;
}