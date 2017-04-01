void shape_function(double N[], double xi[nsd], int topo)
{
	if (topo == 1)//edge for loading
	{
		N[0] = 0.5*(1.+xi[0]);
		N[0] = 0.5*(1.-xi[0]);
	}
	if (topo == 3)//quad
	{
		N[0] = 0.25*(1.-xi[0])*(1.-xi[1]);
		N[1] = 0.25*(1.+xi[0])*(1.-xi[1]);
		N[2] = 0.25*(1.+xi[0])*(1.+xi[1]);
		N[3] = 0.25*(1.-xi[0])*(1.+xi[1]);
	}
}