void shape_function_dr(double dNdxi[][nsd], double xi[nsd], 
    int topo, int nen)
{
    if (topo == 1 && nen == 2)//edge for loading
    {
        dNdxi[0][0] = -0.5;
        dNdxi[0][1] = 0;
        dNdxi[1][0] = 0.5;
        dNdxi[1][1] = 0;
    }
    if (topo == 1 && nen == 3)//quadratic edge
    {
        dNdxi[0][0] = xi[0] - 0.5;
        dNdxi[0][1] = 0;
        dNdxi[1][0] = xi[0] + 0.5;
        dNdxi[1][1] = 0;
        dNdxi[2][0] = 2*xi[0];
        dNdxi[2][1] = 0;
    }
    if (topo == 2 && nen == 3)//tri linear
    {
        dNdxi[0][0] = -1;
        dNdxi[0][1] = -1;
        dNdxi[1][0] = 1;
        dNdxi[1][1] = 0;
        dNdxi[2][0] = 0;
        dNdxi[2][1] = 1;
    }
	if (topo == 3 && nen == 4)//quad linear
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
    if (topo == 2 && nen == 6)//tri quadratic
    {//1-3 vertices 4-6 edge nodes
        double L[3] = {1-xi[0]-xi[1], xi[0], xi[1]};

        dNdxi[0][0] = -1;
        dNdxi[0][1] = -1;
        dNdxi[1][0] = 1;
        dNdxi[1][1] = 0;
        dNdxi[2][0] = 0;
        dNdxi[2][1] = 1;
        dNdxi[3][0] = -2.0e0*L[1];
        dNdxi[3][1] = -2.0e0*L[0];
        dNdxi[4][0] = 2.0e0*L[1];
        dNdxi[4][1] = -2.0e0+2.0e0*L[0]+4.0e0*L[1];
        dNdxi[5][0] = -2.0e0+4.0e0*L[0]+2.0e0*L[1];
        dNdxi[5][1] = 2.0e0*L[0];
    }
    if (topo == 3 && nen == 9)//quad quadratic
    {//1-4 vertices 5-8 edge nodes 9 face node
        double x = xi[0];
        double y = xi[1];
        
        dNdxi[0][0] = (0.25 + xi[0]*(-0.5 + 0.5*xi[1]) - 0.25*xi[1])*xi[1];
        dNdxi[0][1] = xi[0]*(0.25 + xi[0]*(-0.25 + 0.5*xi[1]) - 0.5*xi[1]);
        dNdxi[1][0] = (0.25 + xi[0]*(0.5 - 0.5*xi[1]) - 0.25*xi[1])*xi[1];
        dNdxi[1][1] = -0.5*xi[0]*(1 + xi[0])*(-0.5 + xi[1]*xi[0]);
        dNdxi[2][0] = 0.5*(0.5 + xi[0])*xi[1]*(1. + xi[1]);
        dNdxi[2][1] = 0.5*xi[0]*(1 + xi[0])*(0.5 + xi[1]);
        dNdxi[3][0] = -0.5*(-0.5 + xi[0])*xi[1]*(1. + xi[1]);
        dNdxi[3][1] = xi[0]*(0.25 + xi[0]*(-0.25 - 0.5*xi[1]) + 0.5*xi[1]);
        dNdxi[4][0] = -xi[0]*(-1 + xi[1])*xi[1];
        dNdxi[4][1] = -0.5 + xi[0]*xi[0]*(0.5 - xi[1]) + xi[1];
        dNdxi[5][0] = xi[0]*(1 - xi[1]*xi[1]) - 0.5*xi[1]*xi[1] + 0.5;
        dNdxi[5][1] = -xi[0]*(xi[0] + 1)*xi[1];
        dNdxi[6][0] = -xi[0]*xi[1]*(xi[1]+1);
        dNdxi[6][1] =   xi[0]*xi[0]*(-xi[1] - 0.5) + xi[1] + 0.5;
        dNdxi[7][0] = xi[0]*(1 - xi[1]*xi[1]) + 0.5*xi[1]*xi[1] - 0.5;
        dNdxi[7][1] = -(xi[0] - 1)*xi[0]*xi[1];
        dNdxi[8][0] = 2*xi[0]*(xi[1]*xi[1] - 1);
        dNdxi[8][1] = 2*xi[1]*(xi[0]*xi[0] - 1);
    }
}