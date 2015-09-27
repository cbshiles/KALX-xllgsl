// xll_gsl.h - common header file for all GSL routines
// http://www.gnu.org/software/gsl/manual/html_node/
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
// Uncomment for Excel 2007 and above.
#pragma once
#include "gsl/gsl_errno.h"
#include "gsl/gsl_complex.h"
//#define EXCEL12
#include "xll/xll.h"

#define CATEGORY _T("GSL")
#define PREFIX CATEGORY _T(".")

#define IS_NUM _T("is a number")
#define IS_PREC _T("is the precision from the GSL_PREC_* enumeration")
#define IS_COMPLEX _T("is a two element array of the real and imaginary parts of a complex number")
#define IS_REAL_OR_COMPLEX _T("is a number or a two element array of the real and imaginary parts of a complex number")

typedef xll::traits<XLOPERX>::xword xword;
typedef xll::traits<XLOPERX>::xchar xchar;

template<class X> struct xfp_complex;

typedef xfp_complex<XLOPER> fp_complex;
typedef xfp_complex<XLOPER12> fp12_complex;
typedef xfp_complex<XLOPERX> fpx_complex;
