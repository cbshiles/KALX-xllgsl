// xll_ran_cauchy.cpp - Gaussian variates, density, cumulative distribution, and inverse
// http://www.gnu.org/software/gsl/manual/html_node/The-Gaussian-Distribution.html#The-Gaussian-Distribution
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_cauchy(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_cauchy"), _T("GSL.RAN.CAUCHY"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the scale parameter of the Cauchy. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Cauchy random deviates using a random number generator."))
	.Documentation(R_(
		This function returns a random variate from the Cauchy distribution with scale parameter a. The probability distribution for Cauchy random variates is, 

		p[x] dx = {1 over a pi (1 + (x/a)^2) } dx


		for x in the range -infty to +infty. The Cauchy distribution is also known as the Lorentz distribution. 

	))
	);
double WINAPI xll_ran_cauchy(HANDLEX rng, double a)
{
#pragma XLLEXPORT
	doublex x;

	try {
		if (a == 0)
			a = 1;

		handle<gsl::rng> r(rng);

		x = gsl_ran_cauchy( *r, a);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_ran_cauchy_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_cauchy_pdf"), _T("GSL.DIST.CAUCHY.PDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the scale parameter of the Cauchy. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return cauchy probability density function."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_cauchy_pdf(double x, double a)
{
#pragma XLLEXPORT
	if (a == 0)
		a = 1;

	return gsl_ran_cauchy_pdf(x, a);
}

static AddInX xai_cdf_cauchy_P(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_cauchy_P"), _T("GSL.DIST.CAUCHY.CDF"))
	.Arg(XLL_DOUBLEX, _T("sigma"), _T("is the standard deviation of the Cauchy. Default is 1"), 1.0)
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the cumulative distribution function."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Cauchy cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_cauchy_P(double x, double a)
{
#pragma XLLEXPORT
	if (a == 0)
		a = 1;

	return gsl_cdf_cauchy_P(x, a);
}

static AddInX xai_cdf_cauchy_Pinv(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_cauchy_Pinv"), _T("GSL.DIST.CAUCHY.INV"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the inverse cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("sigma"), _T("is the standard deviation of the Cauchy. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Cauchy inverse cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_cauchy_Pinv(double p, double a)
{
#pragma XLLEXPORT
	if (a == 0)
		a = 1;

	return gsl_cdf_cauchy_Pinv(p, a);
}

XLL_TEST_BEGIN(xll_ran_cauchy)

double eps = 1e-6;

// http://www.wolframalpha.com/input/?i=Table%5BPDF%5BNormalDistribution%5B0%2C1%5D%2C+x%5D%2C%7Bx%2C+-2%2C+2%2C+.1%7D%5D
double pdf[] = { 0.063662, 0.0690477, 0.0750731, 0.0818277, 0.0894129, 0.0979415, \
0.107537, 0.118331, 0.130455, 0.144032, 0.159155, 0.175862, 0.194091, \
0.213631, 0.234051, 0.254648, 0.274405, 0.292027, 0.306067, 0.315158, \
0.31831, 0.315158, 0.306067, 0.292027, 0.274405, 0.254648, 0.234051, \
0.213631, 0.194091, 0.175862, 0.159155, 0.144032, 0.130455, 0.118331, \
0.107537, 0.0979415, 0.0894129, 0.0818277, 0.0750731, 0.0690477, \
0.063662 };
// http://www.wolframalpha.com/input/?i=Table%5BCDF%5BNormalDistribution%5B0%2C1%5D%2C+x%5D%2C%7Bx%2C+-2%2C+2%2C+.1%7D%5D
double cdf[] = { 0.147584, 0.154214, 0.161414, 0.169253, 0.177808, 0.187167, 0.197432, \
0.208714, 0.221142, 0.234854, 0.25, 0.266738, 0.285223, 0.3056, \
0.327979, 0.352416, 0.378881, 0.407226, 0.437167, 0.468274, 0.5, \
0.531726, 0.562833, 0.592774, 0.621119, 0.647584, 0.672021, 0.6944, \
0.714777, 0.733262, 0.75, 0.765146, 0.778858, 0.791286, 0.802568, \
0.812833, 0.822192, 0.830747, 0.838586, 0.845786, 0.852416 };

for (int i = 0; i < sizeof(pdf) / sizeof(*pdf); ++i) {
	double x = -2 + i*0.1;
	ensure(fabs(xll_ran_cauchy_pdf(x, 1) - pdf[i]) < eps);
	ensure(fabs(xll_cdf_cauchy_P(x, 1) - cdf[i]) < eps);
}

// http://www.wolframalpha.com/input/?i=Table%5BInverseCDF%5BNormalDistribution%5B0%2C1%5D%2C+p%5D%2C%7Bp%2C+.1%2C+.9%2C+.1%7D%5D
double inv[] = { -3.07768, -1.37638, -0.726543, -0.32492, 0., 0.32492, 0.726543, \
1.37638, 3.07768 };
for (int i = 0; i < sizeof(inv) / sizeof(*inv); ++i) {
	double p = 0.1 + i*0.1;
	ensure(fabs(xll_cdf_cauchy_Pinv(p, 1) - inv[i]) < 10 * eps);
}

XLL_TEST_END(xll_ran_cauchy)