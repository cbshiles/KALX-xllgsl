// xll_bachelier.h - Bachelier model
#pragma once

// The Bachelier model for a stock is F_t = f + sigma B_t, where B_t is Brownian motion.
// The price of a put option with strike k expiring at t is
//
//   P = (k - F) N(-d) + sigma sqrt(t) n(d),
//
// where N is the standard normal cumulative distribution, n = N' is the density,
// and d = (f - k)/(sigma sqrt(t)).

// Implement the function
double bachelier_put(double f, double sigma, double k, double t)
{
	return 0;
}

// Implement a test to show P = sigma sqrt(t)/(sqrt(2 pi)) for 
// sigma = 0.1, 0.2, and t = 0.5, 1.
inline void test_bachelier_put()
{
}

// Open xll_bachelier.cpp and follow the directions.