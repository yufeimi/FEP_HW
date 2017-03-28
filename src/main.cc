//#include <pumi.h>
//#include <PCU.h>
#include <iostream>
#include <stdio.h>
#include "properties.h"
#include "global_constants.h"
#include "declaration_vectors.h"
#include "input.h"

int main(int argc, char const *argv[])
{
	printf("Starting the FE program...\n");
	//get LM array 
	int LM[ndof*nen][nel] = LM(ID, IEN);
	return 0;
}