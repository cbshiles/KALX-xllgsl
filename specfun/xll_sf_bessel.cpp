// xll_sf_bessel.cpp - Bessel function
// Author: Han Hong
#include "gsl/gsl_sf_bessel.h"
#include "gsl/gsl_errno.h"
#include "../xll_gsl.h"

using namespace xll;

/*
The routines described in this section compute the Cylindrical Bessel functions J_n(x), Y_n(x), 
Modified cylindrical Bessel functions I_n(x), K_n(x), Spherical Bessel functions j_l(x), y_l(x), 
and Modified Spherical Bessel functions i_l(x), k_l(x). For more information see Abramowitz & Stegun, 
Chapters 9 and 10. The Bessel functions are defined in the header file gsl_sf_bessel.h.
*/

/*
Function: double gsl_sf_bessel_J0 (double x)
Function: int gsl_sf_bessel_J0_e (double x, gsl_sf_result * result)
These routines compute the regular cylindrical Bessel function of zeroth order, J_0(x).

Function: double gsl_sf_bessel_J1 (double x)
Function: int gsl_sf_bessel_J1_e (double x, gsl_sf_result * result)
These routines compute the regular cylindrical Bessel function of first order, J_1(x).

Function: double gsl_sf_bessel_Jn (int n, double x)
Function: int gsl_sf_bessel_Jn_e (int n, double x, gsl_sf_result * result)
These routines compute the regular cylindrical Bessel function of order n, J_n(x).

Function: int gsl_sf_bessel_Jn_array (int nmin, int nmax, double x, double result_array[])
This routine computes the values of the regular cylindrical Bessel functions J_n(x) for n from nmin to nmax inclusive,
storing the results in the array result_array. The values are computed using recurrence relations for efficiency,
and therefore may differ slightly from the exact values.
*/

static AddInX xai_xll_sf_bessel(
	FunctionX(XLL_DOUBLEX, _T("?xll_sf_bessel_J0"), PREFIX _T("SF.BESSEL.J0"))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is a number."), 1.)
//	.Arg(XLL_WORDX, _T("_mode"), IS_PREC, GSL_MODE_DEFAULT)
	.Category(CATEGORY)
	.FunctionHelp(_T("The Bessel function J_0(x)"))
	.Documentation(R_(
//		blank
	))
);

double WINAPI xll_sf_bessel_J0(double x)
{
#pragma XLLEXPORT
	gsl_sf_result result;

	try {
		auto status = gsl_sf_bessel_J0_e(x, &result);
		if (status != GSL_SUCCESS)
			throw std::runtime_error(gsl_strerror(status));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result.val;
}

#ifdef _DEBUG

XLL_TEST_BEGIN(test_sf_bessel)

/*
	status = success
	J0(5.0) = -0.177596771314338292
	+ / -0.000000000000000193
	exact = -0.177596771314338292
*/

	double x = 5.0;
	double expected = -0.17759677131433830434739701;
	double y = xll_sf_bessel_J0(x);
	double error_bound = 0.000000000000001; //10^-15

	ensure (abs(y - expected) < error_bound);

XLL_TEST_END(test_sf_bessel)

#endif // _DEBUG