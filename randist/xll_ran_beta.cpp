// xll_ran_beta.cpp - Beta variates, density, cumulative distribution, and inverse
// http://www.gnu.org/software/gsl/manual/html_node/The-Beta-Distribution.html #The-Beta-Distribution
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_beta(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_beta"), _T("GSL.RAN.BETA"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("alpha"), _T("is the first shape parameter of Beta. Default is 2"), 2.0)
	.Arg(XLL_DOUBLEX, _T("beta"), _T("is the second shape parameter of Beta. Default is 2"), 2.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Beta deviates using a random number generator."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_beta(HANDLEX rng, double a, double b)
{
#pragma XLLEXPORT
	doublex x;

	try {
		if (a == 0)
			a = 2;
		if (b == 0)
			b = 2;

		handle<gsl::rng> r(rng);

		x = gsl_ran_beta(*r, a, b);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_ran_beta_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_beta_pdf"), _T("GSL.DIST.BETA.PDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("alpha"), _T("is the first shape parameter of Beta. Default is 2"), 2.0)
	.Arg(XLL_DOUBLEX, _T("beta"), _T("is the second shape parameter of Beta. Default is 2"), 2.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Beta probability density function."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_beta_pdf(double x, double a, double b)
{
#pragma XLLEXPORT
	if (a == 0)
		a = 2;
	if (b == 0)
		b = 2;

	return gsl_ran_beta_pdf(x, a, b);
}

static AddInX xai_cdf_beta_P(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_beta_P"), _T("GSL.DIST.BETA.CDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("alpha"), _T("is the first shape parameter of Beta. Default is 2"), 2.0)
	.Arg(XLL_DOUBLEX, _T("beta"), _T("is the second shape parameter of Beta. Default is 2"), 2.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Beta cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_beta_P(double x, double a, double b)
{
#pragma XLLEXPORT
	if (a == 0)
		a = 2;
	if (b == 0)
		b = 2;

	return gsl_cdf_beta_P(x, a, b);
}

static AddInX xai_cdf_beta_Pinv(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_beta_Pinv"), _T("GSL.DIST.BETA.INV"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the inverse cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("alpha"), _T("is the first shape parameter of Beta. Default is 2"), 2.0)
	.Arg(XLL_DOUBLEX, _T("beta"), _T("is the second shape parameter of Beta. Default is 2"), 2.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Beta inverse cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_beta_Pinv(double p, double a, double b)
{
#pragma XLLEXPORT
	if (a == 0)
		a = 2;
	if (b == 0)
		b = 2;

	return gsl_cdf_beta_Pinv(p, a, b);
}

XLL_TEST_BEGIN(xll_ran_beta)

double eps = 1e-6;

// http://www.wolframalpha.com/input/?i=Table%5BPDF%5BBetaDistribution%5B2%2C2%5D%2C+x%5D%2C%7Bx%2C+0%2C+1%2C+.1%7D%5D
double pdf[] = { 0, 0.54, 0.96, 1.26, 1.44, 1.5, 1.44, 1.26, 0.96, 0.54, 0 };
// http://www.wolframalpha.com/input/?i=Table%5BCDF%5BBetaDistribution%5B2%2C2%5D%2C+x%5D%2C%7Bx%2C+0%2C+1%2C+.1%7D%5D
double cdf[] = { 0, 0.028, 0.104, 0.216, 0.352, 0.5, 0.648, 0.784, 0.896, 0.972, 1 };

for (int i = 0; i < sizeof(pdf) / sizeof(*pdf); ++i) {
	double x = i*0.1;
	ensure(fabs(xll_ran_beta_pdf(x, 2, 2) - pdf[i]) < eps);
	ensure(fabs(xll_cdf_beta_P(x, 2, 2) - cdf[i]) < eps);
}

// http://www.wolframalpha.com/input/?i=Table%5BInverseCDF%5BBetaDistribution%5B2%2C2%5D%2C+p%5D%2C%7Bp%2C+.1%2C+.9%2C+.1%7D%5D
double inv[] = { 0.1958, 0.287141, 0.363257, 0.432931, 0.5, 0.567069, 0.636743, 0.712859, 0.8042 };
for (int i = 0; i < sizeof(inv) / sizeof(*inv); ++i) {
	double p = 0.1 + i*0.1;
	ensure(fabs(xll_cdf_beta_Pinv(p, 2, 2) - inv[i]) < 2 * eps);
}

XLL_TEST_END(xll_ran_beta)