// xll_sf_laguerre.cpp
// Author:Shuaijia Dai
#include "gsl/gsl_sf_laguerre.h"
#include "../xll_gsl.h"

using namespace xll;

/*
The generalized Laguerre polynomials are defined in terms of confluent hypergeometric functions as L^a_n(x) = ((a+1)_n / n!) 1F1(-n,a+1,x),
and are sometimes referred to as the associated Laguerre polynomials. They are related to the plain Laguerre polynomials L_n(x) by L^0_n(x)
= L_n(x) and L^k_n(x) = (-1)^k (d^k/dx^k) L_(n+k)(x). For more information see Abramowitz & Stegun, Chapter 22.
The functions described in this section are declared in the header file gsl_sf_laguerre.h.
*/

/*
Function: double gsl_sf_laguerre_n (const int n, const double a, const double x)
*/
static AddInX xai_xll_sf_laguerre_n(
	FunctionX(XLL_DOUBLEX, _T("?xll_sf_laguerre_n"), PREFIX _T("SF.LAGUERRE.N"))
	.Arg(XLL_WORDX, _T("n"), _T("is an integer"), 1)
	.Arg(XLL_DOUBLEX, _T("a"), _T("is a number."), 1.)
	.Arg(XLL_DOUBLEX, _T("x"), _T("is a number."), 1.)
	.Category(CATEGORY)
	.FunctionHelp(_T("The routine that evaluates the generalized Laguerre polynomials L^a_n(x) for a>-1, n>=0"))
	);
double WINAPI xll_sf_laguerre_n(WORD n, const double a,const double x)
{
#pragma XLLEXPORT
	gsl_sf_result result;

	try {
		auto status = gsl_sf_laguerre_n_e(n,a,x,&result);
		if (status != GSL_SUCCESS)
			throw std::runtime_error(gsl_strerror(status));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result.val;
}

#ifdef _DEBUG

XLL_TEST_BEGIN(test_sf_laguerre_n)


// table[LaguerreL[3,a,1.2],{a,1,2,.1}]
//https://www.wolframalpha.com/input/?i=table%5BLaguerreL%5B3%2Ca%2C1.2%5D%2C%7Ba%2C1%2C2%2C.1%7D%5D
double Ai[] = {-0.608,-0.5135,-0.4,-0.2665,-0.112,0.0645,0.264,0.4875,0.736,1.0105,1.312};
double epsilon = 1e-6;
for (int i = 0; i < sizeof(Ai) / sizeof(*Ai); ++i) {
	ensure(fabs(xll_sf_laguerre_n(3, 1 + i*0.1, 1.2) - Ai[i]) < epsilon);
}
// table[LaguerreL[n,1.7,1.2],{n,1,10,1}]
//https://www.wolframalpha.com/input/?i=table%5BLaguerreL%5Bn%2C1.7%2C1.2%5D%2C%7Bn%2C1%2C10%2C1%7D%5D
double Bi[] = {1.5000000,1.2750000,0.4875000,-0.5840625,-1.6654688,-2.5399453,-3.0664503,-3.1790570,-2.8765477,-2.2076770};

for (int i = 0; i < sizeof(Bi) / sizeof(*Bi); ++i) {
	ensure(fabs(xll_sf_laguerre_n(1+i, 1.7, 1.2) - Bi[i]) < epsilon);
}
// table[LaguerreL[2,1.7,x],{x,1,2,.1}]
//https://www.wolframalpha.com/input/?i=table%5BLaguerreL%5B2%2C1.7%2Cx%5D%2C%7Bx%2C1%2C2%2C.1%7D%5D
double Ci[] = {1.795,1.53,1.275,1.03,0.795,0.57,0.355,0.15,-0.045,-0.23,-0.405  };

for (int i = 0; i < sizeof(Ci) / sizeof(*Ci); ++i) {
	ensure(fabs(xll_sf_laguerre_n(2, 1.7, 1+i*0.1) - Ci[i]) < epsilon);
}
/*
double x = 0;
ensure(x == x);*/
XLL_TEST_END(test_sf_laguerre_n)


#endif // _DEBUG