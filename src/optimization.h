#ifndef OPTIMIZATION_H
#define OPTIMIZATION_H

#include <Eigen/Core>
#include <Eigen/Sparse>

class OptimizationProblem
{
public:
    virtual int getDimension()=0;
    virtual int getNumConstraints()=0;

    virtual double evaluateObjective(const Eigen::VectorXd &q)=0;
    virtual void evaluateJObjective(const Eigen::VectorXd &q, Eigen::VectorXd &Jf);
    virtual void evaluateHObjective(const Eigen::VectorXd &q, Eigen::SparseMatrix<double> &Hf);

    virtual void evaluateConstraints(const Eigen::VectorXd &q, Eigen::VectorXd &c);
    virtual void evaluateJConstraints(const Eigen::VectorXd &q, std::vector<Eigen::VectorXd> &Jc);
    virtual void evaluateHConstraints(const Eigen::VectorXd &q, std::vector<Eigen::SparseMatrix<double> > &Hc);
};

#endif // OPTIMIZATION_H
