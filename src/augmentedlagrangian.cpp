#include "augmentedlagrangian.h"
#include <limits>

using namespace Eigen;
using namespace std;

AugmentedLagrangian::AugmentedLagrangian(OptimizationProblem &opt) : opt_(opt)
{
    initialize();
}

void AugmentedLagrangian::initialize()
{
    int dim             = std::max(0, opt_.getDimension());
    int nconstraints    = std::max(0, opt_.getNumConstraints());

    q0_.resize(dim);
    q0_.setZero();

    lb_.resize(nconstraints);
    lb_.setConstant(-numeric_limits<double>::infinity());

    ub_.resize(nconstraints);
    ub_.setConstant(numeric_limits<double>::infinity());

    status_ = SS_UNSOLVED;
}

VectorXd &AugmentedLagrangian::initialGuess()
{
    return q0_;
}

VectorXd &AugmentedLagrangian::lowerBounds()
{
    return lb_;
}

VectorXd &AugmentedLagrangian::upperBounds()
{
    return ub_;
}

bool AugmentedLagrangian::solve()
{
    if(!checkParameters())
    {
        status_ = SS_BADPROBLEM;
        return false;
    }

    status_ = SS_CONVERGED;
    return true;
}

bool AugmentedLagrangian::checkParameters()
{
    int dim = opt_.getDimension();
    if(q0_.size() != dim)
        return false;

    int nc = opt_.getNumConstraints();
    if(lb_.size() != nc || ub_.size() != nc)
        return false;

    for(int i=0; i<nc; i++)
        if(lb_[i] > ub_[i])
            return false;

    return true;
}

void AugmentedLagrangian::projectOntoB(VectorXd &q)
{
    int dim = q.size();
    assert(dim == ub_.size() && dim == lb_.size());
    for(int i=0; i<dim; i++)
        q[i] = std::min(ub_[i], std::max(lb_[i], q[i]));
}

void AugmentedLagrangian::projectShifted(const VectorXd &x, const VectorXd &v, VectorXd &p)
{
    VectorXd diff = x-v;
    projectOntoB(diff);
    p = x - diff;
}
