// xll_ran_levy_skew.cpp - Stable variates, density, cumulative distribution, and inverse
// http://www.gnu.org/software/gsl/manual/html_node/The-Levy-skew-alpha_002dStable-Distribution.html#The-Levy-skew-alpha_002dStable-Distribution
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_levy_skew(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_levy_skew"), _T("GSL.RAN.LEVY.SKEW"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("c"), _T("is the scale. Default is 1"), 1.0)
	.Arg(XLL_DOUBLEX, _T("alpha"), _T("is the exponent parameter. Default is 2"), 2.0)
	.Arg(XLL_DOUBLEX, _T("beta"), _T("is the skewness. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Stable random deviates using a random number generator."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_levy_skew(HANDLEX rng, double c, double alpha, double beta)
{
#pragma XLLEXPORT
	doublex x;

	try {
		if (alpha == 0)
			alpha = 2;

		handle<gsl::rng> r(rng);

		x = gsl_ran_levy_skew(*r, c, alpha, beta);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}





// XLL_TEST_BEGIN(xll_ran_levy_skew)
// if alpha=1, values can go very high
// if alpha=2, formula match with the website, and the skewness parameter has no effect
// alpha has to be >0
// XLL_TEST_END(xll_ran_levy_skew)