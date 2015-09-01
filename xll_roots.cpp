// xll_roots.cpp - GSL 1-dim root finding
#include "xll_roots.h"
#include "xll_gsl.h"

using namespace xll;

XLL_ENUM_DOCX(p2h<const gsl_root_fsolver_type>(gsl_root_fsolver_bisection),GSL_ROOT_FSOLVER_BISECTION, CATEGORY, _T("Bisection method solver"), _T("Documentation"));
XLL_ENUM_DOCX(p2h<const gsl_root_fsolver_type>(gsl_root_fsolver_brent),GSL_ROOT_FSOLVER_BRENT, CATEGORY, _T("Brent method solver"), _T("Documentation"));
XLL_ENUM_DOCX(p2h<const gsl_root_fsolver_type>(gsl_root_fsolver_falsepos),GSL_ROOT_FSOLVER_FALSEPOS, CATEGORY, _T("False position method solver"), _T("Documentation"));

static AddInX xai_root_fsolve(
	FunctionX(XLL_HANDLEX, _T("?xll_root_fsolve"), PREFIX _T("ROOT.SOLVE"))
	.Arg(XLL_HANDLEX, _T("Type"), _T("is the type of solver from the GSL_ROOT_FSOLVER_* enumeration"))
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a handle to a gsl::root::fsolve object."))
	.Documentation(_T(""))
);
HANDLEX WINAPI xll_root_fsolve(HANDLEX type)
{
#pragma XLLEXPORT
	handlex h;

	try {
		handle<gsl::root_fsolve> h_(new gsl::root_fsolve(h2p<gsl_root_fsolver_type>(type)));

		h = h_.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}

static AddInX xai_root_fsolve_set(
	FunctionX(XLL_HANDLEX, _T("?xll_root_fsolve_set"), PREFIX _T("ROOT.SOLVE.SET"))
	.Arg(XLL_HANDLEX, _T("Solve"), _T("is a handle returned by ") PREFIX _T("ROOT.SOLVE"))
	.Arg(XLL_HANDLEX, _T("Function"), _T("is a handle used by XLL.FUNCTION."))
	.Arg(XLL_DOUBLEX, _T("Lo"), _T("is the lower bound of the search interval."))
	.Arg(XLL_DOUBLEX, _T("Hi"), _T("is the upper bound of the search interval."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a handle to a gsl::root::fsolve object with function and bounds set."))
	.Documentation(_T(""))
);
HANDLEX WINAPI xll_root_fsolve_set(HANDLEX h, HANDLEX f, double lo, double hi)
{
#pragma XLLEXPORT
	try {
		handle<gsl::root_fsolve> h_(h);
		handle<std::function<double(double)>> f_(f);

		h_->set(*f_, lo, hi);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}

static AddInX xai_root_fsolve_iterate(
	FunctionX(XLL_HANDLEX, _T("?xll_root_fsolve_iterate"), PREFIX _T("ROOT.SOLVE.ITERATE"))
	.Arg(XLL_HANDLEX, _T("Solve"), _T("is a handle returned by ") PREFIX _T("ROOT.SOLVE"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a handle to a gsl::root::fsolve object after one iteration step."))
	.Documentation(_T(""))
	);
HANDLEX WINAPI xll_root_fsolve_iterate(HANDLEX h)
{
#pragma XLLEXPORT
	try {
		handle<gsl::root_fsolve> h_(h);

		ensure (GSL_SUCCESS == h_->iterate());
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}

static AddInX xai_root_fsolve_root(
	FunctionX(XLL_HANDLEX, _T("?xll_root_fsolve_root"), PREFIX _T("ROOT.SOLVE.ROOT"))
	.Arg(XLL_HANDLEX, _T("Solve"), _T("is a handle returned by ") PREFIX _T("ROOT.SOLVE"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the current root estimate of a gsl::root::fsolve object."))
	.Documentation(_T(""))
);
HANDLEX WINAPI xll_root_fsolve_root(HANDLEX h)
{
#pragma XLLEXPORT
	handlex root;

	try {
		handle<gsl::root_fsolve> h_(h);

		root = h_->root();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return root;
}

static AddInX xai_root_fsolve_x_lower(
	FunctionX(XLL_HANDLEX, _T("?xll_root_fsolve_x_lower"), PREFIX _T("ROOT.SOLVE.X.LOWER"))
	.Arg(XLL_HANDLEX, _T("Solve"), _T("is a handle returned by ") PREFIX _T("ROOT.SOLVE"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the current lower root bound of a gsl::root::fsolve object."))
	.Documentation(_T(""))
);
HANDLEX WINAPI xll_root_fsolve_x_lower(HANDLEX h)
{
#pragma XLLEXPORT
	handlex lo;

	try {
		handle<gsl::root_fsolve> h_(h);

		lo = h_->x_lower();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return lo;
}

static AddInX xai_root_fsolve_x_upper(
	FunctionX(XLL_HANDLEX, _T("?xll_root_fsolve_x_upper"), PREFIX _T("ROOT.SOLVE.X.UPPER"))
	.Arg(XLL_HANDLEX, _T("Solve"), _T("is a handle returned by ") PREFIX _T("ROOT.SOLVE"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the current upper root bound of a gsl::root::fsolve object."))
	.Documentation(_T(""))
);
HANDLEX WINAPI xll_root_fsolve_x_upper(HANDLEX h)
{
#pragma XLLEXPORT
	handlex lo;

	try {
		handle<gsl::root_fsolve> h_(h);

		lo = h_->x_upper();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return lo;
}

XLL_TEST_BEGIN(xll_test_roots)

	test_gsl_root_fsolver();

XLL_TEST_END(xll_test_roots)