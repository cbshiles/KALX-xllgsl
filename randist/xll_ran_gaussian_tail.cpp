// Code by Zhengkai Feng (ZF2162)
// MATH G4074, Homework 3
// xll_ran_gaussian_tail.cpp - random variates from the upper tail of a Gaussian distribution , density
// http://www.gnu.org/software/gsl/manual/html_node/The-Gaussian-Tail-Distribution.html#The Gaussian Tail Distribution
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_gaussian_tail(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_gaussian_tail"), _T("GSL.RAN.GAUSSIAN_TAIL"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the lower limit of the Gaussian Tail, which must be positive"))
	.Arg(XLL_DOUBLEX, _T("sigma"), _T("is the standard deviation of the Gaussian Tail. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Gaussian Tail random deviates using a random number generator. The values returned are larger than the lower limit"))
	.Documentation(_T(""))
);
double WINAPI xll_ran_gaussian_tail(HANDLEX rng, double a, double sigma)
{
#pragma XLLEXPORT
	doublex x;

	try {
		if (sigma == 0)
			sigma = 1;

		handle<gsl::rng> r(rng);

		x = gsl_ran_gaussian_tail(*r, a, sigma);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_ran_gaussian_tail_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_gaussian_tail_pdf"), _T("GSL.DIST.GAUSSIAN_TAIL.PDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the lower limit of the Gaussian Tail, which must be positive"))
	.Arg(XLL_DOUBLEX, _T("sigma"), _T("is the standard deviation of the Gaussian Tail. Default is 1."), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Gaussian Tail probability density function."))
	.Documentation(_T(""))
);
double WINAPI xll_ran_gaussian_tail_pdf(double x, double a, double sigma)
{
#pragma XLLEXPORT
	if (sigma == 0)
		sigma = 1;

	return gsl_ran_gaussian_tail_pdf(x, a, sigma);
}

XLL_TEST_BEGIN(xll_ran_gaussian_tail)

double eps = 1e-6;

// The probability distribution for Gaussian tail random variates is
// p(x) dx = {1 \over N(a;\sigma) \sqrt{2 \pi \sigma^2}} \exp (- x^2/(2 \sigma^2)) dx
// for x > a where N(a;\sigma) is the normalization constant
// N(a;\sigma) = (1/2) erfc(a / sqrt(2 sigma^2)).
// In the test, we let a = 0.01 and sigma = 1, x = 0.1, 0.2, ..., 1.9, 2.0

// http://www.wolframalpha.com/input/?i=1%2F2*erfc%280.01%2Fsqrt%282%29%29
double normalization_constant = 1 / 0.4960106;
// http://www.wolframalpha.com/input/?i=Table%5BPDF%5BNormalDistribution%5B0%2C1%5D%2C+x%5D%2C%7Bx%2C+.1%2C+2%2C+.1%7D%5D
double pdf[] = {0.396953, 0.391043, 0.381388, 0.36827, 0.352065, 0.333225, 0.312254, 0.289692, 0.266085, 0.241971, 0.217852, 0.194186, 0.171369, 0.149727, 0.129518, 0.110921, 0.0940491, 0.0789502, 0.0656158, 0.053991};

for (int i = 0; i < sizeof(pdf)/sizeof(*pdf); ++i) {
	double x = 0.1 + i*0.1;
	ensure (fabs(xll_ran_gaussian_tail_pdf(x, 0.01, 1) - normalization_constant * pdf[i]) < eps);
}

XLL_TEST_END(xll_ran_gaussian_tail)