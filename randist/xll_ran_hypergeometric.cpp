// xll_ran_hypergeometric.cpp - hypergeometric variates, density, cumulative distribution, and inverse
// http://www.gnu.org/software/gsl/manual/html_node/The-hypergeometric-Distribution.html#The-hypergeometric-Distribution
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"


using namespace xll;

static AddInX xai_ran_hypergeometric(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_hypergeometric"), _T("GSL.RAN.HYPERGEOMETRIC"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("n1"), _T("is the standard deviation of the HYPERGEOMETRIC. Default is 1"), 1)
	.Arg(XLL_DOUBLEX, _T("n2"), _T("is the standard deviation of the HYPERGEOMETRIC. Default is 1"), 1)
	.Arg(XLL_DOUBLEX, _T("t"), _T("is the standard deviation of the HYPERGEOMETRIC. Default is 1"), 1)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Hypergeometric random deviates using a random number generator."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_hypergeometric(HANDLEX rng, unsigned int n1, unsigned int n2, unsigned int t)
{
#pragma XLLEXPORT
	doublex x;

	try {
		

	    handle<gsl::rng> r(rng);

		x = gsl_ran_hypergeometric(*r, n1, n2, t);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_ran_hypergeometric_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_hypergeometric_pdf"), _T("GSL.DIST.HYPERGEOMETRIC.PDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("n1"), _T("is the standard deviation of the Gaussian. Default is 1."), 1.0)
	.Arg(XLL_DOUBLEX, _T("n2"), _T("is the standard deviation of the Gaussian. Default is 1."), 1.0)
	.Arg(XLL_DOUBLEX, _T("t"), _T("is the standard deviation of the Gaussian. Default is 1."), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Hypergeometric probability density function."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_hypergeometric_pdf(unsigned int x, unsigned int n1, unsigned int n2, unsigned int t)
{
#pragma XLLEXPORT
	
	return gsl_ran_hypergeometric_pdf(x, n1, n2, t);
}

static AddInX xai_cdf_hypergeometric_P(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_hypergeometric_P"), _T("GSL.DIST.HYPERGEOMETRIC.CDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("n1"), _T("is the standard deviation. Default is 1"), 1.0)
	.Arg(XLL_DOUBLEX, _T("n2"), _T("is the standard deviation. Default is 1"), 1.0)
	.Arg(XLL_DOUBLEX, _T("t"), _T("is the standard deviation. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Hypergeometric cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_hypergeometric_P(unsigned int x, unsigned int n1, unsigned int n2, unsigned int t)
{
#pragma XLLEXPORT
	
	return gsl_cdf_hypergeometric_P(x,n1,n2,t);
}
XLL_TEST_BEGIN(xll_ran_hypergeometric)

double eps = 1e-6;

// http://www.wolframalpha.com/input/?i=Table%5BPDF%5BHypergeometricDistribution+%5B10%2C10%2C25%5D%2Cx%5D%2C%7Bx%2C+0%2C+10%2C+1%7D%5D
double pdf[] = { 0.0009187, 0.0153116, 0.0885886, 0.2362364, 0.3215439, 0.2315116, 0.0876938, 0.0167036, 0.0014455, 0.0000459, 0.0000003 };
// http://www.wolframalpha.com/input/?i=Table%5BCDF%5BNormalDistribution%5B0%2C1%5D%2C+x%5D%2C%7Bx%2C+-2%2C+2%2C+.1%7D%5D
double cdf[] = { 0.0009187, 0.0162303, 0.1048190, 0.3410553, 0.6625993, 0.8941109, 0.9818047, 0.9985083, 0.9999538, 0.9999997, 1.0000000 };

for (int i = 0; i < sizeof(pdf) / sizeof(*pdf); ++i) {
	double x = i;
	ensure(fabs(xll_ran_hypergeometric_pdf(x,10,15,10) - pdf[i]) < eps);
	ensure(fabs(xll_cdf_hypergeometric_P(x,10,15,10) - cdf[i]) < eps);
}

XLL_TEST_END(xll_ran_hypergeometric)