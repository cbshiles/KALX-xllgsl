//Shuran Zhang (sz2535)
//MATH G4074
//hw3

#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_pascal(
	FunctionX(XLL_USHORTX, _T("?xll_ran_pascal"), _T("GSL.RAN.PASCAL"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("p"), _T("is the probability of success. It is between 0 and 1."))
	.Arg(XLL_USHORTX, _T("n"), _T("is the number of trial. It is a positve integer."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Pascal random deviates using a random number generator."))
	.Documentation(_T(""))
	);
unsigned int WINAPI xll_ran_pascal(HANDLEX rng, double p, unsigned int n)
{
#pragma XLLEXPORT
	unsigned int x;

	handle<gsl::rng> r(rng);
	x = gsl_ran_pascal(*r, p, n);

	return x;
}

static AddInX xai_ran_pascal_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_pascal_pdf"), _T("GSL.DIST.PASCAL.PDF"))
	.Arg(XLL_USHORTX, _T("x"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("p"), _T("is the probability of success. It is between 0 and 1."))
	.Arg(XLL_USHORTX, _T("n"), _T("is the number of trial. It is a positve integer."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Pascal probability density function."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_pascal_pdf(unsigned int x, double p, unsigned int n)
{
#pragma XLLEXPORT

	return gsl_ran_pascal_pdf(x-n, p, n);
}

static AddInX xai_cdf_pascal_P(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_pascal_P"), _T("GSL.DIST.PASCAL.CDF"))
	.Arg(XLL_USHORTX, _T("x"), _T("is the value at which to calculate the cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("p"), _T("is the probability of success. It is between 0 and 1."))
	.Arg(XLL_USHORTX, _T("n"), _T("is the number of trial. It is a positve integer."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Pascal cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_pascal_P(unsigned int x, double p, unsigned int n)
{
#pragma XLLEXPORT


	return gsl_cdf_pascal_P(x-n, p, n);
}


XLL_TEST_BEGIN(xll_ran_pascal)

double eps = 1e-6;


double pdf[] = { 0.0163238, 0.0244856, 0.0335803, 0.0428149, 0.0513779, 0.0585708, 0.0638954, 0.0670902, 0.0681223, 0.0671491, 0.0644632, 0.0604342, 0.0554573, 0.0499116, 0.0441323, 0.0383951, 0.0329101, 0.027824, 0.023227, 0.0191623, 0.0156364 };

double cdf[] = { 0.0338333, 0.0583189, 0.0918993, 0.134714, 0.186092, 0.244663, 0.308558, 0.375648, 0.443771, 0.51092, 0.575383, 0.635817, 0.691275, 0.741186, 0.785318, 0.823714, 0.856624, 0.884448, 0.907675, 0.926837, 0.942473 };

for (int i = 0; i < sizeof(pdf) / sizeof(*pdf); ++i) {
	int x = 15 + i;
	ensure(fabs(xll_ran_pascal_pdf(x, 0.4, 10) - pdf[i]) < eps);
	ensure(fabs(xll_cdf_pascal_P(x, 0.4, 10) - cdf[i]) < eps);
}

XLL_TEST_END(xll_ran_pascal)