// xll_njr.h - Normal Jarrow-Rudd model
#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

namespace njr {

// H_{n+1}(x) = x H_n(x) - n H_{n-1}(x)
inline double hermite_recursive(size_t n, double x)
{
	if (n == 0)
		return 1;
	if (n == 1)
		return x;

	return x*hermite_recursive(n-1, x) - (n - 1)*hermite_recursive(n - 2, x);
}
inline double hermite(size_t n, double x)
{
	if (n == 0)
		return 1;
	if (n == 1)
		return x;

	double h0 = 1, h1 = x, hi;
	for (size_t i = 2; i <= n; ++i) {
		hi = x*h1 - (i - 1)*h0; // h2 = x h1 - 1 h0
		h0 = h1;
		h1 = hi;
	}

	return hi;
}
	
// erf(x) = int_0^x exp(-t^2) dt 2/sqrt(pi)
// N(x) = int_-infty^x exp(-t^2/2) dt/sqrt(2pi)
inline double std_normal_cdf(double x)
{
	return (1 + erf(x/M_SQRT2))/2;
}
inline double std_normal_pdf(double x)
{
	static double M_SQRT2PI = sqrt(2*M_PI);

	return exp(-x*x/2)/M_SQRT2PI;
}
// n-th derivative of cdf
// (d/dx)^n exp(-x^2/2) = (-1)^n exp(-x^2/2) H_n(x) where
// H_n(x) = x H_{n-1}(x) - (n - 1) H_{n-2}(x), are the Hermite polynomials
// N^(n)(x) = (d/dx)^{n-1} exp(-x^2/2)/sqrt(2pi) 
//          = (-1)^{n-1} exp(-x^2/2) H_{n-1}/sqrt(2pi)
inline double std_normal_ndf(size_t n, double x)
{
	static double M_SQRT2PI = sqrt(2*M_PI);

	if (n == 0)
		return std_normal_cdf(x);
	if (n == 1)
		return std_normal_pdf(x);

	return (n&1 ? 1 : -1)*hermite(n - 1, x)*exp(-x*x/2)/M_SQRT2PI;
}


} // njr

#ifdef _DEBUG
#include <cassert>
#include <chrono>
#include <random>

inline void test_njr_hermite(size_t N = 10000, size_t O = 10)
{
	std::default_random_engine e;
	std::uniform_real_distribution<> u;

	for (size_t i = 0; i < 0; ++i) {
		for (size_t n = 0; n < N; ++n) {
			double x = 1/u(e) - 1/u(e);
			assert (njr::hermite_recursive(i, x) == njr::hermite(i, x));
		}
	}
}

#endif // _DEBUG