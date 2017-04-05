void int_weight(double weights[], int nint_local, int nsd_local)
{
	if (nsd_local == 1 && nint_local == 2)
	{
		weights[0] = 1;
		weights[1] = 1;
	}
	if (nsd_local == 1 && nint_local == 3)
	{
		weights[0] = 0.8888888888888;
		weights[1] = 0.5555555555555;
		weights[2] = 0.8888888888888;
	}
	if (nsd_local == 2 && nint_local == 1)
	{
		weights[0] = 1;
	}
	if (nsd_local == 2 && nint_local == 3)
	{
		weights[0] = 0.3333333333333;
		weights[1] = 0.3333333333333;
		weights[2] = 0.3333333333333;
	}
	if (nsd_local == 2 && nint_local == 4)
	{
		weights[0] = 1;
		weights[1] = 1;
		weights[2] = 1;
		weights[3] = 1;
	}
	if (nsd_local == 2 && nint_local == 9)
	{
		weights[0] = 0.3086419753;
		weights[1] = 0.49382716049;
		weights[2] = 0.3086419753;
		weights[3] = 0.49382716049;
		weights[4] = 0.3086419753;
		weights[5] = 0.49382716049;
		weights[6] = 0.3086419753;
		weights[7] = 0.49382716049;
		weights[8] = 0.3086419753;
	}
}