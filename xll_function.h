// xll_function.h - wrappers for std::function
#pragma once
#include <functional>
//#define EXCEL12
#include "../xll8/xll/xll.h"

namespace xll {

	// call a user defined function
	inline double udf(double regid, double x)
	{
		return XLL_XL_(UDF, OPERX(regid), OPERX(x)).val.num;
	}

}