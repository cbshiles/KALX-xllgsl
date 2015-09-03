// xll_roots.h - GSL 1-dim root finding
// http://www.gnu.org/software/gsl/manual/html_node/One-dimensional-Root_002dFinding.html#One-dimensional-Root_002dFinding
#pragma once
#include <functional>
#include <memory>
#include <stdexcept>
#include <tuple>
#include "gsl/gsl_errno.h"
#include "gsl/gsl_roots.h"

namespace gsl {

	using function = std::function<double(double)>;

	// root bracketing solvers
	class root_fsolver {

		function F;
		gsl_function F_;
		gsl_root_fsolver* s;

		// provide double(*)(double,void*) signature for gsl_function
		static double static_function(double x, void* params)
		{
			const function& f = *static_cast<function*>(params);

			return f(x);
		}
	public:
		root_fsolver(const gsl_root_fsolver_type * type)
			: s(gsl_root_fsolver_alloc(type))
		{ }
		root_fsolver(const root_fsolver&) = delete;
		root_fsolver& operator=(const root_fsolver&) = delete;
		~root_fsolver()
		{
			gsl_root_fsolver_free(s);
		}

		// needed for gsl_root_fsolver_* routines
		gsl_root_fsolver* get() const
		{
			return s;
		}
		// syntactic sugar
		operator gsl_root_fsolver*() const
		{
			return s;
		}

		int set(const function& f, double lo, double hi)
		{
			F = f;
			F_.function = static_function;
			F_.params = &F;

			return gsl_root_fsolver_set(s, &F_, lo, hi);
		}

		// forward to gsl_root_fsolver_* functions
		int iterate()
		{
			return gsl_root_fsolver_iterate(s);
		}
		double x_lower() const
		{
			return gsl_root_fsolver_x_lower(s);
		}
		double x_upper() const
		{
			return gsl_root_fsolver_x_upper(s);
		}
		double root() const
		{
			return gsl_root_fsolver_root(s);
		}

		// specify convergence condition
		double solve(const std::function<bool(const root_fsolver&)>& done)
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
		return [epsabs,epsrel](const root_fsolver& s) {
			return GSL_SUCCESS == gsl_root_test_interval(s.x_lower(), s.x_upper(), epsabs, epsrel);
		};
	}

	// root finding using derivatives
	class root_fdfsolver {
		// function and its derivative
		using fdfunction = std::tuple<function,function>;

		fdfunction FdF;
		gsl_function_fdf F_;
		gsl_root_fdfsolver* s;

		// provide pointers for gsl_function_fdf
		static double static_f(double x, void* params)
		{
			const fdfunction& f = *static_cast<fdfunction*>(params);

			return std::get<0>(f)(x);
		}
		static double static_df(double x, void* params)
		{
			const fdfunction& f = *static_cast<fdfunction*>(params);

			return std::get<1>(f)(x);
		}
		static void static_fdf(double x, void* params, double* fx, double* dfx)
		{
			const fdfunction& f = *static_cast<fdfunction*>(params);

			*fx = std::get<0>(f)(x);
			*dfx = std::get<1>(f)(x);
		}
	public:
		root_fdfsolver(const gsl_root_fdfsolver_type * type)
			: s(gsl_root_fdfsolver_alloc(type))
		{ }
		root_fdfsolver(const root_fdfsolver&) = delete;
		root_fdfsolver& operator=(const root_fdfsolver&) = delete;
		~root_fdfsolver()
		{
			gsl_root_fdfsolver_free(s);
		}

		// needed for gsl_root_fdfsolver_* routines
		gsl_root_fdfsolver* get() const
		{
			return s;
		}
		// syntactic sugar
		operator gsl_root_fdfsolver*() const
		{
			return s;
		}

		int set(const function& f, const function& df, double x0)
		{
			FdF = std::make_tuple(f, df);

			F_.f = static_f;
			F_.df = static_df;
			F_.fdf = static_fdf;
			F_.params = &FdF;

			return gsl_root_fdfsolver_set(s, &F_, x0);
		}

		// forward to gsl_root_fdfsolver_* functions
		int iterate()
		{
			return gsl_root_fdfsolver_iterate(s);
		}
		double root() const
		{
			return gsl_root_fdfsolver_root(s);
		}

		// specify convergence condition given previous root
		double solve(const std::function<bool(const root_fdfsolver&,double)>& done)
		{
			double x = root();
			while (GSL_SUCCESS == iterate()) {
				if (done(*this, x))
					break;
				x = root();
			}

			return root();
		}
	};

	// convergence helper functions
	inline auto root_test_delta(double epsabs, double epsrel)
	{
		return [epsabs,epsrel](const root_fdfsolver& s, double x) {
			return GSL_SUCCESS == gsl_root_test_delta(x, s.root(), epsabs, epsrel);
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

// This is bad. Why???
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
	// GSL example
	{
		gsl_root_fsolver* s = gsl_root_fsolver_alloc(gsl_root_fsolver_brent);
		
		quadratic_params params{1.,0.,-5.}; // x^2 - 5
		gsl_function F;
		F.function = quadratic;
		F.params = &params;
		double x_lo = 0.0, x_hi = 5.0;
		double epsabs = 0, epsrel = 1e-5;

		gsl_root_fsolver_set(s, &F, x_lo, x_hi);
		while (GSL_SUCCESS == gsl_root_fsolver_iterate(s)) {
			x_lo = gsl_root_fsolver_x_lower(s);
			x_hi = gsl_root_fsolver_x_upper(s);

			// |x_lo - x_hi| < epsabs + epsrel * min(|x_lo|, |x_hi|)
			if (GSL_SUCCESS == gsl_root_test_interval(x_lo, x_hi, epsabs, epsrel))
				break;
		}
		double root = gsl_root_fsolver_root(s);
		double sqrt5 = sqrt(5.);
		assert (fabs(root - sqrt5) < sqrt5*epsrel);

		gsl_root_fsolver_free(s);
	}
	// root_fsolver class with function<double(double)>
	{
		gsl::root_fsolver s(gsl_root_fsolver_brent);

		std::vector<double> params{-5,0,1}; // -5 + x^2
		auto F = [&params](double x) { return gsl_poly_eval(&params[0], params.size(), x); };
		double x_lo = 0.0, x_hi = 5.0, epsrel = 1e-6;
		s.set(F, x_lo, x_hi);
		
		double root = s.solve(gsl::root_test_interval(0, epsrel));
		double sqrt5 = sqrt(5.);
		assert (fabs(root - sqrt5) < sqrt5*epsrel);
	}
}
inline void test_gsl_root_fdfsolver()
{
	// root_fdfsolver class with function<tuple<double,double>(double)>
	{
		gsl::root_fdfsolver s(gsl_root_fdfsolver_newton);

		// F(x) = x^2 - 5
		auto F = [](double x) {
			return x*x - 5;
		};
		auto dF = [](double x) { 
			return 2*x;
		};
		double x = 5.0, epsrel = 1e-6;
		s.set(F, dF, x);

		double root = s.solve(gsl::root_test_delta(0, epsrel));
		double sqrt5 = sqrt(5.);
		assert (fabs(root - sqrt5) < sqrt5*epsrel);
	}
}

#endif // _DEBUG