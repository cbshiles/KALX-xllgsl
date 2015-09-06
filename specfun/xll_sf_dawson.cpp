// xll_sf_dawson.cpp - Dawson function
// Author: Shaojie He
#include "gsl/gsl_sf_dawson.h"
#include "../xll_gsl.h"

using namespace xll;

/*
The Dawson integral is defined by \exp(-x^2) \int_0^x dt \exp(t^2). 

A table of Dawson¥¯s integral can be found in Abramowitz & Stegun, Table 7.5. 

The Dawson functions are declared in the header file gsl_sf_dawson.h.
*/

/*
Function: double gsl_sf_dawson (double x)
Function: int gsl_sf_dawson_e (double x, gsl_sf_result * result)
*/
static AddInX xai_xll_sf_dawson(
	FunctionX(XLL_DOUBLEX, _T("?xll_sf_dawson"), PREFIX _T("SF.DAWSON"))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is a number."), 1.)
	.Category(CATEGORY)
	.FunctionHelp(_T("The Dawson function Daw(x)"))
	//	.Documentation(R_(
	//		Daw(x) = \exp(-x^2) \int_0^x dt \exp(t^2)
	//	))
	);
double WINAPI xll_sf_dawson(double x)
{
#pragma XLLEXPORT
	gsl_sf_result result;

	try {
		auto status = gsl_sf_dawson_e(x, &result);
		if (status != GSL_SUCCESS)
			throw std::runtime_error(gsl_strerror(status));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result.val;
}

#ifdef _DEBUG

XLL_TEST_BEGIN(test_sf_dawson)

// Table[Dawson[x], {x, -2, 0, 0.1}]
// https://www.wolframalpha.com/input/?i=Table%5BDawson%5Bx%5D%2C+%7Bx%2C-2%2C0%2C.1%7D%5D
double Daw[] = { -0.30134, -0.322974, -0.346773, -0.372559, -0.39994, -0.428249, -0.456507, -0.483398, -0.507273, -0.526207, -0.53808, -0.540724, -0.532102, -0.510504, -0.474763, -0.424436, -0.359943, -0.282632, -0.194751, -0.099336, 0 };
double epsilon = 1e-6;
for (int i = 0; i < sizeof(Daw) / sizeof(*Daw); ++i) {
	ensure(fabs(xll_sf_dawson(-2 + i*0.1) - Daw[i]) < epsilon);
}

XLL_TEST_END(test_sf_dawson)

#endif // _DEBUG