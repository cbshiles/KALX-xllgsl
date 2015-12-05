// xll_vswap.cpp - variance swap pricer
#include "xll_vswap.h"
#include "xll/xll.h"

using namespace xll;

//!!! implement the Excel function
// XLL.VSWAP(Discount, Spot, Futures, Expansion, PutStrike, PutPrices, CallStrikes, CallPrices)
// Use the FP data type for arrays.
static AddInX xai_vswap(
	FunctionX(XLL_DOUBLEX, _T("?xll_vswap"), _T("XLL.VSWAP"))
	.Num(_T("Discount"), _T("is the discount to expiration"))
	.Num(_T("Spot"), _T("is the current spot price of the underlying."))
	.Num(_T("Futures"), _T("is the futures at expiration quote."))
	.Num(_T("Expansion"), _T("is the expansion point."))
	.Array(_T("PutStikes"), _T("is an array of put strikes."))
	.Array(_T("PutPrices"), _T("is an array of put prices at the corresponding strikes"))
	.Array(_T("CallStikes"), _T("is an array of call strikes."))
	.Array(_T("CallPrices"), _T("is an array of call prices at the corresponding strikes"))
);
double WINAPI xll_vswap(double D, double x0, double phi, double z,
	xfpx* kput, xfpx* put, xfpx* kcall, xfpx* call)
{
#pragma XLLEXPORT
	doublex vswap;

	try {
		ensure (size(*kput) == size(*put));
		ensure (size(*kcall) == size(*call));

		vswap = gsl::vswap(D, x0, phi, z, 
			size(*kput), kput->array, put->array,
			size(*kcall), kcall->array, call->array);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return vswap;
}


#ifdef _DEBUG
XLL_TEST_BEGIN(test_vswap)

std::vector<double> x{0,1,2,3}, y{1,2,4,0}, z(4);
gsl::pwfit(x.size(), &x[0], &y[0], &z[0]);

XLL_TEST_END(test_vswap)
#endif // _DEBUG