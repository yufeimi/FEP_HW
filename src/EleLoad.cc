#include "qdptcoord.cc"
#include "shape_function.cc"
#include "shape_function_dr.cc"
#include "int_weight.cc"
#include "mapping.cc"

void EleTraction(double Fe[], int element_num, int IEN[][nen], 
	double coord[][nsd])
{
	//iniialize the element stiffness matrix Ke
	for (int i = 0; i < ndof*nen; ++i)
	{
		Fe[i] = 0;
	}

	int nint_load;//because integration on load 
	//is one dimension off the mesh dimension

	if (nsd = 2)
	{
		nint_load = 2;
	}

	/*The integration points:
	Coords and the weights*/
	double xi_list[nint_load][nsd];
	qdpt_coord(xi_list, nint_load, nsd-1);
	double weights[nint_load];
	int_weight(weights, nint_load, nsd-1);

	//get the coords in the physical space
	double coord_local[nen][nsd];
	for (int i = 0; i < nen; ++i)
	{
		for (int j = 0; j < nsd; ++j)
		{
			coord_local[i][j] = coord[IEN[element_num][i]][j];
		}
	}

	//loop over quadrature points
	double xi[nsd];
	for (int iint = 0; iint < nint_load; ++iint)
	{
		for (int i = 0; i < nsd; ++i)
		{//assign integration point coords
			xi[i] = xi_list[iint][i];
		}
		//assign the shape functions
		double N[nen];
		shape_function(N, xi, nint_load, nsd-1);
		//and its derivatives
		double dNdxi[nen][nsd];
		shape_function_dr(dNdxi, xi, nint_load, nsd-1);
		
		//process the mapping
		double dxdxi[nsd][nsd];
		double dNdx[nen][nsd];
		//This function returns the jacobian determinant
		//and update the dxdxi and dNdx
		double j_det = mapping(dxdxi, dNdx, dNdxi, coord_local);



	}//end of loop over quadrature points
}