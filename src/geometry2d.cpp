#include "geometry2d.hpp"
#include <iostream>
#include <fstream>
#include <string>


///////////////////// constructor and destructor ////////////////////////////
CellGeometry::Geometry2D::Geometry2D(){}
CellGeometry::Geometry2D::~Geometry2D(){}


//////////////////// input/output functions /////////////////////////////////
void CellGeometry::Geometry2D::read(const char* fullfile)
{   // read from Geometry.dat type file
	// open file
	std::ifstream geofile(fullfile);
	std::string str;

	if( not geofile.is_open() )
	{
		std::cout << "Could not open " << fullfile << std::endl;
		return;
	}
	
	// read header
	geofile >> str >> Geometry2D::nx;
	geofile >> str >> Geometry2D::ny;

	int nz;
	geofile >> str >> nz;
	if( nz > 0 )
	{
		std::cout << "You are using a 2D geometry class for a 3D geometry file\n";
	}

	// read geometry
	Geometry2D::indexlength = Geometry2D::nx;
	Geometry2D::array = (int*) calloc( Geometry2D::nx*Geometry2D::ny, sizeof(int) );

	Geometry2D::xlim[0] = 0;
	Geometry2D::xlim[1] = 1;

	Geometry2D::ylim[0] = 0;
	Geometry2D::ylim[1] = 1;

	Geometry2D::hx = (Geometry2D::xlim[1] - Geometry2D::xlim[0])/Geometry2D::nx;
	Geometry2D::hy = (Geometry2D::ylim[1] - Geometry2D::ylim[0])/Geometry2D::ny;

	// std::cout << "Reading Geometry\n";

	int ll;
	for (int jj=0; jj < Geometry2D::ny; jj++)
	{
		for (int ii=0; ii < Geometry2D::nx; ii++)
		{
			ll = Geometry2D::getindex(ii,jj);
			geofile >> Geometry2D::array[ll];
		}
	}

	// close file
	geofile.close();
}

void CellGeometry::Geometry2D::saveas(const char* fullfile)
{	// write to Geometry.dat type file
	// open file
	std::ofstream geofile(fullfile);
	
	if( not geofile.is_open() )
	{
		std::cout << "Couldn't write to " << fullfile << std::endl;
		return;
	}


	// write header
	geofile << "nx= " << Geometry2D::nx << std::endl;
	geofile << "ny= " << Geometry2D::ny << std::endl;
	geofile << "nz= " << Geometry2D::nz << std::endl;

	// write geometry
	int ll;
	for (int jj=0; jj < Geometry2D::ny; jj++)
	{
		for (int ii=0; ii < Geometry2D::nx; ii++)
		{
			ll = Geometry2D::getindex(ii,jj);
			geofile << Geometry2D::array[ll] << " ";
		}
		geofile << std::endl;
	}

	// close file
	geofile.close();
}

/////////////////////////////////// utility functions /////////////////////////////////////////////
void CellGeometry::Geometry2D::print()
{	// print geometry to std::cout
	std::cout << "xlim = [" << Geometry2D::xlim[0] << ", " << Geometry2D::xlim[1] << "]\n";
	std::cout << "nx= " << Geometry2D::nx << std::endl;
	std::cout << "ny= " << Geometry2D::ny << std::endl;

	int ll;

	for (int jj=0; jj < Geometry2D::ny; jj++)
	{
		std::cout << std::endl;
		for (int ii=0; ii < Geometry2D::nx; ii++)
		{
			ll = Geometry2D::getindex(ii,jj);
			std::cout << Geometry2D::array[ll] << " ";
		}
	}
	std::cout << std::endl;
}

float CellGeometry::Geometry2D::porosity()
{
	float volume   = Geometry2D::nx * Geometry2D::ny;
	float nvoid    = 0.0;
	int ll;

	for( int jj=0; jj < Geometry2D::ny; jj++)
	{
		for (int ii=0; ii < Geometry2D::nx; ii++)
		{
			ll = Geometry2D::getindex(ii,jj);
			if( Geometry2D::array[ll] == 0)
			{
				nvoid+=1.0;
			}
		}
	}

	return nvoid/volume;
}


