// xll_ran_gaussian.cpp - Gaussian variates, density, cumulative distribution, and inverse
// http://www.gnu.org/software/gsl/manual/html_node/The-Gaussian-Distribution.html#The-Gaussian-Distribution
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_pareto(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_pareto"), _T("GSL.RAN.PARETO"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the exponent the Pareto. Default is 0"), 0.0)
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the scale of the Pareto. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Pareto random deviates using a random number generator."))
	.Documentation(_T(""))
);
double WINAPI xll_ran_pareto(HANDLEX rng, double a, double b)
{
#pragma XLLEXPORT
	doublex x;

	try {
		if (b == 0)
			b = 1;

		handle<gsl::rng> r(rng);

		x = gsl_ran_pareto(*r, a, b);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_ran_pareto_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_pareto_pdf"), _T("GSL.DIST.PARETO.PDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the exponent of the Pareto. Default is 0."), 0.0)
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the scale of the Pareto. Default is 1."), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Pareto probability density function."))
	.Documentation(_T(""))
);
double WINAPI xll_ran_pareto_pdf(double x, double a, double b)
{
#pragma XLLEXPORT
	if (b == 0)
		b = 1;

	return gsl_ran_pareto_pdf(x, a, b);
}

static AddInX xai_cdf_pareto_P(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_pareto_P"), _T("GSL.DIST.PARETO.CDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the exponent of the Pareto. Default is 0."), 0.0)
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the scale of the Pareto. Default is 1."), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Pareto cumulative distribution function."))
	.Documentation(_T(""))
);
double WINAPI xll_cdf_pareto_P(double x, double a, double b)
{
#pragma XLLEXPORT
	if (b == 0)
		b = 1;

	return gsl_cdf_pareto_P(x, a, b);
}

static AddInX xai_cdf_pareto_Pinv(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_pareto_Pinv"), _T("GSL.DIST.PARETO.INV"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the inverse cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the exponent of the Pareto. Default is 0."), 0.0)
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the scale of the Pareto. Default is 1."), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Pareto inverse cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_pareto_Pinv(double p, double a, double b)
{
#pragma XLLEXPORT
	if (b == 0)
		b = 1;

	return gsl_cdf_pareto_Pinv(p, a, b);
}

XLL_TEST_BEGIN(xll_ran_pareto)

double eps = 1e-6;

// http://www.wolframalpha.com/input/?i=Table%5BPDF%5BParetoDistribution%5B.5%2C3%5D%2Cx%5D%2C%7Bx%2C+3%2C+7%2C+0.1%7D%5D
double pdf[] = { 0.00462963, 0.00406055, 0.00357628, 0.0031621, 0.00280618, 0.00249896, 0.00223265, 0.0020009, 0.00179844, 0.00162096, 0.00146484, 0.00132708, 0.00120513, 0.00109688, 0.00100051, 0.000914495, 0.000837529, 0.000768493, 0.000706425, 0.000650499, 0.0006, 0.000554307, 0.000512883, 0.000475256, 0.000441018, 0.000409808, 0.000381311, 0.000355248, 0.000331375, 0.000309473, 0.000289352, 0.000270839, 0.000253784, 0.00023805, 0.000223517, 0.000210077, 0.000197631, 0.000186094, 0.000175386, 0.000165438, 0.000156185 };
// http://www.wolframalpha.com/input/?i=Table%5BCDF%5BParetoDistribution%5B.5%2C3%5D%2Cx%5D%2C%7Bx%2C+3%2C+7%2C+0.1%7D%5D
double cdf[] = { 0.99537, 0.995804, 0.996185, 0.996522, 0.99682, 0.997085, 0.997321, 0.997532, 0.997722, 0.997893, 0.998047, 0.998186, 0.998313, 0.998428, 0.998533, 0.998628, 0.998716, 0.998796, 0.99887, 0.998938, 0.999, 0.999058, 0.999111, 0.99916, 0.999206, 0.999249, 0.999288, 0.999325, 0.999359, 0.999391, 0.999421, 0.999449, 0.999476, 0.9995, 0.999523, 0.999545, 0.999565, 0.999584, 0.999602, 0.999619, 0.999636 };

for (int i = 0; i < sizeof(pdf)/sizeof(*pdf); ++i) {
	double x = 3 + i*0.1;
	ensure (fabs(xll_ran_pareto_pdf(x, 3, 0.5) - pdf[i]) < eps);
	ensure (fabs(xll_cdf_pareto_P(x, 3, 0.5) - cdf[i]) < eps);
}

double eps0 = 1e-4;

// http://www.wolframalpha.com/input/?i=Table%5BInverseCDF%5BParetoDistribution%5B.5%2C3%5D%2C+p%5D%2C%7Bp%2C+.1%2C+.9%2C+.1%7D%5D
double inv[] = { 0.517872, 0.538609, 0.563124, 0.592816, 0.629961, 0.678604, 0.746901, 0.854988, 1.07722 };
for (int i = 0; i < sizeof(inv)/sizeof(*inv); ++i) {
	double p = 0.1 + i*0.1;
	ensure (fabs(xll_cdf_pareto_Pinv(p, 3, 0.5) - inv[i]) < 2*eps0);
}

XLL_TEST_END(xll_ran_pareto)