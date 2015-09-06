// xll_sf_erf.cpp - Error function
// Author: Yuhong Shi(ys685)
#include "gsl/gsl_sf_erf.h"
#include "../xll_gsl.h"

using namespace xll;

/*
Error Function
Function: double gsl_sf_erf (double x)

These routines compute the error function erf(x), where erf(x) = (2/\sqrt(\pi)) \int_0^x dt \exp(-t^2).

*/

static AddInX xai_gsl_sf_erf(
	FunctionX(XLL_DOUBLEX, _T("?xll_sf_erf"), PREFIX _T("SF.ERF"))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is a number."), 1.)
	.Category(CATEGORY)
	.FunctionHelp(_T("The Error function erf(x)"))
	//	.Documentation(R_(
	//		erf(x) = (2/\sqrt(\pi)) \int_0^x dt \exp(-t^2)
	//	))
	);

double WINAPI xll_sf_erf(double x)
{
#pragma XLLEXPORT
	gsl_sf_result result;

	try {
		auto status = gsl_sf_erf_e(x, &result);
		if (status != GSL_SUCCESS)
			throw std::runtime_error(gsl_strerror(status));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result.val;
}

#ifdef _DEBUG

XLL_TEST_BEGIN(test_sf_erf)

// Table[ErrorAi[x], {x, 0, 1, 0.1}]
// https://www.wolframalpha.com/input/?i=Table%5BAiryAi%5Bx%5D%2C+%7Bx%2C-2%2C2%2C.1%7D%5D
double Ai[] = { 0, 0.112463 , 0.222703, 0.328627, 0.428392, 0.5205, 0.603856, 0.677801, 0.742101, 0.796908, 0.842701, 0.880205, 0.910314, 0.934008, 0.952285, 0.966105, 0.976348, 0.98379, 0.989091, 0.99279, 0.995322 };
double epsilon = 1e-6;
for (int i = 0; i < sizeof(Ai) / sizeof(*Ai); ++i) {
	ensure(fabs(xll_sf_erf(i*0.1) - Ai[i]) < epsilon);
}


XLL_TEST_END(test_sf_erf)

#endif // _DEBUG