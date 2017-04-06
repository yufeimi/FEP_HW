#include <pumi.h>
#include <PCU.h>
#include <iostream>
#include <stdio.h>
#include <Eigen/Sparse>
#include <Eigen/Dense>
#include "global_constants.h"
#include "input.h" //this includes BC, temporarily
#include "EleStiff.cc"
#include "AdjReorder.cc"
#include "element_node_number.cc"
#include "AssembleStiff.cc"
#include "find_BC.cc"
#include "EleLoad.cc"
#include "EleBodyForce.cc"
#include "AssembleBodyForce.cc"
#include "AssembleTraction.cc"
#include "generateEQ.cc"
#include "SolveStiffness.cc"
#include "Disp_out.cc"

int main(int argc, char **argv)
{
	MPI_Init(&argc,&argv);
	pumi_start();
	printf("Starting the FE program...\n");
  	pGeom geom = pumi_geom_load("model.dmg", "mesh");
  	pMesh mesh = pumi_mesh_load(geom, "mesh.smb", 1);

  	printf("Starting reordering...\n");
  	pNumbering reo_node = pumi_numbering_createOwnedNode(
    mesh, "Reorder_nodes", pumi_mesh_getShape(mesh));
  	pNumbering reo_elem = pumi_numbering_createOwned(
    mesh, "Reorder_elements", 2);
    //reorder the nodes, and get global node number nnp
  	int nnp = AdjReorder(mesh, reo_node, reo_elem);


  	printf("Finding BC...");
  	//find the mesh edges on the BC
  	pMeshTag BCtag_ntr = pumi_mesh_createIntTag(mesh,
  		"traction BC", 3);
  	//tag on edges; 3 geo edges at most
  	pMeshIter ie = mesh->begin(1);
	pMeshEnt edge;
	//temp array:1 for eq exsit; 0 for no eq
	int Temp[nnp][ndof];

	//initialize the temp array
	for (int i = 0; i < nnp; ++i)
	{
		for (int j = 0; j < ndof; ++j)
		{
			Temp[i][j] = 1;
		}
	}

	while((edge = mesh->iterate(ie))){
		find_BC(reo_node, BCtag_ntr, mesh, geo_dog, 
  		geo_trac, trac_value, edge, Temp);	
  	}
	mesh->end(ie);
  	printf("done.\n");
  	
  	//This is the ID array in Hughes' textbook
  	Eigen::MatrixXi EqID(nnp,ndof);
  	//generate the EQ matrix to store the eq number per dof
  	int eq_number = generateEQ(EqID, Temp, reo_node, mesh, nnp);
  	//In EqID: -1 for no eq, >= 0 is eq number

	//assemble
	//the global stiffness matrix
	Eigen::SparseMatrix<double> K(eq_number,eq_number);
	Eigen::VectorXd F(eq_number);
	//initialize force vector
	for (int i = 0; i < eq_number; ++i)
	{
		F(i) = 0;
	}

	//loop over elements
	printf("Constructing global stiffness matrix");
	printf(" and body force contribution to the force vector..");
	pMeshEnt iel;
	pMeshIter ele_iterator = mesh->begin(2);
	while ((iel = mesh->iterate(ele_iterator)))
	{
		//get element node number
		pShape s = pumi_mesh_getShape(mesh);
		int edge_node = pumi_shape_getNumNode(s, PUMI_EDGE);
		int nen = element_node_number(edge_node, 
			pumi_ment_getTopo(iel));

		Eigen::MatrixXd Ke(ndof*nen, ndof*nen);
		//get element stiffness matrix
		EleStiff(nen, Ke, iel, mesh);
		//assemble it in the global K
		AssembleStiff(iel, Ke, K, nen, mesh, reo_node, EqID);

		//body force contribution to the local force vector
		Eigen::VectorXd Fe(ndof*nen);
		EleBodyForce(Fe, iel, mesh, nen);
		//assemble it in the force vector
		AssembleBodyForce(iel, Fe, F, nen, mesh, reo_node, EqID);
	}
	mesh->end(ele_iterator);
	printf("done.\n");


	//loop over edges
	pMeshEnt ied;
	pMeshIter edge_iterator = mesh->begin(1);
	while ((ied = mesh->iterate(edge_iterator)))
	{
		//constructing element traction and bodyforce
		//get number of node per edge
		int ned = pumi_shape_getNumNode(pumi_mesh_getShape(mesh),
		 PUMI_EDGE) + 2;

		/*this Fe is for element edges, thus has dimension
		ndof*ned*/
		Eigen::VectorXd Fe(ndof*ned);
		if (pumi_ment_hasTag(ied, BCtag_ntr))
		{
			EleLoad(Fe, ied, mesh, trac_value, ned);
			AssembleTraction(ied, Fe, F, ned, mesh, reo_node, EqID);
		}
	}
	mesh->end(edge_iterator);
	std::cout<<F<<std::endl;

	K.makeCompressed();//compress the stiffness matrix
	//solve the matrix

	printf("Solving...\n");
	Eigen::VectorXd d(eq_number);
	SolveStiffness(K, F, d);
	printf("Get displacement field\n");

	//fill in the displacement into the field;
	pField Disp = pumi_field_create(mesh, "displacement", 1, 
		PUMI_VECTOR, pumi_mesh_getShape(mesh));
	Disp_out(Disp, mesh, reo_node, EqID, d);


	pumi_mesh_write(mesh, "output", "vtk");
	pumi_mesh_delete(mesh);
	pumi_finalize();
	MPI_Finalize();
	return 0;
}