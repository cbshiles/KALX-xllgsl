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
	.Documentation(_T("")
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

class gsl_poly_complex {
	gsl_poly_complex_workspace* pw;
public:
	gsl_poly_complex(int n)
		: pw(gsl_poly_complex_workspace_alloc(n))
	{
		ensure (pw);
	}
	~gsl_poly_complex()
	{
		gsl_poly_complex_workspace_free(pw);
	}
	int solve(const double* a, int n, double* r)
	{
		return gsl_poly_complex_solve(a, n, pw, r);
	}
};

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
	static FPX r;

	try {
		xword n = size(*pp);
		r.resize(n - 1, 2);

		gsl_poly_complex pc(n);

		ensure (0 == pc.solve(pp->array, n, r.array()));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return r.get();
}