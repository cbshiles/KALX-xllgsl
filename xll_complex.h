// xll_complex.h - complex numbers
#pragma once

namespace xll {
	// GSL specific helper class
	template<class X>
	struct xfp_complex {
		typename type_traits<X>::xword rows;
		typename type_traits<X>::xword columns;
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
		double& operator[](xword i)
		{
			ensure (i < 2);

			return array[i];
		}
	};
/*
	typedef xfp_complex<XLOPER>   fp_complex;
	typedef xfp_complex<XLOPER12> fp12_complex;
	typedef xfp_complex<XLOPERX>  fpx_complex;
*/
}