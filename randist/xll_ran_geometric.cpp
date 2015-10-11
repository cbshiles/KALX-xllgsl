//Geometric Distribution

// xll_ran_geometric.cpp - Geometric variates, density, cumulative distribution, and inverse
// http://www.gnu.org/software/gsl/manual/html_node/The-Geometric-Distribution.html#The-Geometric-Distribution
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_geometric(
	FunctionX(XLL_USHORTX, _T("?xll_ran_geometric"), _T("GSL.RAN.GEOMETRIC"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	//.Arg(XLL_DOUBLEX, _T("sigma"), _T("is the standard deviation of the Gaussian. Default is 1"), 1.0)
	.Arg(XLL_DOUBLEX, _T("p"), _T("is the probability of success. Should be within [0,1]"))
	.Category(_T("GSL"))
	//.FunctionHelp(_T("Return Gaussian/normal random deviates using a random number generator."))
	.FunctionHelp(_T("Return a random integer from the geometric distribution."))
	.Documentation(_T(""))
	);
unsigned int WINAPI xll_ran_geometric(HANDLEX rng, double p)
{
#pragma XLLEXPORT
	unsigned int x=0;

	try {

		handle<gsl::rng> r(rng);

		x = gsl_ran_geometric(*r, p);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_ran_geometric_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_geometric_pdf"), _T("GSL.DIST.GEOMETRIC.PDF"))
	.Arg(XLL_USHORTX, _T("k"), _T("is the number of trials."))
	.Arg(XLL_DOUBLEX, _T("p"), _T("is the probability of success. Should be within [0,1]."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Geometric probability density function."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_geometric_pdf(unsigned int k, double p)
{
#pragma XLLEXPORT

	return gsl_ran_geometric_pdf(k, p);
}

static AddInX xai_cdf_geometric_P(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_geometric_P"), _T("GSL.DIST.GEOMETRIC.CDF"))
	//.Arg(XLL_WORDX, _T("k"), _T("is the value at which to calculate the cumulative distribution function."))
	//.Arg(XLL_DOUBLEX, _T("P"), _T("is the standard deviation of the Gaussian. Default is 1"), 1.0)
	.Arg(XLL_USHORTX, _T("k"), _T("is the number of trials."))
	.Arg(XLL_DOUBLEX, _T("p"), _T("is the probability of success. Should be within [0,1]."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Geometric cumulative distribution function."))
	.Documentation(_T(""))
	);

double WINAPI xll_cdf_geometric_P(unsigned int k, double p)
{
#pragma XLLEXPORT

	return gsl_cdf_geometric_P(k, p);
}

XLL_TEST_BEGIN(xll_ran_geometric)

double eps = 1e-6;

//Geometric Distribution Test Result p = 0.5, k = 10
double pdf[] = { 0.5, 0.25, 0.125, 0.0625, 0.03125, 0.015625, 0.0078125, 0.00390625, 0.00195313, 0.000976563 };
double cdf[] = { 0.5, 0.75, 0.875, 0.9375, 0.96875, 0.984375, 0.992188, 0.996094, 0.998047, 0.999023 };
for (int i = 0; i < sizeof(pdf) / sizeof(*pdf); ++i) {
	unsigned int x = i+1;
	ensure(fabs(xll_ran_geometric_pdf(x, 0.5) - pdf[i]) < eps);
	ensure(fabs(xll_cdf_geometric_P(x, 0.5) - cdf[i]) < eps);

}

XLL_TEST_END(xll_ran_geometric)