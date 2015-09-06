// xll_legendre_p.cpp - Legendre Polynomials function
// Author: Sandeep Saju

#include "gsl/gsl_sf_legendre.h"
#include "gsl/gsl_errno.h"
#include "../xll_gsl.h"

using namespace xll;

/*

These functions evaluate the Legendre polynomials P_l(x) using explicit representations for l=1, 2, 3.
*/

/*
Function: double gsl_sf_legendre_P1 (double x)
Function: double gsl_sf_legendre_P2 (double x)
Function: double gsl_sf_legendre_P3 (double x)
Function: int gsl_sf_legendre_P1_e (double x, gsl_sf_result * result)
Function: int gsl_sf_legendre_P2_e (double x, gsl_sf_result * result)
Function: int gsl_sf_legendre_P3_e (double x, gsl_sf_result * result)
Function: double gsl_sf_legendre_P1 (double x)

*/
static AddInX xai_xll_sf_legendre_p(
	FunctionX(XLL_DOUBLEX, _T("?xll_sf_legendre_p"), PREFIX _T("SF.LEGENDREP1"))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is a number."), 1.)	
	.Category(CATEGORY)
	.FunctionHelp(_T("The Legendre function Le(x)"))
	//	.Documentation(R_(
	//		Ai(x) = (1/\pi) \int_0^\infty \cos((1/3) t^3 + xt) dt
	//	))
	);
double WINAPI xll_sf_legendre_p (double x)
{
#pragma XLLEXPORT
	gsl_sf_result result;

	try {
		auto status = gsl_sf_legendre_P1_e(x,  &result);
		if (status != GSL_SUCCESS)
			throw std::runtime_error(gsl_strerror(status));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result.val;
}

#ifdef _DEBUG

XLL_TEST_BEGIN(test_sf_legendre_p)

// Table[LegendreP[x], {x, -2, 2, 0.1}]
// https://www.wolframalpha.com/input/?i=Table%5BAiryAi%5Bx%5D%2C+%7Bx%2C-2%2C2%2C.1%7D%5D
double Ai[] = { 0.227407, 0.2868, 0.340762, 0.388607, 0.429863, 0.464257, 0.4917, 0.512272, 0.526194, 0.533811, 0.535561, 0.53196, 0.523574, 0.511, 0.49485, 0.475728, 0.454226, 0.430903, 0.406284, 0.380849, 0.355028, 0.329203, 0.303703, 0.278806, 0.254742, 0.231694, 0.2098, 0.189162, 0.169846, 0.151887, 0.135292, 0.120049, 0.106126, 0.0934747, 0.082038, 0.0717495, 0.0625369, 0.0543248, 0.0470362, 0.0405944, 0.0349241 };
double epsilon = 1e-6;
for (int i = 0; i < sizeof(Ai) / sizeof(*Ai); ++i) {
	ensure(fabs(xll_sf_legendre_p(-2 + i*0.1) - Ai[i]) < epsilon);
}

XLL_TEST_END(test_sf_legendre_p)

#endif // _DEBUG