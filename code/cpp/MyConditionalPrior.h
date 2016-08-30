#ifndef DNest4_Template_MyConditionalPrior
#define DNest4_Template_MyConditionalPrior

#include "DNest4/code/DNest4.h"

/*
* Represents the conditional prior for mixture components
* in (mu, log_width) space
*/

class MyConditionalPrior:public DNest4::ConditionalPrior
{
	private:
        static const DNest4::Cauchy cauchy;

        // Location and scale parameter for log_width prior
        double location_log_width;
        double scale_log_width;

        // Location and scale parameter for log_amplitude prior
        double location_log_amplitude;
        double scale_log_amplitude;

		double perturb_hyperparameters(DNest4::RNG& rng);

	public:
		MyConditionalPrior();

		void from_prior(DNest4::RNG& rng);

		double log_pdf(const std::vector<double>& vec) const;
		void from_uniform(std::vector<double>& vec) const;
		void to_uniform(std::vector<double>& vec) const;

		void print(std::ostream& out) const;
		static const int weight_parameter = 1;
};

#endif

