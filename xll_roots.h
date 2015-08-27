// xll_roots.h
#pragma once
#include <functional>
#include "gsl/gsl_roots.h"

namespace gsl {
/*
	struct function_base {
		virtual double operator()(double) const = 0;
		virtual ~function_base() = 0;
	};
	class function_lambda : public function_base {
		std::function<double(double)> f;
	public:
		function_lambda(const std::function<double(double)>& f)
			: f(f)
		{ }
		function_lambda(const function_lambda&) = default;
		function_lambda& operator=(const function_lambda&) = default;
		~function_lambda()
		{ }
		double operator()(double x) const override
		{
			return f(x);
		}
	};

	inline double function(double x, void* v)
	{
		const function_base& f = *reinterpret_cast<const function_base*>(v);

		return  f(x);
	}
*/
	class root_fsolver {
		gsl_root_fsolver* p;
		gsl_function _f;
		std::function<double(double)> f_;
		static double function(double x, void* v)
		{
			const std::function<double(double)>& f = *reinterpret_cast<const std::function<double(double)>*>(v);

			return f(x);
		}
	public:
		root_fsolver(const gsl_root_fsolver_type * type)
			: p(gsl_root_fsolver_alloc(type))
		{
			_f.function = function;
		}
		root_fsolver(const root_fsolver&) = delete;
		root_fsolver& operator=(const root_fsolver&) = delete;
		~root_fsolver()
		{
			gsl_root_fsolver_free(p);
		}

		const char* name(void) const
		{
			return gsl_root_fsolver_name(p);
		}
		int set(const std::function<double(double)>& f, double lo, double up)
		{
			f_ = f;

			_f.params = &f_;

			return gsl_root_fsolver_set(p, &_f, lo, up);
		}
		int iterate(void)
		{
			return gsl_root_fsolver_iterate(p);
		}
		double root(void) const
		{
			return gsl_root_fsolver_root(p);
		}
		double x_lower(void) const
		{
			return gsl_root_fsolver_x_lower(p);
		}
		double x_upper(void) const
		{
			return gsl_root_fsolver_x_upper(p);
		}
	};

} // gsl

#ifdef _DEBUG

inline void test_gsl_root_fsolver()
{
	gsl::root_fsolver rs(gsl_root_fsolver_bisection);
	rs.set([](double x) { return x*x - 2; }, 1, 2);
	rs.iterate();
}

#endif // _DEBUG