/////////////////////////////////// manipulate geometry functions /////////////////////////////////
void CellGeometry::Geometry2D::swap()
{
	int temp1;
	float temp2;

	//swap dimensions
	temp1 = Geometry2D::nx;
	Geometry2D::nx = Geometry2D::ny;
	Geometry2D::ny = temp1;

	temp2 = Geometry2D::hx;
	Geometry2D::hx = Geometry2D::hy;
	Geometry2D::hy = temp2;

	for( int ii=0; ii<2; ii++)
	{
		temp2 = Geometry2D::xlim[ii];
		Geometry2D::xlim[ii] = Geometry2D::ylim[ii];
		Geometry2D::ylim[ii] = temp2;
	}
	

	//swap axis roles
	temp1  = Geometry2D::xaxis;
	Geometry2D::xaxis = Geometry2D::yaxis;
	Geometry2D::yaxis = temp1;
}

void CellGeometry::Geometry2D::pad(const int n)
{
	//allocate memory for padded array and inialize to 0
	int *newarray = (int*) calloc( (Geometry2D::nx+n)*Geometry2D::ny, sizeof(int));

	//determine stride for new array
	int newlength;
	if (Geometry2D::xaxis == 0)
	{
		newlength = Geometry2D::indexlength + n;
	}
	else
	{
		newlength = Geometry2D::indexlength;
	}

	//copy old array to new array
	int val, ll;
	for( int jj=0; jj<Geometry2D::ny; jj++)
	{
		for( int ii=0; ii<Geometry2D::nx; ii++)
		{
			val = Geometry2D::array[Geometry2D::getindex(ii,jj)];

			ll  = Geometry2D::getindex(ii+n,jj,newlength);
			newarray[ll] = val;
		}
	}

	free(Geometry2D::array);
	Geometry2D::array  = newarray;

	// update parameters
	Geometry2D::nx      += n;
	Geometry2D::xlim[0] -= Geometry2D::hx * n;
	Geometry2D::indexlength = newlength;
}

void CellGeometry::Geometry2D::trim(const int n)
{
	if( n >= Geometry2D::nx )
	{
		std::cout << "You are trimming too many values\n";
		return;
	}

	//allocate memory for padded array and inialize to 0
	int *newarray = (int*) calloc( (Geometry2D::nx-n)*Geometry2D::ny, sizeof(int));

	//determine stride for new array
	int newlength;
	if (Geometry2D::xaxis == 0)
	{
		newlength = Geometry2D::indexlength - n;
	}
	else
	{
		newlength = Geometry2D::indexlength;
	}

	//copy old array to new array
	int val, ll;
	for( int jj=0; jj<Geometry2D::ny; jj++)
	{
		for( int ii=n; ii<Geometry2D::nx; ii++)
		{
			val = Geometry2D::array[Geometry2D::getindex(ii,jj)];

			ll  = Geometry2D::getindex(ii-n,jj,newlength);
			newarray[ll] = val;
		}
	}

	free(Geometry2D::array);
	Geometry2D::array  = newarray;

	// update parameters
	Geometry2D::nx      -= n;
	Geometry2D::xlim[0] += Geometry2D::hx * n;
	Geometry2D::indexlength = newlength;
}


//////////////////////////////////// helper functions ///////////////////////////////////////////////
int CellGeometry::Geometry2D::getindex(const int ii, const int jj)
{
	if( Geometry2D::xaxis == 0 )
	{
		return jj*Geometry2D::indexlength + ii;
	}
	if( Geometry2D::yaxis == 0 )
	{
		return ii*Geometry2D::indexlength + jj;
	}

	return -1;
	
}
int CellGeometry::Geometry2D::getindex(const int ii, const int jj, const int length)
{
	if( Geometry2D::xaxis == 0 )
	{
		return jj*length+ ii;
	}
	if( Geometry2D::yaxis == 0 )
	{
		return ii*length + jj;
	}

	return -1;
	
}