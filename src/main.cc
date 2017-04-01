#include <pumi.h>
#include <PCU.h>
#include <iostream>
#include <stdio.h>
#include <Eigen/SparseCore>
#include <Eigen/Dense>
#include "properties.h"
#include "global_constants.h"
//#include "declaration_vectors.h"
//#include "input.h" //this includes ID and IEN arrays, temporarily
//#include "LMarray.cc"
#include "EleStiff.cc"
#include "AdjReorder.cc"
#include "element_node_number.cc"
#include "AssembleStiff.cc"

int main(int argc, char **argv)
{
	MPI_Init(&argc,&argv);
	pumi_start();
	printf("Starting the FE program...\n");
  	pGeom geom = pumi_geom_load("model.dmg", "mesh");
  	pMesh mesh = pumi_mesh_load(geom, "mesh.smb", 1);

  	printf("Starting reordering..\n");
  	pNumbering reo_node = pumi_numbering_createOwnedNode(
    mesh, "Reorder_nodes", pumi_mesh_getShape(mesh));
  	pNumbering reo_elem = pumi_numbering_createOwned(
    mesh, "Reorder_elements", 2);
    //reorder the nodes, and get global node number nnp
  	int nnp = AdjReorder(mesh, reo_node, reo_elem);
	//assemble
	//the global stiffness matrix
	Eigen::SparseMatrix<double> K(ndof*nnp,ndof*nnp);
	std::cout << K.coeffRef(97,97) <<std::endl;
	//loop over elements
	pMeshEnt iel;
	pMeshIter ele_iterator = mesh->begin(2);
	while ((iel = mesh->iterate(ele_iterator)))
	{
		pShape s = pumi_mesh_getShape(mesh);
		int edge_node = pumi_shape_getNumNode(s, PUMI_EDGE);
		int nen = element_node_number(edge_node, 
			pumi_ment_getTopo(iel));
		Eigen::MatrixXd Ke(ndof*nen, ndof*nen);
		Eigen::MatrixXd Fe(ndof*nen, 1);
		//printf("Constructing element %d..\n", 
		//	pumi_ment_getNumber(iel, reo_elem, 0, 0));
		EleStiff(nen, Ke, iel, mesh);
		//printf("Constructed\n");
		//std::cout << Ke << std::endl;
		AssembleStiff(iel, Ke, K, nen, mesh, reo_node);
		//EleLoad(Fe, iel, IEN, coord);
		/*the body force function must be called after load, 
		because the EleLoad initializes the FE vector! */
		//EleBodyforce(Fe, iel, IEN, coord);
	}
	std::cout << K << std::endl;
	pumi_mesh_delete(mesh);
	pumi_finalize();
	MPI_Finalize();
	return 0;
}