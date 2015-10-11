// xll_ran_lognormal.cpp - lognormal variates, density, cumulative distribution, and inverse
// http://www.gnu.org/software/gsl/manual/html_node/The-Gaussian-Distribution.html#The-Lognormal-Distribution
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_lognormal(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_lognormal"), _T("GSL.RAN.LOGNORMAL"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("zeta"), _T("is the mean of the lognormal. Default is 0"), 0.0)
	.Arg(XLL_DOUBLEX, _T("sigma"), _T("is the standard deviation of the lognormal. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return lognormal random deviates using a random number generator."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_lognormal(HANDLEX rng, double zeta, double sigma)
{
#pragma XLLEXPORT
	doublex x;

	try {
		if (sigma == 0)
			sigma = 1;
		handle<gsl::rng> r(rng);

		x = gsl_ran_lognormal(*r, zeta, sigma);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_ran_lognormal_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_lognormal_pdf"), _T("GSL.DIST.LOGNORMAL.PDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("zeta"), _T("is the mean of the lognormal. Default is 0"), 0.0)
	.Arg(XLL_DOUBLEX, _T("sigma"), _T("is the standard deviation of the lognormal. Default is 1."), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return lognormal probability density function."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_lognormal_pdf(double x,double zeta, double sigma)
{
#pragma XLLEXPORT
	if (sigma == 0)
		sigma = 1;
	return gsl_ran_lognormal_pdf(x, zeta, sigma);
}

static AddInX xai_cdf_lognormal_P(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_lognormal_P"), _T("GSL.DIST.LOGNORMAL.CDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("zeta"), _T("is the mean of the lognormal. Default is 0"), 0.0)
	.Arg(XLL_DOUBLEX, _T("sigma"), _T("is the standard deviation of the lognormal. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return lognormal cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_lognormal_P(double x, double zeta, double sigma)
{
#pragma XLLEXPORT
	if (sigma == 0)
		sigma = 1;
	return gsl_cdf_lognormal_P(x, zeta, sigma);
}

static AddInX xai_cdf_lognormal_Pinv(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_lognormal_Pinv"), _T("GSL.DIST.LOGNORMAL.INV"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the inverse cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("zeta"), _T("is the mean of the lognormal. Default is 0"), 0.0)
	.Arg(XLL_DOUBLEX, _T("sigma"), _T("is the standard deviation of the lognormal. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return lognormal inverse cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_lognormal_Pinv(double p, double zeta, double sigma)
{
#pragma XLLEXPORT
	if (sigma == 0)
		sigma = 1;

	return gsl_cdf_lognormal_Pinv(p, zeta, sigma);
}

XLL_TEST_BEGIN(xll_ran_lognormal)

double eps = 1e-5;

// http://www.wolframalpha.com/input/?i=Table%5BPDF%5BLogNormalDistribution%5B0%2C1%5D%2C+x%5D%2C%7Bx%2C+0%2C+2%2C+.1%7D%5D
double pdf[] = {0, 0.28159, 0.546268, 0.644203, 0.655444, 0.627496, 0.583574, 0.534795, 0.486416, 0.440816, 0.398942, 0.361031, 0.326972, 0.296496, 0.269276, 0.244974, 0.223265, 0.203854, 0.186472, 0.170882, 0.156874 };
// http://www.wolframalpha.com/input/?i=Table%5BCDF%5BLogNormalDistribution%5B0%2C1%5D%2C+x%5D%2C%7Bx%2C+0%2C+2%2C+.1%7D%5D
double cdf[] = { 0, 0.0106511, 0.0537603, 0.1143, 0.179757, 0.244109, 0.304737, 0.360668, 0.411712, 0.458045, 0.5, 0.537966, 0.572335, 0.60348, 0.631743, 0.657432, 0.680824, 0.702162, 0.721662, 0.739516, 0.755891 };
for (int i = 0; i < sizeof(pdf) / sizeof(*pdf); ++i) {
	double x = 0 + i*0.1;
	ensure(fabs(xll_ran_lognormal_pdf(x, 0, 1) - pdf[i]) < eps);
	ensure(fabs(xll_cdf_lognormal_P(x,0, 1) - cdf[i]) < eps);
}

// http://www.wolframalpha.com/input/?i=Table%5BInverseCDF%5BLogNormalDistribution%5B0%2C1%5D%2C+p%5D%2C%7Bp%2C+.1%2C+.9%2C+.1%7D%5D
double inv[] = { 0.277606, 0.431011, 0.59191, 0.776198, 1., 1.28833, 1.68945, 2.32013, 3.60222 };
for (int i = 0; i < sizeof(inv) / sizeof(*inv); ++i) {
	double p = 0.1 + i*0.1;
	ensure(fabs(xll_cdf_lognormal_Pinv(p, 0, 1) - inv[i]) < 2 * eps);
}

XLL_TEST_END(xll_ran_lognormal)