#ifndef AUGMENTEDLAGRANGIAN_H
#define AUGMENTEDLAGRANGIAN_H

#include "optimization.h"

class AugmentedLagrangian
{
public:
    enum SolverStatus {SS_UNSOLVED, SS_CONVERGED, SS_STALLED, SS_BADPROBLEM};

    AugmentedLagrangian(OptimizationProblem &opt);

    Eigen::VectorXd &upperBounds();
    Eigen::VectorXd &lowerBounds();
    Eigen::VectorXd &initialGuess();

    bool solve();

private:
    void initialize();
    bool checkParameters();
    void projectOntoB(Eigen::VectorXd &q);
    void projectShifted(const Eigen::VectorXd &x, const Eigen::VectorXd &v, Eigen::VectorXd &q);

    OptimizationProblem &opt_;
    SolverStatus status_;

    Eigen::VectorXd ub_;
    Eigen::VectorXd lb_;
    Eigen::VectorXd q0_;
};

#endif // AUGMENTEDLAGRANGIAN_H
