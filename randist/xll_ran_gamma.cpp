/*File Name: xll_ran_gamma.cpp 
* Functions: Implement EXCEL third party ADD-IN.
*	The-Gamma-Distribution: Gamma instance value, density, cumulative distribution, 
*	and inverse cumulative distribution 
*	http://www.gnu.org/software/gsl/manual/html_node/The-Gamma-Distribution.html
* Editor: Qiang Ren
* UNI:qr2118
* Last Edit: 28 Sep. 2015
*/

#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_gamma(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_gamma"), _T("GSL.RAN.GAMMA"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("k"), _T("shape parameter of Gamma distribution, should be above zero, default value is 1.0"), 1.0)
	.Arg(XLL_DOUBLEX, _T("theta"), _T("scale parameter of Gamma distribution, should be above zero, default value is 1.0"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return instance of Gamma distribution using a random number generator."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_gamma(HANDLEX rng, double k, double theta)
{
#pragma XLLEXPORT
	doublex x;

	try {
		if (k <= 0)
			k = 1;
		if (theta <= 0)
			theta = 1;
		handle<gsl::rng> r(rng);

		x = gsl_ran_gamma(*r, k,theta);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddInX xai_ran_gamma_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_gamma_pdf"), _T("GSL.DIST.GAMMA.PDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("k"), _T("is the shape parameter of Gamma distribution, should be above zero, default value is 1.0"), 1.0)
	.Arg(XLL_DOUBLEX, _T("theta"), _T("is the scale parameter of Gamma distribution, should be above zero, default value is 1.0"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Gamma distribution probability density function with shape parameter k and scale of theta."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_gamma_pdf(double x, double k, double theta)
{
#pragma XLLEXPORT
	if (k <= 0)
		k = 1.0;
	if (theta <= 0)
		theta = 1.0;

	return gsl_ran_gamma_pdf(x, k, theta);
}

static AddInX xai_cdf_gamma_P(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_gamma_P"), _T("GSL.DIST.GAMMA.CDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the cumulative distribution function for the lower tail)."))
	.Arg(XLL_DOUBLEX, _T("k"), _T("is the shape parameter of Gamma distribution, should be above zero, default value is 1.0"), 1.0)
	.Arg(XLL_DOUBLEX, _T("theta"), _T("is the scale parameter of Gamma distribution, should be above zero, default value is 1.0"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Gamma distribution cumulative distribution function for the lower tail."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_gamma_P(double x, double k, double theta)
{
#pragma XLLEXPORT
	if (k <= 0)
		k = 1.0;
	if (theta <= 0)
		theta = 1.0;

	return gsl_cdf_gamma_P(x, k, theta);
}

static AddInX xai_cdf_gamma_Pinv(
	FunctionX(XLL_DOUBLEX, _T("?xll_cdf_gamma_Pinv"), _T("GSL.DIST.GAMMA.INV"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the value at which to calculate the inverse cumulative distribution function."))
	.Arg(XLL_DOUBLEX, _T("k"), _T("is the shape parameter of Gamma distribution, should be above zero, default value is 1.0"), 1.0)
	.Arg(XLL_DOUBLEX, _T("theta"), _T("is the scale parameter of Gamma distribution, should be above zero, default value is 1.0"), 1.0)
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Gamma distribution inverse cumulative distribution function for lower tail."))
	.Documentation(_T(""))
	);
double WINAPI xll_cdf_gamma_Pinv(double p, double k, double theta)
{
#pragma XLLEXPORT
	if (k <= 0)
		k = 1.0;
	if (theta <= 0)
		theta = 1.0;

	return gsl_cdf_gamma_Pinv(p, k, theta);
}

XLL_TEST_BEGIN(xll_ran_gamma)

double eps = 1e-6;
double eps_inv = 1e-4; //not accurate enough when using inverse PDF function

//Table[PDF[GammaDistribution[1,1],x],{x,0.1,4,0.1}]
//http://www.wolframalpha.com/input/?i=Table%5BPDF%5BGammaDistribution%5B1%2C1%5D%2Cx%5D%2C%7Bx%2C0.1%2C4%2C0.1%7D%5D
double pdf[] = {0.904837,0.818731,0.740818,0.67032,0.606531,0.548812,0.496585,
   0.449329,0.40657,0.367879,0.332871,0.301194,0.272532,0.246597,
   0.22313,0.201897,0.182684,0.165299,0.149569,0.135335,0.122456,
   0.110803,0.100259,0.090718,0.082085,0.0742736,0.0672055,0.0608101,
   0.0550232,0.0497871,0.0450492,0.0407622,0.0368832,0.0333733,
   0.0301974,0.0273237,0.0247235,0.0223708,0.0202419,0.0183156 };

// Table[CDF[GammaDistribution[1,1], x],{x, 0.1, 4, .1}]
//http://www.wolframalpha.com/input/?i=Table%5BCDF%5BGammaDistribution%5B1%2C1%5D%2C+x%5D%2C%7Bx%2C+0.1%2C+4%2C+.1%7D%5D
double cdf[] = 
{0.0951626,0.181269,0.259182,0.32968,0.393469,0.451188,0.503415,0.550671,
 0.59343,0.632121,0.667129,0.698806,0.727468,0.753403,0.77687,0.798103,
 0.817316,0.834701,0.850431,0.864665,0.877544,0.889197,0.899741,0.909282,
 0.917915,0.925726,0.932794,0.93919,0.944977,0.950213,0.954951,0.959238,
 0.963117,0.966627,0.969803,0.972676,0.975276,0.977629,0.979758,0.981684
};

//verify GSL Gamma Distribution routines
for (int i = 0; i < sizeof(pdf) / sizeof(*pdf); ++i) {
	double x = 0.1 + i*0.1;
	ensure(fabs(xll_ran_gamma_pdf(x, 1, 1) - pdf[i]) < eps);
	ensure(fabs(xll_cdf_gamma_P(x, 1,1) - cdf[i]) < eps);
}

//Table[InverseCDF[GammaDistribution[1,1], p],{p, .1, .9, .1}]
//http://www.wolframalpha.com/input/?i=Table%5BInverseCDF%5BGammaDistribution%5B1%2C1%5D%2C+p%5D%2C%7Bp%2C+.1%2C+.9%2C+.1%7D%5D
double inv[] = {0.105361,0.223144,0.356675,0.510826,0.693147,0.916291,1.20397,1.60944,2.30259};
for (int i = 0; i < sizeof(inv) / sizeof(*inv); ++i) {
	double p = 0.1 + i*0.1;
	ensure(fabs(xll_cdf_gamma_Pinv(p, 1,1) - inv[i]) < 2 * eps_inv);
}

XLL_TEST_END(xll_ran_gamma)