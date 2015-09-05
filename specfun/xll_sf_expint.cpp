// xll_sf_expint.cpp - Exponential Integral function
//Author:Luna Yue Cheng
#include "gsl/gsl_sf_expint.h"
#include "../xll_gsl.h"

using namespace xll;

/*
These routines compute the exponential integral E_n(x) of order n,

E_n(x) := \Re \int_1^\infty dt \exp(-xt)/t^n.
Information on the exponential integrals can be found in Abramowitz & Stegun, Chapter 5.These functions are declared in the header file gsl_sf_expint.h.
*/

/*
Function: double gsl_sf_expint_En (int n, double x)
Function: int gsl_sf_expint_En_e (int n, double x, gsl_sf_result * result)
*/
static AddInX xai_xll_sf_expint_En(
	FunctionX(XLL_DOUBLEX, _T("?xll_sf_expint_En"), PREFIX _T("SF.EXPINTEN"))
	.Arg(XLL_WORDX, _T("n"), _T("is an integer."), 1)
	.Arg(XLL_DOUBLEX, _T("x"), _T("is a number."), 1.)
	.Category(CATEGORY)
	.FunctionHelp(_T("The expint_En function E_n(x)"))
	//	.Documentation(R_(
	//		E_n(x) := \Re \int_1^\infty dt \exp(-xt)/t^n.
	//	))
	);
double WINAPI xll_sf_expint_En(WORD n,double x)
{
#pragma XLLEXPORT
	gsl_sf_result result;

	try {
		auto status = gsl_sf_expint_En_e(n,x, &result);
		if (status != GSL_SUCCESS)
			throw std::runtime_error(gsl_strerror(status));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result.val;
}

#ifdef _DEBUG

XLL_TEST_BEGIN(test_sf_expint_En)

// Table[ExpIntegralE[2, x], {x, 0.1, 2,0.1}]
// https://www.wolframalpha.com/input/?i=Table%5BExpIntegralE%5Bn%2C+x%5D%2C+%7Bn%2C2%7D%2C+%7Bx%2C+0.1%2C+1%2C0.1%7D%5D
//
double En[] = { 0.722545, 0.574201, 0.469115, 0.389368, 0.326644, 0.276184, 0.234947, 0.200852, 0.172404, 0.148496, 0.128281, 0.111104, 0.0964455, 0.0838899, 0.0731008, 0.0638032, 0.0557706, 0.0488153, 0.0427803, 0.0375343 };
double epsilon = 1e-6;
for (int i = 0; i < sizeof(En) / sizeof(*En); ++i) {
	ensure(fabs(xll_sf_expint_En(2, 0.1 + i*0.1) - En[i]) < epsilon);
}

XLL_TEST_END(test_sf_expint_En)

#endif // _DEBUG