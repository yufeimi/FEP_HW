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
	if (nsd_local == 2 && nint_local == 4)
	{
		xi_list[0][0]= -0.5773502692;
		xi_list[0][1]= -0.5773502692;
		xi_list[1][0]= 0.5773502692;
		xi_list[1][1]= -0.5773502692;
		xi_list[2][0]= 0.5773502692;
		xi_list[2][1]= 0.5773502692;
		xi_list[3][0]= -0.5773502692;
		xi_list[3][1]= 0.5773502692;
	}
}