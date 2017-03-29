void shape_function(double N[nen], double xi[nsd])
{
	if (shape == 1 && nsd == 2 && nen == 4)
	{
		N[0] = 0.25*(1.-xi[0])*(1.-xi[1]);
		N[1] = 0.25*(1.+xi[0])*(1.-xi[1]);
		N[2] = 0.25*(1.+xi[0])*(1.+xi[1]);
		N[3] = 0.25*(1.-xi[0])*(1.+xi[1]);
	}
}