//#include "qdptcoord.cc"
//#include "shape_function.cc"
//#include "shape_function_dr.cc"
//#include "int_weight.cc"
//#include "mapping.cc"
#include <Eigen/Dense>
#include "pumi.h"

void EleLoad(Eigen::VectorXd &Fe, pMeshEnt edge, 
	pMesh mesh, double trac_value[], int ned)
{
	int nint = 2;
	if(pumi_shape_hasNode(pumi_mesh_getShape(mesh),PUMI_EDGE))
		nint = 3;
	//because integration on load 
	//is one dimension off the mesh dimension

	//initialize the force vector
	for (int i = 0; i < ndof*ned; ++i)
	{
		Fe(i) = 0;
	}

	/*The integration points:
	Coords and the weights*/
	double xi_list[nint][nsd];
	qdpt_coord(xi_list, nint, nsd-1);
	double weights[nint];
	int_weight(weights, nint, nsd-1);

	//get the coords in the physical space
	double coord_local[ned][nsd];
	pShape s = pumi_mesh_getShape(mesh);
	if (pumi_shape_getNumNode(s, PUMI_EDGE) == 0)
	{//for linear mesh
		std::vector<pMeshEnt> vertices;
		pumi_ment_getAdj(edge, 0, vertices);
		for (int ied = 0; ied < ned; ++ied)
		{
			double x[nsd];
			pumi_node_getCoord(vertices[ied], 0, x);
			for (int isd = 0; isd < nsd; ++isd)
			{
				coord_local[ied][isd] = x[isd];
			}
		}
	}//end for linear mesh


	if (pumi_shape_getNumNode(s, PUMI_EDGE) == 1)
	{//quadratic mesh
		std::vector<pMeshEnt> vertices;
		pumi_ment_getAdj(edge, 0, vertices);
		for (int ied = 0; ied < ned-1; ++ied)
		{
			double x[nsd];
			pumi_node_getCoord(vertices[ied], 0, x);
			for (int isd = 0; isd < nsd; ++isd)
			{
				coord_local[ied][isd] = x[isd];
			}
		}
		double x[nsd];
		pumi_node_getCoord(edge, 0, x);
		for (int isd = 0; isd < nsd; ++isd)
			coord_local[ned-1][isd] = x[isd];
	}//end quadratic mesh


	//loop over quadrature points
	double xi[nsd];
	for (int iint = 0; iint < nint; ++iint)
	{
		for (int i = 0; i < nsd; ++i)
		{//assign integration point coords
			xi[i] = xi_list[iint][i];
		}
		//assign the shape functions
		double N[ned];
		shape_function(N, xi, 1, ned);
		//and its derivatives
		double dNdxi[ned][nsd];
		shape_function_dr(dNdxi, xi, 1, ned);
		
		//process the mapping
		double dxdxi[nsd][nsd];
		double dNdx[ned][nsd];
		//This function returns the jacobian determinant
		//and update the dxdxi and dNdx
		double j_det = mapping(dxdxi, dNdx, dNdxi, coord_local, ned, 1);
		for (int ied = 0; ied < ned; ++ied)
		{
			Fe(2*ied) += trac_value[0]*N[ied]*j_det*weights[iint];
			Fe(2*ied+1) += trac_value[1]*N[ied]*j_det*weights[iint];
		}
		std::cout<<"FE"<<Fe<<std::endl;
	}//end of loop over quadrature points
}