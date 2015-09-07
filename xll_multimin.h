// xll_multimin.h - Wrappers for gsl_multimin.h
// http://www.gnu.org/software/gsl/manual/html_node/Multidimensional-Minimization.html#Multidimensional-Minimization
#pragma once
#include <functional>
#include <stdexcept>
#include <vector>
#include "gsl/gsl_multimin.h"

namespace gsl {

	gsl_vector make_vector(size_t n, const double* x)
	{
		gsl_vector v;

		v.size = n;
		v.data = const_cast<double*>(x);
		v.stride = 1;
		v.owner = false; // so GSL won't mess with the memory, hopefully
		v.block = 0;

		return v;
	}

	namespace multimin {

		// f: T^n -> T
		template<class T>
		using function = std::function<T(size_t n, const T* x)>;

		class fminimizer {
			gsl_multimin_fminimizer* s;
			function<double> F;
			gsl_multimin_function F_;
			gsl_vector x_, dx_;
			static double static_function(const gsl_vector* v, void* params)
			{
				const function<double>& f = *static_cast<function<double>*>(params);

				if (v->stride != 1)
					throw std::runtime_error(__FILE__ ": " __FUNCTION__ ": gsl_vector must have stride 1");

				return f(v->size, v->data);
			}
		public:
			fminimizer(const gsl_multimin_fminimizer_type* type, size_t n)
				: s(gsl_multimin_fminimizer_alloc(type, n))
			{ }
			fminimizer(const fminimizer&) = delete;
			fminimizer& operator=(const fminimizer&) = delete;
			~fminimizer()
			{
				gsl_multimin_fminimizer_free(s);
			}

			// to interface with gsl_multimin_* functions
			gsl_multimin_fminimizer* get()
			{
				return s;
			}
			gsl_multimin_fminimizer* operator&()
			{
				return s;
			}

			// caller responsible for x, dx memory
			int set(const function<double>& f, size_t n, const double* x, const double* dx)
			{
				F = f;
				F_.n = n;
				F_.params = &F;
				F_.f = static_function;

				x_ = make_vector(n, x);
				dx_ = make_vector(n, dx);

				return gsl_multimin_fminimizer_set(s, &F_, &x_, &dx_);
			}

			int iterate()
			{
				return gsl_multimin_fminimizer_iterate(s);
			}

			// current minumum
			double minumum() const
			{
				return gsl_multimin_fminimizer_minimum(s);
			}
			// average distance from the geometrical center of the simplex to all its vertices
			double radius() const
			{
				return gsl_multimin_fminimizer_size(s);
			}
			size_t size() const
			{
				return gsl_multimin_fminimizer_x(s)->size;
			}
			// current best guess
			const double* x() const
			{
				return gsl_multimin_fminimizer_x(s)->data;
			}

		};

		class fdfminimizer {
			gsl_multimin_fdfminimizer* s;
		public:
			fdfminimizer(const gsl_multimin_fdfminimizer_type* type, size_t n)
				: s(gsl_multimin_fdfminimizer_alloc(type, n))
			{ }
			fdfminimizer(const fdfminimizer&) = delete;
			fdfminimizer& operator=(const fdfminimizer&) = delete;
			~fdfminimizer()
			{
				gsl_multimin_fdfminimizer_free(s);
			}
		};

	} // multimin

} // gsl

#ifdef _DEBUG
#include <cassert>

inline void test_gsl_multimin_fminimizer()
{
	{
		gsl::multimin::fminimizer s(gsl_multimin_fminimizer_nmsimplex, 2);

		std::vector<double> a = {1,2,3}, x = {0,0}, dx = {.1,.1};
		s.set([&a](size_t n, const double* x) {
			assert (n == 2);

			return a[0] + (x[0] - a[1])*(x[0] - a[1]) +  (x[1] - a[2])*(x[1] - a[2]);
		}, x.size(), &x[0], &dx[0]);

		double eps = 1e-4;
		int iter = 0;
		while (s.iterate() == GSL_SUCCESS && s.radius() > eps) {
			++iter;
		}
		assert (fabs(s.x()[0] - a[1]) < eps);
		assert (fabs(s.x()[1] - a[2]) < eps);
	}
	{
		gsl::multimin::fminimizer s(gsl_multimin_fminimizer_nmsimplex2, 2);

		std::vector<double> a = {1,2,3}, x = {0,0}, dx = {.1,.1};
		s.set([&a](size_t n, const double* x) {
			assert (n == 2);

			return a[0] + (x[0] - a[1])*(x[0] - a[1]) +  (x[1] - a[2])*(x[1] - a[2]);
		}, x.size(), &x[0], &dx[0]);

		double eps = 1e-4;
		int iter = 0;
		while (s.iterate() == GSL_SUCCESS && s.radius() > eps) {
			++iter;
		}
		assert (fabs(s.x()[0] - a[1]) < eps);
		assert (fabs(s.x()[1] - a[2]) < eps);
	}
}

#endif // _DEBUG