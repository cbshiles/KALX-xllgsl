// xll_nsr.cpp - Normal short rate model.
#include <functional>
#include "xll_nsr.h"
#include "xll_gsl.h"

using namespace xll;

static AddInX xai_caplet_value(
	FunctionX(XLL_DOUBLEX, _T("?xll_caplet_value"), _T("NSR.CAPLET.VALUE"))
	.Num(_T("Du"), _T("is the discount to time u."))
	.Num(_T("Dv"), _T("is the discount to time v."))
	.Num(_T("sigma"), _T("is the normal volatility"))
	.Num(_T("k"), _T("strike"))
	.Num(_T("u"), _T("effecivt"))
	.Num(_T("v"), _T("expiration"))
	.FunctionHelp(_T("Return normal short rate caplet value over the interval from u to v."))
	.Category(_T("NSR"))
	.Documentation()
	);
double WINAPI xll_caplet_value(double Du, double Dv, double sigma, double k, double u, double v)
{
#pragma XLLEXPORT
	doublex c;

	try {
		c = nsr::caplet_value(Du, Dv, sigma, k, u, v);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return c;
}

#ifdef _DEBUG
XLL_TEST_BEGIN(xll_test_nsr)

	test_nsr();

XLL_TEST_END(xll_test_nsr)
#endif // _DEBUG