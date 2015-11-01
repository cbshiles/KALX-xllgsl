// xll_nsr.h - Normal short rate model
#pragma once
#pragma warning(disable: 100)
#include <functional>
#include "xll_black.h"

/******************************************************************************

The normal short rate model is f_t = phi(t) + sigma(t)B_t, where B_t is standard
Brownian motion. The stochastic discount is D_t = exp(-\int_0^t f_s ds).

The price of a zero coupon bond at time t paying one unit at time u, 
D_t(u) = E[D_u/D_t|t] = exp(-int_t^u f_s ds)|_t, has a closed form solution:

log D_t(u) = - (Sigma(u) - Sigma(t)) B_t 
- int_t^u f(s) + (Sigma(u) - Sigma(s))^2/2 ds

where Sigma'(t) = sigma(t). For constant sigma we have

log D_t(u) = -int_t^u f(s) ds - sigma^2(u - t)^3/6 - sigma(u - t) B_t

The forward rate at time t over the interval [u,v] is 

F_t(u,v) = (D_t(u)/D_t(v) - 1)/(v-u).

A caplet pays (v-u) max{F_u(u,v) - k, 0} at time v. It has value

c = E(v-u) max{F_u(u,v) - k, 0} D_v
= E max{1/D_u(v) - 1 - (v-u) k, 0} D_u(v) D_u
= E max{1 - (1 + (v-u) k)D_u(v), 0} D_u
= E max{1 - (1 + (v-u) k)D_u(v) exp(gamma), 0} E D_u

where gamma = Cov(log D_u(v), log D_u) = sigma^2(v - u) int_0^u Cov(B_u, B_s) ds
= sigma^2(v - u)u^2/2.

******************************************************************************/

namespace nsr {

	// expected value of log D_t(u)
	inline double E_logD(const std::function<double(double)>& D, double sigma, double t, double u)
	{
		return log(D(u)/D(t)) - sigma*sigma*pow(u - t, 3)/6;
	}
	// variance of log D_t(u)
	inline double Var_logD(const std::function<double(double)>& D, double sigma, double t, double u)
	{
		return 0; //!!! replace by Var log D_t(u)
	}
	// covariance of log D_t(u) and D_t
	inline double Cov_logD_D(const std::function<double(double)>& D, double sigma, double t, double u)
	{
		return 0; //!!! replace by Cov(log D_t(u), log D_t)
	}

	// value of caplet over [u,v] with strike k
	inline double caplet_value(const std::function<double(double)>& D, double sigma, double u, double v, double k)
	{
		//!!! determine appropriate values for f, s, k, and t;
		double f = 0;
		double s = 0;
		k = 0;
		double t = 0;

		return black_put_value(f, s, k, t)*D(u);
	}

} // nsr

#ifdef _DEBUG
#include <cassert>
#include <algorithm>

inline void test_nsr()
{
	double f = 0.04; // constant forward rate
	double t = 1.0, u = 1.25, dt = u - t;
	auto D = [f](double t) { return exp(-f*t); };

	double sigma, v, v_, dv, eps = std::numeric_limits<double>::epsilon();
	sigma = 0;
	v = -f*dt - sigma*sigma*dt*dt*dt/6;
	v_ = nsr::E_logD(D, sigma, t, u);
	dv = v - v_;
	assert (fabs(dv) <= eps);
	// !!! test Var_logD
	// !!! test Cov_logD_D

	sigma = 0.05;
	v = -f*dt - sigma*sigma*dt*dt*dt/6;
	v_ = nsr::E_logD(D, sigma, t, u);
	dv = v - v_;
	assert (fabs(dv) <= eps);
	// !!! test Var_logD
	// !!! test Cov_logD_D

	double ftu = (D(t)/D(u) - 1)/(u - t);
	double k = 0.04;
	v = (std::max)(ftu - k, 0.)*D(t);
	sigma = 0;
	v_ = nsr::caplet_value(D, sigma, t, u, k);
	dv = v - v_;
	// !!! test caplet_value equals intrinsic
//	assert (fabs(dv) <= eps);
}

#endif // _DEBUG