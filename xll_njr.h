// xll_njr.h - Normal Jarrow-Rudd model
#pragma once
#define _USE_MATH_DEFINES
#include <cassert>
#ifndef ensure
#define ensure(x) assert(x)
#endif
#include <cmath>
#include <vector>

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
inline double std_normal_ddf(size_t n, double x)
{
	static double M_SQRT2PI = sqrt(2*M_PI);

	if (n == 0)
		return std_normal_cdf(x);
	if (n == 1)
		return std_normal_pdf(x);

	return (n&1 ? 1 : -1)*Hermite_loop(n - 1, x)*exp(-x*x/2)/M_SQRT2PI;
}

// Bell polynomials
// B_{n+1}(x_1,...,x_{n+1}) = sum_k=0^n C(n,k) B_{n-k)(x_1,...,x_{n-k}) x_{k+1}
// B_n(x_0,...,x{n-1}) = sum_k=0^{n-1} C(n-1,k) B_{n-1-k}(x_0,...,x_{n-2-k}) x_k
inline double Bell_(size_t n, const double* B, size_t m, const double* x)
{
	ensure (n > 0);
	ensure (m > 0);

	double Cnk = 1;
	double Bn = Cnk*B[n-1]*x[0];
	for (size_t k = 1; k < n && k < m; ++k) {
		Cnk *= (n - k);
		Cnk /= k;
		Bn += Cnk*B[n - 1 - k]*x[k];
	}

	return Bn;
}
// fill B[0], ..., B[n-1] to preallocated memory
inline void Bell(size_t m, const double* x, size_t n, double* B)
{
	ensure (n > 0);
	
	B[0] = 1;
	for (size_t k = 1; k < n; ++k) {
		B[k] = Bell_(k, B, m, x);
	}
}


// Reduced Bell polynomials b_n = B_n/n!
// n! b_n = sum_{k=0}^{n-1} C(n-1,k) (n-1-k)! b_{n-1-k} x_k
// C(n-1,k)(n-1-k)!/n! = (n-1)!/k!n! = 1/n k!
inline double bell_(size_t n, const double* b, size_t m, const double* x)
{
	ensure (n > 0);
	ensure (m > 0);

	double k_ = 1; // 1/k!
	double bn = k_*b[n-1]*x[0];
	for (size_t k = 1; k < n && k < m; ++k) {
		k_ /= k;
		bn += k_*b[n - 1 - k]*x[k];
	}

	return bn/n;
}
// fill b[0], ..., b[n-1] to preallocated memory
inline void bell(size_t m, const double* x, size_t n, double* b)
{
	ensure (n > 0);

	b[0] = 1;
	for (size_t k = 1; k < n; ++k) {
		b[k] = bell_(k, b, m, x);
	}

} 

// Esscher transformed cumulants.
// kappa*_i = sum_{j=0}^i kappa_{i+j} s^j/j!
inline void kappa_(double s, size_t n, const double* k, size_t n_, double* k_)
{
	for (size_t i = 0; i < n && i < n_; ++i) {
		k_[i] = k[i];
		double sj = s; // s^j
		for (size_t j = 1; i + j < n; ++j) {
			k_[i] += k[i + j]*sj/j;
			sj *= s;
		}
	}
	for (size_t i = n; i < n_; ++i)
		k_[i] = 0;
}

// P(X <= x) where kappa are perturbations from normal cumulants
// G(x) = sum_{n>=0} (-1)^n B_n(k[0],...,k[n-1]) F^(n)(x)/n!
inline double cdf(double x, size_t n, const double* kappa)
{
	double G = std_normal_cdf(x);
	std::vector<double> b{1}; // b_0 = 1
	
	b.reserve(30);
	for (size_t i = 1; i < 30; ++i) {
		double bi = bell_(i, b.data(), n, kappa);
		G += (i&1 ? -1 : 1) * bi*std_normal_ddf(i, x);
		b.push_back(bi);
	}

	return G;
}

// F = f exp(-kappa(s) + s X)
// p = E(k - F)^+ = k P(X < z) = f P^*(X < z)
// z = (log(k/f) + kappa(s))/s <=> F = k
template<class X = double>
inline X put_value(X f, X sigma, X k, X t, size_t n = 0, X *kappa = nullptr)
{
	ensure (f > 0);
	ensure (sigma > 0);
	ensure (k > 0);
	ensure (t > 0);

	X s = sigma*sqrt(t);
	X kappa_s = s*s/2; // standard normal kappa(s)
	X si = s;
	for (size_t i = 1; i <= n; ++i)
	{
		kappa_s += kappa[i]*si/i;
		si *= s;
	}

	X z = (log(k/f) + kappa_s)/s;
	X P = cdf(z, n, kappa);

	std::vector<X> kappa_(kappa, kappa + n);
	kappa_[1] += 1; // std normal
	kappa_.resize(2*n);
	njr::kappa_(s, n, &kappa_[0], 2*n, &kappa_[0]);
	kappa_[1] -= 1; 

	X P_ = cdf(z, 2*n, &kappa_[0]);

	return k*P - f*P_;
}

}// njr

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

inline void test_njr_bell()
{
	std::default_random_engine e;
	std::uniform_real_distribution<> u;

	{
		std::vector<double> B(6), x = {1,1,1,1,1,1};
		njr::Bell(x.size(), x.data(), B.size(), &B[0]);
		// http://www.wolframalpha.com/input/?i=Table%5BBellB%5Bn%5D%2C+%7Bn%2C0%2C5%7D%5D
		double BellB[] = {1, 1, 2, 5, 15, 52};
		for (size_t i = 0; i < sizeof(BellB)/sizeof(*BellB); ++i) {
			ensure (B[i] == BellB[i]);
		}
	}

	{
		size_t n = 4;
		std::vector<double> x(n);
		for (size_t i = 0; i < n; ++i) {
			x[i] = 1/u(e) - 1/u(e);
		}

		size_t m = 4;
		std::vector<double> B(m);
		njr::Bell(x.size(), x.data(), B.size(), &B[0]);
		std::vector<double> b(m);
		njr::bell(x.size(), x.data(), b.size(), &b[0]);
		// test B_0 = 1 and b_0 = B_0/0!
		ensure (B[0] == 1);
		ensure (b[0] == B[0]/1);
		// test B_1(x1) = x1 and b_1 = B_1/1!
		ensure (B[1] == x[0]);	
		ensure (b[0] == B[0]/1);
		//!!! test B_2(x1,x2) = x1*x1 + x2 and b_2 = B_2/2!
		ensure (B[2] = x[0]*x[0] + x[1]);
		ensure (b[2] = (x[0]*x[0] + x[1])/2);
		//!!! test B_3(x1,x2,x3) = ??? and b_3 = B_3/3!
		// B_3 = 1B_2 x1 + 2B_1 x2 + B_0 x3
		//     = x1^3 + x1 x2 + 2x1 x2 + x3
		//     = x1^3 + 3 x1 x2 + x3
	}

}

#endif // _DEBUG