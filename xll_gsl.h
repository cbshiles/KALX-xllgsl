// xll_gsl.h - common header file for all GSL routines
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
// Uncomment for Excel 2007 and above.
//#define EXCEL12
#pragma once
#include "gsl/gsl_errno.h"
#include "gsl/gsl_complex.h"
#include "../xll8/xll/xll.h"

#define CATEGORY _T("GSL")
#define PREFIX CATEGORY _T(".")

#define IS_NUM _T("is a number")
#define IS_PREC _T("is the precision from the GSL_PREC_* enumeration")
#define IS_COMPLEX _T("is a two element array of the real and imaginary parts of a complex number")
#define IS_REAL_OR_COMPLEX _T("is a number or a two element array of the real and imaginary parts of a complex number")

typedef xll::traits<XLOPERX>::xfp xfp;
typedef xll::traits<XLOPERX>::xword xword;
typedef xll::traits<XLOPERX>::xchar xchar;

inline char* gsl_message(int status)
{
	switch (status) {
	case GSL_SUCCESS:
		return "";
		//!!! more cases
	default:
		return "GSL error";
	}
}

namespace xll {
// GSL specific helper class
	template<class X>
	struct xfp_complex {
		xword rows;
		xword columns;
		double array[2];
		xfp_complex(double x = 0, double y = 0)
			: rows(1), columns(2)
		{
			array[0] = x;
			array[1] = y;
		}
		xfp_complex(typename const xll::traits<X>::xfp& z)
			: rows(1), columns(2)
		{
			array[0] = z.array[0];
			array[1] = z.array[1];
		}
		xfp_complex(const gsl_complex& z)
			: rows(1), columns(2)
		{
			array[0] = z.dat[0];
			array[1] = z.dat[1];
		}
		xfp_complex& operator=(double x)
		{
			rows = 1;
			columns = 2;

			array[0] = x;
			array[1] = 0;

			return *this;
		}
		xfp_complex& operator=(const gsl_complex& z)
		{
			rows = 1;
			columns = 2;

			array[0] = z.dat[0];
			array[1] = z.dat[1];

			return *this;
		}
		xfp* operator&()
		{
			return reinterpret_cast<xfp*>(this);
		}
		gsl_complex gsl() const
		{
			gsl_complex z;

			z.dat[0] = array[0];
			z.dat[1] = array[1];

			return z;
		}
		double operator[](xword i) const
		{
			ensure (i < 2);

			return array[i];
		}
		double &operator[](xword i)
		{
			ensure (i < 2);

			return array[i];
		}
	};

	typedef xfp_complex<XLOPER>   fp_complex;
	typedef xfp_complex<XLOPER12> fp12_complex;
	typedef xfp_complex<XLOPERX>  fpx_complex;
}