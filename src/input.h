//BC's
int geo_dog = 12;
int geo_trac = 20;// l6 b12 r16 t20- 4 edges for quad model
double trac_value[2] = {100,0};

//mesh properties
const int nsd = 2;//dimension
const int ndof = 2;//degree of freedom


//material properties
double rho = 1.0;//density
double nu = 0.3;//poison's ratio
double young_mod = 1.8e5;//Young's modulus
double g[2] = {0,-10};//gravity