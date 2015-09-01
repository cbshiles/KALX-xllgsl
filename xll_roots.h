// xll_roots.h - GSL 1-dim root finding
#pragma once
#include <functional>
#include <memory>
#include <stdexcept>
#include "gsl/gsl_errno.h"
#include "gsl/gsl_roots.h"

namespace gsl {

	// call gsl_root_fsolver_free when out of scope
	inline auto root_fsolver(const gsl_root_fsolver_type * type)
	{
		return std::unique_ptr<gsl_root_fsolver, void(*)(gsl_root_fsolver*)>(gsl_root_fsolver_alloc(type), gsl_root_fsolver_free);
	};

	class function {
		gsl_function _f;
	public:
		function()
		{ }
		template<class F>
		function(F f, void* params)
		{
			_f.function = static_cast<double (*)(double,void *)>(f);
			_f.params = params;
		}
		~function()
		{ }
		gsl_function* operator&()
		{
			return &_f;
		}
	};

} // gsl

#ifdef _DEBUG
#include <cassert>
#include <gsl/gsl_poly.h>

// a x^2 + b x + c
struct quadratic_params {
	double a, b, c;
};

double quadratic(double x, void *params)
{
	struct quadratic_params *p 
		= (struct quadratic_params *) params;

	double a = p->a;
	double b = p->b;
	double c = p->c;

	return (a * x + b) * x + c;
}

double quadratic_deriv(double x, void *params)
{
	struct quadratic_params *p 
		= (struct quadratic_params *) params;

	double a = p->a;
	double b = p->b;
//	double c = p->c;

	return 2.0 * a * x + b;
}

void quadratic_fdf(double x, void *params, double *y, double *dy)
{
	struct quadratic_params *p 
		= (struct quadratic_params *) params;

	double a = p->a;
	double b = p->b;
	double c = p->c;

	*y = (a * x + b) * x + c;
	*dy = 2.0 * a * x + b;
}

inline void test_gsl_root_fsolver()
{
	// http://www.gnu.org/software/gsl/manual/html_node/Root-Finding-Examples.html#Root-Finding-Examples
	{
		// gsl_root_fsolver unique pointer
		auto s = gsl::root_fsolver(gsl_root_fsolver_brent);
		quadratic_params params{1.,0.,-5.}; // x^2 - 5
		gsl_function F;
		F.function = quadratic;
		F.params = &params;
		double x_lo = 0.0, x_hi = 5.0, root = 0;
		double epsabs = 0, epsrel = 1e-5;

		int iter = 0;
		gsl_root_fsolver_set(s.get(), &F, x_lo, x_hi);
		while (GSL_SUCCESS == gsl_root_fsolver_iterate(s.get())) {
			++iter;
			x_lo = gsl_root_fsolver_x_lower(s.get());
			x_hi = gsl_root_fsolver_x_upper(s.get());
			root = gsl_root_fsolver_root(s.get());

			// |x_lo - x_hi| < epsabs + epsrel * min(|x_lo|, |x_hi|)
			if (GSL_SUCCESS == gsl_root_test_interval(x_lo, x_hi, epsabs, epsrel))
				break;
		}
		double sqrt5 = sqrt(5.);
		assert (fabs(root - sqrt5) < sqrt5*epsrel);
	}
	{
		auto s = gsl::root_fsolver(gsl_root_fsolver_brent);
		double params[] = {-5,0,1}; // -5 + x^2
		auto F = gsl::function([](double x, void* p) { return gsl_poly_eval((const double*)p, 3, x); }, params);
		double x_lo = 0.0, x_hi = 5.0, root = 0;
		gsl_root_fsolver_set(s.get(), &F, x_lo, x_hi);
		while (GSL_SUCCESS == gsl_root_fsolver_iterate(s.get())) {
			x_lo = gsl_root_fsolver_x_lower(s.get());
			x_hi = gsl_root_fsolver_x_upper(s.get());
			root = gsl_root_fsolver_root(s.get());

			// |x_lo - x_hi| < epsabs + epsrel * min(|x_lo|, |x_hi|)
			if (GSL_SUCCESS == gsl_root_test_interval(x_lo, x_hi, 0, .1))
				break;
		}

		assert (root == sqrt(5));
	}
}

#endif // _DEBUG