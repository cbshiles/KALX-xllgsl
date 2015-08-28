// xll_sf.h - GSL special functions
#include "gsl/gsl_sf.h"
#include "xll_gsl.h"

// create the add-in object
#define SF_UNARY(f, F, FH, D) static AddIn xai_ ## f(Function(XLL_FP, ENSURE_STRZ_(xll_ ## f), F) \
	.Arg(XLL_DOUBLE, "x", "is a number") \
	.Category("GSL").FunctionHelp(FH).Documentation(D)); \
	extern "C" __declspec(dllexport) xfp* xll_ ## f(double x, gsl_mode_t mode) { \
	return sf_unary(gsl_ ## f ## _e, x); }

#define SF_UNARY_MODE(f, F, FH, D) static AddIn xai_ ## f(Function(XLL_FP, ENSURE_STRZ_(xll_ ## f), F) \
	.Arg(XLL_DOUBLE, "x", "is a number") \
	.Arg(XLL_WORD, "mode", "is the precision from the PREC_* enumeration") \
	.Category("GSL").FunctionHelp(FH).Documentation(D)); \
	extern "C" __declspec(dllexport) xfp* xll_ ## f(double x, gsl_mode_t mode) { \
	return sf_unary_mode(gsl_ ## f ## _e, x, mode ? mode : GSL_PREC_DOUBLE); }

namespace xll {

	inline xfpx*	sf_unary(int (*f)(double,gsl_sf_result*), double x)
	{
		static FPX y(1, 2);
		gsl_sf_result r;

		try {
			ensure (0 == f(x, &r));
			y[0] = r.val;
			y[1] = r.err;
		}
		catch (const std::exception& ex) {
			XLL_ERROR(ex.what());

			return 0;
		}

		return y.get();
	}

	inline xfpx*	sf_unary_mode(int (*f)(double,gsl_mode_t,gsl_sf_result*), double x, gsl_mode_t mode)
	{
		static FPX y(1, 2);
		gsl_sf_result r;

		try {
			ensure (0 == f(x, mode, &r));
			y[0] = r.val;
			y[1] = r.err;
		}
		catch (const std::exception& ex) {
			XLL_ERROR(ex.what());

			return 0;
		}

		return y.get();
	}

} // xll