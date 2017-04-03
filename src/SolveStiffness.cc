#include <Eigen/Sparse>
#include <Eigen/Dense>

void SolveStiffness(Eigen::SparseMatrix<double> K,
	Eigen::VectorXd F, Eigen::VectorXd &d)
{
	Eigen::SimplicialCholesky<Eigen::SparseMatrix<double> > chol(K);
	d = chol.solve(F);
}