#include <Eigen/Dense>
#include "pumi.h"

void AssembleTraction(pMeshEnt edge, Eigen::VectorXd Fe, 
	Eigen::VectorXd &F, int ned, pMesh mesh,
	pNumbering reo_node, Eigen::MatrixXi EqID)
{
	//for linear element
	if (pumi_shape_getNumNode(
		pumi_mesh_getShape(mesh), PUMI_EDGE) == 0)
	{
		std::vector<pMeshEnt> vertices;
		pumi_ment_getAdj(edge, 0, vertices);
		for (int ied = 0; ied < ned; ++ied)
		{
			//find global node number
			int nn = pumi_ment_getNumber(
				vertices[ied], reo_node, 0, 0);
			for (int idof = 0; idof < ndof; ++idof)
			{
				if (EqID(nn,idof) >= 0)
					F(EqID(nn,idof)) += Fe(2*ied);
			}
		}
	}

	//for quadratic element
	if (pumi_shape_getNumNode(
		pumi_mesh_getShape(mesh), PUMI_EDGE == 1))
	{
		std::vector<pMeshEnt> vertices;
		pumi_ment_getAdj(edge, 0, vertices);
		vertices.push_back(edge);
		for (int ied = 0; ied < ned; ++ied)
		{
			//find global node number
			int nn = pumi_ment_getNumber(
				vertices[ied], reo_node, 0, 0);
			for (int idof = 0; idof < ndof; ++idof)
			{
				if (EqID(nn,idof) >= 0)
					F(EqID(nn,idof)) += Fe(2*ied);
			}
		}
	}
}