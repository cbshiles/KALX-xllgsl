// xll_sf_bessel.cpp - Regular Cylindrical Bessel Functions
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "gsl/gsl_sf_bessel.h"
#include "xll_gsl.h"

#ifndef CATEGORY
#define CATEGORY _T("Special Functions")
#endif

using namespace xll;

static AddInX xai_sf_bessel_J0(
	FunctionX(XLL_FPX, _T("?xll_sf_bessel_J0"), _T("SF.BESSEL.J0"))
	.Arg(XLL_FPX, _T("Array"), _T("is an array of numbers "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Compute the regular cylindrical Bessel function of zeroth order."))
	.Documentation(
		_T("This function is denoted <math>J<subscript>0</subscript></math>(<math>x</math>). ")
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

#ifdef _DEBUG

XLL_TEST_BEGIN(bessel)
	ensure (Excel<XLOPERX>(xlfEvaluate, OPERX(_T("1=SF.BESSEL.J0(0)"))));
XLL_TEST_END(bessel)

#endif // _DEBUG