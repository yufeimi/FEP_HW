void shape_function_dr(double dNdxi[][nsd], double xi[nsd])
{
	if (shape == 1 && nsd == 2 && nen == 4)
	{
		dNdxi[0][0] = -0.25*(1.-xi[1]);
    	dNdxi[0][1] = -0.25*(1.-xi[0]);
    	dNdxi[1][0] = 0.25*(1.-xi[1]);
    	dNdxi[1][1] = -0.25*(1.+xi[0]);
    	dNdxi[2][0] = 0.25*(1.+xi[1]);
    	dNdxi[2][1] = 0.25*(1.+xi[0]);
    	dNdxi[3][0] = -0.25*(1.+xi[1]);
    	dNdxi[3][1] = 0.25*(1.-xi[0]);
	}
}