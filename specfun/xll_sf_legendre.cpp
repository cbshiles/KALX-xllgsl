// xll_legendre.cpp - Legendre Polynomials function
// Author: Sandeep Saju
#include "gsl/gsl_sf_legendre.h"
#include "gsl/gsl_errno.h"
#include "../xll_gsl.h"

using namespace xll;

/*

These functions evaluate the Legendre polynomials P_l(x) using explicit representations for l=1, 2, 3.
*/

/*
Function: int gsl_sf_legendre_Pl_e (int l, double x, gsl_sf_result * result)
These functions evaluate the Legendre polynomial P_l(x) for a specific value of l, x subject to l >= 0, |x| <= 1 
*/
static AddInX xai_sf_legendre_p(
	FunctionX(XLL_DOUBLEX, _T("?xll_sf_legendre_p"), PREFIX _T("SF.LEGENDRE.P"))
	.Arg(XLL_WORDX, _T("n"), _T("is an integer greater than 0"))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is a number."), 1.)	
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the value of the n-th Legendre polynomial at n."))
	//	.Documentation(R_(
	//		Ai(x) = (1/\pi) \int_0^\infty \cos((1/3) t^3 + xt) dt
	//	))
	);
double WINAPI xll_sf_legendre_p (WORD n, double x)
{
#pragma XLLEXPORT
	gsl_sf_result result;

	try {
		auto status = gsl_sf_legendre_Pl_e(n, x,  &result);
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

// Table[LegendreP[3,x], {x, -1, 1, 0.1}]
// https://www.wolframalpha.com/input/?i=Table%5BLegendreP%5B3%2Cx%5D%2C+%7Bx%2C-1%2C1%2C.1%7D%5D
double LegendreP[] = {
	-1., -0.4725, -0.08, 0.1925, 0.36, 0.4375, 0.44, 0.3825, 0.28, 0.1475, 0., -0.1475, -0.28, 
	-0.3825, -0.44, -0.4375, -0.36, -0.1925, 0.08, 0.4725, 1.};
double epsilon = 1e-15;
for (int i = 0; i < sizeof(LegendreP) / sizeof(*LegendreP); ++i) {
	ensure(fabs(xll_sf_legendre_p(3, -1 + i*0.1) - LegendreP[i]) < epsilon);
}

XLL_TEST_END(test_sf_legendre_p)

#endif // _DEBUG