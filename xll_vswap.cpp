// xll_vswap.cpp - variance swap pricer
#include "xll_vswap.h"
#include "xll/xll.h"

using namespace xll;

//!!! implement the Excel function
// XLL.VSWAP(Discount, Spot, Futures, Expansion, PutStrike, PutPrices, CallStrikes, CallPrices)
// Use the FP data type for arrays.


#ifdef _DEBUG
XLL_TEST_BEGIN(xll_vswap)

std::vector<double> x{0,1,2,3}, y{1,2,4,0}, z(4);
gsl::pwfit(x.size(), &x[0], &y[0], &z[0]);

XLL_TEST_END(xll_vswap)
#endif // _DEBUG