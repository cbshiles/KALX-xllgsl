// poly.cpp - polynomials and their roots
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.

#pragma warning(disable: 4127)
#define HAVE_INLINE
#define HAVE_C99_INLINE
#include "gsl/gsl_poly.h"
#include "gsl.h"

#define IS_POLY _T("is an array of polynomial coefficients")

using namespace xll;
using namespace xml;

static AddInX xai_poly_eval(
	FunctionX(XLL_FPX, _T("?xll_poly_eval"), _T("POLY.EVAL"))
	.Arg(XLL_FPX, _T("p"), IS_POLY)
	.Arg(XLL_FPX, _T("x"), _T("is the number at which to evaluate the polynomial "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Evaluate the polynomial p(x)."))
	.Documentation(element()
		._(para()
			._(_T("If <codeInline>p</codeInline> is the array <math>a</math> this function calculates "))
			._(math(
				_T("p(x) = a<subscript>0</subscript> + a<subscript>1</subscript> x + ")
				ENT_middot ENT_middot ENT_middot
				_T(" + a<subscript>n</subscript> x<superscript>n</superscript>")
			  )
			._(_T(".")))
		  )
		._(para()
			._(_T("The polynomial coefficients are assumed to be complex numbers if <codeInline>p</codeInline> "))
			._(_T("has two columns and more than one row. In this case <codeInline>gsl_complex_poly_complex_eval</codeInline> "))
			._(_T("is called. Otherwise, <codeInline>gsl_poly_complex_eval</codeInline> is called if "))
			._(_T("<codeInline>x</codeInline> is an array of two numbers and "))
			._(_T("<codeInline>gsl_poly_eval</codeInline> is called if <codeInline>x</codeInline> is a single number. "))
		  )

	)
);
xfp* WINAPI
xll_poly_eval(const xfp* pa, const xfp* px)
{
#pragma XLLEXPORT
	static fpx_complex p;
	gsl_complex z = {0, 0};

	// figure out if a is complex data
	if (pa->columns == 2 && pa->rows > 1) {
		z.dat[0] = px->array[0];
		if (size(*px) > 1)
			z.dat[1] = px->array[1];

		z = gsl_complex_poly_complex_eval((const gsl_complex*)pa->array, size(*pa)/2, z);
	}
	else {
		if (size(*px) > 1) {
			z.dat[0] = px->array[0];
			z.dat[1] = px->array[1];			
			z = gsl_poly_complex_eval(pa->array, size(*pa), z);
		}
		else {
			z.dat[0] = gsl_poly_eval(pa->array, size(*pa), z.dat[0]);
		}
	}

	p = z;

	return &p;
}

// divided differences
// gsl_poly_dd_init
// gsl_poly_dd_eval
// gsl_poly_dd_taylor

static AddInX xai_poly_complex_solve(
	FunctionX(XLL_FPX, _T("?xll_poly_complex_solve"), _T("POLY.COMPLEX.SOLVE"))
	.Arg(XLL_FPX, _T("p"), IS_POLY)
	.Category(CATEGORY)
	.FunctionHelp(_T("Compute all the roots of a the polynomial p."))
	.Documentation(
		_T("The implementation uses a balanced-QR reduction of the companion matrix. ")
		_T("If <math>n</math> specifies the length of the coefficient array then <math>n - </math>1 roots are returned. ")
		_T("The coefficient of the highest order term must be non-zero. ")
	)
);
xfp* WINAPI
xll_poly_complex_solve(const xfp* pp)
{
#pragma XLLEXPORT
	xword n = size(*pp);
	static FPX r(n - 1, 2);

	if (pp->array[n -1] == 0) {
		XLL_ERROR("COMPLEX.POLY.SOLVE: the coefficient of the highest order term must be non-zero");

		return 0;
	}

	gsl_poly_complex_workspace* pw;
	if (0 == (pw = gsl_poly_complex_workspace_alloc(n))) {
		XLL_ERROR("COMPLEX.POLY.SOLVE: gsl_poly_complex_workspace_alloc failed");

		return 0;
	}
	int result = gsl_poly_complex_solve(pp->array, n, pw, r.array());
	gsl_poly_complex_workspace_free(pw);

	if (0 != result) {
		XLL_ERROR("COMPLEX.POLY.SOLVE: gsl_poly_complex_solve failed");

		return 0;
	}


	return &r;
}