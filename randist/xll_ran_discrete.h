// xll_ran_discrete.h - Discrete random distributions
// http://www.gnu.org/software/gsl/manual/html_node/General-Discrete-Distributions.html#General-Discrete-Distributions
#pragma once
#include <memory>
#include "gsl/gsl_randist.h"

namespace gsl {

	class ran_discrete {
		gsl_ran_discrete_t* g;
	public:
		ran_discrete(size_t K, const double* P)
			: g(::gsl_ran_discrete_preproc(K,P))
		{ }
		ran_discrete(const ran_discrete&) = delete;
		ran_discrete& operator=(const ran_discrete&) = delete;
		~ran_discrete()
		{ 
			::gsl_ran_discrete_free(g);
		}

		operator const gsl_ran_discrete_t*() const
		{
			return g;
		}
	};

} // gsl