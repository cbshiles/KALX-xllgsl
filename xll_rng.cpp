#include "xll_rng.h"
#include "../xll8/xll/xll.h"

using namespace xll;

XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_borosh13), GSL_RNG_BOROSH13, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_coveyou), GSL_RNG_COVEYOU, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_cmrg), GSL_RNG_CMRG, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_fishman18), GSL_RNG_FISHMAN18, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_fishman20), GSL_RNG_FISHMAN20, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_fishman2x), GSL_RNG_FISHMAN2X, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_gfsr4), GSL_RNG_GFSR4, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_knuthran), GSL_RNG_KNUTHRAN, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_knuthran2), GSL_RNG_KNUTHRAN2, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_knuthran2002), GSL_RNG_KNUTHRAN2002, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_lecuyer21), GSL_RNG_LECUYER21, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_minstd), GSL_RNG_MINSTD, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_mrg), GSL_RNG_MRG, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_mt19937), GSL_RNG_MT19937, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_mt19937_1999), GSL_RNG_MT19937_1999, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_mt19937_1998), GSL_RNG_MT19937_1998, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_r250), GSL_RNG_R250, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_ran0), GSL_RNG_RAN0, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_ran1), GSL_RNG_RAN1, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_ran2), GSL_RNG_RAN2, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_ran3), GSL_RNG_RAN3, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_rand), GSL_RNG_RAND, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_rand48), GSL_RNG_RAND48, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_random128_bsd), GSL_RNG_RANDOM128_BSD, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_random128_glibc2), GSL_RNG_RANDOM128_GLIBC2, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_random128_libc5), GSL_RNG_RANDOM128_LIBC5, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_random256_bsd), GSL_RNG_RANDOM256_BSD, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_random256_glibc2), GSL_RNG_RANDOM256_GLIBC2, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_random256_libc5), GSL_RNG_RANDOM256_LIBC5, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_random32_bsd), GSL_RNG_RANDOM32_BSD, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_random32_glibc2), GSL_RNG_RANDOM32_GLIBC2, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_random32_libc5), GSL_RNG_RANDOM32_LIBC5, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_random64_bsd), GSL_RNG_RANDOM64_BSD, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_random64_glibc2), GSL_RNG_RANDOM64_GLIBC2, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_random64_libc5), GSL_RNG_RANDOM64_LIBC5, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_random8_bsd), GSL_RNG_RANDOM8_BSD, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_random8_glibc2), GSL_RNG_RANDOM8_GLIBC2, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_random8_libc5), GSL_RNG_RANDOM8_LIBC5, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_random_bsd), GSL_RNG_RANDOM_BSD, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_random_glibc2), GSL_RNG_RANDOM_GLIBC2, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_random_libc5), GSL_RNG_RANDOM_LIBC5, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_randu), GSL_RNG_RANDU, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_ranf), GSL_RNG_RANF, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_ranlux), GSL_RNG_RANLUX, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_ranlux389), GSL_RNG_RANLUX389, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_ranlxd1), GSL_RNG_RANLXD1, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_ranlxd2), GSL_RNG_RANLXD2, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_ranlxs0), GSL_RNG_RANLXS0, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_ranlxs1), GSL_RNG_RANLXS1, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_ranlxs2), GSL_RNG_RANLXS2, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_ranmar), GSL_RNG_RANMAR, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_slatec), GSL_RNG_SLATEC, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_taus), GSL_RNG_TAUS, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_taus2), GSL_RNG_TAUS2, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_taus113), GSL_RNG_TAUS113, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_transputer), GSL_RNG_TRANSPUTER, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_tt800), GSL_RNG_TT800, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_uni), GSL_RNG_UNI, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_uni32), GSL_RNG_UNI32, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_vax), GSL_RNG_VAX, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_waterman14), GSL_RNG_WATERMAN14, _T("GSL"), _T("A GSL random number generator type."), _T(""));
XLL_ENUM_DOCX(p2h<const gsl_rng_type>(gsl_rng_zuf), GSL_RNG_ZUF, _T("GSL"), _T("A GSL random number generator type."), _T(""));

static AddIn xai_rng(
	FunctionX(XLL_HANDLEX, _T("?xll_rng"), _T("GSL.RNG"))
	.Arg(XLL_HANDLEX, _T("type"), _T("is the type of random number generator from GSL_RNG_* enumeration. Default is GSL_RNG_MT19937()"), _T("GSL_RNG_MT19937()"))
	.Uncalced()
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return a handle to a GSL random number generator."))
);
HANDLEX WINAPI xll_rng(HANDLEX type)
{
#pragma XLLEXPORT
	handlex h;

	try {
		if (type == 0)
			type = p2h<const gsl_rng_type>(gsl_rng_mt19937);

		handle<gsl::rng> h_(new gsl::rng(h2p<gsl_rng_type>(type)));
		
		h = h_.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}

static AddIn xai_rng_max(
	FunctionX(XLL_DOUBLEX, _T("?xll_rng_max"), _T("GSL.RNG.MAX"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return the maximum value generated by a random number generator."))
	);
double WINAPI xll_rng_max(HANDLEX rng)
{
#pragma XLLEXPORT
	doublex x;

	try {
		handle<gsl::rng> r(rng);

		x = (r->max)();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

static AddIn xai_rng_min(
	FunctionX(XLL_DOUBLEX, _T("?xll_rng_min"), _T("GSL.RNG.MIN"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return the minimum value generated by a random number generator."))
	);
double WINAPI xll_rng_min(HANDLEX rng)
{
#pragma XLLEXPORT
	doublex x;

	try {
		handle<gsl::rng> r(rng);

		x = (r->max)();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x;
}

#ifdef _DEBUG
XLL_TEST_BEGIN(xll_rng_test)

gsl_rng_test();

XLL_TEST_END(xll_rng_test)
#endif // _DEBUG