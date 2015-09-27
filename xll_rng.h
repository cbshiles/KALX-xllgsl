// xll_rng.h - Random number generation
// http://www.gnu.org/software/gsl/manual/html_node/Random-Number-Generation.html#Random-Number-Generation
#pragma once
#include <memory> // std::unique_ptr
#include "gsl/gsl_rng.h"

namespace gsl {

	class rng {
		// call gsl_rng_free when out of scope
		std::unique_ptr<::gsl_rng,decltype(&::gsl_rng_free)> r;
	public:
		explicit rng(const gsl_rng_type *type = gsl_rng_mt19937)
			: r{gsl_rng_alloc(type), &::gsl_rng_free}
		{ }
		rng(const rng& r)
			: r{gsl_rng_clone(r.r.get()), &::gsl_rng_free}
		{ }
		rng& operator=(const rng& r_)
		{ 
			if (this != &r_) {
				if (r->type != r_.r->type) {
					r.reset(gsl_rng_clone(r_.r.get()));
				}
				else {
					gsl_rng_memcpy(r.get(), r_.r.get());
				}
			}

			return *this;
		}

		// to interoperate with GSL C functions
		operator const gsl_rng*()
		{
			return r.get();
		}

		// rng properties
		unsigned long max() const
		{
			return gsl_rng_max(r.get());
		}
		unsigned long min() const
		{
			return gsl_rng_min(r.get());
		}
		const char* name() const
		{
			return gsl_rng_name(r.get());
		}
	
		rng& set(unsigned long int s)
		{
			gsl_rng_set(r.get(), s);

			return *this;
		}

		// uniformly distributed in the range [min(), max()]
		unsigned long get() const
		{
			return gsl_rng_get(r.get());
		}
		// uniformly distributed in the range [0,1)
		double uniform() const
		{
			return gsl_rng_uniform(r.get());
		}
		// uniformly distributed in the range (0,1)
		double uniform_pos() const
		{
			return gsl_rng_uniform_pos(r.get());
		}
		// uniformly distributed in the range [0, n)
		unsigned long uniform_int(unsigned long n) const
		{
			return gsl_rng_uniform_int(r.get(), n);
		}
	};

} // gsl

#ifdef _DEBUG
#include <cassert>
#include <vector>

inline void gsl_rng_test()
{
	{
		gsl::rng r;
		auto r0(r); // copy
		r = r0; // assign

		assert (r.max() == r0.max());
		assert (r.min() == r0.min());
		assert (0 == strcmp(r.name(), r0.name()));
		assert (r.uniform() == r0.uniform());
		assert (r.uniform_pos() == r0.uniform_pos());
		assert (r.uniform_int(100) == r0.uniform_int(100));

		unsigned long ul, x;

		ul = 123456789;
		r.set(ul);
		x = r.get();
		r.set(ul);
		assert (x == r.get());

		// s[n] = (x[0] + ... + x[n-1])/n
		// n s[n] - (n - 1) s[n-1] = x[n-1]
		// s[n] = (1 - 1/n) s[n-1] + x[n-1]/n
		//      = s[n-1] + (x[n-1] - s[n-1])/n
		double avg = 0;
		for (int n = 1; n <= 1e6; ++n)
			avg += (r.uniform() - avg)/n;
		assert (fabs(avg - 0.5) < 1e-3);

		avg = 0;
		for (int n = 1; n <= 1e6; ++n)
			avg += (r.uniform_pos() - avg)/n;
		assert (fabs(avg - 0.5) < 1e-3);

		std::vector<unsigned long> hist(10);
		for (int n = 1; n <= 1e6; ++n)
			++hist[r.uniform_int(10)];
		for (int i = 0; i < 10; ++i)
			assert (abs(hist[i] - 1e5) < 5e2);

	}
}

#endif // _DEBUG

