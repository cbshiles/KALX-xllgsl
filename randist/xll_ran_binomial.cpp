// xll_ran_binomial.cpp - Binomial variates, density, cumulative distribution, and inverse
// http://www.gnu.org/software/gsl/manual/html_node/The-Binomial-Distribution.html#The-Binomial-Distribution#The Binomial Distribution
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_binomial(
	FunctionX(XLL_USHORTX, _T("?xll_ran_binomial"), _T("GSL.RAN.BINOMIAL"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("p"), _T("is the probability of success in each independent trial. Default is 0.5."), 0.5)
	.Arg(XLL_USHORTX, _T("n"), _T("is the number of independent trials. Default is 100."), 100)
	.Category(_T("GSL"))
	.FunctionHelp(_T("This function returns a random integer from the binomial distribution, the number of successes in n independent trials with probability p."))
	.Documentation(_T(""))
	);
unsigned int WINAPI xll_ran_binomial(HANDLEX rng, double p, unsigned int n)
{
#pragma XLLEXPORT

	handle<gsl::rng> r(rng);
	return gsl_ran_binomial(*r, p, n);
}

static AddInX xai_ran_binomial_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_binomial_pdf"), _T("GSL.DIST.BINOMIAL.PDF"))
	.Arg(XLL_USHORTX, _T("k"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("p"), _T("is the probability of success in each independent trial. Default is 0.5"), 0.5)
	.Arg(XLL_USHORTX, _T("n"), _T("is the number of independent trials. Default is 100"), 100)
	.Category(_T("GSL"))
	.FunctionHelp(_T("This function computes the probability p(k) of obtaining k from a binomial distribution with parameters p and n."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_binomial_pdf(unsigned int k, double p, unsigned int n)
{
#pragma XLLEXPORT
	
	return gsl_ran_binomial_pdf(k, p, n);
}

static AddInX xai_cdf_binomial_P(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_binomial_P"), _T("GSL.DIST.BINOMIAL.CDF"))
	.Arg(XLL_USHORTX, _T("k"), _T("is the value at which to calculate the cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("p"), _T("is the probability of success in each independent trial. Default is 0.5"), 0.5)
	.Arg(XLL_USHORTX, _T("n"), _T("is the number of independent trials. Default is 100"), 100)
	.Category(_T("GSL"))
	.FunctionHelp(_T("This function computes the cumulative distribution functions P(k) for the binomial distribution with parameters p and n."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_binomial_P(unsigned int k, double p, unsigned int n)
{
#pragma XLLEXPORT

	return gsl_cdf_binomial_P(k, p, n);
}


XLL_TEST_BEGIN(xll_ran_binomial)

double eps = 1e-6; 

// http://www.wolframalpha.com/input/?i=Table%5BPDF%5Bbinomial+distribution+n%3D10%2C+p%3D0.5%2C+k%5D%2C%7Bk%2C+0%2C+10%2C+1%7D%5D
double pdf[] = { 0.000976563, 0.00976562, 0.0439453, 0.117188, 0.205078, 0.246094, 0.205078, 0.117188, 0.0439453, 0.00976562, 0.000976563 };
// http://www.wolframalpha.com/input/?i=Table%5BCDF%5Bbinomial+distribution+n%3D10%2C+p%3D0.5%2C+k%5D%2C%7Bk%2C+0%2C+10%2C+1%7D%5D
double cdf[] = { 0.000976563, 0.0107422, 0.0546875, 0.171875, 0.376953, 0.623047, 0.828125, 0.945313, 0.989258, 0.999023, 1 };

for (int i = 0; i < sizeof(pdf) / sizeof(*pdf); ++i) {
	unsigned int k = 0 + i*1;
	ensure(fabs(xll_ran_binomial_pdf(k, 0.5, 10) - pdf[i]) < eps);
	ensure(fabs(xll_cdf_binomial_P(k, 0.5, 10) - cdf[i]) < eps);
}

XLL_TEST_END(xll_ran_binomial)
