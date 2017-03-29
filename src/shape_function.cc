void shape_function(double N[nen], double xi[nsd], int shape, int nsd, int nen)
{
	if (shape == 1 && nsd == 2 && nen == 4)
	{
		N[1] = 0.25*(1.-xi[1])*(1.-xi[2]);
		N[2] = 0.25*(1.+xi[1])*(1.-xi[2]);
		N[3] = 0.25*(1.+xi[1])*(1.+xi[2]);
		N[4] = 0.25*(1.-xi[1])*(1.+xi[2]);
	}
}