#include <Eigen/Dense>
#include "pumi.h"

void AssembleTraction(pMeshEnt edge, Eigen::VectorXd Fe, 
	Eigen::MatrixXd &F, int ned, pMesh mesh,
	pNumbering reo_node)
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
				F(2*nn-2) += Fe(2*ied);

				F(2*nn-1) += Fe(2*ied+1);
		}
	}
}