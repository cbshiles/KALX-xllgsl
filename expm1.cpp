// expm1.cpp - call expm1()
#include <cmath>
#include "xll/xll.h"

using namespace xll;

static AddInX xai_expm1(
	FunctionX(XLL_DOUBLEX, _T("?xll_expm1"), _T("XLL.EXPM1"))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is a number"))
	.Category(_T("XLL"))
	.FunctionHelp(_T("Return expm1() from <cmath>."))
);
double WINAPI xll_expm1(double x)
{
#pragma XLLEXPORT
	return expm1(x);
}