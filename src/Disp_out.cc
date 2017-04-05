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
		double d_node[3] = {0, 0, 0};
		for (int idof = 0; idof < ndof; ++idof)
		{//if number associate with dof, write the displacement
			if (EqID(nn, idof) >= 0)
				d_node[idof] = d(EqID(nn, idof));
			else//else write 0
				d_node[idof] = 0;
		}
		pumi_ment_setField(v, Disp, 0, d_node);
	}//end vertices
	mesh->end(iv);

	if (pumi_shape_getNumNode(
		pumi_mesh_getShape(mesh), PUMI_EDGE))
	{//if quadratic mesh
		pMeshIter ied = mesh->begin(1);
		pMeshEnt ed;
		while((ed = mesh->iterate(ied)))
		{
			//get edge node number
			int nn = pumi_ment_getNumber(ed, reo_node, 0, 0);
			double d_node[3] = {0, 0, 0};
			for (int idof = 0; idof < ndof; ++idof)
			{//if number associate with dof, write the displcement
				if (EqID(nn, idof) >= 0)
					d_node[idof] = d(EqID(nn, idof));
				else//else write 0
					d_node[idof] = 0;
			}
			pumi_ment_setField(ed, Disp, 0, d_node);
		}//end loop edges
		mesh->end(ied);
		pMeshIter iel = mesh->begin(2);
		pMeshEnt el;
		while((el = mesh->iterate(iel)))
		{
			//get element node number, if quadratic
			if (pumi_ment_getTopo(el) == PUMI_QUAD)
			{
				int nn = pumi_ment_getNumber(el, reo_node, 0, 0);
				double d_node[3] = {0, 0, 0};
				for (int idof = 0; idof < ndof; ++idof)
				{//if number associate with dof, write the displcement
					if (EqID(nn, idof) >= 0)
						d_node[idof] = d(EqID(nn, idof));
					else//else write 0
						d_node[idof] = 0;
				}
				pumi_ment_setField(el, Disp, 0, d_node);
			}
		}//end loop elements
		mesh->end(iel);
	}//end edges and element
}