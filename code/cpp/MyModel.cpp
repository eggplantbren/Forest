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
	// Grab the values from the dataset
	const auto& x = Data::get_instance().get_x();
	const auto& y = Data::get_instance().get_y();
	const auto& y_err = Data::get_instance().get_y_err();

    // Grab the gaussians
    const auto& components = gaussians.get_components();

	double logL = 0.;
	double var, model, mu, sigma, amp;
	for(size_t i=0; i<y.size(); i++)
    {
        // Build the model at location x[j]
        model = 0;
        for(size_t j=0; j<components.size(); j++)
    	{
    		mu = components[j][0];
    		sigma = exp(components[j][1]);
    		amp = exp(components[j][2]);
    		model += amp * exp(-0.5*pow((x[i] - mu)/ sigma,2));
    	}
        var = y_err[i]*y_err[i];
		logL += -0.5*log(2.*M_PI*var) - 0.5*pow(y[i] - model, 2)/var;
    }

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
