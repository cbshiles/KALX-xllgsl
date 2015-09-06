// xll_multimin.cpp
#include "xll_multimin.h"
#include "xll_gsl.h"

using namespace xll;

XLL_ENUM_DOCX(p2h<const gsl_multimin_fminimizer_type>(gsl_multimin_fminimizer_nmsimplex),GSL_MULTIMIN_FMINIMIZER_NMSIMPLEX, CATEGORY, _T("Simplex method solver"), _T("Documentation"));
XLL_ENUM_DOCX(p2h<const gsl_multimin_fminimizer_type>(gsl_multimin_fminimizer_nmsimplex2),GSL_MULTIMIN_FMINIMIZER_NMSIMPLEX2, CATEGORY, _T("Simplex2 method solver"), _T("Documentation"));
XLL_ENUM_DOCX(p2h<const gsl_multimin_fminimizer_type>(gsl_multimin_fminimizer_nmsimplex2rand),GSL_MULTIMIN_FMINIMIZER_NMSIMPLEX2RAND, CATEGORY, _T("Simplex2 method solver"), _T("Documentation"));

static AddInX xai_multimin_fminimizer(
	FunctionX(XLL_HANDLEX, _T("?xll_multimin_fminimizer"), PREFIX _T("MULTMIN.FMINIMIZER"))
	.Arg(XLL_HANDLEX, _T("Type"), _T("is the type of solver from the GSL_MULTIMIN_FMINIMIZER_* enumeration"))
	.Arg(XLL_WORDX, _T("n"), _T("is the dimension of the problem"))
	.Uncalced()
	.FunctionHelp(_T("Return a handle to a gsl::multimin::fminimizer object"))
	.Category(CATEGORY)
	.Documentation(_T(""))
);
HANDLEX WINAPI xll_multimin_fminimizer(HANDLEX type, WORD n)
{
#pragma XLLEXPORT
	handlex h;

	try {
		handle<gsl::multimin::fminimizer> h_(new gsl::multimin::fminimizer(h2p<gsl_multimin_fminimizer_type>(type), n));

		h = h_.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}

static AddInX xai_multimin_fminimizer_set(
	FunctionX(XLL_HANDLEX, _T("?xll_multimin_fminimizer_set"), PREFIX _T("MULTMIN.FMINIMIZER.SET"))
	.Arg(XLL_HANDLEX, _T("Solver"), _T("is a handle returned by GSL.MULTIMIN.fminimizer"))
	.Arg(XLL_HANDLEX, _T("f"), _T("is a handle to a function object"))
	.Arg(XLL_FPX, _T("x"), _T("is the initial root guess"))
	.Arg(XLL_FPX, _T("dx"), _T("is the initial root setp"))
	.FunctionHelp(_T("Return a handle to a gsl::multimin::fminimizer object"))
	.Category(CATEGORY)
	.Documentation(_T(""))
	);
HANDLEX WINAPI xll_multimin_fminimizer_set(HANDLEX s, HANDLEX f, xfpx* px, xfpx* pdx)
{
#pragma XLLEXPORT
	try {
		ensure (size(*px) == size(*pdx));

		handle<gsl::multimin::fminimizer> s_(s);
		handle<gsl::multimin::function<double>> f_(f);

		ensure (GSL_SUCCESS == s_->set(*f_, size(*px), px->array, pdx->array));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return s;
}

static AddInX xai_multimin_fminimizer_iterate(
	FunctionX(XLL_HANDLEX, _T("?xll_multimin_fminimizer_iterate"), PREFIX _T("MULTMIN.FMINIMIZER.ITERATE"))
	.Arg(XLL_HANDLEX, _T("Solver"), _T("is a handle returned by GSL.MULTIMIN.fminimizer"))
	.FunctionHelp(_T("Return a handle to a gsl::multimin::fminimizer object after one iteration step."))
	.Category(CATEGORY)
	.Documentation(_T(""))
	);
HANDLEX WINAPI xll_multimin_fminimizer_iterate(HANDLEX s)
{
#pragma XLLEXPORT
	try {
		handle<gsl::multimin::fminimizer> s_(s);

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