#include <Eigen/Dense>
#include "pumi.h"

void AssembleBodyForce(pMeshEnt iel, Eigen::VectorXd Fe, 
	Eigen::VectorXd &F, int nen, pMesh mesh,
	pNumbering reo_node)
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
				F(2*nn) += Fe(2*ien);

				F(2*nn) += Fe(2*ien+1);
		}
	}
}