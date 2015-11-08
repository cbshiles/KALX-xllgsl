// xll_nsr.h - Normal short rate model
#pragma once
#pragma warning(disable: 100)
#include <cmath>
#include "xll_black.h"
 
// The normal short rate model is $f_t = \phi(t) + \sigma(t) B_t$, where $B_t$ is standard
// Brownian motion. The stochastic discount is $D_t = \exp(-\int_0^t f_s ds)$.
// 
// The discount to time $t$ is $D(t) = E D_t$. Using $E e^N = \exp(E N + 1/2 \Var N)$
// we need to compute $E\log D(t) = -\int_0^t\phi(s)\,ds$ and $\Var\log D(t)$.
// Since $\Cov(B_u,B_v) = \min\{u,v\}$,
// \begin{align*}
// Var(\int_0^t B_s ds) &= Cov(\int_0^t B_s ds,\int_0^t B_s ds) \\
// 						&= \int_0^t \int_0^t min{u,v} du dv \\
// 						&= \int_0^t (\int_0^v u du + v\int_v^t du) dv \\
// 						&= \int_0^t v^2/2 + v(t-v) dv \\
// 						&= \int_0^t vt - v^2/2 dv \\
// 						&= v^3/2 - v^3/6 \\
// 						&= v^3/3 \\
// \end{align*}
// It follows $\Var\log D(t) = \sigma^2 t^3/3$ if $\sigma(t) = \sigma$ is constant and
// $D(t) = \exp(-\int_0^t \phi(s)\,ds + \sigma^2 t^3/6).
// Note $D(t) = \exp(-\int_0^t (\phi(s) - \sigma^2 s^2/2))\,ds)$ so the forward is
// $f(t) = \phi(t) - \sigma^2 t^2/2$. 
//
// The difference between the future and forward, $\sigma^2t^/2$, is called the _convexity_. 
//
// The price of a zero coupon bond at time $t$ paying one unit at time $u$ is
// $D_t(u) = E[D_u/D_t|t] = \exp(-\int_t^u f_s\,ds)|_t$ and has a closed form solution.
// Since $d(t B_t) = t\,dB_t + B_t\,dt$,
// \begin{align*}
//   \int_t^u B_s ds &= \int_t^u d(s B_s) - s dB_s \\
//                   &= u B_u - t B_t - \int_t^u s dB_s \\
//                   &= u B_u (- u B_t + u B_t) - t B_t - \int_t^u s dB_s \\
//                   &= (u B_u - u B_t) + u B_t - t B_t - \int_t^u s dB_s \\
//                   &= (u - t)B_t + \int_t^u (u - s) dB_s.\\
// \end{align*}
// Now we use the fact that $M_t = \exp(-\int_0^t a(s)^2\,ds/2 + \int_0^t a(s)\,dB_s)$
// is a martigale for any function $a(s)$, so $E M_u/M_t|_t = 1$ and taking
// $a(s) = \sigma(u - s)$ we have
// \begin{align*}
//   E\exp(int_t^u \sigma(u - s)\,dB_s)|_t &= \exp(\int_t^u \sigma^2(u - s)^2\,ds/2) \\
//                                         &= \exp(-\sigma^2(u - s)^3/6|_t^u) \\
//                                         &= \exp(\sigma^2(u - t)^3/6). \\
// \end{align*}
// hence
// $$
//   E\exp(\int_t^u B_s\,ds) = \exp((u - t)B_t + (u - t)^3/6).
// $$
// Note
// \[
//   E\exp(-\int_t^u B_s\,ds) = \exp(-(u - t)B_t + (u - t)^3/6)
// \]
// since we can replace $(B_t)$ by $(-B_t)$. Putting these facts together yields
// \begin{align*}
//   D_t(u) &= E D_u/D_t|_t \\
//          &= E \exp(-\int_u^t f_s\,ds)|_t \\
//          &= E \exp(-\int_u^t (\phi(s) + \sigma B_s)\,ds)|_t \\
//          &= E \exp(-\int_u^t \phi(s)\,ds - \sigma (u - t) B_t + \sigma^2 (u - t)^3/6). \\
// \end{align*}
// Note $D_t(u)$ is lognormal and
// \[
//   E\log D_t(u) = -\int_u^t\phi(s) ds +\sigma^2 (u - t)^3/6
// \]
// \[
//   \Var\log D_t(u) = \sigma^2 (u - t)^2 t
// \]
// 
// Define $\Phi(t) = \exp(-\int_0^t \phi(s)\,ds)$.
// Since $\log D(t) = \log\Phi(t) + \sigma^2 t^3/6$ we have
// \begin{align*} 
//   E\log D_t(u) &= \log D(u)/D(t) - \sigma^2(u^3 - t^3)/6 + \sigma^2 (u - t)^3/6 \\
//	              &= \log D(u)/D(t) + \sigma^2(-3u^2t + 3ut^2)/6 \\
//                &= \log D(u)/D(t) - \sigma^2 ut(u - t)/2 \\
// \end{align*}

