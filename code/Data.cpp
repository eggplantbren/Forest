#include "Data.h"
#include <fstream>
#include <iostream>

using namespace std;

Data Data::instance;

Data::Data()
{

}

void Data::load(const char* filename)
{
	fstream fin(filename, ios::in);
	if(!fin)
	{
		cerr<<"# Error. Couldn't open file "<<filename<<"."<<endl;
		return;
	}

	// Empty the vector
	x.clear();
    y.clear();
    y_err.clear();

	double temp1, temp2, temp3;
	while(fin>>temp1 && fin>>temp2 && fin>>temp3)
    {
		x.push_back(temp1);
        y.push_back(temp2);
        y_err.push_back(temp3);
    }

	cout<<"# Loaded "<<x.size()<<" data points from file "
			<<filename<<"."<<endl;
	fin.close();
}

