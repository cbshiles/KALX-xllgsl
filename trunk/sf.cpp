// sf.cpp - special functions
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "gsl.h"
#include "gsl/gsl_sf.h"

#ifndef CATEGORY
#define CATEGORY _T("Special Functions")
#endif

using namespace xll;
using namespace xml;

XLL_ENUM_DOC(GSL_PREC_DOUBLE, PREC_DOUBLE, CATEGORY, _T("Double precision"),
	_T("Double-precision has a relative accuracy of approximately <math>2 ") ENT_times _T(" 10<superscript>-16</superscript></math>."))
XLL_ENUM_DOC(GSL_PREC_SINGLE, PREC_SINGLE, CATEGORY, _T("Single precision"),
	_T("Single-precision has a relative accuracy of approximately <math>10<superscript>-7</superscript></math>.")) 
XLL_ENUM_DOC(GSL_PREC_APPROX, PREC_APPROX, CATEGORY, _T("Approximate values"),
	_T("Approximate values has a relative accuracy of approximately <math>5 ") ENT_times _T(" 10<superscript>-4</superscript></math>.")) 

// call a GSL unary function
inline xfp*
sf_unary(int (*f)(double,gsl_mode_t,gsl_sf_result*), double x, gsl_mode_t mode)
{
	static FPX y(1, 2);
	gsl_sf_result r;

	try {
		ensure (0 == f(x, mode, &r));
		y[0] = r.val;
		y[1] = r.err;
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return y.get();
}

// create the add-in object
// Documentation is not wrapped in _T()
#define SF_UNARY(f, F, FH, D) static AddInX xai_ ## f(FunctionX(XLL_FPX, _T(XLL_STRZ_(xll_ ## f)), _T(F)) \
	.Arg(XLL_DOUBLEX, _T("x"), IS_NUM).Arg(XLL_WORDX, _T("mode"), IS_PREC).Category(CATEGORY).FunctionHelp(_T(FH)).Documentation(D)); \
	extern "C" __declspec(dllexport) xfp* xll_ ## f(double x, gsl_mode_t mode) { \
	return sf_unary(gsl_ ## f ## _e, x, mode); }

SF_UNARY(sf_airy_Ai, "SF.AIRY.Ai",
	"This routine computes the Airy function Ai(x) with an accuracy specified by mode. ",
	element()
	.content(para(_T("The Airy function Ai(<math>x</math>) is defined by the integral representation:")))
	.content(quote(math()
		.content(_R("Ai(") _T("x") _R(") = ") ENT_int)
		.content(sub(_T("0"))).content(sup(ENT_infin)).content(_R("cos(") _T("t")).content(sup(_T("3"))).content(_R("/3") _T(" + xt") _R(")") _T(" dt/" ENT_pi)))
		)
	.content(para(_T("It is a solution of the second order, non-linear differential equation <math>y") ENT_Prime _T(" + xy = ") _R("0") _T("</math>. "))) 
)
SF_UNARY(sf_airy_Bi, "SF.AIRY.Bi",
	"This routine computes the Airy function Bi(x) with an accuracy specified by mode. ",
	element()
	.content(para(_T("The Airy function of the second kind, Bi(<math>x</math>), is defined by the integral representation:")))
	.content(quote(math()
		.content(_R("Bi(") _T("x") _R(") = ") ENT_int)
		.content(sub(_T("0"))).content(sup(ENT_infin)).content(
			_R("[exp(") _T("-t")).content(sup(_T("3"))).content(_R("/3") _T(" + xt") _R(")") 
			_T(" + ") 
			_R("sin(") _T("t")).content(sup(_T("3"))).content(_R("/3") _T(" + xt") _R(")]") _T(" dt/" ENT_pi)))
	  )
	.content(para(_T("It is also a solution of the second order, non-linear differential equation <math>y") ENT_Prime _T(" + xy = ") _R("0") _T("</math>. "))) 
)
/*
SF_UNARY(sf_bessel_J0, "SF.BESSEL.J0",
	"Compute the regular cylindrical Bessel function of zeroth order.",
	"This function is denoted <math>J<subscript>0</subscript></math>(<math>x</math>). "
)
*/