void int_weight(double (&weights)[nint], int nsd, int nint)
{
	if (nsd == 2 && nint == 4)
	{
		weights[1] = 1;
		weights[2] = 1;
		weights[3] = 1;
		weights[4] = 1;
	}
}