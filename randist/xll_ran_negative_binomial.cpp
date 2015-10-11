// gsl_ran_negative_binomial.cpp 
// http://www.gnu.org/software/gsl/manual/html_node/The-Negative-Binomial-Distribution.html

#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_negative_binomial(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_negative_binomial"), _T("GSL.RAN.NEGATIVE.BINOMIAL"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("p"), _T("is the probability of success. "))
	.Arg(XLL_DOUBLEX, _T("n"), _T("is the number of successes. "))
	.Volatile()
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Negative-binomial deviates using a random number generator."))
	.Documentation(R_(
		This function returns a random integer from the negative binomial distribution, the number of failures occurring before n successes in independent trials with probability p of success. The probability distribution for negative binomial variates is, 

		p[k] = {Gamma[n + k] over Gamma[k+1] Gamma[n] } p^n {1-p}^k

		Note that n is not required to be an integer. 
	))
);
double WINAPI xll_ran_negative_binomial(HANDLEX rng, double p, double n)
{
#pragma XLLEXPORT
	doublex x;

	try {

		handle<gsl::rng> r(rng);

		x = gsl_ran_negative_binomial(*r, p,n);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_ran_negative_binomial_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_negative_binomial_pdf"), _T("GSL.DIST.NEGATIVE.BINOMIAL.PDF"))
	.Arg(XLL_WORDX, _T("k"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("p"), _T("is the probability of success."))
	.Arg(XLL_DOUBLEX, _T("n"), _T("is the number of successes."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Negative-Binomial probability density function."))
	.Documentation(R_(
		This function computes the probability p(k) of obtaining k from a negative binomial distribution with parameters p and n, using the formula given above. 
	))
	);
double WINAPI xll_ran_negative_binomial_pdf(WORD k, double p, double n)
{
#pragma XLLEXPORT

	return gsl_ran_negative_binomial_pdf(k, p, n);
}

static AddInX xai_cdf_negative_binomial_P(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_negative_binomial_P"), _T("GSL.DIST.NEGATIVE.BINOMIAL.CDF"))
	.Arg(XLL_WORDX, _T("k"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("p"), _T("is the probability of success."))
	.Arg(XLL_DOUBLEX, _T("n"), _T("is the number of successes."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Negative-Binomial cumulative distribution function."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_negative_binomial_P(WORD k, double p, double n)
{
#pragma XLLEXPORT

	return gsl_cdf_negative_binomial_P(k, p, n);
}


/*!!! needs to be fixed
#ifdef _DEBUG
XLL_TEST_BEGIN(xll_ran_negative_binomial)

double eps = 1e-6;
// http://www.wolframalpha.com/input/?i=Table%5BPDF%5BNormalDistribution%5B0%2C1%5D%2C+x%5D%2C%7Bx%2C+-2%2C+2%2C+.1%7D%5D
double pdf[] = { 0.053991, 0.0656158, 0.0789502, 0.0940491, 0.110921, 0.129518, 0.149727, 0.171369, 0.194186, 0.217852, 0.241971, 0.266085, 0.289692, 0.312254, 0.333225, 0.352065, 0.36827, 0.381388, 0.391043, 0.396953, 0.398942, 0.396953, 0.391043, 0.381388, 0.36827, 0.352065, 0.333225, 0.312254, 0.289692, 0.266085, 0.241971, 0.217852, 0.194186, 0.171369, 0.149727, 0.129518, 0.110921, 0.0940491, 0.0789502, 0.0656158, 0.053991 };
// http://www.wolframalpha.com/input/?i=Table%5BCDF%5BNormalDistribution%5B0%2C1%5D%2C+x%5D%2C%7Bx%2C+-2%2C+2%2C+.1%7D%5D
double cdf[] = { 0.0227501, 0.0287166, 0.0359303, 0.0445655, 0.0547993, 0.0668072, 0.0807567, 0.0968005, 0.11507, 0.135666, 0.158655, 0.18406, 0.211855, 0.241964, 0.274253, 0.308538, 0.344578, 0.382089, 0.42074, 0.460172, 0.5, 0.539828, 0.57926, 0.617911, 0.655422, 0.691462, 0.725747, 0.758036, 0.788145, 0.81594, 0.841345, 0.864334, 0.88493, 0.9032, 0.919243, 0.933193, 0.945201, 0.955435, 0.96407, 0.971283, 0.97725 };

for (int i = 0; i < sizeof(pdf) / sizeof(*pdf); ++i) {
	double x = -2 + i*0.1;
	ensure(fabs(xll_ran_negative_binomial_pdf(x, 1) - pdf[i]) < eps);
	ensure(fabs(xll_cdf_nrgative_binomial_P(x, 1) - cdf[i]) < eps);
}

XLL_TEST_END(xll_ran_negative_binomial)
#endif // _DEBUG
*/
