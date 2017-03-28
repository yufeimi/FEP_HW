/* This subroutine defines the quadrature
points for numerical integration*/
//Note: this is in parametric space!
void qdpt_coord(double (&xi_list)[nint][nsd], int nen,int nsd)
{
	if (nen == 4 && nsd == 2)
	{
		xi_list[1][1]= -0.5773502692;
		xi_list[1][2]= -0.5773502692;
		xi_list[2][1]= 0.5773502692;
		xi_list[2][2]= -0.5773502692;
		xi_list[3][1]= 0.5773502692;
		xi_list[3][2]= 0.5773502692;
		xi_list[4][1]= -0.5773502692;
		xi_list[4][2]= 0.5773502692;
	}
}