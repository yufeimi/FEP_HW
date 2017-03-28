#include "qdpt_coord.cc"
#include "shape_function.cc"
#include "shape_function_dr.cc"
#include "int_weight.cc"

void eleStiff(int element_num, int IEN[][nen], int ID[][ndof], 
	double coord[][nsd], int nen, int nsd)
{
	/*The integration points:
	Coords and the weights*/
	double xi_list[nint][nsd];
	qdptcoord(xi_list, nen, nsd);
	double weights[nint];
	int_weight(weights, nsd, nint);

	if (nsd == 2){
	double lambda = nu*young_mod/((1+nu)*(1-2*nu));//D parameter
	double mu = young_mod/(2*(1+nu));//D parameter
	//define the D matix
	double D[3][3] = {lambda+2*mu, lambda, 0,
				lambda, lambda+2*mu, 0,
				0, 0, mu};//only for 2-D case
	}

	//get the coords in the physical space
	for (int i = 0; i < ; ++i)
	{
		
	}
	//loop over quadrature points
	double xi[nsd];
	for (int iint = 0; iint < nint; ++iint)
	{
		for (int i = 0; i < nsd; ++i)
		{//assign integration point coords
			xi[i] = xi_list[iint][i];
		}
		//assign the shape functions
		double N[nint];
		shape_function(N, xi, shape, nsd, nen);
		//and its derivatives
		double dNdxi[nint][nsd];
		shape_function_dr(dNdxi, xi, shape, nsd, nen);
		
		//process the mapping
		double mapping();
	}
}