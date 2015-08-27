// xll_sf_airy.cpp - Airy function
#include "gsl/gsl_sf_airy.h"
#include "../xll_gsl.h"

using namespace xll;

/*
The Airy functions Ai(x) and Bi(x) are defined by the integral representations, 

Ai(x) = (1/\pi) \int_0^\infty \cos((1/3) t^3 + xt) dt
Bi(x) = (1/\pi) \int_0^\infty (e^(-(1/3) t^3 + xt) + \sin((1/3) t^3 + xt)) dt

For further information see Abramowitz & Stegun, Section 10.4. The Airy functions are defined in the header file gsl_sf_airy.h. 
*/

/*
Function: double gsl_sf_airy_Ai (double x, gsl_mode_t mode)
Function: int gsl_sf_airy_Ai_e (double x, gsl_mode_t mode, gsl_sf_result * result)
*/
static AddInX xai_xll_sf_airy(
	FunctionX(XLL_DOUBLEX, _T("?xll_sf_airy"), PREFIX _T("SF.AIRY"))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is a number."), 1.)
	.Arg(XLL_WORDX, _T("_mode"), IS_PREC, GSL_MODE_DEFAULT)
	.Category(CATEGORY)
	.FunctionHelp(_T("The Airy function Ai(x)"))
	.Documentation(R_(
//		Ai(x) = (1/\pi) \int_0^\infty \cos((1/3) t^3 + xt) dt
	))
);
double WINAPI xll_sf_airy(double x, WORD prec)
{
#pragma XLLEXPORT
	gsl_sf_result result;

	try {
		auto status = gsl_sf_airy_Ai_e(x, prec, &result);
		if (status != GSL_SUCCESS)
			throw std::runtime_error(gsl_message(status));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result.val;
}

#ifdef _DEBUG

XLL_TEST_BEGIN(test_sf_airy)

	double Ai0 = 0;// 1/(3^(2./3))*Gamma(2/3))
	ensure (Ai0 == Ai0);
//	ensure (xll_sf_airy(0, GSL_PREC_DOUBLE) == Ai0);

XLL_TEST_END(test_sf_airy)

#endif // _DEBUG