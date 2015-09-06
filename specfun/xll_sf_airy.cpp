// xll_sf_airy.cpp - Airy function
#include "gsl/gsl_sf_airy.h"
#include "../xll_gsl.h"

using namespace xll;

/*
The Airy functions Ai(x) and Bi(x) are defined by the integral representations, 

Ai(x) = (1/\pi) \int_0^\infty \cos((1/3) t^3 + xt) dt
Bi(x) = (1/\pi) \int_0^\infty (e^(-(1/3) t^3 + xt) + \sin((1/3) t^3 + xt)) dt

For further information see Abramowitz & Stegun, Section 10.4. The Airy functions are defined in the header file gsl_sf_airy.h. 
*/

/*
Function: double gsl_sf_airy_Ai (double x, gsl_mode_t mode)
Function: int gsl_sf_airy_Ai_e (double x, gsl_mode_t mode, gsl_sf_result * result)
*/
static AddInX xai_xll_sf_airy_Ai(
	FunctionX(XLL_DOUBLEX, _T("?xll_sf_airy_Ai"), PREFIX _T("SF.AIRY.AI"))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is a number."), 1.)
	.Arg(XLL_WORDX, _T("_mode"), IS_PREC, GSL_MODE_DEFAULT)
	.Category(CATEGORY)
	.FunctionHelp(_T("The Airy function Ai(x)"))
//	.Documentation(R_(
//		Ai(x) = (1/\pi) \int_0^\infty \cos((1/3) t^3 + xt) dt
//	))
);
double WINAPI xll_sf_airy_Ai(double x, WORD prec)
{
#pragma XLLEXPORT
	gsl_sf_result result;

	try {
		auto status = gsl_sf_airy_Ai_e(x, prec, &result);
		if (status != GSL_SUCCESS)
			throw std::runtime_error(gsl_strerror(status));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result.val;
}

static AddInX xai_xll_sf_airy_Ai_deriv(
	FunctionX(XLL_DOUBLEX, _T("?xll_sf_airy_Ai_deriv"), PREFIX _T("SF.AIRY.AI.DERIV"))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is a number."), 1.)
	.Arg(XLL_WORDX, _T("_mode"), IS_PREC, GSL_MODE_DEFAULT)
	.Category(CATEGORY)
	.FunctionHelp(_T("The derivative of the Airy function Ai(x)"))
	//	.Documentation(R_(
	//		Ai(x) = (1/\pi) \int_0^\infty \cos((1/3) t^3 + xt) dt
	//	))
);
double WINAPI xll_sf_airy_Ai_deriv(double x, WORD prec)
{
#pragma XLLEXPORT
	gsl_sf_result result;

	try {
		auto status = gsl_sf_airy_Ai_deriv_e(x, prec, &result);
		if (status != GSL_SUCCESS)
			throw std::runtime_error(gsl_strerror(status));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result.val;
}
/*
Function: double gsl_sf_airy_zero_Ai (unsigned int s)Function: int gsl_sf_airy_zero_Ai_e (unsigned int s, gsl_sf_result * result)
	These routines compute the location of the s-th zero of the Airy function Ai(x). 
*/
static AddInX xai_xll_sf_airy_zero_Ai(
	FunctionX(XLL_DOUBLEX, _T("?xll_sf_airy_zero_Ai"), PREFIX _T("SF.AIRY.ZERO.AI"))
	.Arg(XLL_WORDX, _T("s"), _T("is a positive integer."), 1.)
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the s-th zero of the Airy function Ai(x)"))
	//	.Documentation(R_(
	//		Ai(x) = (1/\pi) \int_0^\infty \cos((1/3) t^3 + xt) dt
	//	))
	);
double WINAPI xll_sf_airy_zero_Ai(WORD s)
{
#pragma XLLEXPORT
	gsl_sf_result result;

	try {
		auto status = gsl_sf_airy_zero_Ai_e(s, &result);
		if (status != GSL_SUCCESS)
			throw std::runtime_error(gsl_strerror(status));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result.val;
}

#ifdef _DEBUG

XLL_TEST_BEGIN(test_sf_airy)

	// Table[AiryAi[x], {x, -2, 2, 0.1}]
	// https://www.wolframalpha.com/input/?i=Table%5BAiryAi%5Bx%5D%2C+%7Bx%2C-2%2C2%2C.1%7D%5D
	double Ai[] = {0.227407, 0.2868, 0.340762, 0.388607, 0.429863, 0.464257, 0.4917, 0.512272,
		0.526194, 0.533811, 0.535561, 0.53196, 0.523574, 0.511, 0.49485, 0.475728, 0.454226, 
		0.430903, 0.406284, 0.380849, 0.355028, 0.329203, 0.303703, 0.278806, 0.254742, 0.231694, 
		0.2098, 0.189162, 0.169846, 0.151887, 0.135292, 0.120049, 0.106126, 0.0934747, 0.082038, 
		0.0717495, 0.0625369, 0.0543248, 0.0470362, 0.0405944, 0.0349241};
	double epsilon = 1e-6;
	for (int i = 0; i < sizeof(Ai)/sizeof(*Ai); ++i) {
		ensure (fabs(xll_sf_airy_Ai(-2 + i*0.1, GSL_MODE_DEFAULT) - Ai[i]) < epsilon);
	}
	// Table[AiryAiPrime[x], {x, -2, 2, 0.1}]
	// https://www.wolframalpha.com/input/?i=Table%5BAiryAiPrime%5Bx%5D%2C+%7Bx%2C-2%2C2%2C.1%7D%5D
	double AiPrime[] = {0.618259, 0.568092, 0.509998, 0.446125, 0.378542, 0.309187, 0.239819, 
		0.171992, 0.107032, 0.0460292, -0.0101606, -0.060911, -0.10581, -0.144641, -0.177363, 
		-0.204082, -0.225031, -0.240545, -0.251033, -0.256958, -0.258819, -0.25713, -0.252405, 
		-0.245146, -0.235832, -0.224911, -0.212793, -0.199851, -0.186413, -0.172764, -0.159147, 
		-0.145766, -0.132785, -0.120334, -0.10851, -0.097382, -0.0869959, -0.0773749, -0.0685248, 
		-0.0604368, -0.0530904};
	for (int i = 0; i < sizeof(AiPrime)/sizeof(*AiPrime); ++i) {
		ensure (fabs(xll_sf_airy_Ai_deriv(-2 + i*0.1, GSL_MODE_DEFAULT) - AiPrime[i]) < epsilon);
	}
	// Table[AiryAiZero[n], {x, 1, 10}]
	// https://www.wolframalpha.com/input/?i=Table%5BAiryAiZero%5Bn%5D%2C%7Bn%2C1%2C10%7D%5D
	double AiZero[] = {
		-2.3381074104597670,
		-4.0879494441309706,
		-5.5205598280955511
	};
	for (int i = 0; i < sizeof(AiZero)/sizeof(*AiZero); ++i) {
		ensure (xll_sf_airy_zero_Ai(i + 1) == AiZero[i]);
	}

XLL_TEST_END(test_sf_airy)

#endif // _DEBUG