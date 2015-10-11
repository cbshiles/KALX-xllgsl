
#include "../xll_rng.h"
#include "../xll_randist.h"
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_logarithmic(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_logarithmic"), _T("GSL.RAN.LOGARITHMIC"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("p"), _T("is the parameter p."))
	.Volatile()
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Logarithmic random deviates using a random number generator."))
	.Documentation(_T(""))
	);
unsigned int WINAPI xll_ran_logarithmic(HANDLEX rng, double p)
{
#pragma XLLEXPORT
	unsigned int k = 1;

	try {
		if (p < 0) {
			p = 0;
		}
		if (p > 1) {
			p = 1;
		}
		handle<gsl::rng> r(rng);

		k = gsl_ran_logarithmic(*r, p);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return k;
}

static AddInX xai_ran_logarithmic_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_logarithmic_pdf"), _T("GSL.DIST.LOGARITHMIC.PDF"))
	.Arg(XLL_USHORTX, _T("k"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("p"), _T("is the parameter p."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Logarithmic probability density function."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_logarithmic_pdf(unsigned int k, double p)
{
#pragma XLLEXPORT

	if (p < 0) {
		p = 0;
	}
	if (p > 1) {
		p = 1;
	}

	return gsl_ran_logarithmic_pdf(k, p);
}
/*
XLL_TEST_BEGIN(xll_ran_logarithmic)

double eps = 1e1;

double pdf[] = { 0.053991, 0.0656158, 0.0789502, 0.0940491, 0.110921, 0.129518, 0.149727, 0.171369, 0.194186, 0.217852, 0.241971, 0.266085, 0.289692, 0.312254, 0.333225, 0.352065, 0.36827, 0.381388, 0.391043, 0.396953, 0.398942, 0.396953, 0.391043, 0.381388, 0.36827, 0.352065, 0.333225, 0.312254, 0.289692, 0.266085, 0.241971, 0.217852, 0.194186, 0.171369, 0.149727, 0.129518, 0.110921, 0.0940491, 0.0789502, 0.0656158, 0.053991 };
double cdf[] = { 0.0227501, 0.0287166, 0.0359303, 0.0445655, 0.0547993, 0.0668072, 0.0807567, 0.0968005, 0.11507, 0.135666, 0.158655, 0.18406, 0.211855, 0.241964, 0.274253, 0.308538, 0.344578, 0.382089, 0.42074, 0.460172, 0.5, 0.539828, 0.57926, 0.617911, 0.655422, 0.691462, 0.725747, 0.758036, 0.788145, 0.81594, 0.841345, 0.864334, 0.88493, 0.9032, 0.919243, 0.933193, 0.945201, 0.955435, 0.96407, 0.971283, 0.97725 };

for (int i = 0; i < sizeof(pdf) / sizeof(*pdf); i++) {
	int k = 1 + i;
	ensure(fabs(xll_ran_logarithmic_pdf(k, 1) - pdf[i]) < eps);
}

XLL_TEST_END(xll_ran_logarithmic)
*/