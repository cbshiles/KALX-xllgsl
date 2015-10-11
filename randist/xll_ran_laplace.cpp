// xll_ran_laplace.cpp - Laplace variates, density, cumulative distribution, and inverse
// http://www.gnu.org/software/gsl/manual/html_node/The-Laplace-Distribution.html#The-Laplace-Distribution
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_laplace(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_laplace"), _T("GSL.RAN.LAPLACE"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the width of the Laplace. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Laplace random deviates using a random number generator."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_laplace(HANDLEX rng, double a)
{
#pragma XLLEXPORT
	doublex x;

	try {
		if (a == 0)
			a = 1;

		handle<gsl::rng> r(rng);

		x = gsl_ran_laplace(*r, a);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_ran_laplace_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_laplace_pdf"), _T("GSL.DIST.LAPLACE.PDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the width of the Laplace. Default is 1."), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Laplace probability density function."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_laplace_pdf(double x, double a)
{
#pragma XLLEXPORT
	if (a == 0)
		a = 1;

	return gsl_ran_laplace_pdf(x, a);
}

static AddInX xai_cdf_laplace_P(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_laplace_P"), _T("GSL.DIST.LAPLACE.CDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the width of the Laplace. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Laplace cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_laplace_P(double x, double a)
{
#pragma XLLEXPORT
	if (a == 0)
		a = 1;

	return gsl_cdf_laplace_P(x, a);
}

static AddInX xai_cdf_laplace_Pinv(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_laplace_Pinv"), _T("GSL.DIST.LAPLACE.INV"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the inverse cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the width of the Laplace. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Laplace inverse cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_laplace_Pinv(double p, double a)
{
#pragma XLLEXPORT
	if (a == 0)
		a = 1;

	return gsl_cdf_laplace_Pinv(p, a);
}

XLL_TEST_BEGIN(xll_ran_laplace)

double eps = 1e-4;

// http://www.wolframalpha.com/input/?i=Table%5BPDF%5BLaplaceDistribution%5B0%2C1%5D%2C+x%5D%2C%7Bx%2C+-2%2C+2%2C+.1%7D%5D
double pdf[] = { 0.0676676, 0.0747843, 0.0826494, 0.0913418, 0.100948, 0.111565, 0.123298, 0.136266, 0.150597, 0.166436, 0.18394, 0.203285, 0.224664, 0.248293, 0.274406, 0.303265, 0.33516, 0.370409, 0.409365, 0.452419, 0.5, 0.452419, 0.409365, 0.370409, 0.33516, 0.303265, 0.274406, 0.248293, 0.224664, 0.203285, 0.18394, 0.166436, 0.150597, 0.136266, 0.123298, 0.111565, 0.100948, 0.0913418, 0.0826494, 0.0747843, 0.0676676 };
// http://www.wolframalpha.com/input/?i=Table%5BCDF%5BLaplaceDistribution%5B0%2C1%5D%2C+x%5D%2C%7Bx%2C+-2%2C+2%2C+.1%7D%5D
double cdf[] = { 0.0676676, 0.0747843, 0.0826494, 0.0913418, 0.100948, 0.111565, 0.123298, 0.136266, 0.150597, 0.166436, 0.18394, 0.203285, 0.224664, 0.248293, 0.274406, 0.303265, 0.33516, 0.370409, 0.409365, 0.452419, 0.5, 0.547581, 0.590635, 0.629591, 0.66484, 0.696735, 0.725594, 0.751707, 0.775336, 0.796715, 0.81606, 0.833564, 0.849403, 0.863734, 0.876702, 0.888435, 0.899052, 0.908658, 0.917351, 0.925216, 0.932332 };

for (int i = 0; i < sizeof(pdf) / sizeof(*pdf); ++i) {
	double x = -2 + i*0.1;
	ensure(fabs(xll_ran_laplace_pdf(x, 1) - pdf[i]) < eps);
	ensure(fabs(xll_cdf_laplace_P(x, 1) - cdf[i]) < eps);
}

// http://www.wolframalpha.com/input/?i=Table%5BInverseCDF%5BLaplaceDistribution%5B0%2C1%5D%2C+p%5D%2C%7Bp%2C+.1%2C+.9%2C+.1%7D%5D
double inv[] = { -1.60944, -0.916291, -0.510826, -0.223144, 0, 0.223144, 0.510826, 0.916291, 1.60944 };
for (int i = 0; i < sizeof(inv) / sizeof(*inv); ++i) {
	double p = 0.1 + i*0.1;
	ensure(fabs(xll_cdf_laplace_Pinv(p, 1) - inv[i]) < 2 * eps);
}

XLL_TEST_END(xll_ran_laplace)