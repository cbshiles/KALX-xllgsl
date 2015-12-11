// xll_black.h - Black formula
#pragma once
#ifndef ensure
#include <cassert>
#define ensure assert
#endif
#define _USE_MATH_DEFINES
#include <cmath>

#ifndef M_SQRT2
#define M_SQRT2 1.41421356237309504880
#endif
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// erf(x) = int_0^x exp(-t^2) dt 2/sqrt(pi)
// N(x) = int_-infty^x exp(-t^2/2) dt/sqrt(2pi)
inline double std_normal_cdf(double x)
{
	return (1 + erf(x/M_SQRT2))/2;
}

/*****************************************************************************
The Fischer Black pricing formula gives the forward value of an option.
The forward at time  t  be  F = f exp(-sigma^2 t/2 + sigma B_t).
Using the fact Eexp(N)g(M) = Eexp(N) Eg(M + Cov(M, N)) for N, M jointly normal
v = E max{k - F, 0} = kP(F <= k) - E F1(F<=k)
= k P(F <= k) - f P(F <= k exp(-sigma^2 t))
since E F = f. Note:
F <= k if and only if B_t/sqrt(t) <= (log k/f + sigma^2 t/2)/sigma sqrt(t) 
*****************************************************************************/

template<class F, class S, class K, class T>
inline auto black_put_value(F f, S sigma, K k, T t) -> decltype(f+sigma+k+t)
{
	ensure (f >= 0);
	ensure (sigma >= 0);
	ensure (k >= 0);
	ensure (t >= 0);

	// edge cases
	if (f == 0)
		return k;
	if (sigma == 0 || t == 0)
		return (std::max)(k - f, K(0)-F(0));
	if (k == 0)
		return 0;

	auto srt = sigma*sqrt(t);
	auto d = (log(k/f) + srt*srt/2)/srt;
	auto d_ = d - srt;

	return k*std_normal_cdf(d) - f*std_normal_cdf(d_);
}

template<class F, class S, class K, class T>
inline auto black_put_delta(F f, S sigma, K k, T t) -> decltype(f+sigma+k+t)
{
	ensure (f >= 0);
	ensure (sigma >= 0);
	ensure (k >= 0);
	ensure (t >= 0);

	// edge cases
	if (f == 0)
		return k;
	if (sigma == 0 || t == 0)
		return (std::max)(k - f, K(0)-F(0));
	if (k == 0)
		return 0;

	auto srt = sigma*sqrt(t);
	auto d = (log(k/f) + srt*srt/2)/srt;
	auto d_ = d - srt;

	return -std_normal_cdf(d_);
}

// vega is the same for put or call
template<class F, class S, class K, class T>
inline double black_vega(F f, S sigma, K k, T t)
{
	ensure (f >= 0);
	ensure (sigma >= 0);
	ensure (k >= 0);
	ensure (t > 0);

	static double sqrt2pi = sqrt(2*M_PI);
	auto srt = sigma*sqrt(t);
	auto d = (log(f/k) + srt*srt/2)/srt;

	return f*sqrt(t)*exp(-d*d/2)/sqrt2pi;
}

// Implement Corrado-Miller formula (10) from CorMil1993.pdf
// f - forward, v - call value, k - strike, t - expiration
// sigma0 is returned when CM formula fails
template<class X>
inline X corrado_miller_implied_volatility(const X& f, const X& v, const X& k, const X& t, X sigma0 = 0.2)
{
	ensure (f > 0);
	ensure (v > 0);
	ensure (v > f - k);
	ensure (v <= f);
	ensure (k > 0);
	ensure (t > 0);

	static X M_SQRT_2PI = sqrt(2*M_PI);

	X s = v - (f - k)/2;
	s *= s;
	s -= (f - k)*(f - k)/M_PI;	
	if (s < 0)
		return sigma0;
	s = sqrt(s);
	s += v - (f - k)/2;
	s *= M_SQRT_2PI/((f + k)*sqrt(t));

	return s;
}

// Return the volatility that gives put value p.
inline double black_put_implied_volatility(double f, double p, double k, double t,
	double eps = 1e-8, double sigma = 0.2, size_t n = 100)
{
	ensure (f >= 0);
	ensure (p >= k - f && p >= 0);
	ensure (k > 0);
	ensure (t > 0);

//	double v = p + f - k;
//	double sigma = corrado_miller_implied_volatility(f, v, k, t, 0.2);
	ensure (sigma > 0);
	double s = sigma;
	do {
		std::swap(s, sigma);
		s = sigma - (-p + black_put_value(f, sigma, k, t))/black_vega(f, sigma, k, t);
		if (s < 0) {
			s = sigma/2;
		}
	} while (n-- && fabs(s - sigma) > eps);

	return s;
}
/*****************************************************************************
The Black-Scholes/Merton pricing formula gives the present value of an option.
The put value is exp(-rt)Emax{k - S, 0} 
where S = s exp((r - sigma^/2)t + sigma B_t = exp(rt) F.
*****************************************************************************/
inline double bms_put_value(double r, double s, double sigma, double k, double t)
{
	auto R = exp(r*t);
	auto f = s*R;

	return black_put_value(f, sigma, k, t)/R;
}
// (d/ds) E(k - S)^+/R = (d/df)E(k -R)^+/R df/ds = dp R/R = dp
template<class X>
inline X bms_put_delta(X r, X s, X sigma, X k, X t)
{
	return black_put_delta(s*exp(r*t), sigma, k, t);
}

#undef ensure