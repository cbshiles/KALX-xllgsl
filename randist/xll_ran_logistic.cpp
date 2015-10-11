#include "../xll_rng.h"
#include "../xll_randist.h"
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_logistic(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_logistic"), _T("GSL.RAN.LOGISTIC"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the scale parameter of logistic. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return logistic random deviates using a random number generator."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_logistic(HANDLEX rng, double a)
{
#pragma XLLEXPORT
	doublex x;

	try {
		if (a == 0)
			a = 1;

		handle<gsl::rng> r(rng);

		x = gsl_ran_logistic(*r, a);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_ran_logistic_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_logistic_pdf"), _T("GSL.DIST.LOGISTIC.PDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the scale parameter of logistic. Default is 1."), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return logistic probability density function."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_logistic_pdf(double x, double a)
{
#pragma XLLEXPORT
	if (a == 0)
		a = 1;

	return gsl_ran_logistic_pdf(x, a);
}

static AddInX xai_cdf_logistic_P(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_logistic_P"), _T("GSL.DIST.LOGISTIC.CDF.P"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the scale parameter of the logistic. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return logistic cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_logistic_P(double x, double a)
{
#pragma XLLEXPORT
	if (a == 0)
		a = 1;

	return gsl_cdf_logistic_P(x, a);
}

static AddInX xai_cdf_logistic_Q(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_logistic_Q"), _T("GSL.DIST.LOGISTIC.CDF.Q"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the scale parameter of the logistic. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return logistic cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_logistic_Q(double x, double a)
{
#pragma XLLEXPORT
	if (a == 0)
		a = 1;

	return gsl_cdf_logistic_Q(x, a);
}

static AddInX xai_cdf_logistic_Pinv(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_logistic_Pinv"), _T("GSL.DIST.LOGISTIC.INV.P"))
	.Arg(XLL_HANDLEX, _T("p"), _T("is the value at which to calculate the inverse cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the scale parameter of the logistic. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return logistic inverse cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_logistic_Pinv(double p, double a)
{
#pragma XLLEXPORT
	if (a == 0)
		a = 1;

	return gsl_cdf_logistic_Pinv(p, a);
}

static AddInX xai_cdf_logistic_Qinv(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_logistic_Qinv"), _T("GSL.DIST.LOGISTIC.INV.Q"))
	.Arg(XLL_HANDLEX, _T("q"), _T("is the value at which to calculate the inverse cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("a"), _T("is the scale parameter of the logistic. Default is 1"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return logistic inverse cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_logistic_Qinv(double q, double a)
{
#pragma XLLEXPORT
	if (a == 0)
		a = 1;

	return gsl_cdf_logistic_Qinv(q, a);
}


XLL_TEST_BEGIN(xll_ran_logistic)

double eps = 1e-4;

// http://www.wolframalpha.com/input/?i=Table%5BPDF%5BLogisticDistribution%5B0%2C1%5D%2C+x%5D%2C%7Bx%2C+-2%2C+2%2C+.1%7D%5D
double pdf[] = { 0.104994, 0.11318, 0.121729, 0.130606, 0.139764, 0.149146, 0.158685, 0.168298, 0.177894, 0.18737, 0.196612, 0.2055, 0.21391, 0.221713, 0.228784, 0.235004, 0.240261, 0.244458, 0.247517, 0.249376, 0.25, 0.249376, 0.247517, 0.244458, 0.240261, 0.235004, 0.228784, 0.221713, 0.21391, 0.2055, 0.196612, 0.18737, 0.177894, 0.168298, 0.158685, 0.149146, 0.139764, 0.130606, 0.121729, 0.11318, 0.104994 };
// http://www.wolframalpha.com/input/?i=Table%5BCDF%5BLogisticDistribution%5B0%2C1%5D%2C+x%5D%2C%7Bx%2C+-2%2C+2%2C+.1%7D%5Ddouble 
double cdf[] = { 0.119203, 0.130108, 0.141851, 0.154465, 0.167982, 0.182426, 0.197816, 0.214165, 0.231475, 0.24974, 0.268941, 0.28905, 0.310026, 0.331812, 0.354344, 0.377541, 0.401312, 0.425557, 0.450166, 0.475021, 0.5, 0.524979, 0.549834, 0.574443, 0.598688, 0.622459, 0.645656, 0.668188, 0.689974, 0.71095, 0.731059, 0.75026, 0.768525, 0.785835, 0.802184, 0.817574, 0.832018, 0.845535, 0.858149, 0.869892, 0.880797 };
// http://www.wolframalpha.com/input/?i=Table%5BCDF%5BLogisticDistribution%5B0%2C1%5D%2C+x%5D%2C%7Bx%2C+-2%2C+2%2C+.1%7D%5Ddouble 
double qcdf[] = { 0.119203, 0.130108, 0.141851, 0.154465, 0.167982, 0.182426, 0.197816, 0.214165, 0.231475, 0.24974, 0.268941, 0.28905, 0.310026, 0.331812, 0.354344, 0.377541, 0.401312, 0.425557, 0.450166, 0.475021, 0.5, 0.524979, 0.549834, 0.574443, 0.598688, 0.622459, 0.645656, 0.668188, 0.689974, 0.71095, 0.731059, 0.75026, 0.768525, 0.785835, 0.802184, 0.817574, 0.832018, 0.845535, 0.858149, 0.869892, 0.880797 };

for (int i = 0; i < sizeof(pdf) / sizeof(*pdf); ++i) {
	double x = -2 + i*0.1;
	ensure(fabs(xll_ran_logistic_pdf(x, 1) - pdf[i]) < eps);
	ensure(fabs(xll_cdf_logistic_P(x, 1) - cdf[i]) < eps);
	ensure(fabs(xll_cdf_logistic_Q(x, 1) + qcdf[i] - 1) < eps);
}

// http://www.wolframalpha.com/input/?i=Table%5BInverseCDF%5BNormalDistribution%5B0%2C1%5D%2C+p%5D%2C%7Bp%2C+.1%2C+.9%2C+.1%7D%5D
double Pinv[] = { -2.19722, -1.38629, -0.847298, -0.405465, 0, 0.405465, 0.847298, 1.38629, 2.19722 };
// http://www.wolframalpha.com/input/?i=Table%5BInverseCDF%5BNormalDistribution%5B0%2C1%5D%2C+p%5D%2C%7Bp%2C+.1%2C+.9%2C+.1%7D%5D
double Qinv[] = { -2.19722, -1.38629, -0.847298, -0.405465, 0, 0.405465, 0.847298, 1.38629, 2.19722 };

for (int i = 0; i < sizeof(Pinv) / sizeof(*Pinv); ++i) {
	double p = 0.1 + i*0.1;
	ensure(fabs(xll_cdf_logistic_Pinv(p, 1) - Pinv[i]) < 2 * eps);
	ensure(fabs(xll_cdf_logistic_Qinv(p, 1) + Qinv[i]) < 2 * eps);
}

XLL_TEST_END(xll_ran_logistic)