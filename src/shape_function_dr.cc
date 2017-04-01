void shape_function_dr(double dNdxi[][nsd], double xi[nsd], 
    int topo)
{
    if (topo == 1)//edge for loading
    {
        dNdxi[0][0] = 0.5;
        dNdxi[0][1] = 0;
        dNdxi[1][0] = -0.5;
        dNdxi[1][1] = 0;
    }
	if (topo == 3)//quad
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