#pragma once
// #include "geometry2d.hpp"
#include "geometry3d.hpp"
#include <string>

namespace CellGeometry
{
	/*
	class HybgeParam2D
	{
	public:
		CellGeometry::Geometry2D geometry;

		int solver_max_iterations       = 1000;
		float solver_absolute_tolerance = 1e-8;
		float solver_relative_tolerance = 1e-6;
		int solver_verbose              = 2;

		void saveas(const std::string fullfile);
	};
	*/
	
	class HybgeParam3D
	{
	public:
		HybgeParam3D();
		HybgeParam3D(const std::string fullfile);

		CellGeometry::Geometry3D geometry;

		int solver_max_iterations       = 1000;
		float solver_absolute_tolerance = 1e-8;
		float solver_relative_tolerance = 1e-6;
		int solver_verbose              = 2;

		void saveas(const std::string fullfile);
	};
}