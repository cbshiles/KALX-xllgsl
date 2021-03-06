// xll_ran_exponential.cpp - exponential variates, density, cumulative distribution, and inverse
// http://www.gnu.org/software/gsl/manual/html_node/The-Exponential-Distribution.html#The-Exponential-Distribution
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_exponential(
	FunctionX(XLL_DOUBLE, _T("?xll_ran_exponential"),_T("GSL.RAN.EXPONENTIAL"))
	.Arg(XLL_HANDLEX, _T("rng"),_T("is a handle returned by GSL.RNG"))
	.Arg(XLL_DOUBLEX, _T("mu"), _T("is the mean of the exponential distribution"))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return exponential random deviates using a random number generator."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_exponential(HANDLEX rng, double mu)
{
#pragma XLLEXPORT
	doublex x;

	try {
		

		handle<gsl::rng> r(rng);

		x = gsl_ran_exponential(*r, mu);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_ran_exponential_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_exponential_pdf"), _T("GSL.DIST.EXPONENTIAL.PDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("mu"), _T("is the mean of the exponential distribution"))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return exponential probability density function."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_exponential_pdf(double x, double mu)
{
#pragma XLLEXPORT
	

	return gsl_ran_exponential_pdf(x, mu);
}

static AddInX xai_cdf_exponential_P(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_exponential_P"), _T("GSL.DIST.EXPONENTIAL.CDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("mu"), _T("is the mean of the exponential distribution"))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return exponential cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_exponential_P(double x, double mu)
{
#pragma XLLEXPORT
	

	return gsl_cdf_exponential_P(x, mu);
}

static AddInX xai_cdf_exponential_Pinv(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_exponential_Pinv"), _T("GSL.DIST.EXPONENTIAL.INV"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the inverse cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("mu"), _T("is the mean of the exponential distribution"))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return exponential inverse cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_exponential_Pinv(double p, double mu)
{
#pragma XLLEXPORT
	

	return gsl_cdf_exponential_Pinv(p, mu);
}

XLL_TEST_BEGIN(xll_ran_exponential)

double eps = 1e-6;

//http://www.wolframalpha.com/input/?i=Table%5BPDF%5BExponentialDistribution%5B1%5D%2C+x%5D%2C%7Bx%2C+1%2C+4%2C+.1%7D%5D
double pdf[] = { 0.367879, 0.332871, 0.301194, 0.272532, 0.246597, 0.22313, 0.201897, 0.182684, 0.165299, 0.149569, 0.135335, 0.122456, 0.110803, 0.100259, 0.090718, 0.082085, 0.0742736, 0.0672055, 0.0608101, 0.0550232, 0.0497871, 0.0450492, 0.0407622, 0.0368832, 0.0333733, 0.0301974, 0.0273237, 0.0247235, 0.0223708, 0.0202419, 0.0183156 };
//http://www.wolframalpha.com/input/?i=Table%5BCDF%5BExponentialDistribution%5B1%5D%2C+x%5D%2C%7Bx%2C+1%2C+4%2C+.1%7D%5D
double cdf[] = { 0.632121, 0.667129, 0.698806, 0.727468, 0.753403, 0.77687, 0.798103, 0.817316, 0.834701, 0.850431, 0.864665, 0.877544, 0.889197, 0.899741, 0.909282, 0.917915, 0.925726, 0.932794, 0.93919, 0.944977, 0.950213, 0.954951, 0.959238, 0.963117, 0.966627, 0.969803, 0.972676, 0.975276, 0.977629, 0.979758, 0.981684 };

for (int i = 0; i < sizeof(pdf) / sizeof(*pdf); ++i) {
	double x = 1 + i*0.1;
	ensure(fabs(xll_ran_exponential_pdf(x, 1) - pdf[i]) < eps);
	ensure(fabs(xll_cdf_exponential_P(x, 1) - cdf[i]) < eps);
}

// http://www.wolframalpha.com/input/?i=Table%5BInverseCDF%5BExponentialDistribution%5B1%5D%2C+p%5D%2C%7Bp%2C+.1%2C+.9%2C+.1%7D%5D
double inv[] = { 0.105361, 0.223144, 0.356675, 0.510826, 0.693147, 0.916291, 1.20397, 1.60944, 2.30259 };
for (int i = 0; i < sizeof(inv) / sizeof(*inv); ++i) {
	double p = 0.1 + i*0.1;
	ensure(fabs(xll_cdf_exponential_Pinv(p, 1) - inv[i]) < 2 * 0.0001);
}

XLL_TEST_END(xll_ran_exponential)