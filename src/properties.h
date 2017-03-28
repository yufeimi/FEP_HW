//mesh properties
const int nsd = 2;//dimension
const int ndof = 2;//degree of freedom

const int nnp = 10;//node number
const int nel = 4;//element number
const int nen = 4;//node number per element
const int ele_type = 1;//1 for tri, 2 for quad
const int shape = 1;//1 for linear, 2 for quadratic

//material properties
double rho = 1.0;//density
double nu = 0.3;//poison's ratio
double young_mod = 1e8;//Young's modulus
double lambda = nu*young_mod/((1+nu)*(1-2*nu));//D parameter
double mu = young_mod/(2*(1+nu));//D parameter
//define the D matix
double D[3][3] = {lambda+2*mu, lambda, 0,
				lambda, lambda+2*mu, 0,
				0, 0, mu};
