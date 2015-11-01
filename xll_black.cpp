// xll_black.cpp - Black forward model
#include "xll_roots.h"
#include "xll_black.h"
//#include "xll_njr.h"
#include "xll/xll.h"

using namespace xll;

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
static AddInX xai_black_put_delta(
	FunctionX(XLL_DOUBLEX, _T("?xll_black_put_delta"), _T("BLACK.PUT.DELTA"))
	.Num(_T("f"), _T("forward"), 100)
	.Num(_T("sigma"), _T("vol"), .2)
	.Num(_T("k"), _T("strike"), 100)
	.Num(_T("t"), _T("expiration"), .25)
	.FunctionHelp(_T("Return Black put delta."))
	.Category(_T("BSM"))
	.Documentation()
	);
double WINAPI xll_black_put_delta(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	doublex v;

	try {
		v = black_put_delta(f, sigma, k, t);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return v;
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

static AddInX xai_corrado_miller_implied_volatility(
	FunctionX(XLL_DOUBLEX, _T("?xll_corrado_miller_implied_volatility"), _T("BLACK.CORRADO.MILLER.IMPLIED.VOLATILITY"))
	.Num(_T("f"), _T("forward"), 100)
	.Num(_T("p"), _T("call"), 3.987775)
	.Num(_T("k"), _T("strike"), 100)
	.Num(_T("t"), _T("expiration"), .25)
);
double WINAPI xll_corrado_miller_implied_volatility(double f, double p, double k, double t)
{
#pragma XLLEXPORT
	doublex sigma;

	try {
		double v = p + f - k;
		sigma = corrado_miller_implied_volatility<double>(f, v, k, t);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

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
static AddInX xai_bms_put_value(
	FunctionX(XLL_DOUBLEX, _T("?xll_bms_put_value"), _T("BMS.PUT.VALUE"))
	.Num(_T("r"), _T("rate"), .01)
	.Num(_T("s"), _T("spot"), 100)
	.Num(_T("sigma"), _T("vol"), .2)
	.Num(_T("k"), _T("strike"), 100)
	.Num(_T("t"), _T("expiration"), .25)
	.FunctionHelp(_T("Return bms put value."))
	.Category(_T("BSM"))
	.Documentation()
	);
double WINAPI xll_bms_put_value(double r, double s, double sigma, double k, double t)
{
#pragma XLLEXPORT
	doublex v;

	try {
		v = bms_put_value(r, s, sigma, k, t);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return v;
}

static AddInX xai_bms_put_delta(
	FunctionX(XLL_DOUBLEX, _T("?xll_bms_put_delta"), _T("BMS.PUT.DELTA"))
	.Num(_T("r"), _T("rate"), .01)
	.Num(_T("s"), _T("spot"), 100)
	.Num(_T("sigma"), _T("vol"), .2)
	.Num(_T("k"), _T("strike"), 100)
	.Num(_T("t"), _T("expiration"), .25)
	.FunctionHelp(_T("Return bms put delta."))
	.Category(_T("BSM"))
	.Documentation()
	);
double WINAPI xll_bms_put_delta(double r, double s, double sigma, double k, double t)
{
#pragma XLLEXPORT
	doublex v;

	try {
		v = bms_put_delta(r, s, sigma, k, t);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return v;
}

#ifdef _DEBUG
#include "xll_deriv.h"
XLL_TEST_BEGIN(xll_black_test)

double eps = std::numeric_limits<double>::epsilon();

ensure (fabs (black_put_value(100,.2,100,.25) - 3.9877611676744920) <= eps);
//!!!test black_put_delta using gsl::deriv::central in xll_deriv.h, e.g., use
auto delta = gsl::deriv::central([](double f) { return black_put_value(f,.2,100,.25); });
// and compare with black_put_delta
auto put_delta = black_put_delta(100, .2,100,0.25);
ensure (fabs(delta(100)- put_delta) < 2e-6);

ensure (fabs (black_vega(100,.2,100,.25) - 19.922195704738204) <= eps);
ensure (fabs (black_put_implied_volatility(100,3.9877611676744920,100,.25) - 0.2) <= eps);

//!!! test bms_put_value

//!!! test bms_put_delta using gsl::deriv::central xll_deriv.h


/*
In graphical analyses not reported here, we found that with option maturities of 3 months or more, 
the improved quadratic formula in Eq. (10) provides near perfect accuracy for stock prices within 
+ 10 percent of a discounted strike price. With shorter maturities, say, 1 month, the range of 
precision is reduced to about + 5 percent of a discounted strike price.
*/
// ensure(...

XLL_TEST_END(xll_black_test)
#endif 