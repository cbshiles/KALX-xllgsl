// xll_ran_chisq.cpp - Chi-squared distribution, density, cumulative distribution, and inverse
// http://www.gnu.org/software/gsl/manual/html_node/The-Chi_002dsquared-Distribution.html#The-Chi_002dsquared-Distribution
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_chisq(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_chisq"), _T("GSL.RAN.CHISQ"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("nu"), _T("is the degree of freedom of the Chi-squared."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Chi-squared random deviates using a random number generator."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_chisq(HANDLEX rng, double nu)
{
#pragma XLLEXPORT
	doublex x;

	try {
		if (nu == 0)
			nu = 1;

		handle<gsl::rng> r(rng);

		x = gsl_ran_chisq(*r, nu);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_ran_chisq_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_chisq_pdf"), _T("GSL.DIST.CHISQ.PDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("nu"), _T("is the degree of freedom of the Chi - squared."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Chi - squared random deviates using a random number generator."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_chisq_pdf(double x, double nu)
{
#pragma XLLEXPORT
	if (nu == 0)
		nu = 1;

	return gsl_ran_chisq_pdf(x, nu);
}

static AddInX xai_cdf_chisq_P(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_chisq_P"), _T("GSL.DIST.CHISQ.CDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("nu"), _T("is the degree of freedom of the Chi - squared."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Chi - squared random deviates using a random number generator."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_chisq_P(double x, double nu)
{
#pragma XLLEXPORT
	if (nu == 0)
		nu = 1;

	return gsl_cdf_chisq_P(x, nu);
}

static AddInX xai_cdf_chisq_Pinv(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_chisq_Pinv"), _T("GSL.DIST.CHISQ.INV"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the inverse cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("nu"), _T("is the degree of freedom of the Chi - squared."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Chi - squared random deviates using a random number generator."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_chisq_Pinv(double p, double nu)
{
#pragma XLLEXPORT
	if (nu == 0)
		nu = 1;

	return gsl_cdf_chisq_Pinv(p, nu);
}

XLL_TEST_BEGIN(xll_ran_chisq)

double eps = 1e-4;

// http://www.wolframalpha.com/input/?i=Table%5BPDF%5BChi-squared+Distribution%5B5%5D%2C+x%5D%2C%7Bx%2C+0%2C+2%2C+.1%7D%5D
double pdf[] = { 0, 0.00400013, 0.0107623, 0.0188073, 0.0275435, 0.0366159, 0.0457854, 0.0548824, 0.0637832, 0.0723969, 0.0806569, 0.0885148, 0.0959365, 0.102899, 0.109389, 0.1154, 0.12093, 0.125983, 0.130567, 0.134691, 0.138369 };
// http://www.wolframalpha.com/input/?i=Table%5BCDF%5BChi-squared+Distribution%5B5%5D%2C+x%5D%2C%7Bx%2C+0%2C+2%2C+.1%7D%5D
double cdf[] = { 0, 0.000162317, 0.000886139, 0.00235691, 0.00467041, 0.00787671, 0.0119968, 0.0170313, 0.0229667, 0.0297784, 0.0374342, 0.0458963, 0.0551226, 0.0650683, 0.0756867, 0.0869302, 0.0987507, 0.1111, 0.123932, 0.137198, 0.150855 };

for (int i = 0; i < sizeof(pdf) / sizeof(*pdf); ++i) {
	double x = 0 + i*0.1;
	ensure(fabs(xll_ran_chisq_pdf(x, 5) - pdf[i]) < eps);
	ensure(fabs(xll_cdf_chisq_P(x, 5) - cdf[i]) < eps);
}

// http://www.wolframalpha.com/input/?i=Table%5BInverseCDF%5BChi-squared+Distribution%5B1%5D%2C+p%5D%2C%7Bp%2C+.1%2C+.9%2C+.1%7D%5D
double inv[] = { 0.0157908, 0.0641848, 0.148472, 0.274996, 0.454936, 0.708326, 1.07419, 1.64237, 2.70554 };
for (int i = 0; i < sizeof(inv) / sizeof(*inv); ++i) {
	double p = 0.1 + i*0.1;
	ensure(fabs(xll_cdf_chisq_Pinv(p, 1) - inv[i]) < 2 * eps);
}

XLL_TEST_END(xll_ran_chisq)
