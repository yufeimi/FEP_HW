//BC's
int geo_dog = 6;
int geo_trac = 6;// l6 b12 r16 t20- 4 edges for quad model
				//plate model center22 left6 bottom10 right14 top17
				//r14 10 6 17 for beam
double trac_value[2] = {0,0};

//mesh properties
const int nsd = 2;//dimension
const int ndof = 2;//degree of freedom


//material properties
double rho = 1000.0;//density
double nu = 0.3;//poison's ratio
double young_mod = 1.8e5;//Young's modulus
double g[2] = {0,-10};//gravity