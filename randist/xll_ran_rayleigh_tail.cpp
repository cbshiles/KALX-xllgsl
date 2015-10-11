// xll_ran_gaussian.cpp - Gaussian variates, density, cumulative distribution, and inverse
// http://www.gnu.org/software/gsl/manual/html_node/The-Gaussian-Distribution.html#The-Gaussian-Distribution
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_rayleigh_tail(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_rayleigh_tail"), _T("GSL.RAN.rayleightail"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the lower limit of rayleightail. Default is 0"), 0.0)
	.Arg(XLL_DOUBLEX, _T("sigma"), _T("is the standard deviation of the rayleightail. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return rayleightail random deviates using a random number generator."))
	.Documentation(_T(""))
);
double WINAPI xll_ran_rayleigh_tail(HANDLEX rng, double a, double sigma)
{
#pragma XLLEXPORT
	doublex x;
	try {
		if (sigma == 0)
			sigma = 1;
		if (a == 0)
			a = 0;
		handle<gsl::rng> r(rng);
		x = gsl_ran_rayleigh_tail(*r, a, sigma);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	return x;
}

static AddInX xai_ran_rayleigh_tail_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_rayleigh_tail_pdf"), _T("GSL.DIST.RAYLEIGHTAIL.PDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the lower limits of rayleightail. Default is 0."), 0.0)
	.Arg(XLL_DOUBLEX, _T("sigma"), _T("is the standard deviation of the rayleightail. Default is 1."), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return rayleightail probability density function."))
	.Documentation(_T(""))
);
double WINAPI xll_ran_rayleigh_tail_pdf(double x, double a, double sigma)
{
#pragma XLLEXPORT
	if (sigma == 0)
		sigma = 1;

	return gsl_ran_rayleigh_tail_pdf(x, a,  sigma);
}



XLL_TEST_BEGIN(xll_ran_rayleigh_tail)

double eps = 1e-6;

//http://www.wolframalpha.com/input/?i=Table%5BPDF%5BRayleighDistribution%5B1%5D%2C+x%5D%2C%7Bx%2C+-2%2C+2%2C+.1%7D%5D
//since no rayleigh tail distritution availale in Wolframalpha, conform with rayleigh distribution with limit factor a = 0;
double pdf[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.0995012, 0.19604, 0.286799, 0.369247, 0.441248, 0.501162, 0.547893, 0.580919, 0.600279, 0.606531, 0.600682, 0.584103, 0.558425, 0.525436, 0.486979, 0.44486, 0.400768, 0.356218, 0.312501, 0.270671 };

for (int i = 0; i < sizeof(pdf)/sizeof(*pdf); ++i) {
	double x = -2 + i*0.1;
	ensure (fabs(xll_ran_rayleigh_tail_pdf(x, 0 ,1) - pdf[i]) < eps);
}


XLL_TEST_END(xll_ran_rayleigh_tail)