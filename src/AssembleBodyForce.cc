#include <Eigen/Dense>
#include "pumi.h"

void AssembleBodyForce(pMeshEnt iel, Eigen::VectorXd Fe, 
	Eigen::VectorXd &F, int nen, pMesh mesh,
	pNumbering reo_node, Eigen::MatrixXi EqID)
{
	//for linear element
	if (pumi_shape_getNumNode(
		pumi_mesh_getShape(mesh), PUMI_EDGE) == 0)
	{
		std::vector<pMeshEnt> vertices;
		pumi_ment_getAdj(iel, 0, vertices);
		for (int ien = 0; ien < nen; ++ien)
		{
			//find global node number
			int nn = pumi_ment_getNumber(
				vertices[ien], reo_node, 0, 0);
			for (int idof = 0; idof < ndof; ++idof)
			{
				if (EqID(nn,idof) >= 0)
					F(EqID(nn,idof)) += Fe(2*ien);
			}
		}
	}

	//for quadratic element
	if (pumi_shape_getNumNode(
		pumi_mesh_getShape(mesh), PUMI_EDGE == 1))
	{
		std::vector<pMeshEnt> vertices;
		pumi_ment_getAdj(iel, 0, vertices);
		std::vector<pMeshEnt> edge_nodes;
		pumi_ment_getAdj(iel, 1, edge_nodes);
		for (unsigned ied = 0; ied < edge_nodes.size(); ++ied)
		{
			vertices.push_back(edge_nodes[ied]);
		}
		if (pumi_ment_getTopo(iel) == PUMI_QUAD)
			vertices.push_back(iel);
		for (int ien = 0; ien < nen; ++ien)
		{
			//find global node number
			int nn = pumi_ment_getNumber(
				vertices[ien], reo_node, 0, 0);
			for (int idof = 0; idof < ndof; ++idof)
			{
				if (EqID(nn,idof) >= 0)
					F(EqID(nn,idof)) += Fe(2*ien);
			}
		}
	}
}