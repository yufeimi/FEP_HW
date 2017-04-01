#include <Eigen/SparseCore>
#include <Eigen/Dense>
#include "pumi.h"
#include "PCU.h"

void AssembleStiff(pMeshEnt iel, Eigen::MatrixXd Ke, 
	Eigen::SparseMatrix<double> &K, int nen, pMesh mesh,
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
			//find global node number a
			int nnb = pumi_ment_getNumber(
				vertices[ien], reo_node, 0, 0);
			for (int jen = 0; jen <= ien; ++jen)
			{
				//global node number b
				int nna = pumi_ment_getNumber(
					vertices[jen], reo_node, 0, 0);
				K.coeffRef(2*nna-2, 2*nnb-2) += Ke(2*jen, 2*ien);
				K.coeffRef(2*nnb-2, 2*nna-2) += Ke(2*jen, 2*ien);

				if (nna < nnb){
					K.coeffRef(2*nna-1, 2*nnb-2) += Ke(2*jen+1, 2*ien);
					K.coeffRef(2*nnb-2, 2*nna-1) += Ke(2*jen+1, 2*ien);
				}

				K.coeffRef(2*nna-2, 2*nnb-1) += Ke(2*jen, 2*ien+1);
				K.coeffRef(2*nnb-1, 2*nna-2) += Ke(2*jen, 2*ien+1);

				K.coeffRef(2*nna-1, 2*nnb-1) += Ke(2*jen+1, 2*ien+1);
				K.coeffRef(2*nnb-1, 2*nna-1) += Ke(2*jen+1, 2*ien+1);
			}
		}
	}
}