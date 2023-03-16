#include "hybge_param.hpp"
#include <iostream>
#include <fstream>
#include <string>

/*
void CellGeometry::HybgeParam2D::saveas(const std::string fullfile)
{ // write to hybge Parameters.dat type file
	// open file
	std::ofstream paramfile(fullfile);
	
	if( not paramfile.is_open() )
	{
		std::cout << "Couldn't write to " << fullfile << std::endl;
		return;
	}

	// write dimensions
	paramfile << "length= " << HybgeParam2D::geometry.nx * HybgeParam2D::geometry.hx << std::endl;
	paramfile << "width= "  << HybgeParam2D::geometry.ny * HybgeParam2D::geometry.hy << std::endl;
	paramfile << "height= " << HybgeParam2D::geometry.nz * HybgeParam2D::geometry.hz << std::endl;

	// write solver settings
	paramfile << "solver_max_iterations= "     << HybgeParam2D::solver_max_iterations     << std::endl;
	paramfile << "solver_absolute_tolerance= " << HybgeParam2D::solver_absolute_tolerance << std::endl;
	paramfile << "solver_relative_tolerance= " << HybgeParam2D::solver_relative_tolerance << std::endl;
	paramfile << "solver_verbose= "            << HybgeParam2D::solver_verbose;
}
*/

CellGeometry::HybgeParam3D::HybgeParam3D(const std::string fullfile)
{
	HybgeParam3D::geometry = CellGeometry::Geometry3D(fullfile);
}

CellGeometry::HybgeParam3D::HybgeParam3D(){}

void CellGeometry::HybgeParam3D::saveas(const std::string fullfile)
{ // write to hybge Parameters.dat type file
	// open file
	std::ofstream paramfile(fullfile);
	
	if( not paramfile.is_open() )
	{
		std::cout << "Couldn't write to " << fullfile << std::endl;
		return;
	}

	// write dimensions
	paramfile << "length= " << HybgeParam3D::geometry.n[0] * HybgeParam3D::geometry.h[0] << std::endl;
	paramfile << "width= "  << HybgeParam3D::geometry.n[1] * HybgeParam3D::geometry.h[1] << std::endl;
	paramfile << "height= " << HybgeParam3D::geometry.n[2] * HybgeParam3D::geometry.h[2] << std::endl;

	// write solver settings
	paramfile << "solver_max_iterations= "     << HybgeParam3D::solver_max_iterations     << std::endl;
	paramfile << "solver_absolute_tolerance= " << HybgeParam3D::solver_absolute_tolerance << std::endl;
	paramfile << "solver_relative_tolerance= " << HybgeParam3D::solver_relative_tolerance << std::endl;
	paramfile << "solver_verbose= "            << HybgeParam3D::solver_verbose;
}