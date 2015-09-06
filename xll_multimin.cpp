// xll_multimin.cpp
#include "xll_multimin.h"
#include "xll_gsl.h"

using namespace xll;

XLL_ENUM_DOCX(p2h<const gsl_mutimin_fsolver_type>(gsl_multimin_fminimizer_nmsimplex),GSL_MULTIMIN_FMINIMIZER_NMSIMPLEX, CATEGORY, _T("Simplex method solver"), _T("Documentation"));
XLL_ENUM_DOCX(p2h<const gsl_mutimin_fsolver_type>(gsl_multimin_fminimizer_nmsimplex2),GSL_MULTIMIN_FMINIMIZER_NMSIMPLEX2, CATEGORY, _T("Simplex2 method solver"), _T("Documentation"));

static AddInX xai_multimin_fsolver(
	FunctionX(XLL_HANDLEX, _T("?xll_multimin_fsolver"), PREFIX _T("MULTMIN.FSOLVER"))
	.Arg(XLL_HANDLEX, _T("Type"), _T("is the type of solver from the GSL_MULTIMIN_FMINIMIZER_* enumeration"))
	.Uncalced()
	.FunctionHelp(_T("Return a handle to a gsl::multimin::fsolver object"))
	.Category(CATEGORY)
	.Documentation(_T(""))
);
HANDLEX WINAPI xll_multimin_fsolver(HANDLEX type)
{
#pragma XLLEXPORT
	handlex h;

	try {
		handle<gsl::multimin::fsolver> h_(new gsl::multimin::fsolver(h2p<gsl_mutimin_fsolver_type>(type)));

		h = h_->get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}

static AddInX xai_multimin_fsolver_set(
	FunctionX(XLL_HANDLEX, _T("?xll_multimin_fsolver_set"), PREFIX _T("MULTMIN.FSOLVER.SET"))
	.Arg(XLL_HANDLEX, _T("Solver"), _T("is a handle returned by GSL.MULTIMIN.FSOLVER"))
	.Arg(XLL_HANDLEX, _T("f"), _T("is a handle to a function object"))
	.Arg(XLL_FPX, _T("x"), _T("is the initial root guess"))
	.Arg(XLL_FPX, _T("dx"), _T("is the initial root setp"))
	.FunctionHelp(_T("Return a handle to a gsl::multimin::fsolver object"))
	.Category(CATEGORY)
	.Documentation(_T(""))
	);
HANDLEX WINAPI xll_multimin_fsolver(HANDLEX s, HANDLEX f, xfpx* px, xfpx* pdx)
{
#pragma XLLEXPORT
	try {
		ensure (size(*px) == size(*pdx));

		handle<gsl::multimin::fsolver> s_(s);
		handle<gsl::multimin::function> f_(f);

		ensure (GSL_SUCCESS == s_->set(&f_, size(*px), px->array, pdx->array));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return s;
}

static AddInX xai_multimin_fsolver_iterate(
	FunctionX(XLL_HANDLEX, _T("?xll_multimin_fsolver_iterate"), PREFIX _T("MULTMIN.FSOLVER.ITERATE"))
	.Arg(XLL_HANDLEX, _T("Solver"), _T("is a handle returned by GSL.MULTIMIN.FSOLVER"))
	.FunctionHelp(_T("Return a handle to a gsl::multimin::fsolver object after one iteration step."))
	.Category(CATEGORY)
	.Documentation(_T(""))
	);
HANDLEX WINAPI xll_multimin_fsolver(HANDLEX s)
{
#pragma XLLEXPORT
	try {
		handle<gsl::multimin::fsolver> s_(s);

		ensure (GSL_SUCCESS == s_->iterate());
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return s;
}


#ifdef _DEBUG

XLL_TEST_BEGIN(xll_multimin_fmininimizer)

	test_gsl_multimin_fminimizer();

XLL_TEST_END(xll_multimin_fmininimizer)

#endif // _DEBUG