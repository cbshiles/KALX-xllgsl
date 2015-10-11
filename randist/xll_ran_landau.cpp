// xll_ran_landau.cpp -Landau distribution variates and density
// http://www.gnu.org/software/gsl/manual/html_node/The-Landau-Distribution.html#The-Landau-Distribution
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_landau(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_landau"), _T("GSL.RAN.LANDAU"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return random deviates from Landau distribution using a random number generator."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_landau(HANDLEX rng)
{
#pragma XLLEXPORT
	doublex x;

	try {
		handle<gsl::rng> r(rng);

		x = gsl_ran_landau(*r);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_ran_landau_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_landau_pdf"), _T("GSL.DIST.LANDAU.PDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the density function."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Landau distribution probability density function."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_landau_pdf(double x)
{
#pragma XLLEXPORT

	return gsl_ran_landau_pdf(x);
}

// cdf and inv are not available for Landau distribution in GSL.

XLL_TEST_BEGIN(xll_ran_landau)

double eps = 1e-6;

// Different definition found in GSL and Wolfram documents. Use GSL outputs as an example for the test.
double pdf[] = { 0.043985478, 0.054259062, 0.065311333, 0.076891507, 0.088728939, 0.100550752, 0.112097341, 0.123134699, 0.133463069, 0.142921965, 0.151391911, 0.158793517, 0.165084522, 0.170255516, 0.174324893, 0.177333547, 0.179339682, 0.180413983, 0.180635324, 0.180087096, 0.178854161, 0.177020436, 0.174667033, 0.171870904, 0.168703915, 0.165232275, 0.16151625, 0.157610102, 0.153562202, 0.149415257, 0.145206637, 0.140968738, 0.13672939, 0.132512269, 0.128337308, 0.124221094, 0.120177245, 0.116216764, 0.112348366, 0.108578774, 0.104912989 };

for (int i = 0; i < sizeof(pdf) / sizeof(*pdf); ++i) {
	double x = -2 + i*0.1;
	ensure(fabs(xll_ran_landau_pdf(x) - pdf[i]) < eps);
}

XLL_TEST_END(xll_ran_landau)
