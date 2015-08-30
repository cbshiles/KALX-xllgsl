// xll_roots.cpp - GSL 1-dim root finding
#include "xll_roots.h"
#include "xll_gsl.h"

using namespace xll;

XLL_TEST_BEGIN(xll_test_roots)

	test_gsl_root_fsolver();

XLL_TEST_END(xll_test_roots)