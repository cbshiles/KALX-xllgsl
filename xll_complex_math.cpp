// xll_complex_math.cpp - Regular Cylindrical Bessel Functions
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#pragma warning(disable: 4127)
#include "gsl/gsl_complex_math.h"
#include "xll_gsl.h"

#ifndef CATEGORY
#define CATEGORY _T("Complex Numbers")
#endif

// double[2] to gsl_complex
//#define GSL_COMPLEX(x) (*((gsl_complex*)x)) 
using namespace xll;

//XLL_ENUM_DOC(GSL_COMPLEX_ONE, GSL_COMPLEX_ONE, CATEGORY, _T("The complex number 1."), _T(""))
//XLL_ENUM_DOC(GSL_COMPLEX_ZERO, GSL_COMPLEX_ZERO, CATEGORY, _T("The complex number 0."), _T(""))
//XLL_ENUM_DOC(GSL_COMPLEX_NEGONE, GSL_COMPLEX_NEGONE, CATEGORY, _T("The complex number -1."), _T(""))

static AddInX xai_complex_polar(
	FunctionX(XLL_FPX, _T("?xll_complex_polar"), PREFIX _T("COMPLEX.POLAR"))
	.Arg(XLL_DOUBLEX, _T("r"), _T("is the distance to the origin"))
	.Arg(XLL_DOUBLEX, _T("theta"), _T("is the angle in radians from the positive x-axis "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Create a complex number from its polar representation."))
	.Documentation(
		_T("<codeInline>COMPLEX.POLAR(1, PI())</codeInline> is not equal to -1! ")
	)
);
xfpx* WINAPI
xll_complex_polar(double r, double theta)
{
#pragma XLLEXPORT
	static fpx_complex z;

	z = gsl_complex_polar(r, theta);

	return &z;
}

static AddInX xai_complex_rect(
	FunctionX(XLL_FPX, _T("?xll_complex_rect"), PREFIX _T("COMPLEX.RECT"))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is the real part of the complex number"))
	.Arg(XLL_DOUBLEX, _T("y"), _T("is the imaginary part of the complex number "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Create a complex number from its rectangular representation."))
	.Documentation(
	)
);
xfpx* WINAPI
xll_complex_rect(double x, double y)
{
#pragma XLLEXPORT
	static fpx_complex z;

	z = gsl_complex_rect(x, y);

	return &z;
}

static AddInX xai_complex_arg(
	FunctionX(XLL_DOUBLEX, _T("?xll_complex_arg"), PREFIX _T("COMPLEX.ARG"))
	.Arg(XLL_FPX, _T("Arg"), IS_COMPLEX)
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the angle in radians of Arg from the positive real axis."))
	.Documentation(
		_T("The value returned is between -") _T(ENT_pi) _T(" and ") _T(ENT_pi)
	)
);
double WINAPI
xll_complex_arg(const xfpx* pz)
{
#pragma XLLEXPORT
	if (size(*pz) != 2) {
		XLL_ERROR("COMPLEX.ARG: the argument must be an array of the real and imaginary parts of a complex number.");
	}

	return gsl_complex_arg(fpx_complex(*pz).gsl());
}
static AddInX xai_complex_abs(
	FunctionX(XLL_DOUBLEX, _T("?xll_complex_abs"), PREFIX _T("COMPLEX.ABS"))
	.Arg(XLL_FPX, _T("Arg"), IS_COMPLEX)
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the distance from the origin of Arg."))
	.Documentation(
		_T("This is also called the <newTerm>modulus</newTerm> of the argument. ")
	)
);
double WINAPI
xll_complex_abs(xfpx* pz)
{
#pragma XLLEXPORT
	if (size(*pz) != 2) {
		XLL_ERROR("COMPLEX.ABS: the argument must be an array of the real and imaginary parts of a complex number.");
	}

	return gsl_complex_abs(fpx_complex(*pz).gsl());
}
static AddInX xai_complex_abs2(
	FunctionX(XLL_DOUBLEX, _T("?xll_complex_abs2"), PREFIX _T("COMPLEX.ABS2"))
	.Arg(XLL_FPX, _T("Arg"), IS_COMPLEX)
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the square of the distance from the origin of Arg."))
	.Documentation(
		_T("This is also called the <newTerm>modulus squared</newTerm> of the argument. ")
	)
);
double WINAPI
xll_complex_abs2(xfpx* pz)
{
#pragma XLLEXPORT
	if (size(*pz) != 2) {
		XLL_ERROR("COMPLEX.ABS2: the argument must be an array of the real and imaginary parts of a complex number.");
	}

	return gsl_complex_abs2(fpx_complex(*pz).gsl());
}
static AddInX xai_complex_logabs(
	FunctionX(XLL_DOUBLEX, _T("?xll_complex_logabs"), PREFIX _T("COMPLEX.LOGABS"))
	.Arg(XLL_FPX, _T("Arg"), IS_COMPLEX)
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the natural logarithm of the distance from the origin of Arg."))
	.Documentation(
		_T("This is also called the <newTerm>log modulus</newTerm> of the argument. ")
	)
);
double WINAPI
xll_complex_logabs(xfpx* pz)
{
#pragma XLLEXPORT
	if (size(*pz) != 2) {
		XLL_ERROR("COMPLEX.LOGABS: the argument must be an array of the real and imaginary parts of a complex number.");
	}

	return gsl_complex_logabs(fpx_complex(*pz).gsl());
}

// binary functions
static AddInX xai_complex_add(
	FunctionX(XLL_FPX, _T("?xll_complex_add"), PREFIX _T("COMPLEX.ADD"))
	.Arg(XLL_FPX, _T("x"), IS_COMPLEX)
	.Arg(XLL_FPX, _T("y"), IS_REAL_OR_COMPLEX)
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the complex sum of x and y."))
	.Documentation(_T("<math>x + y</math>"))
);
xfpx* WINAPI
xll_complex_add(xfpx* px, xfpx* py)
{
#pragma XLLEXPORT
	static fpx_complex z;

	if (size(*px) != 2) {
		XLL_ERROR("COMPLEX.ADD: the first argument must be an array of the real and imaginary parts of a complex number.");

		return 0;
	}
	if (size(*py) == 1) {
		z = gsl_complex_add_real(fpx_complex(*px).gsl(), py->array[0]);
	}
	else {
		z = gsl_complex_add(fpx_complex(*px).gsl(), fpx_complex(*py).gsl());
	}

	return &z;
}
static AddInX xai_complex_sub(
	FunctionX(XLL_FPX, _T("?xll_complex_sub"), PREFIX _T("COMPLEX.SUB"))
	.Arg(XLL_FPX, _T("x"), IS_COMPLEX)
	.Arg(XLL_FPX, _T("y"), IS_COMPLEX)
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the complex difference of x and y."))
	.Documentation(_T("<math>x - y</math>"))
);
xfpx* WINAPI
xll_complex_sub(xfpx* px, xfpx* py)
{
#pragma XLLEXPORT
	static fpx_complex z;

	if (size(*px) != 2) {
		XLL_ERROR("COMPLEX.SUB: the first argument must be an array of the real and imaginary parts of a complex number.");

		return 0;
	}
	if (size(*py) == 1) {
		z = gsl_complex_sub_real(fpx_complex(*px).gsl(), py->array[0]);
	}
	else {
		z = gsl_complex_sub(fpx_complex(*px).gsl(), fpx_complex(*py).gsl());
	}

	return &z;
}
static AddInX xai_complex_mul(
	FunctionX(XLL_FPX, _T("?xll_complex_mul"), PREFIX _T("COMPLEX.MUL"))
	.Arg(XLL_FPX, _T("x"), IS_COMPLEX)
	.Arg(XLL_FPX, _T("y"), IS_REAL_OR_COMPLEX)
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the complex product of x and y."))
	.Documentation(_T("<math>x ") _T(ENT_times) _T(" y</math>"))
);
xfpx* WINAPI
xll_complex_mul(xfpx* px, xfpx* py)
{
#pragma XLLEXPORT
	static fpx_complex z;

	if (size(*px) != 2) {
		XLL_ERROR("COMPLEX.MUL: the first argument must be an array of the real and imaginary parts of a complex number.");

		return 0;
	}
	if (size(*py) == 1) {
		z = gsl_complex_mul_real(fpx_complex(*px).gsl(), py->array[0]);
	}
	else {
		z = gsl_complex_mul(fpx_complex(*px).gsl(), fpx_complex(*py).gsl());
	}

	return &z;
}
static AddInX xai_complex_div(
	FunctionX(XLL_FPX, _T("?xll_complex_div"), PREFIX _T("COMPLEX.DIV"))
	.Arg(XLL_FPX, _T("x"), IS_COMPLEX)
	.Arg(XLL_FPX, _T("y"), IS_COMPLEX)
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the complex quotient of x and y."))
	.Documentation(_T("<math>x / y</math>"))
);
xfpx* WINAPI
xll_complex_div(xfpx* px, xfpx* py)
{
#pragma XLLEXPORT
	static fpx_complex z;

	if (size(*px) != 2) {
		XLL_ERROR("COMPLEX.DIV: the first argument must be an array of the real and imaginary parts of a complex number.");

		return 0;
	}
	if (size(*py) == 1) {
		z = gsl_complex_div_real(fpx_complex(*px).gsl(), py->array[0]);
	}
	else {
		z = gsl_complex_div(fpx_complex(*px).gsl(), fpx_complex(*py).gsl());
	}

	return &z;
}

static AddInX xai_complex_pow(
	FunctionX(XLL_FPX, _T("?xll_complex_pow"), PREFIX _T("COMPLEX.POW"))
	.Arg(XLL_FPX, _T("x"), IS_COMPLEX)
	.Arg(XLL_FPX, _T("y"), IS_COMPLEX)
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the complex power of x to the y."))
	.Documentation(_T("<math>x<superscript>y</superscript></math>"))
);
xfpx* WINAPI
xll_complex_pow(xfpx* px, xfpx* py)
{
#pragma XLLEXPORT
	static fpx_complex z;

	if (size(*px) != 2) {
		XLL_ERROR("COMPLEX.POW: the first argument must be an array of the real and imaginary parts of a complex number.");

		return 0;
	}
	if (size(*py) == 1) {
		z = gsl_complex_pow_real(fpx_complex(*px).gsl(), py->array[0]);
	}
	else {
		z = gsl_complex_pow(fpx_complex(*px).gsl(), fpx_complex(*py).gsl());
	}

	return &z;
}

// unary functions

#define ARG_ERR  ": the argument must be an array of the real and imaginary parts of a complex number."

template<class X>
typename traits<X>::xfp* complex_unary(gsl_complex(*f)(gsl_complex), typename traits<X>::xfp* pz)
{
	ensure (size(*pz) == 2);

	gsl_complex z;

	z.dat[0] = pz->array[0];
	z.dat[1] = pz->array[1];

	z = f(z);

	pz->array[0] = z.dat[0];
	pz->array[1] = z.dat[1];

	return pz;
}

static AddInX xai_complex_congjugate(
	FunctionX(XLL_FPX , _T("xll_complex_conjugate"), PREFIX _T("COMPLEX.CONJUGATE"))
	.Arg(XLL_FPX, _T("Arg"), IS_COMPLEX)
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the complex conjugate of Arg"))
	.Documentation(_T("The conjugate of <math>x + i y</math> is <math>x - iy</math>." ))
);
extern "C" __declspec(dllexport) 
xfpx* xll_complex_conjugate(xfpx* pz)
{
	if (size(*pz) != 2) {
		XLL_ERROR("COMPLEX.CONJUGATE" ARG_ERR);

		return 0;
	}

	pz = complex_unary<XLOPERX>(gsl_complex_conjugate, pz);

	return pz;
}
#define COMPLEX_UNARY(f, F, FH, D) static AddInX xai_ ## f(FunctionX(XLL_FPX, _T(ENSURE_STRZ_(xll_ ## f)), _T(F)) \
	.Arg(XLL_FPX, _T("Arg"), IS_COMPLEX).Category(CATEGORY).FunctionHelp(_T(FH)).Documentation(_T(D))); \
	extern "C" __declspec(dllexport) xfpx* xll_ ## f(xfpx* pz) { \
	if (size(*pz) != 2) { XLL_ERROR(F ARG_ERR); return 0; } \
	return complex_unary<XLOPERX>(gsl_ ## f, pz); }

COMPLEX_UNARY(complex_inverse, "GSL.COMPLEX.INVERSE", 
	"Return the complex inverse of Arg.", 
	"The inverse of <math>z</math> is <math>1/z</math>.")
COMPLEX_UNARY(complex_negative, "GSL.COMPLEX.NEGATIVE", 
	"Return the complex negative of Arg.", 
	"The inverse of <math>z</math> is <math>-z</math>.")

COMPLEX_UNARY(complex_sqrt, "GSL.COMPLEX.SQRT", 
	"Return the complex principal square root of Arg.", 
	"The square root of <math>z</math> is denoted <math>&#8730;z</math>.")
COMPLEX_UNARY(complex_exp, "GSL.COMPLEX.EXP", 
	"Return the complex exponential of Arg.", 
	"The exponential of <math>z</math> is <math>e<superscript>z</superscript></math>.")
COMPLEX_UNARY(complex_log, "GSL.COMPLEX.LOG", 
	"Return the complex natural logarithm of Arg.", 
	"The logarithm of <math>z</math> is log <math>z</math>.")
COMPLEX_UNARY(complex_log10, "GSL.COMPLEX.LOG10", 
	"Return the complex base 10 logarithm of Arg.", 
	"The base 10 logarithm of <math>z</math> is log<math><subscript>10</subscript> z</math>.")

// complex trigonometric functions
COMPLEX_UNARY(complex_sin, "GSL.COMPLEX.SIN", 
	"Return the complex sine of Arg.", 
	"The sine of <math>z</math> is sin <math>z</math>.")
COMPLEX_UNARY(complex_cos, "GSL.COMPLEX.COS", 
	"Return the complex cosine of Arg.", 
	"The cosine of <math>z</math> is cos <math>z</math>.")
COMPLEX_UNARY(complex_tan, "GSL.COMPLEX.TAN", 
	"Return the complex tangent of Arg.", 
	"The tangent of <math>z</math> is tan <math>z = </math>cos<math> z/</math>sin<math> z</math>.")
COMPLEX_UNARY(complex_sec, "GSL.COMPLEX.SEC", 
	"Return the complex secant of Arg.", 
	"The secant of <math>z</math> is sec <math>z = 1/</math>sin<math> z</math>.")
COMPLEX_UNARY(complex_csc, "GSL.COMPLEX.CSC", 
	"Return the complex cosecant of Arg.", 
	"The cosecant of <math>z</math> is csc <math>z = 1/</math>cos<math> z</math>.")
COMPLEX_UNARY(complex_cot, "GSL.COMPLEX.COT", 
	"Return the complex cotangent of Arg.", 
	"The cotangent of <math>z</math> is cot <math>z = 1/</math>tan<math> z</math>.")

// complex inverse trigonometric functions
COMPLEX_UNARY(complex_arcsin, "GSL.COMPLEX.ARCSIN", 
	"Return the complex arc sine of Arg.", 
	"The arc sine of <math>z</math> is arcsin <math>z = </math>sin<math><superscript>-</superscript>&#185; z</math>.")
COMPLEX_UNARY(complex_arccos, "GSL.COMPLEX.ARCCOS", 
	"Return the complex arc cosine of Arg.", 
	"The arc cosine of <math>z</math> is arccos <math>z = </math>cos<math><superscript>-</superscript>&#185; z</math>." _T(ENT_sup1))
COMPLEX_UNARY(complex_arctan, "GSL.COMPLEX.ARCTAN", 
	"Return the complex arc tangent of Arg.", 
	"The arc tangent of <math>z</math> is arctan <math>z = </math>tan<math><superscript>-</superscript>&#185; z</math>.")
COMPLEX_UNARY(complex_arcsec, "GSL.COMPLEX.ARCSEC", 
	"Return the complex arc secant of Arg.", 
	"The arc secant of <math>z</math> is arcsec <math>z = </math>sec<math><superscript>-</superscript>&#185; z</math>.")
COMPLEX_UNARY(complex_arccsc, "GSL.COMPLEX.ARCCSC", 
	"Return the complex arc cosecant of Arg.", 
	"The arc cosecant of <math>z</math> is arccsc <math>z = </math>csc<math><superscript>-</superscript>&#185; z</math>.")
COMPLEX_UNARY(complex_arccot, "GSL.COMPLEX.ARCCOT", 
	"Return the complex arc cotangent of Arg.", 
	"The arc cotangent of <math>z</math> is arccot <math>z = </math>cot<math><superscript>-</superscript>&#185; z</math>.")

// complex hyperbolic functions
COMPLEX_UNARY(complex_sinh, "GSL.COMPLEX.SINH", 
	"Return the complex hyperbolic sin of Arg.", 
	"The hyperbolic sin of <math>z</math> is sinh<math> z = (e<superscript>z</superscript> - e<superscript>-z</superscript>)/2</math>.")
COMPLEX_UNARY(complex_cosh, "GSL.COMPLEX.COSH", 
	"Return the complex hyperbolic cosine of Arg.", 
	"The hyperbolic cosine of <math>z</math> is cosh<math> z = (e<superscript>z</superscript> + e<superscript>z</superscript>)/2</math>.")
COMPLEX_UNARY(complex_tanh, "GSL.COMPLEX.TANH", 
	"Return the complex hyperbolic tangent of Arg.", 
	"The hyperbolic tangent of <math>z</math> is tanh<math> z = </math>sinh<math> z/</math>cosh<math> z</math>.")
COMPLEX_UNARY(complex_sech, "GSL.COMPLEX.SECH", 
	"Return the complex hyperbolic secant of Arg.", 
	"The hyperbolic secant of <math>z</math> is sech<math> z = 1/</math>sinh<math> z</math>.")
COMPLEX_UNARY(complex_csch, "GSL.COMPLEX.CSCH", 
	"Return the complex hyperbolic cosecant of Arg.", 
	"The hyperbolic cosecant of <math>z</math> is csch<math> z = 1/</math>cosh<math> z</math>.")
COMPLEX_UNARY(complex_coth, "GSL.COMPLEX.COTH", 
	"Return the complex hyperbolic cotangent of Arg.", 
	"The hyperbolic cotangent of <math>z</math> is coth<math> z = 1/</math>tanh<math> z</math>.")

// complex inverse hyperbolic functions
COMPLEX_UNARY(complex_arcsinh, "GSL.COMPLEX.ARCSINH", 
	"Return the complex hyperbolic arc sine of Arg.", 
	"The hyperbolic arc sine of <math>z</math> is arcsinh <math>z = </math>sinh<math><superscript>-</superscript>&#185; z</math>.")
COMPLEX_UNARY(complex_arccosh, "GSL.COMPLEX.ARCCOSH", 
	"Return the complex hyperbolic arc cosine of Arg.", 
	"The hyperbolic arc cosine of <math>z</math> is arccosh <math>z = </math>cosh<math><superscript>-</superscript>&#185; z</math>.")
COMPLEX_UNARY(complex_arctanh, "GSL.COMPLEX.ARCTANH", 
	"Return the complex hyperbolic arc tangent of Arg.", 
	"The hyperbolic arc tangent of <math>z</math> is arctanh <math>z = </math>tanh<math><superscript>-</superscript>&#185; z</math>.")
COMPLEX_UNARY(complex_arcsech, "GSL.COMPLEX.ARCSECH", 
	"Return the complex hyperbolic arc secant of Arg.", 
	"The hyperbolic arc secant of <math>z</math> is arcsech <math>z = </math>sech<math><superscript>-</superscript>&#185; z</math>.")
COMPLEX_UNARY(complex_arccsch, "GSL.COMPLEX.ARCCSCH", 
	"Return the complex hyperbolic arc cosecant of Arg.", 
	"The hyperbolic arc cosecant of <math>z</math> is arccsch <math>z = </math>csch<math><superscript>-</superscript>&#185; z</math>.")
COMPLEX_UNARY(complex_arccoth, "GSL.COMPLEX.ARCCOTH", 
	"Return the complex hyperbolic arc cotangent of Arg.", 
	"The hyperbolic arc cotangent of <math>z</math> is arccoth <math>z = </math>coth<math><superscript>-</superscript>&#185; z</math>.")



#ifdef _DEBUG

#define EVAL(e) Excel<XLOPERX>(xlfEvaluate, OPERX(_T(e)))
XLL_TEST_BEGIN(complex_math)

	fpx_complex z;
	ensure (z[0] == 0);
	ensure (z[1] == 0);

	fpx_complex z2(1);
	ensure (z2[0] == 1);
	ensure (z2[1] == 0);

	gsl_complex w;
	GSL_SET_COMPLEX(&w, 2, 3);
	ensure (w.dat[0] == 2);
	ensure (w.dat[1] == 3);

	fpx_complex z3(w);
	ensure (z3[0] == 2);
	ensure (z3[1] == 3);

	gsl_complex w2;
	w2 = z3.gsl();
	ensure (GSL_COMPLEX_EQ(w, w2));
	OPERX one = XLL_EVALUATE(_T("GSL.COMPLEX.POLAR(1,0)"));
	OPER one1 = Excel<XLOPER>(xlfEvaluate, OPER("GSL.COMPLEX.POLAR(1,0)"));
	one1.size();
//	ensure (one.size() == 2);
//	ensure (one[0] == 1);
//	ensure (one[1] == 0);
/*	XLL_ENSURE(_T("{1, 0} = GSL.COMPLEX.POLAR(1, 0)"));
	XLL_ENSURE(_T("{1, 0} = GSL.COMPLEX.POLAR(1, 0)"));
//		XLL_ENSURE(_T("{-1, 0} = GSL.COMPLEX.POLAR(1, PI())")); // fails!
	XLL_ENSURE(_T("{4,6} = GSL.COMPLEX.ADD({1,2},{3,4})"));
	XLL_ENSURE(_T("{-2,-2} = GSL.COMPLEX.SUB({1,2},{3,4})"));
	XLL_ENSURE(_T("{-5,10} = GSL.COMPLEX.MUL({1,2},{3,4})"));
	OPERX div = XLL_EVALUATE(_T("GSL.COMPLEX.DIV({1,2},{3,4})"));
	OPERX inv = XLL_EVALUATE(_T("GSL.COMPLEX.MUL({1,2},GSL.COMPLEX.INVERSE({3,4}))"));
	ensure (fabs(inv[0] - div[0]) < 1e-16);
	ensure (fabs(inv[1] - div[1]) < 1e-16);
*/
XLL_TEST_END(complex_math)

#endif // _DEBUG
