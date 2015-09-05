// gsl_sf_zeta.cpp - Riemann zeta function
// Author: Erica (Mengying) Zhang
#include "gsl/gsl_sf_zeta.h"
#include "../xll_gsl.h"

using namespace xll;

/*
The Riemann zeta function is defined by the infinite sum \zeta(s) = \sum_{k=1}^\infty k^{-s}.
Function: double gsl_sf_zeta (double s)
Function: int gsl_sf_zeta_e (double s, gsl_sf_result * result)
These routines compute the Riemann zeta function \zeta(s) for arbitrary s, s \ne 1.
*/

/*
Function: double gsl_sf_zeta (double s)
Function: int gsl_sf_zeta_e (double s, gsl_sf_result * result)
*/
static AddInX xai_xll_sf_zeta(
	FunctionX(XLL_DOUBLEX, _T("?xll_sf_zeta"), PREFIX _T("SF.ZETA"))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is a number."), 1.)
	.Category(CATEGORY)
	.FunctionHelp(_T("These routines compute the Riemann zeta function zeta(s) for arbitrary s, s ne 1."))
	);

double WINAPI xll_sf_zeta(double x)
{
#pragma XLLEXPORT
	gsl_sf_result result;

	try {
		auto status = gsl_sf_zeta_e(x, &result);
		if (status != GSL_SUCCESS)
			throw std::runtime_error(gsl_strerror(status));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result.val;
}

#ifdef _DEBUG

XLL_TEST_BEGIN(test_sf_zeta)

// Table[Zeta[x], {x, -.9, .9, 0.05}]
// https://www.wolframalpha.com/input/?i=Table%5BZeta%5Bx%5D%2C+%7Bx%2C-0.9%2C0.9%2C.05%7D%5D
//double Ai[] = { 0.227407, 0.2868, 0.340762, 0.388607, 0.429863, 0.464257, 0.4917, 0.512272, 0.526194, 0.533811, 0.535561, 0.53196, 0.523574, 0.511, 0.49485, 0.475728, 0.454226, 0.430903, 0.406284, 0.380849, 0.355028, 0.329203, 0.303703, 0.278806, 0.254742, 0.231694, 0.2098, 0.189162, 0.169846, 0.151887, 0.135292, 0.120049, 0.106126, 0.0934747, 0.082038, 0.0717495, 0.0625369, 0.0543248, 0.0470362, 0.0405944, 0.0349241 };
double Ze[] = { -0.101194, -0.111194, -0.121987, -0.133643, -0.146237, -0.159856, -0.174596, -0.190565, -0.207886, -0.2267, -0.247165, -0.269466, -0.293813, -0.320451, -0.349666, -0.381793, -0.417228, -0.456442, -0.5, -0.548587, -0.603038, -0.664385, -0.733921, -0.813278, -0.904559, -1.01051, -1.1348, -1.28241, -1.46035, -1.67872, -1.95266, -2.30599, -2.77839, -3.44129, -4.43754, -6.10048, -9.43011 };
double epsilon = 1e-5;
for (int i = 0; i < sizeof(Ze) / sizeof(*Ze); ++i) {
	ensure(fabs(xll_sf_zeta(-.9 + i*0.05) - Ze[i]) < epsilon);
}

XLL_TEST_END(test_sf_zeta)

#endif // _DEBUG