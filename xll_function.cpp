// xll_function.cpp - std::function<double(double)> objects
#include <functional>
#include "xll_gsl.h"

using namespace xll;

inline double regid_call(double regid, double x)
{
	return XLL_XL_(UDF, OPERX(regid), OPERX(x)).val.num;
}

static AddInX xai_function_call(
	FunctionX(XLL_DOUBLEX, _T("?xll_function_call"), _T("XLL.FUNCTION.CALL"))
	.Arg(XLL_DOUBLEX, _T("f"), _T("is the handle of a function taking a double and returning a double."))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is argument to call the function."))
	.Category(_T("XLL"))
	.FunctionHelp(_T("Returns f(x)."))
	.Documentation(_T(""))
);
double WINAPI xll_function_call(HANDLEX f, double x)
{
#pragma XLLEXPORT
	handlex y;

	try {
		handle<std::function<double(double)>> f_(f);

		y = (*f_)(x);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return y;
}

static AddInX xai_function_regid(
	FunctionX(XLL_HANDLEX, _T("?xll_function_regid"), _T("XLL.FUNCTION.REGID"))
	.Arg(XLL_DOUBLEX, _T("Regid"), _T("is the register id of a function taking a double and returning a double."))
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
		using function = std::function<double(double)>;

		handle<function> h_(new function([regid](double x) { return regid_call(regid, x);}));

		h = h_.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}
