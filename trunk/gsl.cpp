// gsl.cpp - GNU Scientific Library routines
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#pragma warning(disable: 4127)
#include "gsl.h"

using namespace xll;

static AddInX xai_gsl(
	ArgsX(CATEGORY)
	.Documentation(xml::Conceptual(_T("Call the GNU Scientific Library from Excel."))
		.section(_T("Introduction"), xml::element()
			.content(_T("The GNU Scientific Library ("))
			.content(xml::externalLink(_T("GSL"), _T("http://www.gnu.org/software/gsl/")))
			.content(_T(") is a collection of routines for numerical computing. "))
			.content(_T("The routines have been written from scratch in C, and present a modern Applications Programming Interface "))
			.content(_T("(API) for C programmers, allowing wrappers to be written for very high level languages. "))
			.content(_T("The source code is distributed under the GNU General Public License. "))
		)
		.section(_T("Routines available in GSL"), xml::element()
			.content(_T("The library covers a wide range of topics in numerical computing. Routines are available for the following areas, "))
			.content(xml::element(_T("table"))
				.content(xml::element(_T("row"))
					.content(xml::element(_T("entry"))
						.content(xml::element(_T("para"))
							.content(_T("Complex Numbers"))
						)
					)
					.content(xml::element(_T("entry"))
						.content(xml::element(_T("para"))
							.content(_T("Roots of Polynomials"))
						)
					)
				)
				.content(xml::element(_T("row"))
					.content(xml::element(_T("entry"))
						.content(xml::element(_T("para"))
							.content(_T("Special Functions"))
						)
					)
					.content(xml::element(_T("entry"))
						.content(xml::element(_T("para"))
							.content(_T("Vectors and Matrices"))
						)
					)
				)
			)
			.content(xml::element(_T("para"))
				.content(_T("The use of these routines is described in this manual. Each chapter provides detailed definitions of the functions, followed by example programs and references to the articles on which the algorithms are based. "))
			)
			.content(xml::element(_T("para"))
				.content(_T("Where possible the routines have been based on reliable public-domain packages such as FFTPACK and QUADPACK, which the developers of GSL have reimplemented in C with modern coding conventions. "))
			)
		)
	)
/*
 
 
 Permutations  Combinations 
 
 Sorting  BLAS Support 
 
 Linear Algebra  CBLAS Library 
 
 Fast Fourier Transforms  Eigensystems 
 
 Random Numbers  Quadrature 
 
 Random Distributions  Quasi-Random Sequences 
 
 Histograms  Statistics 
 
 Monte Carlo Integration  N-Tuples 
 
 Differential Equations  Simulated Annealing 
 
 Numerical Differentiation  Interpolation 
 
 Series Acceleration  Chebyshev Approximations 
 
 Root-Finding  Discrete Hankel Transforms 
 
 Least-Squares Fitting  Minimization 
 
 IEEE Floating-Point  Physical Constants 
 
 Basis Splines  Wavelets 
 
*/
);	
