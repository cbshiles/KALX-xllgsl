// xll_njr.cpp - normal Jarrow-Rudd
#include "xll/xll.h"
#include "xll_njr.h"

using namespace xll;

static AddInX xai_std_normal_ddf(
	FunctionX(XLL_DOUBLEX, _T("?xll_std_normal_ddf"), _T("NJR.DDF"))
	.Arg(XLL_WORDX, _T("n"), _T("n-th derivative"))
	.Arg(XLL_DOUBLEX, _T("x"), _T("value at which to compute the n-th derivative."))
	.Category(_T("NJR"))
	.FunctionHelp(_T("Return n-th derivative of standard normal cdf at x."))
);
double WINAPI xll_std_normal_ddf(WORD n, double x)
{
#pragma XLLEXPORT
	return njr::std_normal_ddf(n, x);
}

static AddInX xai_njr_bell(
	FunctionX(XLL_FPX, _T("?xll_njr_bell"), _T("NJR.BELL"))
	.Arg(XLL_WORDX, _T("n"), _T("is the order of the bell polynomial"))
	.Arg(XLL_FPX, _T("x"), _T("are the values at which to compute the Bell polynomial."))
	.Category(_T("NJR"))
	.FunctionHelp(_T("Return (n + 1) x 1 array of B_0,...,B_n(x_0,...,x_{n-1}"))
);
xfpx* WINAPI xll_njr_bell(WORD n, const xfpx* px)
{
#pragma XLLEXPORT
	static FPX B;

	B.resize(n + 1, 1);
	njr::Bell(size(*px), px->array, B.size(), B.array());

	return B.get();
}
static AddInX xai_njr_bell_reduced(
	FunctionX(XLL_FPX, _T("?xll_njr_bell_reduced"), _T("NJR.BELL.REDUCED"))
	.Arg(XLL_WORDX, _T("n"), _T("is the order of the bell polynomial"))
	.Arg(XLL_FPX, _T("x"), _T("are the values at which to compute the reduced Bell polynomial."))
	.Category(_T("NJR"))
	.FunctionHelp(_T("Return (n + 1) x 1 array of b_0,...,b_n(x_0,...,x_{n-1}"))
	);
xfpx* WINAPI xll_njr_bell_reduced(WORD n, const xfpx* px)
{
#pragma XLLEXPORT
	static FPX b;

	b.resize(n + 1, 1);
	njr::bell(size(*px), px->array, b.size(), b.array());

	return b.get();
}

static AddInX xai_njr_kappa_(
	FunctionX(XLL_FPX, _T("?xll_njr_kappa_"), _T("NJR.KAPPA_"))
	.Num(_T("s"), _T("is a number."))
	.Arg(XLL_FPX, _T("x"), _T("are the cumulant values."))
	.Arg(XLL_WORDX, _T("n"), _T("is number of adjusted cumulants to compute."))
	.Category(_T("NJR"))
	.FunctionHelp(_T("Return kappa_[i] = sum_{j>=0} kappa[i + j] s^j/j!"))
);
xfpx* WINAPI xll_njr_kappa_(double s, const xfpx* pk, WORD n)
{
#pragma XLLEXPORT
	static FPX k_;

	try {
		if (n == 0)
			n = 2*size(*pk);
		k_.resize(n, 1);
		njr::kappa_(s, size(*pk), pk->array, k_.size(), k_.array());
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return k_.get();
}

static AddInX xai_njr_cdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_njr_cdf"), _T("NJR.CDF"))
	.Arg(XLL_DOUBLEX, _T("x"), _T("value at which to compute the cumulative distribution."))
	.Arg(XLL_FPX, _T("kappa"), _T("the perturbations of the stanard normal cumulants."))
	.Category(_T("NJR"))
	.FunctionHelp(_T("Return the perturbed cumulative distribution at x."))
	);
double WINAPI xll_njr_cdf(double x, xfpx* pkappa)
{
#pragma XLLEXPORT
	doublex G;

	try {
		G = njr::cdf(x, size(*pkappa), pkappa->array);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return G;
}


static AddInX xai_njr_put_value(
	FunctionX(XLL_DOUBLEX, _T("?xll_njr_put_value"), _T("NJR.PUT.VALUE"))
	.Num(_T("f"), _T("forward"), 100)
	.Num(_T("sigma"), _T("vol"), .2)
	.Num(_T("k"), _T("strike"), 100)
	.Num(_T("t"), _T("expiration"), .25)
	.Arg(XLL_FPX, _T("kappa"), _T("perturbation of standard normal cumulants"), 0)
	.FunctionHelp(_T("Return Black put value."))
	.Category(_T("BSM"))
	.Documentation()
	);
double WINAPI xll_njr_put_value(double f, double sigma, double k, double t, xfpx* pkappa)
{
#pragma XLLEXPORT
	doublex v;

	try {
		v = njr::put_value(f, sigma, k, t, size(*pkappa), pkappa->array);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return v;
}
#ifdef _DEBUG
XLL_TEST_BEGIN(xll_njr)

test_njr_hermite();
test_njr_bell();

XLL_TEST_END(xll_njr)
#endif // _DEBUG