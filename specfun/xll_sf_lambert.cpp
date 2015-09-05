// xll_sf_lambert.cpp - Lambert W0 function
// Author: Yiyun Han
#include "gsl/gsl_sf_lambert.h"
#include "gsl/gsl_errno.h"
#include "../xll_gsl.h"

using namespace xll;

/*
Lamberts W functions, W(x), are defined to be solutions of the equation W(x) \exp(W(x)) = x. 
This function has multiple branches for x < 0; however, it has only two real-valued branches.
We define W_0(x) to be the principal branch, where W > -1 for x < 0, and W_{-1}(x) to be the other real branch,
where W < -1 for x < 0. The Lambert functions are declared in the header file gsl_sf_lambert.h.
*/

/*
Function: double gsl_sf_lambert_W0 (double x)Function: int gsl_sf_lambert_W0_e (double x, gsl_sf_result * result)
These compute the principal branch of the Lambert W function, W_0(x).

*/

static AddInX xai_xll_sf_lambert(
	FunctionX(XLL_DOUBLEX, _T("?xll_sf_lambert_W0"), PREFIX _T("SF.LAMBERT.W0"))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is a number."), 1.)
	//	.Arg(XLL_WORDX, _T("_mode"), IS_PREC, GSL_MODE_DEFAULT)
	.Category(CATEGORY)
	.FunctionHelp(_T("The Lambert function W_0(x)"))
	.Documentation(R_(
		//		blank
		))
	);

double WINAPI xll_sf_lambert_W0(double x)
{
#pragma XLLEXPORT
	gsl_sf_result result;

	try {
		auto status = gsl_sf_lambert_W0_e(x, &result);
		if (status != GSL_SUCCESS)
			throw std::runtime_error(gsl_strerror(status));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result.val;
}

#ifdef _DEBUG

XLL_TEST_BEGIN(test_sf_lambert)

/*
status = success
W0(1.0) = 0.567143290409783872

*/

double x = 1.0;
double expected = 0.567143290409783872;
double y = xll_sf_lambert_W0(x);
double error_bound = 0.000000000000001; //10^-15

ensure(abs(y - expected) < error_bound);

XLL_TEST_END(test_sf_lambert)

#endif // _DEBUG