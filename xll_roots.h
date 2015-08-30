// xll_roots.h - GSL 1-dim root finding
#pragma once
#include <memory>
#include <stdexcept>
#include "gsl/gsl_roots.h"

namespace gsl {

	inline auto root_fsolver(const gsl_root_fsolver_type * type)
	{
		return std::unique_ptr<gsl_root_fsolver, void(*)(gsl_root_fsolver*)>(gsl_root_fsolver_alloc(type), gsl_root_fsolver_free);
	};
/*
	template<class... Ts>
	inline auto function(const std::function<double(double,Ts ...ts)& f)
	{

	};
*/
} // gsl

#ifdef _DEBUG

inline void test_gsl_root_fsolver()
{
	{
		auto s = gsl::root_fsolver(gsl_root_fsolver_brent);
		double params[] = {1,0,-5};
		auto function = [&params](double x) { return params[0] + x*(params[1] + x*params[2]); };
//		gsl_root_fsolver_set(s.get(), gsl_function{function,params}, 0, 5);
	}
}

#endif // _DEBUG