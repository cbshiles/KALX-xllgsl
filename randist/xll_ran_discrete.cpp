// xll_ran_discrete.cpp - discrete random distrbution
#include "xll_ran_discrete.h"
#include "../xll_rng.h"
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_discrete_preproc(
	FunctionX(XLL_HANDLEX, _T("?xll_ran_discrete_preproc"), _T("GSL.RAN.DISCRETE.PREPROC"))
	.Arg(XLL_FPX, _T("p"), _T("is an array of probabilities for the discrete distribution."))
	.Uncalced()
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return a handle to a distribution with probability p[k] for the value k."))
	.Documentation(_T(""))
);
HANDLEX WINAPI xll_ran_discrete_preproc(xfpx* pp)
{
#pragma XLLEXPORT
	handlex h;

	try {
		handle<gsl::ran_discrete> h_(new gsl::ran_discrete(size(*pp), pp->array));

		h = h_.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}

static AddInX xai_ran_discrete(
	FunctionX(XLL_WORDX, _T("?xll_ran_discrete"), _T("GSL.RAN.DISCRETE"))
	.Arg(XLL_HANDLEX, _T("Rng"), _T("is a handle returned by GSL.RAN"))
	.Arg(XLL_HANDLEX, _T("Discrete"), _T("is a handle returned by GSL.RAN.DISCRETE.PREPROC"))
	.Volatile()
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return a random value k with probability p[k]."))
	.Documentation(_T(""))
);
WORD WINAPI xll_ran_discrete(HANDLEX rng, HANDLEX discrete)
{
#pragma XLLEXPORT
	WORD k = static_cast<WORD>(-1);

	try {
		handle<gsl::rng> r(rng);
		handle<gsl::ran_discrete> g(discrete);

		k = static_cast<WORD>(gsl_ran_discrete(*r, *g));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return k;
}

static AddInX xai_ran_discrete_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_discrete_pdf"), _T("GSL.RAN.DISCRETE.PDF"))
	.Arg(XLL_WORDX, _T("k"), _T("is a non-negative integer."))
	.Arg(XLL_HANDLEX, _T("Disc"), _T("is a handle returned by GSL.RAN.DISCRETE.PREPROC"))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return discrete pdf."))
	);
double WINAPI xll_ran_discrete_pdf(WORD k, HANDLEX disc)
{
#pragma XLLEXPORT
	handle<gsl::ran_discrete> d(disc);

	return gsl_ran_discrete_pdf(k, *d);
}

/*
XLL_TEST_BEGIN(xll_rand_discrete)
std::vector<double> p{0.1,0.2,0.3};
gsl::ran_discrete d(p.size(), p.data());
size_t k;
XLL_TEST_END(xll_rand_discrete)
*/
