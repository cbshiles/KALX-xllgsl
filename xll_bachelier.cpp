// xll_bachelier.cpp
// Include appropriate header files below.
#include "xll_bachelier.h"
#include "xll/xll.h"

using namespace xll;

static AddIn xai_bachelier_put(
	Function(XLL_DOUBLE, "?xll_bachelier_put", "XLL.BACHELIER.PUT")
	.Num("f", "is the forward")
	.Num("sigma", "is the volatility")
	.Num("k", "is the strike")
	.Num("t", "is the expiration")
	.Category("XLL")
	.FunctionHelp("Return the Bachelier put value.")
);
double WINAPI xll_bachelier_put(double f, double sigma, double k,double t)
{
#pragma XLLEXPORT
	doublex value;

	try {
		return bachelier_put(f, sigma, k, t);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return value;
}

XLL_TEST_BEGIN(xll_bachelier)

test_bachelier_put();

XLL_TEST_END(xll_bachelier)


// Create a spreadsheet bachelier.xlsx that verifies the
// tests in test_bachelier_put.

