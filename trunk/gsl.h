// gsl.h - common header file for all GSL routines
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
// Uncomment for Excel 2007 and above.
//#define EXCEL12
#pragma once
#include "gsl/gsl_complex.h"
#include "xll/xll.h"

#define CATEGORY _T("GSL")
#define PREFIX _T("GSL.")

#define IS_NUM _T("is a number")
#define IS_PREC _T("is the precision from the PREC_* enumeration")
#define IS_COMPLEX _T("is a two element array of the real and imaginary parts of a complex number")
#define IS_REAL_OR_COMPLEX _T("is a number of a two element array of the real and imaginary parts of a complex number")

// escape math mode
#define _R(s) _T("</math>" _T(s) _T("<math>"))

typedef xll::traits<XLOPERX>::xfp xfp;
typedef xll::traits<XLOPERX>::xword xword;

// GSL specific helper class
namespace xll {
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
			return array[i];
		}
		double &operator[](xword i)
		{
			return array[i];
		}
	};
	typedef xfp_complex<XLOPER>   fp_complex;
	typedef xfp_complex<XLOPER12> fp12_complex;
	typedef xfp_complex<XLOPERX>  fpx_complex;
}

