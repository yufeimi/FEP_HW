#include <Eigen/Dense>
#include "pumi.h"

void EleBodyForce(Eigen::VectorXd &Fe, pMeshEnt element, 
	pMesh mesh, int nen)
{
	int nint = 0;
	if (pumi_ment_getTopo(element) == PUMI_QUAD)
	{
		nint = 4;
	}else if (pumi_ment_getTopo(element) == PUMI_TRIANGLE)
	{
		nint = 1;
	}

	//initialize the force vector
	for (int i = 0; i < ndof*nen; ++i)
		{
			Fe(i) = 0;
		}

	/*The integration points:
	Coords and the weights*/
	double xi_list[nint][nsd];
	qdpt_coord(xi_list, nint, nsd);
	double weights[nint];
	int_weight(weights, nint, nsd);

	//get the coords in the physical space
	double coord_local[nen][nsd];
	pShape s = pumi_mesh_getShape(mesh);
	if (pumi_shape_getNumNode(s, PUMI_EDGE) == 0)
	{//for linear mesh
		std::vector<pMeshEnt> vertices;
		pumi_ment_getAdj(element, 0, vertices);
		for (int ien = 0; ien < nen; ++ien)
		{
			double x[nsd];
			pumi_node_getCoord(vertices[ien], 0, x);
			for (int isd = 0; isd < nsd; ++isd)
			{
				coord_local[ien][isd] = x[isd];
			}
		}
	}//end for linear mesh


	//loop over quadrature points
	double xi[nsd];
	for (int iint = 0; iint < nint; ++iint)
	{
		for (int i = 0; i < nsd; ++i)
		{//assign integration point coords
			xi[i] = xi_list[iint][i];
		}
		//assign the shape functions
		double N[nen];
		shape_function(N, xi, pumi_ment_getTopo(element));
		//and its derivatives
		double dNdxi[nen][nsd];
		shape_function_dr(dNdxi, xi, pumi_ment_getTopo(element));
		
		//process the mapping
		double dxdxi[nsd][nsd];
		double dNdx[nen][nsd];
		//This function returns the jacobian determinant
		//and update the dxdxi and dNdx
		double j_det = mapping(dxdxi, dNdx, dNdxi, coord_local, nen);
		for (int ien = 0; ien < nen; ++ien)
		{
			Fe(2*ien) += g[0]*rho*N[ien]*j_det*weights[iint];
			Fe(2*ien+1) += g[1]*rho*N[ien]*j_det*weights[iint];
		}
	}//end of loop over quadrature points

}