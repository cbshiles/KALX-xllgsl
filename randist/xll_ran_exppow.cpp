// xll_ran_exppow.cpp - ExponentialPower variates, density, and cumulative distribution
// http://www.gnu.org/software/gsl/manual/html_node/The-Exponential-Power-Distribution.html#The-Exponential-Power-Distribution
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_exppow(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_exppow"), _T("GSL.RAN.EXPPOW"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the scale parameter of the Exppow. Default is 1"), 1.0)
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the exponent of the Exppow. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Exponential Power random deviates using a random number generator."))
	.Documentation(_T(""))
);
double WINAPI xll_ran_exppow(HANDLEX rng, double a, double b)
{
#pragma XLLEXPORT
	doublex x;

	try {

		handle<gsl::rng> r(rng);

		x = gsl_ran_exppow(*r, a, b);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_ran_exppow_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_exppow_pdf"), _T("GSL.DIST.EXPPOW.PDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the scale parameter of the Exppow. Default is 1."), 1.0)
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the exponent of the Exppow. Default is 1."), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Exponential Power probability density function."))
	.Documentation(_T(""))
);
double WINAPI xll_ran_exppow_pdf(double x, double a, double b)
{
#pragma XLLEXPORT
	

	return gsl_ran_exppow_pdf(x, a, b);
}

static AddInX xai_cdf_exppow_P(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_exppow_P"), _T("GSL.DIST.EXPPOW.CDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the scale parameter of the Exppow. Default is 1"), 1.0)
	.Arg(XLL_DOUBLEX, _T("b"), _T("is the exponent of the Exppow. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Exponential Power cumulative distribution function."))
	.Documentation(_T(""))
);
double WINAPI xll_cdf_exppow_P(double x, double a, double b)
{
#pragma XLLEXPORT


	return gsl_cdf_exppow_P(x, a, b);
}




XLL_TEST_BEGIN(xll_ran_exppow)

double eps = 1e-4;

//http://www.wolframalpha.com/input/?i=TABLE%5BPDF%5BExponentialPowerDistribution%5B1%2C0%2C1%5D%2C+x%5D%2C%7Bx%2C-2.2%2C6.2%2C.5%7D%5D
double pdf[] = {0.0554016, 0.0913418, 0.150597, 0.248293, 0.409365, 0.370409, 0.224664, 0.136266, 0.0826494, 0.0501294, 0.030405, 0.0184416, 0.0111854, 0.00678428, 0.00411487, 0.0024958, 0.00151378};
//http://www.wolframalpha.com/input/?i=TABLE%5BCDF%5BExponentialPowerDistribution%5B1%2C0%2C1%5D%2C+x%5D%2C%7Bx%2C-2.2%2C6.2%2C.5%7D%5D
double cdf[] = {0.0554016, 0.0913418, 0.150597, 0.248293, 0.409365, 0.629591, 0.775336, 0.863734, 0.917351, 0.949871, 0.969595, 0.981558, 0.988815, 0.993216, 0.995885, 0.997504, 0.998486};

for (int i = 0; i < sizeof(pdf)/sizeof(*pdf); ++i) {
	double x = -2.2 + i*0.5;
	ensure (fabs(xll_ran_exppow_pdf(x, 1, 1) - pdf[i]) < eps);
	ensure (fabs(xll_cdf_exppow_P(x, 1, 1) - cdf[i]) < eps);
	
}

XLL_TEST_END(xll_ran_exppow)