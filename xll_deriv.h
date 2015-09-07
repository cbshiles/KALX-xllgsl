// xll_derive.h - numerical differentiation
// http://www.gnu.org/software/gsl/manual/html_node/Numerical-Differentiation.html#Numerical-Differentiation
#pragma once
#include <functional>
#include <stdexcept>
#include "gsl/gsl_errno.h"
#include "gsl/gsl_deriv.h"

namespace gsl {

	using function = std::function<double(double)>;

	struct deriv {
		double h, result, abserr;
		gsl_function f_;
		static double static_f(double x, void* params)
		{
			const function& f = *static_cast<function*>(params);

			return f(x);
		}

		double central(const function& f, double x)
		{
			f_.function = deriv::static_f;
			f_.params = (void*)&f;

			if (GSL_SUCCESS != gsl_deriv_central(&f_, x, h, &result, &abserr))
				throw std::runtime_error(__FILE__ ": gsl::central failed");

			return result;
		}
		double forward(const function& f, double x)
		{
			f_.function = deriv::static_f;
			f_.params = (void*)&f;

			if (GSL_SUCCESS != gsl_deriv_forward(&f_, x, h, &result, &abserr))
				throw std::runtime_error(__FILE__ ": gsl::forward failed");

			return result;
		}
		double backward(const function& f, double x)
		{
			f_.function = deriv::static_f;
			f_.params = (void*)&f;

			if (GSL_SUCCESS != gsl_deriv_backward(&f_, x, h, &result, &abserr))
				throw std::runtime_error(__FILE__ ": gsl::backward failed");

			return result;
		}
	};

	inline auto central(deriv& h, const function& f)
	{
		return [f,&h](double x) { return h.central(f, x); };
	}
	inline auto forward(deriv& h, const function& f)
	{
		return [f,&h](double x) { return h.forward(f, x); };
	}
	inline auto backward(deriv& h, const function& f)
	{
		return [f,&h](double x) { return h.backward(f, x); };
	}

} // gsl

#ifdef _DEBUG
#include <cassert>

inline void test_gsl_deriv()
{
	double y;
	auto f = [](double x) { return x*x; };

	for (double h = 1; 1 + h != 1; h /= 2) {
		auto d = gsl::deriv{h};
		y = d.central(f, 1);
		assert (fabs(y - 2) < d.abserr);
		y = d.forward(f, 1);
		assert (fabs(y - 2) < d.abserr);
		y = d.backward(f, 1);
		assert (fabs(y - 2) < d.abserr);
	}

	auto d = gsl::deriv{.1};
	{
		auto df = central(d, f);
		for (double x = -1; x <= 1; x += 0.1) {
			y = df(x);
			assert (fabs(y - 2*x) < d.abserr);
		}
	}
	{
		auto df = forward(d, f);
		for (double x = -1; x <= 1; x += 0.1) {
			y = df(x);
			assert (fabs(y - 2*x) < d.abserr);
		}
	}
	{
		auto df = backward(d, f);
		for (double x = -1; x <= 1; x += 0.1) {
			y = df(x);
			assert (fabs(y - 2*x) < d.abserr);
		}
	}
}

#endif // _DEBUG