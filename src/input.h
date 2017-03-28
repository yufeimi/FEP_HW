//This is a test input which is to
//be removed when read_input is implemented
//ID array for ndof assignment
//nnp * ndof
int ID[10][2] = {0,0,1,2,0,0,3,4,
				5,6,7,8,9,10,11,12,13,
				14,15,16};
//equation number starts with 1, because 0 denotes to fixed
//IEN array for element connectivity
//nel * nen
int IEN[4][4] = {0,1,3,2,1,5,4,3,
				5,6,7,4,6,9,8,7};
//coordinates
double coord[10][2] = {{0,0},{0.25,0},{0,0.25},
				{0.25,0.25},{0.5,0.25},{0.5,0},
				{0.75,0},{0.75,0.25},{1.0,0.25},
				{1.0,0}};