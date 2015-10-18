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
} // derive
} // gsl

#ifdef _DEBUG
#include <cassert>

inline void test_gsl_deriv()
{
	double y;

	auto f = [](double x) { return x*x; };
	for (double h = 1; h > 10*std::numeric_limits<double>::epsilon(); h /= 2) {
		auto df = gsl::deriv::central(f, h);
		y = df(1);
		assert (fabs(y - 2) < h);
		auto df_ = gsl::deriv::forward(f, h);
		y = df_(1);
		assert (fabs(y - 2) < 100*h);
		auto _df = gsl::deriv::backward(f, h);
		y = _df(1);
		assert (fabs(y - 2) < 10*h);
	}

}

#endif // _DEBUG