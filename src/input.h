//BC's
int geo_dog = 14;
int geo_trac = 6;// l6 b12 r16 t20- 4 edges for quad model
				//plate model center22 left6 bottom10 right14 top17
double trac_value[2] = {10000,0};

//mesh properties
const int nsd = 2;//dimension
const int ndof = 2;//degree of freedom


//material properties
double rho = 100.0;//density
double nu = 0.3;//poison's ratio
double young_mod = 1.8e5;//Young's modulus
double g[2] = {0,0};//gravity