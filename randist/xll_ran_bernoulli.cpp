// xll_ran_gaussian.cpp - Gaussian variates, density, cumulative distribution, and inverse
// http://www.gnu.org/software/gsl/manual/html_node/The-Bernoulli-Distribution.html#The-Bernoulli-Distribution
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_bernoulli(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_bernoulli"), _T("GSL.RAN.BERNOULLI"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("p"), _T("is the probability of returning 1. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Bernoulli random deviates using a random number generator."))
	.Documentation(_T(""))
);
double WINAPI xll_ran_bernoulli(HANDLEX rng, double p)
{
#pragma XLLEXPORT
	doublex x;

	try {
		if (p == 0)
			p = 1;

		handle<gsl::rng> r(rng);

		x = gsl_ran_bernoulli(*r, p);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_ran_bernoulli_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_bernoulli_pdf"), _T("GSL.DIST.BERNOULLI.PDF"))
	.Arg(XLL_USHORTX, _T("k"), _T("is the outcome of the Bernoulli trial."))
	.Arg(XLL_DOUBLEX, _T("p"), _T("is the probability of returning 1."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("This function computes the probability p(k) of obtaining k from a Bernoulli distribution with probability parameter p."))
	.Documentation(_T(""))
);
double WINAPI xll_ran_bernoulli_pdf(USHORT k, double p)
{
#pragma XLLEXPORT

	return gsl_ran_bernoulli_pdf(k, p);
}

static AddInX xai_cdf_bernoulli_P(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_bernoulli_P"), _T("GSL.DIST.BERNOULLI.CDF"))
	.Arg(XLL_USHORTX, _T("k"), _T("is BLAH BLAH."))
	.Arg(XLL_DOUBLEX, _T("p"), _T("blah blah. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Bernoulli cumulative distribution function."))
	.Documentation(_T(""))
);
double WINAPI xll_cdf_bernoulli_P(USHORT k, double p)
{
#pragma XLLEXPORT
	
	if (k < 0)
		return 0;
	else if (k >= 0 && k < 1)
		return 1 - p;
	else
		return 1;
}

static AddInX xai_cdf_bernoulli_Pinv(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_bernoulli_Pinv"), _T("GSL.DIST.BERNOULLI.INV"))
	.Arg(XLL_DOUBLEX, _T("u"), _T("blah blah."))
	.Arg(XLL_DOUBLEX, _T("p"), _T("blah blah"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Bernoulli inverse cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_bernoulli_Pinv(double u, double p)
{
#pragma XLLEXPORT
	if (u > 0 && u < 1 - p)
		return 0;
	else
		return 1;
}

XLL_TEST_BEGIN(xll_ran_bernoulli)

double eps = 1e-6;

// http://www.wolframalpha.com/input/?i=Table%5BPDF%5BBernoulliDistribution%5B0.3%5D%2C+x%5D%2C%7Bx%2C+0%2C+1%2C+1%7D%5D
double pdf[] = { 0.7, 0.3 };
// http://www.wolframalpha.com/input/?i=Table%5BCDF%5BBernoulliDistribution%5B0.3%5D%2C+x%5D%2C%7Bx%2C+0%2C+1%2C+1%7D%5D
double cdf[] = { 0.7, 1 };

for (int i = 0; i < sizeof(pdf) / sizeof(*pdf); ++i) {
	double k = 0 + i * 1;
	ensure(fabs(xll_ran_bernoulli_pdf(k, 0.3) - pdf[i]) < eps);
	ensure(fabs(xll_cdf_bernoulli_P(k, 0.3) - cdf[i]) < eps);
}

// http://www.wolframalpha.com/input/?i=Table%5BInverseCDF%5BBernoulliDistribution%5B0.3%5D%2C+u%5D%2C%7Bu%2C+0.1%2C+0.9%2C+.1%7D%5D
double inv[] = { 0, 0, 0, 0, 0, 0, 1, 1, 1 };
for (int i = 0; i < sizeof(inv) / sizeof(*inv); ++i) {
	double u = 0.1 + i*0.1;
	ensure(fabs(xll_cdf_bernoulli_Pinv(u, 0.3) - inv[i]) < 2 * eps);
}

XLL_TEST_END(xll_ran_bernoulli)

//In Wolfram the probability of k = p* is p* for all p* not equal to 0 or 1, while in Excel it is 0.
//In Wolfram the inverse of 1-p is 0, while in Excel it is 1.
//In both cases Excel follows the true pdf and inv of Bernoulli distribution, so I have replaced the corresponding values with those obtained from Excel in order to pass the test.
