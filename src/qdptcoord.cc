/* This subroutine defines the quadrature
points for numerical integration*/
//Note: this is in parametric space!
void qdpt_coord(double xi_list[][nsd], int nint_local, int nsd_local)
{
	if (nsd_local == 1 && nint_local == 2)
	{//for load integration in 2-D
		xi_list[0][0] = -0.5773502692;
		xi_list[0][1] = 0;
		xi_list[1][0] = 0.5773502692;
		xi_list[1][1] = 0;
	}
	if (nsd_local == 1 && nint_local == 3)
	{
		xi_list[0][0] = -0.77459666924;
		xi_list[0][1] = 0;

		xi_list[1][0] = 0;
		xi_list[1][1] = 0;

		xi_list[2][0] = 0.77459666924;
		xi_list[2][1] = 0;
	}
	if (nsd_local == 2 && nint_local == 1)
	{//for tri
		xi_list[0][0] = 0.3333333333;
		xi_list[0][1] = 0.3333333333;
	}
	if (nsd_local == 2 && nint_local == 3)
	{//quadratic tri
		xi_list[0][0] = 0;
		xi_list[0][1] = 0.5;

		xi_list[1][0] = 0.5;
		xi_list[1][1] = 0;
		
		xi_list[2][0] = 0.5;
		xi_list[2][1] = 0.5;
	}
	if (nsd_local == 2 && nint_local == 4)
	{//for quad
		xi_list[0][0]= -0.5773502692;
		xi_list[0][1]= -0.5773502692;
		xi_list[1][0]= 0.5773502692;
		xi_list[1][1]= -0.5773502692;
		xi_list[2][0]= 0.5773502692;
		xi_list[2][1]= 0.5773502692;
		xi_list[3][0]= -0.5773502692;
		xi_list[3][1]= 0.5773502692;
	}
	if (nsd_local == 2 && nint_local == 9)
	{//for quadratic quad
		xi_list[0][0]= -0.77459666924;
		xi_list[0][1]= -0.77459666924;

		xi_list[1][0]= 0;
		xi_list[1][1]= -0.77459666924;

		xi_list[2][0]= 0.77459666924;
		xi_list[2][1]= -0.77459666924;

		xi_list[3][0]= -0.77459666924;
		xi_list[3][1]= 0;

		xi_list[4][0]= 0;
		xi_list[4][1]= 0;

		xi_list[5][0]= 0.77459666924;
		xi_list[5][1]= 0;

		xi_list[6][0]= -0.77459666924;
		xi_list[6][1]= 0.77459666924;

		xi_list[7][0]= 0;
		xi_list[7][1]= 0.77459666924;

		xi_list[8][0]= 0.77459666924;
		xi_list[8][1]= 0.77459666924;
	}
}