// xll_vswap.h - variance swap pricing
#pragma once
#include <algorithm>
#include <numeric>

namespace gsl {

	// Given (x_i, y_i), 0 <= i < n, find 
	// the number of puts/calls required to replicate the piecewise
	// linear and continuous function determined by these points.
	// It is assumed all pointers are to pre-allocated memory of
	// size n*sizeof(X). Leave the values z[0] and z[n-1] unchanged
	// on output, the value of z[i] should be the number of puts/calls
	// to be bought at strike x[i].
	template<class X>
	inline void pwfit(size_t n, const X* x, const X* y, X* z)
	{
		// first derivative
		for (size_t i = 1; i < n; ++i )
			z[i] = (y[i] - y[i-1])/(x[i] - x[i-1]);
		// second derivative
		std::adjacent_difference(z + 1, z + n, z);
	}

	// If p is the array of put/call values, return the cost of
	// setting up the put/call position. Do not use p[0] or p[n-1].
	template<class X>
	inline X cost(size_t n, const X* x, const X* y, const X* p)
	{
		//!!! implement sum_i=1^i=n-2 z[i]*p[i]
		std::vector<X> z(n);
		pwfit(n, x, y, &z[0]);

		X c = 0;
		for (size_t i = 1; i < n - 1; ++i)
			c += z[i]*p[i];

		return c;
	}

	// The cost of setting up a piecewise linear continuous approximation
	// to the payoff function, f, can be computed from the formula
	// f_(x) = f(z) + f'(z)(x - z) 
	//        + sum_{k_i < z} f''(k_i) (k_i - x)^+
	//        + sum_{k_j > z} f''(k_j) (x - k_j)^+
	// The present value of the payoff is
	// D Ef_(X) = D f(z) + D f'(z) (phi - z) + sum f''(k_i) p_i + sum f''(k_j) c_j,
	// where D is the discount, phi is the futures quote, and p_i, c_j are put
	// and call prices at the corresponding strikes.
	// Use payoff function f(x) = -2 log(x/x0) + 2(x - x0)/z to compute the
	// cost of setting up the static hedge for a variance swap.
	template<class X>
	inline X vswap(const X& D, const X& x0, const X& phi, const X& z,
		size_t nput, const X* kput, const  X* put, // put strikes and prices
		size_t ncall, const X* kcall, const X* call) // call strikes and prices
	{
		// assume kput is increasing and find largest n with kput[n] < phi
		// lower_bound, upper_bound
		size_t n;
		for (n = 0; n < nput; ++n)
			if (kput[n] >= phi)
				break;
		
		std::vector<X> f(n);
		for (size_t i = 0; i < n; ++i)
			f[i] = -2*log(kput[i]/x0) + 2*(kput[i] - x0)/z;

		X put_cost = cost(n, kput, &f[0], put); // use the cost function above

		// assume kcall is increasing and find smallest n with kcall[n] > z
		for (n = 0; n < ncall; ++n)
			if (kcall[n] > phi)
				break;

		f.resize(ncall - n);
		for (size_t i = n; i < kcall[i]; ++i)
			f[i-n] = -2*log(kcall[i]/x0) + 2*(kcall[i] - x0)/z;

		X call_cost = cost(ncall - n, kcall + n, &f[0], call + n); // ditto

		return D*(-2*log(z/x0) + 2*(z - x0)/z + 0) + put_cost + call_cost;
	}

} // namespace gsl
