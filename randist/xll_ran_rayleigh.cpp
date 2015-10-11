// xll_ran_rayleigh.cpp - Rayleigh variates, density, cumulative distribution, and inverse
// http://www.gnu.org/software/gsl/manual/html_node/The-Rayleigh-Distribution.html#The-Rayleigh-Distribution
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_rayleigh(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_rayleigh"), _T("GSL.RAN.RAYLEIGH"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("sigma"), _T("is the sigma of the Rayleigh Distribution. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Rayleigh random deviates using a random number generator."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_rayleigh(HANDLEX rng, double sigma)
{
#pragma XLLEXPORT
	doublex x;

	try {
		if (sigma == 0)
			sigma = 1;

		handle<gsl::rng> r(rng);

		x = gsl_ran_rayleigh(*r, sigma);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_ran_rayleigh_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_rayleigh_pdf"), _T("GSL.DIST.RAYLEIGH.PDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("sigma"), _T("is the standard deviation of the Rayleigh Distribution. Default is 1."), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Rayleigh probability density function."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_rayleigh_pdf(double x, double sigma)
{
#pragma XLLEXPORT
	if (sigma == 0)
		sigma = 1;

	return gsl_ran_rayleigh_pdf(x, sigma);
}

static AddInX xai_cdf_rayleigh_P(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_rayleigh_P"), _T("GSL.DIST.RAYLEIGH.CDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("sigma"), _T("is the standard deviation of the Rayleigh Distribution. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Rayleigh cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_rayleigh_P(double x, double sigma)
{
#pragma XLLEXPORT
	if (sigma == 0)
		sigma = 1;

	return gsl_cdf_rayleigh_P(x, sigma);
}

static AddInX xai_cdf_rayleigh_Pinv(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_rayleigh_Pinv"), _T("GSL.DIST.RAYLEIGH.INV"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the inverse cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("sigma"), _T("is the standard deviation of the Rayleigh Distribution. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Rayleigh inverse cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_rayleigh_Pinv(double p, double sigma)
{
#pragma XLLEXPORT
	if (sigma == 0)
		sigma = 1;

	return gsl_cdf_rayleigh_Pinv(p, sigma);
}

XLL_TEST_BEGIN(xll_ran_rayleigh)

double eps = 1e-6;
//Query: "Table[PDF[RayleighDistribution[1], x],{x, 0, 5, .1}]"
// http://www.wolframalpha.com/input/?i=Table%5BPDF%5BRayleighDistribution%5B1%5D%2C+x%5D%2C%7Bx+%2C0%2C+5%2C+.1%7D%5D
double pdf[] = { 0, 0.0995012, 0.19604, 0.286799, 0.369247, 0.441248, 0.501162, 0.547893, 0.580919, 0.600279, 0.606531, 0.600682, 0.584103, 0.558425, 0.525436, 0.486979, 0.44486, 0.400768, 0.356218, 0.312501, 0.270671, 0.231526, 0.195628, 0.163312, 0.134723, 0.109842, 0.0885234, 0.0705278, 0.0555551, 0.0432703, 0.033327, 0.025385, 0.0191233, 0.0142489, 0.0105016, 0.00765622, 0.00552172, 0.00393964, 0.00278085, 0.00194203, 0.00134185, 0.000917358, 0.000620543, 0.000415352, 0.000275095, 0.000180294, 0.000116929, 0.0000750439, 0.0000476616, 0.0000299565, 0.0000186333 };
//Query: "Table[CDF[RayleighDistribution[1], x],{x ,0, 5, .1}]"
// http://www.wolframalpha.com/input/?i=Table%5BCDF%5BRayleighDistribution%5B1%5D%2C+x%5D%2C%7Bx+%2C0%2C+5%2C+.1%7D%5D
double cdf[] = { 0, 0.00498752, 0.0198013, 0.0440025, 0.0768837, 0.117503, 0.16473, 0.217295, 0.273851, 0.333023, 0.393469, 0.453926, 0.513248, 0.570443, 0.624689, 0.675348, 0.721963, 0.764254, 0.802101, 0.835526, 0.864665, 0.889749, 0.911078, 0.928995, 0.943865, 0.956063, 0.965953, 0.973879, 0.980159, 0.985079, 0.988891, 0.991811, 0.994024, 0.995682, 0.996911, 0.997813, 0.998466, 0.998935, 0.999268, 0.999502, 0.999665, 0.999776, 0.999852, 0.999903, 0.999937, 0.99996, 0.999975, 0.999984, 0.99999, 0.999994, 0.999996 };

for (int i = 0; i < sizeof(pdf) / sizeof(*pdf); ++i) {
	double x = 0 + i*0.1;
	ensure(fabs(xll_ran_rayleigh_pdf(x, 1) - pdf[i]) < eps);
	ensure(fabs(xll_cdf_rayleigh_P(x, 1) - cdf[i]) < eps);
}

eps = 1e-5;
//Epsilon value needs to be changed since some data provided by Wolfram Alpha only have precision of 1e-5.
//Query: "Table[InverseCDF[RayleighDistribution[1], p],{p , .1, .9, .1}]"
// http://www.wolframalpha.com/input/?i=Table%5BInverseCDF%5BRayleighDistribution%5B1%5D%2C+p%5D%2C%7Bp+%2C+.1%2C+.9%2C+.1%7D%5D
double inv[] = { 0.459044, 0.668047, 0.8446, 1.01077, 1.17741, 1.35373, 1.55176, 1.79412, 2.14597 };
for (int i = 0; i < sizeof(inv) / sizeof(*inv); ++i) {
	double p = 0.1 + i*0.1;
	ensure(fabs(xll_cdf_rayleigh_Pinv(p, 1) - inv[i]) < 2 * eps);
}

XLL_TEST_END(xll_ran_rayleigh)