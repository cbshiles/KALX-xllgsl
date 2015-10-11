// xll_ran_gumbel2.cpp - Gumbel type 2 variates, density, cumulative distribution, and inverse
// http://www.gnu.org/software/gsl/manual/html_node/The-Type_002d2-Gumbel-Distribution.html#The-Type_002d2-Gumbel-Distribution
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_gumbel2(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_gumbel2"), _T("GSL.RAN.GUMBEL2"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the parameter a. Default is 1"), 1.0)
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the parameter b. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Gumbel2 random deviates using a random number generator."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_gumbel2(HANDLEX rng, double a, double b)
{
#pragma XLLEXPORT
	doublex x;

	try {

		handle<gsl::rng> r(rng);

		x = gsl_ran_gumbel2(*r, a, b);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_ran_gumbel2_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_gumbel2_pdf"), _T("GSL.DIST.GUMBEL2.PDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the parameter a. Default is 1"), 1.0)
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the parameter b. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Gumbel2 probability density function."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_gumbel2_pdf(double x, double a, double b)
{
#pragma XLLEXPORT

	return gsl_ran_gumbel2_pdf(x, a, b);
}

static AddInX xai_cdf_gumbel2_P(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_gumbel2_P"), _T("GSL.DIST.GUMBEL2.CDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the parameter a. Default is 1"), 1.0)
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the parameter b. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Gumbel2 cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_gumbel2_P(double x, double a, double b)
{
#pragma XLLEXPORT

	return gsl_cdf_gumbel2_P(x, a, b);
}

static AddInX xai_cdf_gumbel2_Pinv(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_gumbel2_Pinv"), _T("GSL.DIST.GUMBEL2.INV"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the inverse cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the parameter a. Default is 1"), 1.0)
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the parameter b. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Gumbel2 inverse cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_gumbel2_Pinv(double p, double a, double b)
{
#pragma XLLEXPORT

	return gsl_cdf_gumbel2_Pinv(p, a, b);
}

static AddInX xai_cdf_gumbel2_Q(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_gumbel2_Q"), _T("GSL.DIST.GUMBEL2.QCDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the parameter a. Default is 1"), 1.0)
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the parameter b. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Gumbel2 cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_gumbel2_Q(double x, double a, double b)
{
#pragma XLLEXPORT

	return gsl_cdf_gumbel2_Q(x, a, b);
}

static AddInX xai_cdf_gumbel2_Qinv(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_gumbel2_Qinv"), _T("GSL.DIST.GUMBEL2.QINV"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the inverse cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the parameter a. Default is 1"), 1.0)
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the parameter b. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Gumbel2 Qinverse cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_gumbel2_Qinv(double p, double a, double b)
{
#pragma XLLEXPORT

	return gsl_cdf_gumbel2_Qinv(p, a, b);
}


XLL_TEST_BEGIN(xll_ran_gumbel2)

double eps = 1e-3;

// http://www.wolframalpha.com/input/?i=Table%5BPDF%5BFrechetDistribution%5B1%2C1%5D%2C+x%5D%2C%7Bx%2C+1%2C+3%2C+.1%7D%5D
// use the special case of type-2 gumbel distribution where b=1, so the distribution becomes Frechet.
double pdf[] = { 0, 0.00453999, 0.168449, 0.396378, 0.513031, 0.541341, 0.524654, 0.489084, 0.447664, 0.406411, 0.367879, 0.332967, 0.301804, 0.274183, 0.249766, 0.228185, 0.209086, 0.192148, 0.177084, 0.16365, 0.151633, 0.140849, 0.131144, 0.122383, 0.114451, 0.107251, 0.100697, 0.0947159, 0.0892439, 0.0842262, 0.0796146, 0.0753671, 0.0714468, 0.0678216, 0.0644627, 0.0613451, 0.0584464, 0.0557468, 0.0532286, 0.050876, 0.048675};
//http://www.wolframalpha.com/input/?i=Table%5BCDF%5BFrechetDistribution%5B1%2C1%5D%2C+x%5D%2C%7Bx%2C+0%2C+4%2C+.1%7D%5D
double cdf[] = { 0, 0.0000453999, 0.00673795, 0.035674, 0.082085, 0.135335, 0.188876, 0.239651, 0.286505, 0.329193, 0.367879, 0.40289, 0.434598, 0.463369, 0.489542, 0.513417, 0.535261, 0.555306, 0.573753, 0.590778, 0.606531, 0.621145, 0.634736, 0.647405, 0.659241, 0.67032, 0.680712, 0.690479, 0.699673, 0.708342, 0.716531, 0.724278, 0.731616, 0.738577, 0.745189, 0.751477, 0.757465, 0.763173, 0.768621, 0.773824, 0.778801};

for (int i = 0; i < sizeof(pdf) / sizeof(*pdf); ++i) {
	double x = i*0.1;
	ensure(fabs(xll_ran_gumbel2_pdf(x, 1, 1) - pdf[i]) < eps);
	ensure(fabs(xll_cdf_gumbel2_P(x, 1, 1) - cdf[i]) < eps);
	ensure(fabs(xll_cdf_gumbel2_Q(x, 1, 1) + cdf[i] - 1) < eps);
}

// http://www.wolframalpha.com/input/?i=Table%5BInverseCDF%5BFrechetDistribution%5B1%2C1%5D%2C+p%5D%2C%7Bp%2C+0.1%2C+0.9%2C+.1%7D%5D
double inv[] = { 0.434294, 0.621335, 0.830584, 1.09136, 1.4427, 1.95762, 2.80367, 4.48142, 9.49122};
for (int i = 0; i < sizeof(inv) / sizeof(*inv); ++i) {
	double p = 0.1 + i*0.1;
	ensure(fabs(xll_cdf_gumbel2_Pinv(p, 1, 1) - inv[i]) < 2 * eps);
	ensure(fabs(xll_cdf_gumbel2_Qinv(1-p, 1, 1) - inv[i]) < 2 * eps);
}

XLL_TEST_END(xll_ran_gumbel2)  