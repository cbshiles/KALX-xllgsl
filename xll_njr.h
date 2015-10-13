// xll_njr.h - Normal Jarrow-Rudd model
#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <iterator>

namespace njr {

// H_{n+1}(x) = x H_n(x) - n H_{n-1}(x)
inline double Hermite_recursive(size_t n, double x)
{
	if (n == 0)
		return 1;
	if (n == 1)
		return x;

	return x*Hermite_recursive(n-1, x) - (n - 1)*Hermite_recursive(n - 2, x);
}

inline double Hermite_loop(size_t n, double x)
{
	if (n == 0)
		return 1;
	if (n == 1)
		return x;

	double h0 = 1, h1 = x, hi = 0;
	for (size_t i = 2; i <= n; ++i) {
		hi = x*h1 - (i - 1)*h0; // h2 = x h1 - 1 h0
		h0 = h1;
		h1 = hi;
	}

	return hi;
}

template<class X = double>
class Hermite : public std::iterator<std::input_iterator_tag, X> {
	size_t n;
	X x, h, h_;
public:
	Hermite(const X& x = 0)
		: n(0), x(x), h(1), h_(0)
	{ }
	X operator*() const
	{
		return h;
	}
	Hermite& operator++()
	{
		X _h = x*h - n*h_;
		h_ = h;
		h = _h;
		++n;

		return *this;
	}
	Hermite operator++(int)
	{
		auto _h(*this);

		operator++();

		return _h;
	}
	bool operator==(const Hermite& H) const
	{
		return n == H.n && x == H.x && h == H.h && h_ == H.h_;
	}
	bool operator!=(const Hermite& H) const
	{
		return !operator==(H);
	}
};

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

	return (n&1 ? 1 : -1)*Hermite_loop(n - 1, x)*exp(-x*x/2)/M_SQRT2PI;
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

	{
		for (size_t i = 0; i < O; ++i) {
			for (size_t n = 0; n < N; ++n) {
				double x = 1/u(e) - 1/u(e);
				assert (njr::Hermite_recursive(i, x) == njr::Hermite_loop(i, x));
			}
		}
	}
	{
		njr::Hermite<> H;
		auto H1(H);
		assert (H1 == H);
		assert (!(H1 != H));
		H = H1;
		assert (H1 == H);
		assert (!(H1 != H));

		for (size_t n = 0; n < N; ++n) {
			double x = 1/u(e) - 1/u(e);
			auto H_ = njr::Hermite<>(x);
			for (size_t i = 0; i < O; ++i) {
				assert (*H_++ == njr::Hermite_loop(i, x));
			}
		}
	}
}

#endif // _DEBUG