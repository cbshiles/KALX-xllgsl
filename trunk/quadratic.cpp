// quadratic.cpp - Roots of the quadratic equation.
#include "gsl/gsl_poly.h"
#include "gsl.h"

using namespace xll;

static AddIn xai_poly_solve_quadratic(
	Function(XLL_FP, "?xll_poly_solve_quadratic", "POLY.SOLVE.QUADRATIC")
	.Arg(XLL_DOUBLE, "a", "is the coefficient of x^2.")
	.Arg(XLL_DOUBLE, "b", "is the coefficient of x.")
	.Arg(XLL_DOUBLE, "c", "is the constant term. ")
	.Category(CATEGORY)
	.FunctionHelp("Return the roots of ax^2 + bx + c = 0 in a 2x1 array.")
	.Documentation(
		"The number of real roots (either zero, one or two) is returned, and their locations are stored in x0 and x1. If no real roots are found then x0 and x1 are not modified. If one real root is found (i.e. if a=0) then it is stored in x0. When two real roots are found they are stored in x0 and x1 in ascending order. The case of coincident roots is not considered special. For example (x-1)^2=0 will have two roots, which happen to have exactly equal values."
		"</para><para>"
		"The number of roots found depends on the sign of the discriminant b^2 - 4 a c. This will be subject to rounding and cancellation errors when computed in double precision, and will also be subject to errors if the coefficients of the polynomial are inexact. These errors may cause a discrete change in the number of roots. However, for polynomials with small integer coefficients the discriminant can always be computed exactly. "
	)
);
xfp* WINAPI xll_poly_solve_quadratic(double a, double b, double c)
{
#pragma XLLEXPORT
	static FPX x(2,1);

	gsl_poly_solve_quadratic(a, b, c, &x[0], &x[1]);

	return x.get();
}