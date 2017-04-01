void int_weight(double weights[], int nint_local, int nsd_local)
{
	if (nsd_local == 1 && nint_local == 2)
	{
		weights[0] = 1;
		weights[1] = 1;
	}
	if (nsd_local == 2 && nint_local == 4)
	{
		weights[0] = 1;
		weights[1] = 1;
		weights[2] = 1;
		weights[3] = 1;
	}
}