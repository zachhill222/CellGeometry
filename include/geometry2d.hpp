#pragma once

namespace CellGeometry
{
	class Geometry2D
	{
	public:
		Geometry2D();
		~Geometry2D();

		// io functions
		void read(const char* fullfile); // read from file
		void saveas(const char* fullfile); // save geometry file


		// manipulate geometry functions
		void swap(); //swap x and y axes
		void pad(const int n); //pad x axis with zeros	(from the front)
		void trim(const int n); //trim first n values from the x-axis

		// utility functions
		void print(); // print array to standard out
		float porosity(); //return porosity


		// physical geometry properties
		int nx = 0;
		int ny = 0;
		int nz = 0;

		float hx = 0.0;
		float hy = 0.0;
		float hz = 0.0;

		float xlim[2];
		float ylim[2];
		float zlim[2];

	private:
		// geometry storage
		int xaxis = 0;
		int yaxis = 1;

		int indexlength;
		int* array;

		int getindex(const int ii, const int jj);
		int getindex(const int ii, const int jj, const int length);
	};
}