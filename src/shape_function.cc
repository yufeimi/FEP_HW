void shape_function(double N[], double xi[nsd], int topo, int nen)
{
	if (topo == 1 && nen == 2)//edge for loading
	{
		N[0] = 0.5*(1.-xi[0]);
		N[1] = 0.5*(1.+xi[0]);
	}
	if (topo == 1 && nen == 3)//quadratic edge
	{
		N[0] = 0.5*xi[0]*(xi[0] - 1);
		N[1] = 0.5*xi[0]*(xi[0] + 1);
		N[2] = (xi[0] + 1)*(xi[0] - 1);//mid node
	}
	if (topo == 2 && nen == 3)//tri linear
	{
		N[0] = 1 - xi[0] - xi[1];
		N[1] = xi[0];
		N[2] = xi[1];
	}
	if (topo == 3 && nen == 4)//quad linear
	{
		N[0] = 0.25*(1.-xi[0])*(1.-xi[1]);
		N[1] = 0.25*(1.+xi[0])*(1.-xi[1]);
		N[2] = 0.25*(1.+xi[0])*(1.+xi[1]);
		N[3] = 0.25*(1.-xi[0])*(1.+xi[1]);
	}
	if (topo == 2 && nen == 6)//tri quadratic
	{//1-3 vertices 4-6 edge nodes
		N[0] = 2*(1 - xi[0] - xi[1])*(0.5 - xi[0] - xi[1]);
		N[1] = 2*xi[0]*(xi[0]-0.5);
		N[2] = 2*xi[1]*(xi[1]-0.5);
		N[3] = 4*(1 - xi[0] - xi[1])*xi[0];
		N[4] = 4*xi[0]*xi[1];
		N[5] = 4*(1 - xi[0] - xi[1])*xi[1];
	}
	if (topo == 3 && nen == 9)//quad quadratic
	{//1-4 vertices 5-8 edge nodes 9 face node
		N[0] = 0.25*(1 - xi[0])*(1 - xi[1])*xi[0]*xi[1];
		N[1] = 0.25*(1 + xi[0])*(1 - xi[1])*xi[0]*xi[1];
		N[2] = 0.25*(1 + xi[0])*(1 + xi[1])*xi[0]*xi[1];
		N[3] = 0.25*(1 - xi[0])*(1 + xi[1])*xi[0]*xi[1];
		N[4] = 0.5*(1 - xi[0]*xi[0])*xi[1]*(xi[1] - 1);
		N[5] = 0.5*(1 - xi[1]*xi[1])*xi[0]*(xi[0] + 1);
		N[6] = 0.5*(1 - xi[0]*xi[0])*xi[1]*(xi[1] + 1);
		N[7] = 0.5*(1 - xi[1]*xi[1])*xi[0]*(xi[0] -	1);
		N[8] = (1 - xi[1]*xi[1])*(1 - xi[0]*xi[0]);
	}
}