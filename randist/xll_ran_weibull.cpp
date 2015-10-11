// xll_ran_weibull.cpp - Weibull variates, density, cumulative distribution, and inverse
// http://www.gnu.org/software/gsl/manual/html_node/The-Weibull-Distribution.html \#The-Weibull-Distribution#The-Gaussian-Distribution
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_weibull(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_weibull"), _T("GSL.RAN.WEIBULL"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is a scale"))
	.Arg(XLL_DOUBLEX,_T("b"),_T("is a exponent"))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return weilbull random deviates using a random number generator."))
	.Documentation(_T(""))
	);

double WINAPI xll_ran_weibull(HANDLEX rng, double a, double b)
{
#pragma XLLEXPORT
	doublex x;

	try {
		handle<gsl::rng> r(rng);

		x = gsl_ran_weibull(*r, a, b);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_ran_weibull_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_weibull_pdf"), _T("GSL.DIST.WEIBULL.PDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is a scale"))
	.Arg(XLL_DOUBLEX, _T("b"), _T("is a exponent"))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Weibull probability density function."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_weibull_pdf(double x, double a, double b)
{
#pragma XLLEXPORT

	return gsl_ran_weibull_pdf(x, a, b);
}

static AddInX xai_cdf_weibull_P(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_weibull_P"), _T("GSL.DIST.WEIBULL.CDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is a scale"))
	.Arg(XLL_DOUBLEX, _T("b"), _T("is a exponent"))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Weilbull cumulative distribution function P(x)."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_weibull_P(double x, double a, double b)
{
#pragma XLLEXPORT
	return gsl_cdf_weibull_P(x, a,b);
}

static AddInX xai_cdf_weibull_Pinv(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_gaussian_Pinv"), _T("GSL.DIST.WEIBULL.INV"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the inverse cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is a scale"))
	.Arg(XLL_DOUBLEX, _T("b"), _T("is a exponent"))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Weibull P inverse cumulative distribution function."))
	.Documentation(_T(""))
);
double WINAPI xll_cdf_weibull_Pinv(double p, double a, double b)
{
#pragma XLLEXPORT

	return gsl_cdf_weibull_Pinv(p, a, b);
}

/*!!! this needs to be fixed
XLL_TEST_BEGIN(xll_ran_weibull)

double eps = 1e-6;

// http://www.wolframalpha.com/input/?i=Table%5BPDF%5BWeibullDistribution%5B5%2C5%5D%2C+p%5D%2C%7Bp%2C+1%2C+5+%2C+.1%7D%5D
double pdf[] = { 0.00159949, 0.00234135, 0.00331512, 0.00456433, 0.00613599, 0.00808034, 0.0104506, 0.0133028, 0.0166949, 0.0206868, 0.0253392, 0.0307129, 0.0368679, 0.0438618, 0.0517486, 0.0605771, 0.0703884, 0.0812145, 0.0930752, 0.105976, 0.119904, 0.134828, 0.150691, 0.167412, 0.184881, 0.202955, 0.221461, 0.240191, 0.258903, 0.277326, 0.295155, 0.312065, 0.32771, 0.341735, 0.353785, 0.363516, 0.370609, 0.374784, 0.375814, 0.373539, 0.367879 };
// http://www.wolframalpha.com/input/?i=Table%5BCDF%5BWeibullDistribution%5B5%2C5%5D%2C+p%5D%2C%7Bp%2C+1%2C+5+%2C+.1%7D%5D
double cdf[] = { 0.000319949, 0.00051523, 0.000795945, 0.00118743, 0.00171956, 0.00242705, 0.00334982, 0.00453324, 0.00602837, 0.00789221, 0.0101877, 0.0129841, 0.0163564, 0.0203856, 0.0251585, 0.0307668, 0.0373067, 0.0448783, 0.0535841, 0.063528, 0.0748136, 0.0875421, 0.10181, 0.117709, 0.135318, 0.154705, 0.175923, 0.199005, 0.223961, 0.250776, 0.279406, 0.309777, 0.341777, 0.375265, 0.410059, 0.445944, 0.482674, 0.519969, 0.557526, 0.595021, 0.632121 };
for (int i = 0; i < sizeof(pdf) / sizeof(*pdf); ++i) {
	double x = 1 + i*0.1;
	ensure(fabs(xll_ran_weibull_pdf(x, 5,5) - pdf[i]) < eps);
	ensure(fabs(xll_cdf_weibull_P(x, 5, 5) - cdf[i]) < eps);
}

// http://www.wolframalpha.com/input/?i=Table%5BInverseCDF%5BWeibullDistribution%5B5%2C5%5D%2C+p%5D%2C%7Bp%2C+0.1%2C+0.9+%2C+.1%7D%5D
double inv[] = { 3.18791, 3.70414, 4.06841, 4.37144, 4.6466, 4.91334, 5.18912, 5.49927, 5.90763 };
for (int i = 0; i < sizeof(inv) / sizeof(*inv); ++i) {
	double p = 0.1 + i*0.1;
	ensure(fabs(xll_cdf_weibull_Pinv(p,5,5) - 1+ inv[i]) < 2 * eps);
}

XLL_TEST_END(xll_ran_weibull)
*/