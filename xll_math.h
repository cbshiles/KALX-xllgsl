// xll_math.h
#pragma once
#include <functional>
#include "gsl/gsl_math.h"

namespace gsl {

	struct function : public gsl_function_struct {
		function(double (*function)(double, void*), void* params)
		{
			gsl_function::function = function;
			gsl_function::params = params;
		}
		function(const function&) = delete;
		function& operator=(const function&) = delete;
		~function()
		{ }
		double operator()(double x)
		{
			return gsl_function_struct::function(x, params);
		}
	};

	inline double function(double x, void* f)
	{
		const function_base& f_ = 0;
	}

	// user manages lifetime of f
	inline std::function<double(double)> make_function(const gsl_function_struct& f)
	{
		return [&f](double x) { return f.function(x,  f.params); };
	}
}