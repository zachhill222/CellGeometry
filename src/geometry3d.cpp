#include "geometry3d.hpp"



///////////////////// constructor and destructor ////////////////////////////
CellGeometry::Geometry3D::Geometry3D(const std::string fullfile)
{
	Geometry3D::read(fullfile);
}
CellGeometry::Geometry3D::Geometry3D(){}
CellGeometry::Geometry3D::~Geometry3D(){}


//////////////////// input/output functions /////////////////////////////////
void CellGeometry::Geometry3D::read(const std::string fullfile)
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
	geofile >> str >> Geometry3D::n[0];
	geofile >> str >> Geometry3D::n[1];
	geofile >> str >> Geometry3D::n[2];

	// set cell size
	for( int ii=0; ii<Geometry3D::dim; ii++)
	{
		if(Geometry3D::n[ii]>0)
		{
			Geometry3D::h[ii] = 1.0/Geometry3D::n[ii];
		}
	}

	// read geometry
	Geometry3D::stride[0] = Geometry3D::n[0];
	Geometry3D::stride[1]  = Geometry3D::n[1];
	Geometry3D::array = (int*) calloc( Geometry3D::n[0]*Geometry3D::n[1]*Geometry3D::n[2], sizeof(int) );

	// std::cout << "Reading Geometry\n";

	int ll;
	for ( int kk=0; kk < Geometry3D::n[2]; kk++)
	{
		for (int jj=0; jj < Geometry3D::n[1]; jj++)
		{
			for (int ii=0; ii < Geometry3D::n[0]; ii++)
			{
				ll = Geometry3D::getindex(ii,jj,kk);
				geofile >> Geometry3D::array[ll];
				// std::cout << ll << std::endl;
			}
		}
	}
	// close file
	geofile.close();
}

void CellGeometry::Geometry3D::saveas(const std::string fullfile)
{	// write to Geometry.dat type file
	// open file

	std::ofstream geofile(fullfile);

	if( not geofile.is_open() )
	{
		std::cout << "Couldn't write to " << fullfile << std::endl;
		geofile.close();
		return;
	}

	Geometry3D::print(geofile);
	

	// close file
	geofile.close();
}

/////////////////////////////////// utility functions /////////////////////////////////////////////
void CellGeometry::Geometry3D::print(std::ostream &stream)
{	// print geometry to output stream
	stream << "nx= " << Geometry3D::n[0] << std::endl;
	stream << "ny= " << Geometry3D::n[1] << std::endl;
	stream << "nz= " << Geometry3D::n[2] << std::endl;


	int ll;
	for (int kk=0; kk < Geometry3D::n[2]; kk++)
	{
		for (int jj=0; jj < Geometry3D::n[1]; jj++)
		{
			for (int ii=0; ii < Geometry3D::n[0]; ii++)
			{
				ll = Geometry3D::getindex(ii,jj,kk);
				stream << Geometry3D::array[ll] << " ";
			}
			stream << std::endl;
		}
		stream << std::endl;
	}
}

float CellGeometry::Geometry3D::porosity()
{
	float volume   = Geometry3D::n[0] * Geometry3D::n[1] * Geometry3D::n[2];
	float nvoid    = 0.0;
	int ll;
	for( int kk=0; kk < Geometry3D::n[2]; kk++)
	{
		for( int jj=0; jj < Geometry3D::n[1]; jj++)
		{
			for (int ii=0; ii < Geometry3D::n[0]; ii++)
			{
				ll = Geometry3D::getindex(ii,jj,kk);
				if( Geometry3D::array[ll] == 0)
				{
					nvoid+=1.0;
				}
			}
		}
	}

	return nvoid/volume;
}


/////////////////////////////////// manipulate geometry functions /////////////////////////////////
void CellGeometry::Geometry3D::swap(const int axis1, const int axis2)
{	
	if( axis1 >= axis2 or axis1 < 0 or axis2 >= Geometry3D::dim)
	{
		std::cout << "The arguments must satisfy 0 <= axis1 < axis2 < " << Geometry3D::dim << std::endl;
		return;
	}

	int temp1;

	//swap dimensions
	temp1 = Geometry3D::n[axis1];
	Geometry3D::n[axis1] = Geometry3D::n[axis2];
	Geometry3D::n[axis2] = temp1;

	
	//swap axis roles
	temp1  = Geometry3D::axisorder[axis1];
	Geometry3D::axisorder[axis1] = Geometry3D::axisorder[axis2];
	Geometry3D::axisorder[axis2] = temp1;
	
	//swap cell dimensions
	float temp2 = Geometry3D::h[axis1];
	Geometry3D::h[axis1] = Geometry3D::h[axis2];
	Geometry3D::h[axis2] = temp2;
}

void CellGeometry::Geometry3D::setaxes(const int axis1, const int axis2, const int axis3)
{
	const int order[3] = {axis1, axis2, axis3};

	for(int ii=0; ii<Geometry3D::dim-1; ii++)
	{
		if(order[ii] == Geometry3D::axisorder[ii])
			{
				continue;
			}

		for(int jj=ii+1; jj<Geometry3D::dim; jj++)
		{
			if(order[ii] == Geometry3D::axisorder[jj])
			{
				Geometry3D::swap(ii, jj);
			}
		}
	}
}



