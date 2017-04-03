#include <Eigen/Dense>
#include "qdptcoord.cc"
#include "shape_function.cc"
#include "shape_function_dr.cc"
#include "int_weight.cc"
#include "mapping.cc"
#include "pumi.h"
#include "PCU.h"

void EleStiff(int nen, Eigen::MatrixXd &Ke, pMeshEnt element,
 pMesh mesh)
{
	/* number of nodes of the element and
	number of integration points*/
	int nint = 0;
	if (pumi_ment_getTopo(element) == PUMI_QUAD)
	{
		nint = 4;
	}else if (pumi_ment_getTopo(element) == PUMI_TRIANGLE)
	{
		nint = 1;
	}


	//iniialize the element stiffness matrix Ke
	for (int i = 0; i < ndof*nen; ++i)
	{
		for (int j = 0; j < ndof*nen; ++j)
		{
			Ke(i,j) = 0;
		}
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

		//calculate the element stiffness matrix Ke using BDB
		if (nsd == 2)
		{
			double lambda = nu*young_mod/((1+nu)*(1-2*nu));//D parameter
			double mu = young_mod/(2*(1+nu));//D parameter
			//define the D matix
			double D[3][3] = {lambda+2*mu, lambda, 0,
				lambda, lambda+2*mu, 0, 0, 0, mu};//only for 2-D case

			//calculate the tilde D, which is j*xi_int*D
			double D_tilde[3][3];
			for (int i = 0; i < 3; i++){
				for (int j = 0; j < 3; j++){
					D_tilde[i][j] = D[i][j]*j_det*weights[iint];
				}
			}

			//calculate the element stiffness matrix
			//Hughes's FEM textbook p.153 implementation 2
			for (int b = 0; b < nen; ++b)
			{
				double B1 = dNdx[b][0];
				double B2 = dNdx[b][1];
				double temp[3][2] = {{D_tilde[0][0]*B1,
					D_tilde[0][1]*B2}, {D_tilde[0][1]*B1,
					D_tilde[1][1]*B2}, {D_tilde[2][2]*B2,
					D_tilde[2][2]*B1}};

				for (int a = 0; a < nen; ++a)
				{
					B1 = dNdx[a][0];
					B2 = dNdx[a][1];
					Ke(2*a,2*b) += B1*temp[0][0] + B2*temp[2][0];
					Ke(2*a,2*b+1) += B1*temp[0][1] + B2*temp[2][1];
					Ke(2*a+1,2*b) += B2*temp[1][0] + B1*temp[2][0];
					Ke(2*a+1,2*b+1) += B2*temp[1][1] + B1*temp[2][1];
				}
			}//end calculate element stiffness matrix
		}
	}//end of loop over quadrature points
}