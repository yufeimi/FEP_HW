//#include <pumi.h>
//#include <PCU.h>
#include <iostream>
#include <stdio.h>
#include "properties.h"
#include "global_constants.h"
#include "declaration_vectors.h"
#include "input.h" //this includes ID and IEN arrays, temporarily
#include "LMarray.cc"
#include "EleStiff.cc"

int main(int argc, char const *argv[])
{
	printf("Starting the FE program...\n");
	//get LM array
	//See LMarray subroutine
	int LM[nel][ndof*nen];
	LMarray(LM, ID, IEN, nnp, nen, nel, ndof);
	double Ke[ndof*nen][ndof*nen];
	EleStiff(Ke, 2, IEN, coord, nen);
	printf("%d element stiffness mat\n", 2);
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			printf("%5.2f\t", Ke[i][j]);
		}
		printf("\n");
	}
	return 0;
}