void CellGeometry::Geometry3D::pad(const int n, const int m)
{
	//allocate memory for padded array and inialize to 0
	int *newarray = (int*) calloc( (Geometry3D::n[0]+n+m)*Geometry3D::n[1]*Geometry3D::n[2], sizeof(int));

	//update stride for linear indexing
	int stride0 = Geometry3D::stride[0];
	int stride1 = Geometry3D::stride[1];

	if( Geometry3D::axisorder[0] == 0){stride0 += n+m;}
	if( Geometry3D::axisorder[0] == 1){stride1 += n+m;}

	//copy old array to new array
	int val, ll;
	for( int kk=0; kk<Geometry3D::n[2]; kk++)
	{
		for( int jj=0; jj<Geometry3D::n[1]; jj++)
		{
			for( int ii=0; ii<Geometry3D::n[0]; ii++)
			{
				ll  = Geometry3D::getindex(ii,jj,kk);
				val = Geometry3D::array[ll];

				ll  = Geometry3D::getnewindex(ii+n, jj, kk, stride0, stride1);
				newarray[ll] = val;
			}
		}
	}
	delete(Geometry3D::array);
	Geometry3D::array  = newarray;

	// update parameters
	Geometry3D::n[0] += n+m;
	Geometry3D::stride[0] = stride0;
	Geometry3D::stride[1] = stride1;
	return;
}

void CellGeometry::Geometry3D::trim(const int n, const int m)
{
	if( n+m >= Geometry3D::n[0])
	{
		std::cout << "Trimming too many values\n";
		return; 
	}

	//allocate memory for padded array and inialize to 0
	int *newarray = (int*) calloc( (Geometry3D::n[0]-n-m)*Geometry3D::n[1]*Geometry3D::n[2], sizeof(int));

	//update stride for linear indexing
	int stride0 = Geometry3D::stride[0];
	int stride1 = Geometry3D::stride[1];

	if( Geometry3D::axisorder[0] == 0){stride0 -= (n+m);}
	if( Geometry3D::axisorder[0] == 1){stride1 -= (n+m);}

	//copy old array to new array
	int val, ll;
	for( int kk=0; kk<Geometry3D::n[2]; kk++)
	{
		for( int jj=0; jj<Geometry3D::n[1]; jj++)
		{
			for( int ii=n; ii<Geometry3D::n[0]-m; ii++)
			{
				ll  = Geometry3D::getindex(ii,jj,kk);
				val = Geometry3D::array[ll];

				ll  = Geometry3D::getnewindex(ii-n, jj, kk, stride0, stride1);
				newarray[ll] = val;
			}
		}
	}
	delete(Geometry3D::array);
	Geometry3D::array  = newarray;

	// update parameters
	Geometry3D::n[0] -= (n+m);
	Geometry3D::stride[0] = stride0;
	Geometry3D::stride[1] = stride1;
	return;
}


void CellGeometry::Geometry3D::trim_all(const int n)
{
	// save initial order
	const int order[3] = {Geometry3D::axisorder[0], Geometry3D::axisorder[1], Geometry3D::axisorder[2]};

	//trim first axis
	Geometry3D::setaxes(0,1,2);
	Geometry3D::trim(n,n);

	//trim second axis
	Geometry3D::setaxes(1,2,0);
	Geometry3D::trim(n,n);

	//triim third axis
	Geometry3D::setaxes(2,0,1);
	Geometry3D::trim(n,n);

	//put geometry in the correct orientation

	Geometry3D::setaxes(order[0],order[1],order[2]);
	return;
}


//////////////////////////////////// helper functions ///////////////////////////////////////////////
int CellGeometry::Geometry3D::getindex(const int ii, const int jj, const int kk)
{
	return Geometry3D::getnewindex(ii, jj, kk, Geometry3D::stride[0], Geometry3D::stride[1]);
}

int CellGeometry::Geometry3D::getnewindex(const int ii, const int jj, const int kk, const int stride1, const int stride2)
{
	const int index[3] = {ii, jj, kk};
	int ll=0;

	// first storage axis
	for(int ii=0; ii<Geometry3D::dim; ii++)
	{
		if(Geometry3D::axisorder[ii] == 0)
		{
			ll += index[ii];
		}
	}

	// second storage axis
	for(int ii=0; ii<Geometry3D::dim; ii++)
	{
		if(Geometry3D::axisorder[ii] == 1)
		{
			ll += stride1*index[ii];
		}
	}

	// third storage axis
	for(int ii=0; ii<Geometry3D::dim; ii++)
	{
		if(Geometry3D::axisorder[ii] == 2)
		{
			ll += stride1*stride2*index[ii];
		}
	}
	return ll;
}

std::string CellGeometry::Geometry3D::getaxisorder()
{
	std::string order = "";
	const std::string names = "xyz";

	for( int ii=0; ii<Geometry3D::dim; ii++)
	{
		order += names[Geometry3D::axisorder[ii]];
	}

	return order;
}