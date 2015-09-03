// xll_function.cpp - std::function<vector<double>(const vector<double>&)> objects
// Use allocators to avoid copying???
#include <functional>
#include "xll_gsl.h"

using namespace xll;

using function = std::function<double(double)>;

inline double udf(double regid, double x)
{
	// check regid???
	return XLL_XL_(UDF, OPERX(regid), OPERX(x)).val.num;
}

static AddInX xai_function_call(
	FunctionX(XLL_DOUBLEX, _T("?xll_function_call"), _T("XLL.FUNCTION.CALL"))
	.Arg(XLL_HANDLEX, _T("f"), _T("is the handle of a function."))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is an array of one or more number."))
	.Category(_T("XLL"))
	.FunctionHelp(_T("Returns f(x)."))
	.Documentation(_T(""))
);
double WINAPI xll_function_call(HANDLEX f, double x)
{
#pragma XLLEXPORT
	handlex y;

	try {
		handle<function> f_(f);

		y = (*f_)(x);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return y;
}

static AddInX xai_function_regid(
	FunctionX(XLL_HANDLEX, _T("?xll_function_regid"), _T("XLL.FUNCTION.REGID"))
	.Arg(XLL_HANDLEX, _T("Regid"), _T("is an array of register ids of functions taking a array and returning a double."))
	.Uncalced()
	.Category(_T("XLL"))
	.FunctionHelp(_T("Create a std::function<double(double)> handle."))
	.Documentation(_T(""))
);
HANDLEX WINAPI xll_function_regid(double regid)
{
#pragma XLLEXPORT
	handlex h;

	try {
		handle<function> h_(new function([regid](double x) {
			return udf(regid, x);
		}));

		h = h_.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}
