// xll_sf.cpp - special functions
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "xll_sf.h"

#ifndef CATEGORY
#define CATEGORY _T("Special Functions")
#endif

using namespace xll;

XLL_ENUM_DOCX(GSL_PREC_DOUBLE, PREC_DOUBLE, CATEGORY, _T("Double precision"),
	_T("Double-precision has a relative accuracy of approximately <math>2 ") _T(ENT_times) _T(" 10<superscript>-16</superscript></math>."))
XLL_ENUM_DOCX(GSL_PREC_SINGLE, PREC_SINGLE, CATEGORY, _T("Single precision"),
	_T("Single-precision has a relative accuracy of approximately <math>10<superscript>-7</superscript></math>.")) 
XLL_ENUM_DOCX(GSL_PREC_APPROX, PREC_APPROX, CATEGORY, _T("Approximate values"),
	_T("Approximate values has a relative accuracy of approximately <math>5 ") _T(ENT_times) _T(" 10<superscript>-4</superscript></math>.")) 

// create the add-in object
#define SF_UNARY_MODE(f, F, FH, D) static AddIn xai_ ## f(Function(XLL_FP, ENSURE_STRZ_(xll_ ## f), F) \
	.Arg(XLL_DOUBLE, "x", "is a number") \
	.Arg(XLL_WORD, "mode", "is the precision from the PREC_* enumeration") \
	.Category("GSL").FunctionHelp(FH).Documentation(D)); \
	extern "C" __declspec(dllexport) xfp* xll_ ## f(double x, gsl_mode_t mode) { \
	return sf_unary_mode(gsl_ ## f ## _e, x, mode ? mode : GSL_PREC_DOUBLE); }

SF_UNARY_MODE(sf_airy_Ai, "SF.AIRY.Ai",
	"This routine computes the Airy function Ai(x) with an accuracy specified by mode. ",
	"The Airy function Ai(<math>x</math>) is defined by the integral representation:"
	/*
	.content(quote(math()
		.content(_R("Ai(") _T("x") _R(") = ") ENT_int)
		.content(sub(_T("0"))).content(sup(ENT_infin)).content(_R("cos(") _T("t")).content(sup(_T("3"))).content(_R("/3") _T(" + xt") _R(")") _T(" dt/" ENT_pi)))
		)
	.content(para(_T("It is a solution of the second order, non-linear differential equation <math>y") ENT_Prime _T(" + xy = ") _R("0") _T("</math>. "))) 
	*/
)
SF_UNARY_MODE(sf_airy_Bi, "SF.AIRY.Bi",
	"This routine computes the Airy function Bi(x) with an accuracy specified by mode. ",
	"The Airy function of the second kind, Bi(<math>x</math>), is defined by the integral representation:"
	/*
	.content(quote(math()
		.content(_R("Bi(") _T("x") _R(") = ") ENT_int)
		.content(sub(_T("0"))).content(sup(ENT_infin)).content(
			_R("[exp(") _T("-t")).content(sup(_T("3"))).content(_R("/3") _T(" + xt") _R(")") 
			_T(" + ") 
			_R("sin(") _T("t")).content(sup(_T("3"))).content(_R("/3") _T(" + xt") _R(")]") _T(" dt/" ENT_pi)))
	  )
	.content(para(_T("It is also a solution of the second order, non-linear differential equation <math>y") ENT_Prime _T(" + xy = ") _R("0") _T("</math>. "))) 
	*/
)

SF_UNARY(sf_bessel_J0, "SF.BESSEL.J0",
	"Compute the regular cylindrical Bessel function of zeroth order.",
	"This function is denoted <math>J<subscript>0</subscript></math>(<math>x</math>). "
)
