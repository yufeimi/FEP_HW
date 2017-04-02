//This is a test input which is to
//be removed when read_input is implemented
//ID array for ndof assignment
//nnp * ndof
//int ID[10][2] = {0,0,1,2,0,0,3,4,
//				5,6,7,8,9,10,11,12,13,
//				14,15,16};
//equation number starts with 1, because 0 denotes to fixed
//IEN array for element connectivity
//nel * nen
//int IEN[4][4] = {0,1,3,2,1,5,4,3,
//				5,6,7,4,6,9,8,7};
//coordinates
//double coord[10][2] = {{0,0},{1,0},{0,1},
//				{1,1},{2,1},{2,0},
//				{3,0},{3,1},{4,1},
//				{4,0}};

int geo_dog = 6;
int geo_trac = 16;//6  12 16 20
double trac_value[2] = {100,0};