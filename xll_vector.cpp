// xll_vector.cpp
#include "xll_vector.h"
#include "xll/xll.h"

using namespace xll;

#ifdef _DEBUG
XLL_TEST_BEGIN(xll_test_vector)

gsl_test_vector<int>();
gsl_test_vector<double>();

XLL_TEST_END(xll_test_vector)
#endif // _DEBUG