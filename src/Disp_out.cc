#include "pumi.h"
#include <Eigen/Dense>

void Disp_out(pField &Disp, pMesh &mesh, pNumbering reo_node,
	Eigen::MatrixXi EqID, Eigen::VectorXd d)
{
	pMeshIter iv = mesh->begin(0);
	pMeshEnt v;
	while ((v = mesh->iterate(iv)))
	{
		//get vertex number
		int nn = pumi_ment_getNumber(v, reo_node, 0, 0);
		double d_node[3];
		d_node[2] = 0;
		for (int idof = 0; idof < ndof; ++idof)
		{//if number associate with dof, write the displacement
			if (EqID(nn, idof) >= 0)
				d_node[idof] = d(EqID(nn, idof));
			else//else write 0
				d_node[idof] = 0;
		}
		pumi_ment_setField(v, Disp, 0, d_node);
	}
}