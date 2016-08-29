#include "MyConditionalPrior.h"
#include "DNest4/code/DNest4.h"
#include <cmath>
#include "Data.h"

using namespace DNest4;

const Cauchy MyConditionalPrior::cauchy(0.0, 5.0);

MyConditionalPrior::MyConditionalPrior()
{

}

void MyConditionalPrior::from_prior(RNG& rng)
{
    const auto& data = Data::get_instance();

    location_mu = data.get_x_min() + data.get_x_range()*rng.rand();
    scale_mu = exp(cauchy.generate(rng));

    location_log_width = cauchy.generate(rng);
    scale_log_width = 5.0*rng.rand();

    location_log_amplitude = cauchy.generate(rng);
    scale_log_amplitude = 5.0*rng.rand();
}

double MyConditionalPrior::perturb_hyperparameters(RNG& rng)
{
	double logH = 0.0;

    // Choose a parameter to move
    int which = rng.rand_int(6);

    if(which == 0)
    {
        const auto& data = Data::get_instance();
        location_mu += data.get_x_range()*rng.randh();
        wrap(location_mu, data.get_x_min(), data.get_x_max());
    }
    else if(which == 1)
    {
        scale_mu = log(scale_mu);
        logH += cauchy.perturb(scale_mu, rng);
        scale_mu = exp(scale_mu);

        if(scale_mu == 0)
            scale_mu = 1E-300;
        if(std::isinf(scale_mu))
            scale_mu = 1E300;
    }
    else if(which == 2)
    {
        logH += cauchy.perturb(location_log_width, rng);
    }
    else if(which == 3)
    {
        scale_log_width += 5.0*rng.randh();
        wrap(scale_log_width, 0.0, 5.0);
    }
    else if(which == 4)
    {
        logH += cauchy.perturb(location_log_amplitude, rng);
        wrap(scale_log_amplitude, 0.0, 5.0);
    }
    else
    {
        scale_log_amplitude += 5.0*rng.randh();
        wrap(scale_log_amplitude, 0.0, 5.0);
    }

	return logH;
}

// vec = {mu, log_width, log_amplitude}
double MyConditionalPrior::log_pdf(const std::vector<double>& vec) const
{
    // Three Laplace distributions
    Laplace l1(location_mu, scale_mu);
    Laplace l2(location_log_width, scale_log_width);
    Laplace l3(location_log_amplitude, scale_log_amplitude);

	return l1.log_pdf(vec[0]) + l2.log_pdf(vec[1]) + l3.log_pdf(vec[2]);
}

void MyConditionalPrior::from_uniform(std::vector<double>& vec) const
{
    // Three Laplace distributions
    Laplace l1(location_mu, scale_mu);
    Laplace l2(location_log_width, scale_log_width);
    Laplace l3(location_log_amplitude, scale_log_amplitude);

    vec[0] = l1.cdf_inverse(vec[0]);
    vec[1] = l2.cdf_inverse(vec[1]);
    vec[2] = l3.cdf_inverse(vec[2]);
}

void MyConditionalPrior::to_uniform(std::vector<double>& vec) const
{
    // Three Laplace distributions
    Laplace l1(location_mu, scale_mu);
    Laplace l2(location_log_width, scale_log_width);
    Laplace l3(location_log_amplitude, scale_log_amplitude);

    vec[0] = l1.cdf(vec[0]);
    vec[1] = l2.cdf(vec[1]);
    vec[2] = l3.cdf(vec[2]);
}

void MyConditionalPrior::print(std::ostream& out) const
{
    out<<location_mu<<' '<<scale_mu<<' '<<location_log_width<<' ';
    out<<scale_log_width<<' '<<location_log_amplitude<<' ';
    out<<scale_log_amplitude<<' ';
}

