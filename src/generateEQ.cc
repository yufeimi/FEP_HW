#include "pumi.h"

void generateEQ(int EqID[][ndof], int Temp[][ndof],
pNumbering reo_node, pMesh mesh, int nnp)
{

	//initialize the array
	for (int i = 0; i < nnp; ++i)
	{
		for (int j = 0; j < ndof; ++j)
		{
			EqID[i][j] = 0;
		}
	}
	

	//need another loop over edges for quadratic

	//now fill into the eq array
	int eq_number = 0;
	for (int inp = 0; inp < nnp; ++inp)
	{//fill in -1 for no eq, >= 0 ->eq number
		for (int idof = 0; idof < ndof; ++idof)
		{
			if (Temp[inp][idof] == 1)
			{
				EqID[inp][idof] = eq_number;
				++eq_number;
			}else if(Temp[inp][idof] == 0)
			{
				EqID[inp][idof] = -1;
			}
		}
	}
}