// xll_sum.cpp - GNU Scientific Library series acceleration.
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "xll_gsl.h"
#include "gsl/gsl_sum.h"

using namespace xll;

typedef handle<gsl_sum_levin_u_workspace, void (*)(gsl_sum_levin_u_workspace*)> handle_sum_levin;

static AddInX xai_gsl_sum_levin(
	FunctionX(XLL_HANDLEX XLL_UNCALCEDX, _T("?xll_gsl_sum_levin"), PREFIX _T("SUM.LEVIN"))
	.Arg(XLL_LONGX, _T("Size"), _T("is the size of the series to be accelerated. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Allocate a workspace of given Size to perform series acceleration."))
);
HANDLEX WINAPI
xll_gsl_sum_levin(LONG n)
{
#pragma XLLEXPORT

	handle_sum_levin h(gsl_sum_levin_u_alloc(n), gsl_sum_levin_u_free);

	return h.get();
}

static AddInX xai_sum_levin_accel(
	FunctionX(XLL_FPX, _T("?xll_gsl_sum_levin_accel"), PREFIX _T("SUM.LEVIN.ACCEL"))
	.Arg(XLL_HANDLEX, _T("Handle"), _T("is a handle returned by ") PREFIX _T("SUM.LEVIN."))
	.Arg(XLL_FPX, _T("Series"), _T("is a series to accelerate. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the estimate of the convergent term and it's error estimate."))
);
xfp* WINAPI
xll_gsl_sum_levin_accel(HANDLEX hx, xfp* px)
{
#pragma XLLEXPORT
	static FPX result(2, 1);

	try {
		handle_sum_levin h(hx);

		gsl_sum_levin_u_accel(px->array, size(*px), &*h, &result[0], &result[1]);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		result = FPX();
	}

	return result.get();
}