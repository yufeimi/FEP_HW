/*This subroutine find the essential
and natural BCs and tage them*/
#include "pumi.h"

void find_BC(pNumbering reo_node, pMeshTag BCTag_ntr,
	pMesh mesh, int geo_dog, int geo_trac, 
	double trac_value[ndof], pMeshEnt edge, int Temp[][ndof])
{
	//const int fix = 0;
	//const int x_fix = 1;
	//const int y_fix = 2;

	const int traction = 1;

  	pGeomEnt geo_edge = pumi_ment_getGeomClas(edge);
  	int id = pumi_gent_getID(geo_edge);
    //std::cout << "ID:" << id <<std::endl;
  	if(id == geo_dog)
  	{//set essential BC (both dir fixed)
  		std::vector<pMeshEnt> vertices;
  		pumi_ment_getAdj(edge, 0, vertices);
  		Temp[pumi_ment_getNumber(vertices[0], reo_node, 0, 0)][0] = 0;
  		Temp[pumi_ment_getNumber(vertices[0], reo_node, 0, 0)][1] = 0;
  		Temp[pumi_ment_getNumber(vertices[1], reo_node, 0, 0)][0] = 0;
  		Temp[pumi_ment_getNumber(vertices[1], reo_node, 0, 0)][1] = 0;
  		if (pumi_shape_getNumNode(
  			pumi_mesh_getShape(mesh), PUMI_EDGE) == 1)
  		{//if there is node on the edge
  			Temp[pumi_ment_getNumber(edge, reo_node, 0, 0)][0] = 0;
  			Temp[pumi_ment_getNumber(edge, reo_node, 0, 0)][1] = 0;
  		}
  	}
  	if (id == geo_trac)
  	{
  		pumi_ment_setIntTag(edge, BCTag_ntr, &traction);
  	}
}