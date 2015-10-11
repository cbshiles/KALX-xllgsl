// xll_ran_dirichlet.cpp - Dirichlet variates, density, cumulative distribution, and inverse
// http://www.gnu.org/software/gsl/manual/html_node/The-Dirichlet-Distribution.html#The-Dirichlet-Distribution#The-Dirichlet-Distribution
#include "../xll_rng.h"
#include "../xll_randist.h"
//#define EXCEL12
#include "xll/xll.h"

using namespace xll;

static AddInX xai_ran_dirichlet(
	FunctionX(XLL_FPX, _T("?xll_ran_dirichlet"), _T("GSL.RAN.DIRICHLET"))
	.Arg(XLL_HANDLEX, _T("rng"), _T("is a handle returned by GSL.RNG."))
	
	.Arg(XLL_FPX, _T("alpha"), _T("is an array of concentration parameters."))
	
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return dirichlet random deviates using a random number generator."))
	.Documentation(_T(""))
	);

xfpx* WINAPI xll_ran_dirichlet(HANDLEX rng, xfpx*alpha)
{
	
#pragma XLLEXPORT
	static FPX theta;
	try {

		handle<gsl::rng> r(rng);

		gsl_ran_dirichlet(*r, size(*alpha),alpha->array, theta.begin());
	
	}
	
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	return theta.get();
	
}


static AddInX xai_ran_dirichlet_pdf(
	FunctionX(XLL_DOUBLEX, _T("?xll_ran_dirichlet_pdf"), _T("GSL.DIST.DIRICHLET.PDF"))
	
	.Arg(XLL_FPX, _T("alpha"), _T("is an array of concentration parameters."))
	.Arg(XLL_FPX, _T("theta"), _T("is x."))
	.Category(_T("GSL"))
	.FunctionHelp(_T("Return Dirichlet probability density function."))
	.Documentation(_T(""))
	);


double WINAPI xll_ran_dirichlet_pdf( xfpx*alpha, xfpx*theta){

#pragma XLLEXPORT



	return gsl_ran_dirichlet_pdf(size(*alpha), alpha->array, theta->array);
}

//There is no cdf and inverse of this distribution in GSL.
XLL_TEST_BEGIN(xll_ran_dirichlet)

double eps = 1e-4;

//The Dirichlet Distribution cannot be found in Wolframalpha. Using R to compute the pdf. Set K=2, alpha={1,4}, x=[0.05,0.95,0.05]

double pdf[] = { 3.4295, 2.9160, 2.4565, 2.0480, 1.6875, 1.3720, 1.0985, 0.8640, 0.6655, 0.5000, 0.3645, 0.2560, 0.1715, 0.1080, 0.0625, 0.0320, 0.0135, 0.0040, 0.0005 };

for (int i = 0; i < sizeof(pdf) / sizeof(*pdf); ++i) {
  double x = 0.05 + i*0.05;
  double y = 1 - x;
  double alpha[2] = { 1,4 };


  double theta[2] = { x,y };
  ensure(fabs(gsl_ran_dirichlet_pdf(2,alpha, theta) - pdf[i]) < eps);
}

XLL_TEST_END(xll_ran_dirichlet)