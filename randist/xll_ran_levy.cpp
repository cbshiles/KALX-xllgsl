// xll_ran_levy.cpp - random variate from the Levy symmetric stable distribution
// http://www.gnu.org/software/gsl/manual/html_node/The-Levy-alpha_002dStable-Distributions.html#The-Levy-alpha_002dStable-Distributions
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_levy(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_levy"), _T("GSL.RAN.LEVY"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("c"), _T("is the scale of the Levy."))
	.Arg(XLL_DOUBLEX, _T("alpha"), _T("is the exponent of the Levy."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return levy random deviates using a random number generator."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_levy(HANDLEX rng, double c,double alpha)
{
#pragma XLLEXPORT
	doublex x;

	try {
		

		handle<gsl::rng> r(rng);

		x = gsl_ran_levy(*r, c, alpha);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}
