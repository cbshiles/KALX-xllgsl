// xll_deriv.cpp
#include "xll_deriv.h"
#include "xll_gsl.h"

using namespace xll;
/*
static AddInX xai_function_deriv_central(
	FunctionX(XLL_HANDLEX, _T("?xll_function_deriv_central"), PREFIX _T("FUNCTION.DERIV.CENTRAL"))
	.Arg(XLL_DOUBLEX, _T("h"), _T("is the step size"))
	.Arg(XLL_HANDLEX, _T("f"), _T("is a handle to a function"))
	.Category(_T("XLL"))
	.FunctionHelp(_T("Return a handle to the numerical derivative of f."))
	.Documentation(R_(
	This function computes the numerical derivative of the function f at the point x 
	using an adaptive central difference algorithm with a step-size of h. 
	The derivative is returned in result and an estimate of its absolute error is 
	returned in abserr. 

	The initial value of h is used to estimate an optimal step-size, based on the 
	scaling of the truncation error and round-off error in the derivative calculation. 
	The derivative is computed using a 5-point rule for equally spaced abscissae at x-h,
	x-h/2, x, x+h/2, x+h, with an error estimate taken from the difference between the 
	5-point rule and the corresponding 3-point rule x-h, x, x+h. 
	Note that the value of the function at x does not contribute to the derivative calculation, 
	so only 4-points are actually used
	))
);
*/
#ifdef _DEBUG
XLL_TEST_BEGIN(test_gsl_deriv)

	test_gsl_deriv();

XLL_TEST_END(test_gsl_deriv)
#endif // _DEBUG