// xll_sf_debye.cpp - Debye function
//Author: Jiyao Fan
#include "gsl/gsl_sf_debye.h"
#include "../xll_gsl.h"

using namespace xll;

/*
The Debye functions D_n(x) are defined by the following integral,

D_n(x) = n/x^n \int_0^x dt (t^n/(e^t - 1))

For further information see Abramowitz & Stegun, Section 27.1. The Debye functions are declared in the header file gsl_sf_debye.h.
*/

/*
Function: double gsl_sf_debye_1 (double x)
Function: int gsl_sf_debye_1_e (double x, gsl_sf_result * result)
These routines compute the first-order Debye function D_1(x) = (1/x) \int_0^x dt (t/(e^t - 1)).
*/
static AddInX xai_xll_sf_debye(
	FunctionX(XLL_DOUBLEX, _T("?xll_sf_debye"), PREFIX _T("SF.DEBYE"))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is a number."), 1.)
	.Category(CATEGORY)
	.FunctionHelp(_T("The Debye function D_1(x)"))
	//	.Documentation(R_(
	//		D_1(x) = (1/x) \int_0^x dt (t/(e^t - 1))
	//	))
	);
double WINAPI xll_sf_debye(double x)
{
#pragma XLLEXPORT
	gsl_sf_result result;

	try {
		auto status = gsl_sf_debye_1_e(x, &result);
		if (status != GSL_SUCCESS)
			throw std::runtime_error(gsl_strerror(status));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result.val;
}

#ifdef _DEBUG

XLL_TEST_BEGIN(test_sf_debye)

// Debye_1[x], {x, 0.1, 2, 0.1}  There is no available Debye functions in WolframAlpha, so function values are calculated manually on the grid.
// http://www.wolframalpha.com/input/?i=%281%2F2%29+%5Cint_0%5E2+%28t%2F%28e%5Et+-+1%29%29+dt
double Ai[] = { 0.975278, 0.951111, 0.927498, 0.904437, 0.881927, 0.859964, 0.838545, 0.817665, 0.79732, 0.777505, 0.758213, 0.739438, 0.721173, 0.703412, 0.686145, 0.669366, 0.653066, 0.637235, 0.621865, 0.606947 };
double epsilon = 1e-6;
for (int i = 0; i < sizeof(Ai) / sizeof(*Ai); ++i) {
	ensure(fabs(xll_sf_debye(0.1 + i*0.1) - Ai[i]) < epsilon);
}

XLL_TEST_END(test_sf_debye)

#endif // _DEBUG