#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_bivariate_gaussian(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_bivariate_gaussian"), _T("GSL.RAN.BIVARIATE.GAUSSIAN"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Arg(XLL_DOUBLEX, _T("sigma_x"), _T("is the standard deviation of the BivariateGaussian. Default is 1"), 1.0)
	.Arg(XLL_DOUBLEX, _T("sigma_y"), _T("is the standard deviation of the BivariateGaussian. Default is 1."), 1.0)
	.Arg(XLL_DOUBLEX, _T("rho"), _T("is the correlation coefficient of the BivariateGaussian."))
	.Arg(XLL_DOUBLE_, _T("direct_x"), _T("is the direction of the BivariateGaussian."))
	.Arg(XLL_DOUBLE_, _T("direct_y"), _T("is the direction of the BivariateGaussian."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Bivariate Gaussian/normal random deviates using a random number generator."))
	.Documentation(_T(""))
	);
void WINAPI xll_ran_bivariate_gaussian(HANDLEX rng, double sigma_x, double sigma_y, double rho, double * x, double * y)
{
#pragma XLLEXPORT

	try {
		if (sigma_x == 0)
			sigma_x = 1;
		if (sigma_y == 0)
			sigma_y = 1;
		if (rho > 1)
			rho = 1;
		if (rho < -1)
			rho = -1;
			
		handle<gsl::rng> r(rng);

		gsl_ran_bivariate_gaussian(*r, sigma_x, sigma_y, rho, x, y);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

}

static AddInX xai_ran_bivariate_gaussian_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_bivariate_gaussian_pdf"), _T("GSL.DIST.BIVARIATE.GAUSSIAN.PDF"))
	.Arg(XLL_HANDLEX, _T("x"), _T("is the x value at which to calculate the density function."))
	.Arg(XLL_HANDLEX, _T("y"), _T("is the y value at which to calculate the density function."))
	.Arg(XLL_DOUBLEX, _T("sigma_x"), _T("is the variance of x of the BivariateGaussian. Default is 1."), 1.0)
	.Arg(XLL_DOUBLEX, _T("sigma_y"), _T("is the variance of y of the BivariateGaussian. Default is 1."), 1.0)
	.Arg(XLL_DOUBLEX, _T("rho"), _T("is the correlation coefficient of the BivariateGaussian."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Bivariate Gaussian/normal probability density function."))
	.Documentation(_T(""))
	);
double WINAPI xll_ran_bivariate_gaussian_pdf(double x, double y, double sigma_x, double sigma_y, double rho)
{
#pragma XLLEXPORT
	if (sigma_x == 0)
		sigma_x = 1;
	if (sigma_y == 0)
		sigma_y = 1;
	if (rho > 1)
		rho = 1;
	if (rho < -1)
		rho = -1;


	return gsl_ran_bivariate_gaussian_pdf(x, y, sigma_x, sigma_y, rho);
}


//No cdf or inv functions


XLL_TEST_BEGIN(xll_ran_bivariate_gaussian)

double eps = 1e-6;

//no Wolfram Alpha data, used R instead

double pdf[]= { 0.01276941, 0.01656103, 0.02119402, 0.02676386, 0.03334983, 0.04100603, 0.04975210, 0.05956407, 0.07036664, 0.08202734, 0.09435390, 0.10709532, 0.11994731, 0.13256228, 0.14456356, 0.15556328, 0.16518277, 0.17307400,0.17894036, 0.18255520, 0.18377630, 0.18255520, 0.17894036, 0.17307400, 0.16518277, 0.15556328, 0.14456356, 0.13256228, 0.11994731, 0.10709532, 0.09435390, 0.08202734, 0.07036664, 0.05956407, 0.04975210, 0.04100603, 0.03334983, 0.02676386, 0.02119402, 0.01656103, 0.01276941};

//sizeof(a)/sizeof(*a)=length(a)
for (int i = 0; i < sizeof(pdf)/sizeof(*pdf); ++i) {
	double x = -2+i*0.1;
	double y = -2+i*0.1;

	ensure(fabs(xll_ran_bivariate_gaussian_pdf(x, y, 1, 1, .5 ) - pdf[i]) < eps);
}


XLL_TEST_END(xll_ran_bivariate_gaussian)