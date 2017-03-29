double mapping(double dxdxi[][nsd], double dNdx[][nsd], double dNdxi[][nsd],
	double coord_local[][nsd], int nsd)
{
	if (nsd == 2){
		//dxdxi is a 2-D array for nsd = 2
		/*the form is below:
		dx(1)/dxi(1)	dx(1)/dxi(2)
		dx(2)/dxi(1)	dx(2)/dxi(2)
		*/
		for (int isd = 0; isd < nsd; ++isd)
		{
			for (int jsd = 0; jsd < nsd; ++jsd){
				dxdxi[isd][jsd] = 0;
				for (int ien = 0; i < nen; ++ien)
				{
					dxdxi[isd][jsd] += dNdxi[ien][jsd]*
					coord_local[ien][isd];
				}
			}
		}

		//calculate the jacobian determinant
		double j_det = (dxdxi[1][1]*dxdxi[2][2] - 
		dxdxi[1][2]*dxdxi[2][1]);

		/*calculate the derivative of shape function in
		physical space*/
		//dNdxi has dimension of nen*nsd
		for (int ien = 0; ien < nen; ++ien)
		{
			dNdx[ien][1] = (dNdxi[ien][1]*dxdxi[2][2] - 
			dNdxi[ien][2]*dxdxi[2][1])/j_det;

			dNdxi[ien][2] = -(dNdxi[ien][1]*dxdxi[1][2] - 
			dNdxi[ien][2]*dxdxi[1][1])/j_det;
		}
	}
	return j_det;
}