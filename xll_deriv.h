// xll_derive.h - numerical differentiation
// http://www.gnu.org/software/gsl/manual/html_node/Numerical-Differentiation.html#Numerical-Differentiation
#pragma once
#include <functional>
#include <stdexcept>
#include "gsl/gsl_errno.h"
#include "gsl/gsl_deriv.h"
#include "xll_math.h"

namespace gsl {
namespace deriv {

	using function = std::function<double(double)>;

	inline auto central(const function& f, double h = 1e-8)
	{
		return [f,h](double x) {
			double result, abserr;
			gsl::function f_(f);
			
			if (GSL_SUCCESS != gsl_deriv_central(&f_, x, h, &result, &abserr))
				throw std::runtime_error(__FILE__ ": " __FUNCTION__ ": failed");

			return result;
		};
	}
	inline auto forward(const function& f, double h = 1e-8)
	{
		return [f,h](double x) {
			double result, abserr;
			gsl::function f_(f);

			if (GSL_SUCCESS != gsl_deriv_forward(&f_, x, h, &result, &abserr))
				throw std::runtime_error(__FILE__ ": " __FUNCTION__ ": failed");

			return result;
		};
	}
	inline auto backward(const function& f, double h = 1e-8)
	{
		return [f,h](double x) {
			double result, abserr;
			gsl::function f_(f);

			if (GSL_SUCCESS != gsl_deriv_backward(&f_, x, h, &result, &abserr))
				throw std::runtime_error(__FILE__ ": " __FUNCTION__ ": failed");

			return result;
		};
	}
	/*	inline auto forward(deriv& h, const function& f)
	{
		return [f,&h](double x) { return h.forward(f, x); };
	}
	inline auto backward(deriv& h, const function& f)
	{
		return [f,&h](double x) { return h.backward(f, x); };
	}
*/
} // derive
} // gsl

#ifdef _DEBUG
#include <cassert>

inline void test_gsl_deriv()
{
	double y;

	for (double h = 1; h > 10*std::numeric_limits<double>::epsilon(); h /= 2) {
		auto f = gsl::deriv::central([](double x) { return x*x; }, h);
		y = f(1);
		assert (fabs(y - 2) < h);
		auto g = gsl::deriv::forward([](double x) { return x*x; }, h);
		y = g(1);
//		assert (fabs(y - 2) < 10*h);
		auto k = gsl::deriv::backward([](double x) { return x*x; }, h);
		y = k(1);
//		assert (fabs(y - 2) < 10*h);
	}

}

#endif // _DEBUG