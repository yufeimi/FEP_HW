#include <Eigen/SparseCore>
#include <Eigen/Dense>
#include "pumi.h"

void AssembleStiff(pMeshEnt iel, Eigen::MatrixXd Ke, 
	Eigen::SparseMatrix<double> &K, int nen, pMesh mesh,
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
			//find global node number b
			int nnb = pumi_ment_getNumber(
				vertices[ien], reo_node, 0, 0);
			for (int jen = 0; jen < nen; ++jen)
			{
				//global node number a
				int nna = pumi_ment_getNumber(
					vertices[jen], reo_node, 0, 0);
				for (int idof = 0; idof < ndof; ++idof)
				{
					for (int jdof = 0; jdof < ndof; ++jdof)
					{
						if (EqID(nna,idof) >= 0 && EqID(nnb, jdof) >= 0)
						{
							K.coeffRef(EqID(nna, idof),EqID(nnb, jdof)) += 
							Ke(2*jen+idof, 2*ien+jdof);
						}
					}
				}
				
				// K.coeffRef(2*nna, 2*nnb) += Ke(2*jen, 2*ien);
				// K.coeffRef(2*nnb, 2*nna) += Ke(2*jen, 2*ien);

				// if (nna < nnb){
				// 	K.coeffRef(2*nna+1, 2*nnb) += Ke(2*jen+1, 2*ien);
				// 	K.coeffRef(2*nnb, 2*nna+1) += Ke(2*jen+1, 2*ien);
				// }

				// K.coeffRef(2*nna, 2*nnb+1) += Ke(2*jen, 2*ien+1);
				// K.coeffRef(2*nnb+1, 2*nna) += Ke(2*jen, 2*ien+1);

				// K.coeffRef(2*nna+1, 2*nnb+1) += Ke(2*jen+1, 2*ien+1);
				// K.coeffRef(2*nnb+1, 2*nna+1) += Ke(2*jen+1, 2*ien+1);
			}
		}
	}
}