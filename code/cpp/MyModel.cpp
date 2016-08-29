#include "MyModel.h"
#include "DNest4/code/DNest4.h"
#include "Data.h"
#include <limits>

using namespace std;
using namespace DNest4;

MyModel::MyModel()
:gaussians(3, 100, false, MyConditionalPrior(), PriorType::log_uniform)
{

}

void MyModel::from_prior(RNG& rng)
{
    gaussians.from_prior(rng);
}

double MyModel::perturb(RNG& rng)
{
	double logH = 0.0;

    logH += gaussians.perturb(rng);

	return logH;
}

double MyModel::log_likelihood() const
{
	double logL = 0.0;

	return logL;
}

void MyModel::print(std::ostream& out) const
{
    gaussians.print(out);
}

string MyModel::description() const
{
	return string("");
}

