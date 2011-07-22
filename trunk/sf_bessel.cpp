// sf_bessel.cpp - Regular Cylindrical Bessel Functions
#include "gsl.h"
extern "C" {
#include "gsl/gsl_sf_bessel.h"
}

#ifndef CATEGORY
#define CATEGORY _T("Special Functions")
#endif

using namespace xll;

static AddIn xai_sf_bessel_J0(
	Function(XLL_FP, "?xll_sf_bessel_J0", "SF.BESSEL.J0")
	.Arg(XLL_FP, "Array", "is an array of numbers ")
	.Category("GSL")
	.FunctionHelp("Compute the regular cylindrical Bessel function of zeroth order.")
	.Documentation(
		"This function is denoted <math>J<subscript>0</subscript>(x)</math>. "
	)
);
xfp* WINAPI
xll_sf_bessel_J0(xfp* px)
{
#pragma XLLEXPORT

	for (xword i = 0; i < size(*px); ++i)
		px->array[i] = gsl_sf_bessel_J0(px->array[i]);

	return px;
}