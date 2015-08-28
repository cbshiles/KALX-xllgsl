// xll_poly.cpp - polynomials and their roots
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.

#pragma warning(disable: 4127)
#define HAVE_INLINE
#define HAVE_C99_INLINE
#include "gsl/gsl_poly.h"
#include "xll_gsl.h"

#define IS_POLY _T("is an array of polynomial coefficients")

using namespace xll;

static AddIn xai_poly_solve_quadratic(
	Function(XLL_FP, "?xll_poly_solve_quadratic", "GSL.POLY.SOLVE.QUADRATIC")
	.Arg(XLL_DOUBLE, "a", "is the coefficient of x^2.")
	.Arg(XLL_DOUBLE, "b", "is the coefficient of x.")
	.Arg(XLL_DOUBLE, "c", "is the constant term. ")
	.Category("GSL")
	.FunctionHelp("Return the roots of ax^2 + bx + c = 0 in a 1x2 array.")
	.Documentation(
		"The real roots (either zero, one or two) are returned."
		"</para><para>"
		"The number of roots found depends on the sign of the discriminant b^2 - 4 a c. This will be subject to rounding and cancellation errors when computed in double precision, and will also be subject to errors if the coefficients of the polynomial are inexact. These errors may cause a discrete change in the number of roots. However, for polynomials with small integer coefficients the discriminant can always be computed exactly. "
	)
);
xfpx* WINAPI xll_poly_solve_quadratic(double a, double b, double c)
{
#pragma XLLEXPORT
	static FPX x(1,2);

	x[0] = std::numeric_limits<double>::quiet_NaN();
	x[1] = std::numeric_limits<double>::quiet_NaN();

	gsl_poly_solve_quadratic(a, b, c, &x[0], &x[1]);

	return x.get();
}

static AddInX xai_poly_eval(
	FunctionX(XLL_FPX, _T("?xll_poly_eval"), PREFIX _T("POLY.EVAL"))
	.Arg(XLL_FPX, _T("p"), IS_POLY)
	.Arg(XLL_FPX, _T("x"), _T("is the number at which to evaluate the polynomial "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Evaluate the polynomial p(x)."))
	.Documentation(_T("")
	)
);
xfpx* WINAPI
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
	FunctionX(XLL_FPX, _T("?xll_poly_complex_solve"), PREFIX _T("POLY.COMPLEX.SOLVE"))
	.Arg(XLL_FPX, _T("p"), IS_POLY)
	.Category(CATEGORY)
	.FunctionHelp(_T("Compute all the roots of a the polynomial p."))
	.Documentation(
		_T("The implementation uses a balanced-QR reduction of the companion matrix. ")
		_T("If <math>n</math> specifies the length of the coefficient array then <math>n - </math>1 roots are returned. ")
		_T("The coefficient of the highest order term must be non-zero. ")
	)
);
xfpx* WINAPI
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