// xll_bachelier.h - Bachelier model
#pragma once
#include <cmath>
#include "xll/ensure.h"
#include "gsl/gsl_randist.h"
#include "gsl/gsl_cdf.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// The Bachelier model for a stock is F_t = f + sigma B_t, where B_t is Brownian motion.
// The price of a put option with strike k expiring at t is
//
//   P = (k - f) N(-d) + sigma sqrt(t) n(d),
//
// where N is the standard normal cumulative distribution, n = N' is the density,
// and d = (f - k)/(sigma sqrt(t)).

// Implement using gsl_ran_gaussian_pdf and gsl_cdf_gaussian_P.
double bachelier_put(double f, double sigma, double k, double t)
{
	ensure (f > 0);
	ensure (sigma > 0);
	ensure (k > 0);
	ensure (t > 0);

	double srt = sigma*sqrt(t);
	double d = (f - k)/srt;

	return (k - f)*gsl_cdf_gaussian_P(-d, 1) + srt*gsl_ran_gaussian_pdf(d, 1);
}

// Implement a test to show P = sigma sqrt(t)/(sqrt(2 pi)) for 
// the four cases sigma = 0.1, 0.2 and t = 0.5, 1 when f = k.
inline void test_bachelier_put()
{
	double f = 100, k = 100, sigma, t;
	double srt;
	double M_SQRT_2PI = sqrt(2*M_PI);

	sigma = 0.1;
	t = 0.5;
	srt = sigma*sqrt(t);
	double p;
	p = bachelier_put(f, sigma, k, t) - srt/M_SQRT_2PI;
	ensure (p == 0);
	sigma = 0.1;
	t = 1;
	srt = sigma*sqrt(t);
	p = bachelier_put(f, sigma, k, t) - srt/M_SQRT_2PI;
	ensure (p == 0);
	sigma = 0.2;
	t = 0.5;
	srt = sigma*sqrt(t);
	p = bachelier_put(f, sigma, k, t) - srt/M_SQRT_2PI;
	ensure (p == 0);
	sigma = 0.2;
	t = 1;
	srt = sigma*sqrt(t);
	p = bachelier_put(f, sigma, k, t) - srt/M_SQRT_2PI;
	ensure (p == 0);
}

// Open xll_bachelier.cpp and follow the directions.