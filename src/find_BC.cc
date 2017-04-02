/*This subroutine find the essential
and natural BCs and tage them*/
#include "pumi.h"

void find_BC(pMeshTag &BCTag_ess, pMeshTag &BCTag_ntr,
	pMesh &mesh, int geo_dog, int geo_trac, 
	double trac_value[ndof], pMeshEnt &edge)
{
	const int fix = 0;
	//const int x_fix = 1;
	//const int y_fix = 2;

	const int traction = 1;

  	pGeomEnt geo_edge = pumi_ment_getGeomClas(edge);
  	int id = pumi_gent_getID(geo_edge);
  	if(id == geo_dog)
  	{//set essential BC
  		std::vector<pMeshEnt> vertices;
  		pumi_ment_getAdj(edge, 0, vertices);
  		pumi_ment_setIntTag(vertices[1], BCTag_ess,
  			&fix);
  		pumi_ment_setIntTag(vertices[2], BCTag_ess,
  			&fix);
  		if (pumi_shape_getNumNode(
  			pumi_mesh_getShape(mesh), PUMI_EDGE) == 1)
  			pumi_ment_setIntTag(edge, BCTag_ess, &fix);
  	}
  	if (id == geo_trac)
  	{
  		pumi_ment_setIntTag(edge, BCTag_ntr, &traction);
  	}

}