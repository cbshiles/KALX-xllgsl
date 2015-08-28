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

typedef xll::traits<XLOPERX>::xword xword;
typedef xll::traits<XLOPERX>::xchar xchar;

// convert error status to string from gsl_errno.h
inline char* gsl_message(int status)
{
	switch (status) {
		case GSL_SUCCESS: return "";
		case GSL_FAILURE: return "failure";
		case GSL_CONTINUE: return "iteration has not converged";
		case GSL_EDOM: return "input domain error, e.g sqrt(-1)";
		case GSL_ERANGE: return "output range error, e.g. exp(1e100)";
		case GSL_EFAULT: return "invalid pointer";
		case GSL_EINVAL: return "invalid argument supplied by user";
		case GSL_EFAILED: return "generic failure";
		case GSL_EFACTOR: return "factorization failed";
		case GSL_ESANITY: return "sanity check failed - shouldn't happen";
		case GSL_ENOMEM: return "malloc failed";
		case GSL_EBADFUNC: return "problem with user-supplied function";
		case GSL_ERUNAWAY: return "iterative process is out of control";
		case GSL_EMAXITER: return "exceeded max number of iterations";
		case GSL_EZERODIV: return "tried to divide by zero";
		case GSL_EBADTOL: return "user specified an invalid tolerance";
		case GSL_ETOL: return "failed to reach the specified tolerance";
		case GSL_EUNDRFLW: return "underflow";
		case GSL_EOVRFLW: return "overflow";
		case GSL_ELOSS: return "loss of accuracy";
		case GSL_EROUND: return "failed because of roundoff error";
		case GSL_EBADLEN: return "matrix, vector lengths are not conformant";
		case GSL_ENOTSQR: return "matrix not square";
		case GSL_ESING: return "apparent singularity detected";
		case GSL_EDIVERGE: return "integral or series is divergent";
		case GSL_EUNSUP: return "requested feature is not supported by the hardware";
		case GSL_EUNIMPL: return "requested feature not (yet) implemented";
		case GSL_ECACHE: return "cache limit exceeded";
		case GSL_ETABLE: return "table limit exceeded";
		case GSL_ENOPROG: return "iteration is not making progress towards solution";
		case GSL_ENOPROGJ: return "jacobian evaluations are not improving the solution";
		case GSL_ETOLF: return "cannot reach the specified tolerance in F";
		case GSL_ETOLX: return "cannot reach the specified tolerance in X";
		case GSL_ETOLG: return "cannot reach the specified tolerance in gradient";
		case GSL_EOF: return "end of file";
	}

	return "unknown error";
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
		xfpx* operator&()
		{
			return reinterpret_cast<xfpx*>(this);
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