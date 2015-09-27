// xll_ran_gaussian.h
#include "gsl/gsl_randist.h"
#include "gsl/gsl_cdf.h"
#include "../xll_rng.h"
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_gaussian(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_gaussian"), _T("GSL.RAN.GAUSSIAN"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("sigma"), _T("is the standard deviation of the Gaussian. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Gaussian/normal random deviates using a random number generator."))
	.Documentation(_T(""))
);
double WINAPI xll_ran_gaussian(HANDLEX rng, double sigma)
{
#pragma XLLEXPORT
	doublex x;

	try {
		if (sigma == 0)
			sigma = 1;

		handle<gsl::rng> r(rng);

		x = gsl_ran_gaussian(*r, sigma);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_ran_gaussian_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_gaussian_pdf"), _T("GSL.DIST.GAUSSIAN.PDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("sigma"), _T("is the standard deviation of the Gaussian. Default is 1."), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Gaussian/normal probability density function."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_gaussian_pdf(double x, double sigma)
{
#pragma XLLEXPORT
	if (sigma == 0)
		sigma = 1;

	return gsl_ran_gaussian_pdf(x, sigma);
}

static AddInX xai_cdf_gaussian_P(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_gaussian_P"), _T("GSL.DIST.GAUSSIAN.CDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("sigma"), _T("is the standard deviation of the Gaussian. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Gaussian/normal cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_gaussian_P(double x, double sigma)
{
#pragma XLLEXPORT
	if (sigma == 0)
		sigma = 1;

	return gsl_cdf_gaussian_P(x, sigma);
}

static AddInX xai_cdf_gaussian_Pinv(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_gaussian_Pinv"), _T("GSL.DIST.GAUSSIAN.INV"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the inverse cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("sigma"), _T("is the standard deviation of the Gaussian. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Gaussian/normal inverse cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_gaussian_Pinv(double p, double sigma)
{
#pragma XLLEXPORT
	if (sigma == 0)
		sigma = 1;

	return gsl_cdf_gaussian_Pinv(p, sigma);
}

XLL_TEST_BEGIN(xll_ran_gausian)

double eps = 1e-6;

// http://www.wolframalpha.com/input/?i=Table%5BPDF%5BNormalDistribution%5B0%2C1%5D%2C+x%5D%2C%7Bx%2C+-2%2C+2%2C+.1%7D%5D
double pdf[] = {0.053991, 0.0656158, 0.0789502, 0.0940491, 0.110921, 0.129518, 0.149727, 0.171369, 0.194186, 0.217852, 0.241971, 0.266085, 0.289692, 0.312254, 0.333225, 0.352065, 0.36827, 0.381388, 0.391043, 0.396953, 0.398942, 0.396953, 0.391043, 0.381388, 0.36827, 0.352065, 0.333225, 0.312254, 0.289692, 0.266085, 0.241971, 0.217852, 0.194186, 0.171369, 0.149727, 0.129518, 0.110921, 0.0940491, 0.0789502, 0.0656158, 0.053991};
// http://www.wolframalpha.com/input/?i=Table%5BCDF%5BNormalDistribution%5B0%2C1%5D%2C+x%5D%2C%7Bx%2C+-2%2C+2%2C+.1%7D%5D
double cdf[] = {0.0227501, 0.0287166, 0.0359303, 0.0445655, 0.0547993, 0.0668072, 0.0807567, 0.0968005, 0.11507, 0.135666, 0.158655, 0.18406, 0.211855, 0.241964, 0.274253, 0.308538, 0.344578, 0.382089, 0.42074, 0.460172, 0.5, 0.539828, 0.57926, 0.617911, 0.655422, 0.691462, 0.725747, 0.758036, 0.788145, 0.81594, 0.841345, 0.864334, 0.88493, 0.9032, 0.919243, 0.933193, 0.945201, 0.955435, 0.96407, 0.971283, 0.97725};

for (int i = 0; i < sizeof(pdf)/sizeof(*pdf); ++i) {
	double x = -2 + i*0.1;
	ensure (fabs(xll_ran_gaussian_pdf(x, 1) - pdf[i]) < eps);
	ensure (fabs(xll_cdf_gaussian_P(x, 1) - cdf[i]) < eps);
}

// http://www.wolframalpha.com/input/?i=Table%5BInverseCDF%5BNormalDistribution%5B0%2C1%5D%2C+p%5D%2C%7Bp%2C+.1%2C+.9%2C+.1%7D%5D
double inv[] = {-1.28155, -0.841621, -0.524401, -0.253347, 0, 0.253347, 0.524401, 0.841621, 1.28155};
for (int i = 0; i < sizeof(inv)/sizeof(*inv); ++i) {
	double p = 0.1 + i*0.1;
	ensure (fabs(xll_cdf_gaussian_Pinv(p, 1) - inv[i]) < 2*eps);
}

XLL_TEST_END(xll_ran_gausian)