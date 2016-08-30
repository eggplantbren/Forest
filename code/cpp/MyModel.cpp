#include "MyModel.h"
#include "DNest4/code/DNest4.h"
#include "Data.h"
#include <limits>

using namespace std;
using namespace DNest4;

MyModel::MyModel()
:gaussians(3, 100, false, MyConditionalPrior(), PriorType::log_uniform)
,model(Data::get_instance().get_x().size())
{

}

void MyModel::from_prior(RNG& rng)
{
    gaussians.from_prior(rng);
    calculate_model();
}

double MyModel::perturb(RNG& rng)
{
	double logH = 0.0;

    logH += gaussians.perturb(rng);

    // Is a fast update of the model possible?
    bool update = gaussians.get_removed().size() == 0;
    calculate_model(update);

	return logH;
}

void MyModel::calculate_model(bool update)
{
    // Zero the model unless doing a fast update
    if(!update)
        for(auto& m: model)
            m = 0.0;

    // Get the components added (for updates)
    // or all components (if recomputing from scratch)
    const auto& components = (update)?
                                (gaussians.get_added()):
                                (gaussians.get_components());

    // Get the x-values from the data
    const auto& x = Data::get_instance().get_x();

    // Add the model components
	double mu, sigma, amp, tau;
    for(size_t i=0; i<components.size(); ++i)
	{
		mu = components[i][0];
		sigma = exp(components[i][1]);
		amp = exp(components[i][2]);
        tau = 1.0/(sigma*sigma);

        for(size_t j=0; j<model.size(); ++j)
    		model[j] += amp * exp(-0.5*tau*pow(x[j] - mu, 2));
	}
}

double MyModel::log_likelihood() const
{
	// Grab the values from the dataset
	const auto& y = Data::get_instance().get_y();
	const auto& y_err = Data::get_instance().get_y_err();

	double logL = 0.;

    double var;
	for(size_t i=0; i<y.size(); i++)
    {
        var = y_err[i]*y_err[i];
		logL += -0.5*log(2.*M_PI*var) - 0.5*pow(y[i] - model[i], 2)/var;
    }

	return logL;
}

void MyModel::print(std::ostream& out) const
{
    // Output the model first
    for(double m: model)
        out<<m<<' ';
    gaussians.print(out);
}

string MyModel::description() const
{
	return string("");
}

