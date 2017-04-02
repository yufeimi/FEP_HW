//mesh properties
const int nsd = 2;//dimension
const int ndof = 2;//degree of freedom

//const int nnp = 10;//node number
const int nel = 4;//element number
//const int nen = 4;//node number per element
const int ele_type = 2;//1 for tri, 2 for quad
const int shape = 1;//1 for linear, 2 for quadratic
//const int nint = 4;//4 quadrature points

//material properties
double rho = 1.0;//density
double nu = 0.3;//poison's ratio
double young_mod = 1.8e3;//Young's modulus
double g[2] = {10,0};//gravity