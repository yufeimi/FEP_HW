//#include <pumi.h>
//#include <PCU.h>
#include <iostream>
#include <stdio.h>
#include "properties.h"
#include "global_constants.h"
#include "declaration_vectors.h"
#include "input.h" //this includes ID and IEN arrays, temporarily
#include "LMarray.cc"

int main(int argc, char const *argv[])
{
	printf("Starting the FE program...\n");
	//get LM array
	//See LMarray subroutine
	int LM[nel][ndof*nen];
	LMarray(LM, ID, IEN, nnp, nen, nel, ndof);
	printf("%d\n",LM[3][4]);
	return 0;
}