// xll_ran_poisson.cpp - poisson variates, density, cumulative distribution, and inverse
// http://www.gnu.org/software/gsl/manual/html_node/The-Poisson-Distribution.html#The-Poisson-Distribution
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_poisson(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_poisson"), _T("GSL.RAN.POISSON"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("mu"), _T("is the mean of the Poisson."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Poisson random deviates using a random number generator."))
	.Documentation(_T(""))
);
unsigned int WINAPI xll_ran_poisson(HANDLEX rng, double mu)
{
#pragma XLLEXPORT
	doublex x;

	try {

		handle<gsl::rng> r(rng);

		x = gsl_ran_poisson(*r, mu);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_ran_poisson_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_poisson_pdf"), _T("GSL.DIST.POISSON.PDF"))
	.Arg(XLL_HANDLEX, _T("k"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("mu"), _T("is the mean of the Poisson."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Poisson probability density function."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_poisson_pdf(unsigned int k, double mu)
{
#pragma XLLEXPORT

	return gsl_ran_poisson_pdf(k, mu); 
}

static AddInX xai_cdf_poisson_P(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_poisson_P"), _T("GSL.DIST.POISSON.CDF"))
	.Arg(XLL_HANDLEX, _T("k"), _T("is the value at which to calculate the cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("mu"), _T("is the mean of the Poisson."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Poisson cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_poisson_P(unsigned int k, double mu)
{
#pragma XLLEXPORT


	return gsl_cdf_poisson_P(k, mu);
}


XLL_TEST_BEGIN(xll_ran_poisson)

double eps = 1e-4;

// http://www.wolframalpha.com/input/?i=Table%5BPDF%5BPoissonDistribution%5B5%5D%2Ck%5D%2C+%7Bk%2C+1%2C+20%7D%5D
double pdf[] = { 0.0336879, 0.0842243, 0.140347, 0.175467, 0.175467, 0.146223, 0.104445, 0.065278, 0.0362656, 0.0181328 };
// http://www.wolframalpha.com/input/?i=Table%5BCDF%5BPoissonDistribution%5B5%5D%2Ck%5D%2C+%7Bk%2C+1%2C+20%7D%5D
double cdf[] = { 0.0404277, 0.124652, 0.265026, 0.440493, 0.615961, 0.762183, 0.866628, 0.931906, 0.968172, 0.986305 };

for (int i = 0; i < sizeof(pdf) / sizeof(*pdf); ++i) {
	double x = 1 + i;
	ensure(fabs(xll_ran_poisson_pdf(x, 5) - pdf[i]) < eps);
	ensure(fabs(xll_cdf_poisson_P(x, 5) - cdf[i]) < eps);
}

XLL_TEST_END(xll_ran_poisson)

