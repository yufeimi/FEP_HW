void shape_function_dr(double dNdxi[][nsd], double xi[nsd], int shape, int nsd, int nen)
{
	if (shape == 1 && nsd == 2 && nen == 4)
	{
		dNdxi[1][1] = -0.25*(1.-xi[2]);
    	dNdxi[1][2] = -0.25*(1.-xi[1]);
    	dNdxi[2][1] = 0.25*(1.-xi[2]);
    	dNdxi[2][2] = -0.25*(1.+xi[1]);
    	dNdxi[3][1] = 0.25*(1.+xi[2]);
    	dNdxi[3][2] = 0.25*(1.+xi[1]);
    	dNdxi[4][1] = -0.25*(1.+xi[2]);
    	dNdxi[4][2] = 0.25*(1.-xi[1]);
	}
}