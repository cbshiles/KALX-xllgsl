// xll_ran_fdist.cpp - F-distribution density, cumulative distribution, and inverse
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_fdist(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_fdist"), _T("GSL.RAN.FDIST"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("d_1"), _T("is the first parameter of the F-distribution"), 1.0)
	.Arg(XLL_DOUBLEX, _T("d_2"), _T("is the second parameter of the F-distribution"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return F-distribution random deviates using a random number generator."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_fdist(HANDLEX rng, double d_1, double d_2)
{
#pragma XLLEXPORT
	doublex x;

	try {
		if (d_1 <= 0)
			d_1 = 1;
		if (d_2 <= 0)
			d_2 = 1;
		handle<gsl::rng> r(rng);

		x = gsl_ran_fdist(*r, d_1, d_2);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}


static AddInX xai_ran_fdist_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_fdist_pdf"), _T("GSL.DIST.FDIST.PDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("d_1"), _T("is the first parameter of the F-distribution"), 1.0)
	.Arg(XLL_DOUBLEX, _T("d_2"), _T("is the second parameter of the F-distribution"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return F-distribution probability density function."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_fdist_pdf(double x, double d_1, double d_2)
{
#pragma XLLEXPORT
	if (d_1 <= 0)
		d_1 = 1;
	if (d_2 <= 0)
		d_2 = 1;
	return gsl_ran_fdist_pdf(x, d_1, d_2);
}

static AddInX xai_cdf_fdist_P(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_fdist_P"), _T("GSL.DIST.FDIST.CDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("d_1"), _T("is the first parameter of the F-distribution"), 1.0)
	.Arg(XLL_DOUBLEX, _T("d_2"), _T("is the second parameter of the F-distribution"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return F-distribution cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_fdist_P(double x, double d_1, double d_2)
{
#pragma XLLEXPORT
	if (d_1 <= 0)
		d_1 = 1;
	if (d_2 <= 0)
		d_2 = 1;
	return gsl_cdf_fdist_P(x, d_1, d_2);
}

static AddInX xai_cdf_fdist_Pinv(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_fdist_Pinv"), _T("GSL.DIST.FDIST.INV"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the inverse cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("d_1"), _T("is the first parameter of the F-distribution"), 1.0)
	.Arg(XLL_DOUBLEX, _T("d_2"), _T("is the second parameter of the F-distribution"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return F-distribution inverse cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_fdist_Pinv(double p, double d_1, double d_2)
{
#pragma XLLEXPORT
	if (d_1 <= 0)
		d_1 = 1;
	if (d_2 <= 0)
		d_2 = 1;
	return gsl_cdf_fdist_Pinv(p, d_1, d_2);
}

XLL_TEST_BEGIN(xll_ran_fdist)

double eps = 1e-6;

double pdf[] = { 0.91507658, 0.59313545, 0.44703976, 0.35949437, 0.30010544, 0.25683519, 0.22379593, 0.19771182, 0.17659373, 0.15915494, 0.14452218, 0.13207993, 0.12138097, 0.11209206, 0.10395957, 0.09678695, 0.09041946, 0.08473364, 0.07962975, 0.07502636 };
double cdf[] = { 0.1949822, 0.2677205, 0.3190057, 0.3590170, 0.3918266, 0.4195694, 0.4435320, 0.4645591, 0.4832391, 0.5000000, 0.5151633, 0.5289773, 0.5416373, 0.5533004, 0.5640942, 0.5741242, 0.5834784, 0.5922308, 0.6004445, 0.6081734 };
for (int i = 0; i < sizeof(pdf) / sizeof(*pdf); ++i) {
	double x = 0.1 + i*0.1;
	ensure(fabs(xll_ran_fdist_pdf(x, 1, 1) - pdf[i]) < eps);
	ensure(fabs(xll_cdf_fdist_P(x, 1, 1) - cdf[i]) < eps);
}

double inv[] = { 0.02508563,  0.10557281,  0.25961618,  0.52786405,  1.00000000,  1.89442719,  3.85184000,  9.47213595, 39.86345819 };
for (int i = 0; i < sizeof(inv) / sizeof(*inv); ++i) {
	double p = 0.1 + i*0.1;
	ensure(fabs(xll_cdf_fdist_Pinv(p, 1, 1) - inv[i]) < 2 * eps);
}

XLL_TEST_END(xll_ran_fdist)