namespace nsr {

	// expected value of log D_t(u)
	inline double E_logD(double Dt, double Du, double sigma, double t, double u)
	{
		return log(Du/Dt) - sigma*sigma*u*t*(u-t)/2;
	}
	// expected value of log D_t(u) using the forward Fuv = F_0(u,v).
	inline double E_logD(double Ftu, double sigma, double t, double u)
	{
		return 0; //!!!write in term the forward Fuv = (D(t)/D(u) - 1)/(u - t).
	}
	// variance of log D_t(u)
	inline double Var_logD(double sigma, double t, double u)
	{
		return 0; //!!! replace by Var log D_t(u)
	}
}

// The _forward rate_ at time $t$ over the interval 
// $[u,v]$ is $F_t(u,v) = (D_t(u)/D_t(v) - 1)/(v-u)$.
// 
// A caplet pays $(v-u)\max\{F_u(u,v) - k, 0\}$ at time $v$. It has value
// \begin{align*}
//   c &= E(v-u)\max\{F_u(u,v) - k, 0\} D_v \\
//     &= E\max\{1/D_u(v) - 1 - (v-u) k, 0\} D_u(v) D_u \\
//     &= E\max\{1 - (1 + (v-u) k)D_u(v), 0\} D_u \\
//     &= E\max\{1 - (1 + (v-u) k)D_u(v) e^\gamma, 0\} E D_u \\
// \end{align*}
// where 
// \begin{align*}
//   \gamma &= \Cov(\log D_u(v), \log D_u) \\
//          &= \Cov(-\sigma(v - u)B_u, -\int_0^u \sigma B_s\,ds \\
//          &= \sigma^2(v - u)\int_0^u \Cov(B_u, B_s)\,ds \\
//          &= \sigma^2(v - u)\int_0^u s\,ds \\
//          &= \sigma^2(v - u)u^2/2 \\
// \end{align*}

namespace nsr {
	// covariance of log D_t(u) and D_t
	inline double Cov_logD_D(double sigma, double t, double u)
	{
		return 0; //!!! replace by Cov(log D_t(u), log D_t)
	}

	// value of caplet over [u,v] with strike k
	inline double caplet_value(double Du, double Dv, double sigma, double k, double u, double v)
	{
		//!!! Determine appropriate values for f and s using 
		// E_LogD, Var_logD, and Cov_logD_D.
		// Recall E exp(N) = exp(E[N] + Var(N)/2) if N is normal.
		double f = 0; // f = EF = E(1 + (v-u) k)D_u(v) e^gamma
		double s = 0; // s^2 t = Var log F = Var log D_u(v)
		k = 1;
		double t = u;

		return black_put_value(f, s, k, t)*Du;
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
	v_ = nsr::E_logD(D(t), D(u), sigma, t, u);
	dv = v - v_;
	assert (fabs(dv) <= eps);
	// !!! test Var_logD
	// !!! test Cov_logD_D

	sigma = 0.05;
	v = -f*dt - sigma*sigma*dt*dt*dt/6;
	v_ = nsr::E_logD(D(t), D(u), sigma, t, u);
	dv = v - v_;
	assert (fabs(dv) <= eps);
	// !!! test Var_logD
	// !!! test Cov_logD_D

	double ftu = (D(t)/D(u) - 1)/(u - t);
	double k = 0.04;
	v = (std::max)(ftu - k, 0.)*D(t);
	sigma = 0;
	v_ = nsr::caplet_value(D(t), D(u), sigma, k, t, u);
	dv = v - v_;
	// !!! test caplet_value equals intrinsic
//	assert (fabs(dv) <= eps);
}

#endif // _DEBUG