double mapping(double dxdxi[][nsd], double dNdx[][nsd], double dNdxi[][nsd],
	double coord_local[][nsd], int nen, int dim)
{
	double j_det;
	if (nsd == 2){
		//dxdxi is a 2-D array for nsd = 2
		/*the form is below:
		dx(0)/dxi(0)	dx(0)/dxi(1)
		dx(1)/dxi(0)	dx(1)/dxi(1)
		*/
		//initialize
		for (int isd = 0; isd < nsd; ++isd)
		{
			for (int jsd = 0; jsd < nsd; ++jsd)
			{
				dxdxi[isd][jsd] = 0;
			}
		}

		//calculate
		for (int isd = 0; isd < nsd; ++isd)
		{
			for (int jsd = 0; jsd < nsd; ++jsd){
				for (int ien = 0; ien < nen; ++ien)
				{
					dxdxi[isd][jsd] += dNdxi[ien][jsd]*
					coord_local[ien][isd];
				}
			}
		}
		
		//calculate the jacobian determinant
		j_det = (dxdxi[0][0]*dxdxi[1][1] - 
		dxdxi[0][1]*dxdxi[1][0]);

		if (dim == 1)
			j_det = sqrt(dxdxi[0][0]*dxdxi[0][0] + 
				dxdxi[1][0]*dxdxi[1][0]);

		/*calculate the derivative of shape function in
		physical space*/
		//dNdxi has dimension of nen*nsd
		for (int ien = 0; ien < nen; ++ien)
		{
			dNdx[ien][0] = (dNdxi[ien][0]*dxdxi[1][1] - 
			dNdxi[ien][1]*dxdxi[1][0])/j_det;

			dNdx[ien][1] = (dNdxi[ien][1]*dxdxi[0][0] - 
			dNdxi[ien][0]*dxdxi[0][1])/j_det;
		}
	}
	return j_det;
}