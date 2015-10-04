// xll_black.cpp - Black forward model
#define _USE_MATH_DEFINES
#include <cmath>
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

inline double black_put_value(double f, double sigma, double k, double t)
{
	ensure (f >= 0);
	ensure (sigma >= 0);
	ensure (k >= 0);
	ensure (t > 0);

	if (sigma == 0)
		return k - f >= 0 ? k - f : 0;

	double srt = sigma*sqrt(t);
	double d = (log(k/f) + srt*srt/2)/srt;
	double d_ = d - srt;

	return k*N(d) - f*N(d_);
}
static AddInX xai_black_put_value(
	FunctionX(XLL_DOUBLEX, _T("?xll_black_put_value"), _T("BLACK.PUT.VALUE"))
	.Num(_T("f"), _T("forward"), 100)
	.Num(_T("sigma"), _T("vol"), .2)
	.Num(_T("k"), _T("strike"), 100)
	.Num(_T("t"), _T("expiration"), .25)
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

// vega is the same for put or call
inline double black_vega(double f, double sigma, double k, double t)
{
	ensure (f >= 0);
	ensure (sigma >= 0);
	ensure (k >= 0);
	ensure (t > 0);

	static double sqrt2pi = sqrt(2*M_PI);
	double srt = sigma*sqrt(t);
	double d = (log(f/k) + srt*srt/2)/srt;

	return f*sqrt(t)*exp(-d*d/2)/sqrt2pi;
}
static AddInX xai_black_vega(
	FunctionX(XLL_DOUBLEX, _T("?xll_black_vega"), _T("BLACK.VEGA"))
	.Num(_T("f"), _T("forward"), 100)
	.Num(_T("sigma"), _T("vol"), .2)
	.Num(_T("k"), _T("strike"), 100)
	.Num(_T("t"), _T("expiration"), .25)
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

//!!! implement the following using gsl::fdfsolver
inline double black_put_implied_volatility(double f, double p, double k, double t)
{
	ensure (f >= 0);
	ensure (p >= k - f);
	ensure (k > 0);
	ensure (t > 0)
	
	return 0;
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

//!!! add tests for implied volatility

XLL_TEST_END(xll_black_test)
#endif 