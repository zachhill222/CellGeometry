#pragma once
#include <iostream>
#include <fstream>
#include <string>

namespace CellGeometry
{
	class Geometry3D
	{
	public:
		Geometry3D();
		Geometry3D(const std::string fullfile);
		~Geometry3D();
		
		
		// physical geometry properties
		static const int dim = 3;
		int n[dim];
		

		// io functions
		void read(const std::string fullfile); // read from file
		void saveas(const std::string fullfile); // save geometry file


		// manipulate geometry functions
		void swap(const int axis1, const int axis2); //swap the roles of two axes
		void setaxes(const int axis1, const int axis2, const int axis3); //[0,1,2] for original order
		void pad(const int n, const int m=0); //pad n zeros to the start of the first axis and m to the end
		void trim(const int n, const int m=0); //trim first n and last m values from the first axis
		void trim_all(const int n); //trim n entries from all sides of the geometry
		// utility functions
		void print(std::ostream &stream); // print array to output stream
		float porosity(); //return porosity
		std::string getaxisorder();

		float h[3] = {0.0, 0.0, 0.0};

	private:
		// geometry storage
		int axisorder[dim] = {0, 1, 2};

		int stride[dim-1];
		int* array;

		int getindex(const int ii, const int jj, const int kk);
		int getnewindex(const int ii, const int jj, const int kk, const int stride1, const int stride2);
	};
}