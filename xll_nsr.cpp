// xll_nsr.cpp - Normal short rate model.
#include <functional>
#include "xll_nsr.h"
#include "xll_gsl.h"

using namespace xll;

static AddInX xai_caplet_value(
	FunctionX(XLL_DOUBLEX, _T("?xll_caplet_value"), _T("NSR.CAPLET.VALUE"))
	.Handle(_T("D"), _T("is a handle to a discount function."))
	.Num(_T("sigma"), _T("is the normal volatility"))
	.Num(_T("u"), _T("effecivt"))
	.Num(_T("v"), _T("expiration"))
	.Num(_T("k"), _T("strike"))
	.FunctionHelp(_T("Return normal short rate caplet value."))
	.Category(_T("NSR"))
	.Documentation()
	);
double WINAPI xll_caplet_value(HANDLEX D, double sigma, double u, double v, double k)
{
#pragma XLLEXPORT
	doublex c;

	try {
		handle<std::function<double(double)>> D_(D);
		//!!! implement caplet value
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return c;
}

#ifdef _DEBUG
XLL_TEST_BEGIN(xll_nsr_test)

	test_nsr();

XLL_TEST_END(xll_nsr_test)
#endif // _DEBUG