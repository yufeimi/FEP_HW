void LMarray(int LM[][ndof*nen], int ID[][ndof], int IEN[][nen], int nnp,
 int nen, int nel, int dof)
{
	//LM array: row = equations per element;
	//column = elements number
	//this array stores global dof and elements
	for (int i = 0; i < nel; ++i)
	{
		//loop over nodes on the element
		for (int j = 0; j < nen; ++j)
		{
			for (int k = 0; k < ndof; ++k)
			{
				LM[i][ndof*j+k] = ID[IEN[i][j]][k];
			}
		}
	}
}
