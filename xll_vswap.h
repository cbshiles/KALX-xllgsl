// xll_vswap.h - variance swap pricing
#pragma once

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
		//!!! implement
	}

	// If p is the array of put/call values, return the cost of
	// setting up the put/call position. Do not use p[0] or p[n-1].
	template<class X>
	inline X cost(size_t n, const X* x, const X* y, const X* p)
	{
		//!!! implement sum_i=1^i=n-2 z[i]*p[i]
		return 0;
	}

	// The cost of setting up a piecewise linear continuous approximation
	// to the payoff function, f, can be computed from the formula
	// f_(x) = f(z) + f'(z)(x - z) 
	//        + sum_{k_i < z} f''(k_i) (k_i - x)^+
	//        + sum_{k_j > z} f''(k_j) (x - k_j)^+
	// The present value of the payoff is
	// D Ef_(X) = D f(z) + D f'(z) (phi - z) + sum f''(k_i) p_i + sum f''(k_j) c_j,
	// where D is the discount, phi is the furtures quote, and p_i, c_j are put
	// and call prices at the corresponding strikes.
	// Use payoff function f(x) = -2 log(x/x0) + 2(x - x0)/z to compute the
	// cost of setting up the static hedge for a variance swap.
	template<class X>
	inline X cost(const X& D, const X& x0, const X& phi, const X& z,
		size_t nput, const X* kput, const  X* put, // put strikes and prices
		size_t ncall, const X* kcall, const X* call) // call strikes and prices
	{
		// assume kput is increasing and find largest n with kput[n] < z
		X put_cost = 0; // use the cost function above

		// assume kcall is increasing and find smallest n with kcall[n] > z
		X call_cost = 0; // ditto

		return 0; // cash + forward + put cost + call cost
	}

} // namespace gsl