// xll_ran_gumbel1.cpp - Type-1 Gumbel variates, density, cumulative distribution, and inverse
// http://www.gnu.org/software/gsl/manual/html_node/The-Type_002d1-Gumbel-Distribution.html#The-Type_002d1-Gumbel-Distribution
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_gumbel1(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_gumbel1"), _T("GSL.RAN.GUMBEL1"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the parameter a. Default is 1"), 1.0)
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the parameter b. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Type-1 Gumbel random variable using a random number generator and two parameters."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_gumbel1(HANDLEX rng, double a, double b)
{
#pragma XLLEXPORT
	doublex x;

	try {

		if (a == 0)
			a = 1;
		if (b == 0)
			b = 1;

		handle<gsl::rng> r(rng);

		x = gsl_ran_gumbel1(*r, a, b);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_ran_gumbel1_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_gumbel1_pdf"), _T("GSL.DIST.GUMBEL1.PDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the parameter a. Default is 1."), 1.0)
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the parameter b. Default is 1."), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Type-1 Gumbel random variable probability density function."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_gumbel1_pdf(double x, double a, double b)
{
#pragma XLLEXPORT

	if (a == 0)
		a = 1;
	if (b == 0)
		b = 1;

	return gsl_ran_gumbel1_pdf(x, a, b);
}

static AddInX xai_cdf_gumbel1_P(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_gumbel1_P"), _T("GSL.DIST.GUMBEL1.CDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the parameter a. Default is 1"), 1.0)
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the parameter b. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Type-1 Gumbel random variable cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_gumbel1_P(double x, double a, double b)
{
#pragma XLLEXPORT

	if (a == 0)
		a = 1;
	if (b == 0)
		b = 1;

	return gsl_cdf_gumbel1_P(x, a, b);
}

static AddInX xai_cdf_gumbel1_Pinv(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_gumbel1_Pinv"), _T("GSL.DIST.GUMBEL1.INV"))
	.Arg(XLL_HANDLEX, _T("p"), _T("is the value at which to calculate the inverse cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the parameter a. Default is 1"), 1.0)
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the parameter b. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Type-1 Gumbel inverse cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_gumbel1_Pinv(double p, double a, double b)
{
#pragma XLLEXPORT

	if (a == 0)
		a = 1;
	if (b == 0)
		b = 1;

	return gsl_cdf_gumbel1_Pinv(p, a, b);
}

XLL_TEST_BEGIN(xll_ran_gumbel1)

double eps = 1e-5;

// http://www.wolframalpha.com/input/?i=Table%5BPDF%5BGUMBELDistribution%5B0%2C1%5D%2C+x%5D%2C%7Bx%2C+-2%2C+2%2C+.1%7D%5D
double pdf[] = { 0.118205, 0.12879, 0.140114, 0.152181, 0.164986, 0.178507, 0.192705, 0.207519, 0.222864, 0.238623, 0.254646, 0.270747, 0.286697, 0.302224, 0.317013, 0.330704, 0.342899, 0.353166, 0.361053, 0.366104, 0.367879, 0.365982, 0.360089, 0.349987, 0.335604, 0.317042, 0.294605, 0.268809, 0.240378, 0.210219, 0.179374, 0.148947, 0.120018, 0.0935465, 0.0702848, 0.0507071, 0.0349781, 0.0229612, 0.0142693, 0.00834665, 0.00456628 };
// http://www.wolframalpha.com/input/?i=Table%5BCDF%5BGUMBELDistribution%5B0%2C1%5D%2C+x%5D%2C%7Bx%2C+-2%2C+2%2C+.1%7D%5D
double cdf[] = {0.126577, 0.138921, 0.15236, 0.166968, 0.182821, 0.199989, 0.218544, 0.238551, 0.260066, 0.283137, 0.307799, 0.334069, 0.361944, 0.391395, 0.422364, 0.454761, 0.488455, 0.523276, 0.559009, 0.595392, 0.632121, 0.668846, 0.705184, 0.740723, 0.775038, 0.807704, 0.838317, 0.866513, 0.891991, 0.914531, 0.934012, 0.95042, 0.963851, 0.974506, 0.982668, 0.988686, 0.992938, 0.995805, 0.997641, 0.998752, 0.999382};
for (int i = 0; i < sizeof(pdf) / sizeof(*pdf); ++i) {
	double x = -2 + i*0.1;
	ensure(fabs(xll_ran_gumbel1_pdf(-x, 1, 1) - pdf[i]) < eps);
	ensure(fabs(1-xll_cdf_gumbel1_P(-x, 1, 1) - cdf[i]) < eps);
}

// http://www.wolframalpha.com/input/?i=Table%5BInverseCDF%5BGUMBELDistribution%5B0%2C1%5D%2C+p%5D%2C%7Bp%2C+.1%2C+.9%2C+.1%7D%5D
double inv[] = { -2.25037, -1.49994, -1.03093, -0.671727, -0.366513, -0.0874216, 0.185627, 0.475885, 0.834032 };
for (int i = 0; i < sizeof(inv) / sizeof(*inv); ++i) {
	double p = 0.1 + i*0.1;
	ensure(fabs(-xll_cdf_gumbel1_Pinv(1-p, 1, 1) - inv[i]) < 2 * eps);
}

XLL_TEST_END(xll_ran_gumbel1)