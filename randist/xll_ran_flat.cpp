// xll_ran_flat.cpp - Uniform variates, density, cumulative distribution, and inverse
// http://www.gnu.org/software/gsl/manual/html_node/The-Flat-_0028Uniform_0029-Distribution.html#The Flat Uniform Distribution
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_flat(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_flat"), _T("GSL.RAN.FLAT"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the lower bound of the uniformly distributed random variate."))
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the upper bound of the uniformly distributed random variate."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return a uniform random variate using a random number generator."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_flat(HANDLEX rng, double a, double b)
{
#pragma XLLEXPORT
	doublex x;

	try {

		handle<gsl::rng> r(rng);

		x = gsl_ran_flat(*r, a, b);
	}

	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_ran_flat_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_flat_pdf"), _T("GSL.DIST.FLAT.PDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the lower bound of the uniformly distributed random variate."))
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the upper bound of the uniformly distributed random variate."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return uniform probability density function."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_flat_pdf(double x, double a, double b)
{
#pragma XLLEXPORT

	return gsl_ran_flat_pdf(x, a, b);
}

static AddInX xai_cdf_flat_P(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_flat_P"), _T("GSL.DIST.FLAT.CDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the lower bound of the uniformly distributed random variate."))
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the upper bound of the uniformly distributed random variate."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return uniform cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_flat_P(double x, double a, double b)
{
#pragma XLLEXPORT

	return gsl_cdf_flat_P(x, a, b);
}

static AddInX xai_cdf_flat_Pinv(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_flat_Pinv"), _T("GSL.DIST.FLAT.INV"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the inverse cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the lower bound of the uniformly distributed random variate."))
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the upper bound of the uniformly distributed random variate."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return uniform inverse cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_flat_Pinv(double p, double a, double b)
{
#pragma XLLEXPORT

	return gsl_cdf_flat_Pinv(p, a, b);
}

XLL_TEST_BEGIN(xll_ran_flat)

double eps = 1e-6;

// http://www.wolframalpha.com/input/?i=Table%5BPDF%5BUniformDistribution%5B-2%2C2%5D%2C+x%5D%2C%7Bx%2C+-2%2C+1.9%2C+.1%7D%5D
double pdf[] = {0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25};
// http://www.wolframalpha.com/input/?i=Table%5BCDF%5BUniformDistribution%5B-2%2C2%5D%2C+x%5D%2C%7Bx%2C+-2%2C+1.9%2C+.1%7D%5D
double cdf[] = {0, 0.025, 0.05, 0.075, 0.1, 0.125, 0.15, 0.175, 0.2, 0.225, 0.25, 0.275, 0.3, 0.325, 0.35, 0.375, 0.4, 0.425, 0.45, 0.475, 0.5, 0.525, 0.55, 0.575, 0.6, 0.625, 0.65, 0.675, 0.7, 0.725, 0.75, 0.775, 0.8, 0.825, 0.85, 0.875, 0.9, 0.925, 0.95, 0.975};

for (int i = 0; i < sizeof(pdf) / sizeof(*pdf); ++i) {
	double x = -2 + i*0.1;
	ensure(fabs(xll_ran_flat_pdf(x, -2, 2) - pdf[i]) < eps);
	ensure(fabs(xll_cdf_flat_P(x, -2, 2) - cdf[i]) < eps);
}

// http://www.wolframalpha.com/input/?i=Table%5BInverseCDF%5BUniformDistribution%5B-2%2C2%5D%2C+p%5D%2C%7Bp%2C+.1%2C+.9%2C+.1%7D%5D
double inv[] = {-1.6, -1.2, -0.8, -0.4, 0, 0.4, 0.8, 1.2, 1.6};
for (int i = 0; i < sizeof(inv) / sizeof(*inv); ++i) {
	double p = 0.1 + i*0.1;
	ensure(fabs(xll_cdf_flat_Pinv(p, -2, 2) - inv[i]) < 2 * eps);
}

XLL_TEST_END(xll_ran_flat)