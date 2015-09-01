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

	// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2010/n3043.html
	// convert non-capturing lambda to function pointer
	template<class F>
	inline gsl_function function(F f, void* params)
	{
		gsl_function _f;

		_f.function = static_cast<double (*)(double,void *)>(f);
		_f.params = params;

		return _f;
	}

	class root_fsolve {
		using function = std::function<double(double)>;

		function F;
		gsl_function F_;
		std::unique_ptr<gsl_root_fsolver, void(*)(gsl_root_fsolver*)> s;

		// provide double(*)(double,void*) signature for gsl_function
		static double static_function(double x, void* params)
		{
			const function& f = *reinterpret_cast<function*>(params);

			return f(x);
		}
	public:
		root_fsolve(const gsl_root_fsolver_type * type)
			: s(root_fsolver(type))
		{ }
		root_fsolve(const root_fsolve&) = delete;
		root_fsolve& operator=(const root_fsolve&) = delete;
		~root_fsolve()
		{ }

		// needed for gsl_root_fsolver_* routines
		gsl_root_fsolver* get() const
		{
			return s.get();
		}
		// syntactic sugar
		operator gsl_root_fsolver*() const
		{
			return get();
		}

		int set(const function& f, double lo, double hi)
		{
			F = f;
			F_.function = static_function;
			F_.params = &F;

			return gsl_root_fsolver_set(s.get(), &F_, lo, hi);
		}

		int iterate()
		{
			return gsl_root_fsolver_iterate(s.get());
		}
		double x_lower() const
		{
			return gsl_root_fsolver_x_lower(s.get());
		}
		double x_upper() const
		{
			return gsl_root_fsolver_x_upper(s.get());
		}
		double root() const
		{
			return gsl_root_fsolver_root(s.get());
		}

		// specify convergence condition
		double solve(const std::function<bool(const root_fsolve&)>& done)
		{
			while (GSL_SUCCESS == iterate()) {
				if (done(*this))
					break;
			}

			return root();
		}
	};

	// convergence helper functions
	inline auto root_test_interval(double epsabs, double epsrel)
	{
		return [epsabs,epsrel](const root_fsolve& s) {
			return GSL_SUCCESS == gsl_root_test_interval(s.x_lower(), s.x_upper(), epsabs, epsrel);
		};
	}
} // gsl

#ifdef _DEBUG
#include <cassert>
#include <vector>
#include <gsl/gsl_poly.h>

// http://www.gnu.org/software/gsl/manual/html_node/Root-Finding-Examples.html#Root-Finding-Examples

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
	{	// simple inline function wrappers
		auto s = gsl::root_fsolver(gsl_root_fsolver_brent);

		double params[] = {-5,0,1}; // -5 + x^2
		auto F = gsl::function([](double x, void* p) { return gsl_poly_eval((const double*)p, 3, x); }, params);
		
		double x_lo = 0.0, x_hi = 5.0, epsrel = 1e-6;
		gsl_root_fsolver_set(s.get(), &F, x_lo, x_hi);
		
		while (GSL_SUCCESS == gsl_root_fsolver_iterate(s.get())) {
			x_lo = gsl_root_fsolver_x_lower(s.get());
			x_hi = gsl_root_fsolver_x_upper(s.get());

			// |x_lo - x_hi| < epsabs + epsrel * min(|x_lo|, |x_hi|)
			if (GSL_SUCCESS == gsl_root_test_interval(x_lo, x_hi, 0, epsrel))
				break;
		}
		
		double root = gsl_root_fsolver_root(s.get());
		double sqrt5 = sqrt(5.);
		assert (fabs(root - sqrt5) < sqrt5*epsrel);
	}
	{	// root_fsolve class
		gsl::root_fsolve s(gsl_root_fsolver_brent);

		std::vector<double> params{-5,0,1}; // -5 + x^2
		double x_lo = 0.0, x_hi = 5.0, epsrel = 1e-6;
		s.set([&params](double x) { return gsl_poly_eval(&params[0], params.size(), x); }, x_lo, x_hi);

		while (GSL_SUCCESS == s.iterate()) {
			x_lo = gsl_root_fsolver_x_lower(s.get());
			x_hi = gsl_root_fsolver_x_upper(s); // operator gsl_root_fsolver*

			// |x_lo - x_hi| < epsabs + epsrel * min(|x_lo|, |x_hi|)
			if (GSL_SUCCESS == gsl_root_test_interval(x_lo, x_hi, 0, epsrel))
				break;
		}

		double root = gsl_root_fsolver_root(s.get());
		double sqrt5 = sqrt(5.);
		assert (fabs(root - sqrt5) < sqrt5*epsrel);
	}
	{	// root_fsolve class
		gsl::root_fsolve s(gsl_root_fsolver_brent);

		std::vector<double> params{-5,0,1}; // -5 + x^2
		double x_lo = 0.0, x_hi = 5.0, epsrel = 1e-6;
		s.set([&params](double x) { return gsl_poly_eval(&params[0], params.size(), x); }, x_lo, x_hi);
		
		double root = s.solve(gsl::root_test_interval(0, epsrel));
		double sqrt5 = sqrt(5.);
		assert (fabs(root - sqrt5) < sqrt5*epsrel);
	}
}

#endif // _DEBUG