#ifndef DNest4_Data
#define DNest4_Data

#include <vector>
#include <algorithm>

class Data
{
	private:
		std::vector<double> x;
        std::vector<double> y;
        std::vector<double> y_err;

	public:
		Data();
		void load(const char* filename);

		// Getters
		const std::vector<double>& get_x() const { return x; }
        const std::vector<double>& get_y() const { return y; }
        const std::vector<double>& get_y_err() const { return y_err; }
        double get_x_min() const
	{ return *std::min_element(x.begin(), x.end()); }
	double get_x_max() const
        { return *std::max_element(x.begin(), x.end()); }
        double get_x_range() const
        { return get_x_max() - get_x_min(); }

	// Singleton
	private:
		static Data instance;
	public:
		static Data& get_instance() { return instance; }
};

#endif

