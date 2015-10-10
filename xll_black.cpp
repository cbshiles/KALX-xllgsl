// xll_black.cpp - Black forward model
#define _USE_MATH_DEFINES
#include <cmath>
#include "xll_roots.h"
#include "xll/xll.h"

using namespace xll;

// erf(x) = int_0^x exp(-t^2) dt 2/sqrt(pi)
// N(x) = int_-infty^x exp(-t^2/2) dt/sqrt(2pi)
inline double std_normal_cdf(double x)
{
	return (1 + erf(x/M_SQRT2))/2;
}
#define N std_normal_cdf

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
inline double black_put_value(F f, S sigma, K k, T t)
{
	ensure (f >= 0);
	ensure (sigma >= 0);
	ensure (k >= 0);
	ensure (t >= 0);

	if (f == 0)
		return k;
	if (sigma == 0 || t == 0)
		return (std::max)(k - f, K(0) - F(0));
	if (k == 0)
		return 0;

	auto srt = sigma*sqrt(t);
	auto d = (log(k/f) + srt*srt/2)/srt;
	auto d_ = d - srt;

	return k*N(d) - f*N(d_);
}
static AddInX xai_black_put_value(
	FunctionX(XLL_DOUBLEX, _T("?xll_black_put_value"), _T("BLACK.PUT.VALUE"))
	.Num(_T("f"), _T("forward"), 100)
	.Num(_T("sigma"), _T("vol"), .2)
	.Num(_T("k"), _T("strike"), 100)
	.Num(_T("t"), _T("expiration"), .25)
	.FunctionHelp(_T("Return Black put value."))
	.Category(_T("BSM"))
	.Documentation()
);
double WINAPI xll_black_put_value(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	doublex v;

	try {
		v = black_put_value(f, sigma, k, t);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return v;
}

/*****************************************************************************
The Black-Scholes/Merton pricing formula gives the present value of an option.
The put value is exp(-rt)Emax{k - S, 0} where S = Fexp(-rt).
*****************************************************************************/
//!!! implement this using black_put_value
template<class F, class S, class K, class T>
inline double bms_put_value(F f, S sigma, K k, T t)
{
	return 0;
}
//!!! and this
// static AddInX xai_bms_put_value(...

//!!! implement this
template<class F, class S, class K, class T>
inline double black_put_delta(F f, S sigma, K k, T t)
{
	return 0;
}
//!!! and this
// static AddInX xai_black_put_delta(...

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
static AddInX xai_black_vega(
	FunctionX(XLL_DOUBLEX, _T("?xll_black_vega"), _T("BLACK.VEGA"))
	.Num(_T("f"), _T("forward"), 100)
	.Num(_T("sigma"), _T("vol"), .2)
	.Num(_T("k"), _T("strike"), 100)
	.Num(_T("t"), _T("expiration"), .25)
	.Category(_T("BSM"))
	.FunctionHelp(_T("Return the Black vega for a put or call."))
);
double WINAPI xll_black_vega(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	doublex v;

	try {
		v = black_vega(f, sigma, k, t);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return v;
}

//!!!Implement Corrado-Miller formula (10) from http://...
// Use r = b = 0.
inline double corrado_miller(double f, double k, double t)
{
	return 0;
}

// Return the volatility that gives put value p.
inline double black_put_implied_volatility(double f, double p, double k, double t)
{
	ensure (f >= 0);
	ensure (p >= k - f && p >= 0);
	ensure (k > 0);
	ensure (t > 0);

	gsl::root::fdfsolver s(gsl_root_fdfsolver_newton);
	
	auto F = [f,p,k,t](double sigma) { 
		return -p + black_put_value(f, sigma, k, t); 
	};
	auto dF = [f,k,t](double sigma) { 
		return black_vega(f, sigma, k, t); 
	};
	//!!!Use corrado_miller for this.
	double sigma = 0.3;
	s.set(F, dF, sigma);

	double epsrel = 1e-6;
	sigma = s.solve(gsl::root::test_delta(0, epsrel));

	return sigma;
}
static AddInX xai_black_put_implied_volatility(
	FunctionX(XLL_DOUBLEX, _T("?xll_black_put_implied_volatility"), _T("BLACK.PUT.IMPLIED.VOLATILTIY"))
	.Num(_T("f"), _T("forward"), 100)
	.Num(_T("p"), _T("price"), 3.987775)
	.Num(_T("k"), _T("strike"), 100)
	.Num(_T("t"), _T("expiration"), .25)
	);
double WINAPI xll_black_put_implied_volatility(double f, double p, double k, double t)
{
#pragma XLLEXPORT
	doublex v;

	try {
		v = black_put_implied_volatility(f, p, k, t);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return v;
}

#ifdef _DEBUG
XLL_TEST_BEGIN(xll_black_test)

double eps = std::numeric_limits<double>::epsilon();

ensure (fabs (black_put_value(100,.2,100,.25) - 3.9877611676744920) <= eps);
ensure (fabs (black_vega(100,.2,100,.25) - 19.922195704738204) <= eps);
ensure (fabs (black_put_implied_volatility(100,3.9877611676744920,100,.25) - 0.2) <= eps);

//!!!  add tests that verify Corrado and Miller's claim:
/*
In graphical analyses not reported here, we found that with option maturities of 3 months or more, 
the improved quadratic formula in Eq. (10) provides near perfect accuracy for stock prices within 
+ 10 percent of a discounted strike price. With shorter maturities, say, 1 month, the range of 
precision is reduced to about + 5 percent of a discounted strike price.
*/
// ensure(...

XLL_TEST_END(xll_black_test)
#endif 