// xll_vector.h - GSL vector classes
// http://www.gnu.org/software/gsl/manual/html_node/Vectors.html#Vectors
#pragma once
//#define HAVE_INLINE
#include "gsl/gsl_vector.h"

namespace gsl {

	template<class X>
	struct vector_traits { };
	
	template<>
	struct vector_traits<double> {
		typedef gsl_vector vector_type;
		static vector_type* alloc(size_t n)
		{
			return gsl_vector_alloc(n);
		}
		static vector_type* alloc_from_vector(vector_type* pv)
		{
			return gsl_vector_alloc_from_vector(pv, 0, pv->size, pv->stride);
		}
		static void free(vector_type* pv)
		{
			gsl_vector_free(pv);
		}
		static double get(const vector_type* pv, size_t i)
		{
			return gsl_vector_get(pv, i);
		}
		static void set(vector_type* pv, size_t i, double x)
		{
			return gsl_vector_set(pv, i, x);
		}
	};

	template<>
	struct vector_traits<int> {
		typedef gsl_vector_int vector_type;
		static vector_type* alloc(size_t n)
		{
			return gsl_vector_int_alloc(n);
		}
		static vector_type* alloc_from_vector(vector_type* pv)
		{
			return gsl_vector_int_alloc_from_vector(pv, 0, pv->size, pv->stride);
		}
		static void free(vector_type* pv)
		{
			gsl_vector_int_free(pv);
		}
		static int get(const vector_type* pv, size_t i)
		{
			return gsl_vector_int_get(pv, i);
		}
		static void set(vector_type* pv, size_t i, int x)
		{
			return gsl_vector_int_set(pv, i, x);
		}
	};

	template<class X> 
	class vector {
		typename vector_traits<X>::vector_type* pv;
	public:
		vector()
			: pv(nullptr)
		{ }
		vector(size_t size, size_t stride = 1, const X* px = 0)
			: pv(vector_traits<X>::alloc(size))
		{
			pv->stride = stride;
			if (px)
				for (size_t i = 0; i < size; ++i)
					operator[](i) = px[i];
		}
		vector(const vector& v)
			: pv(vector_traits<X>::alloc(v.size()))
		{
			for (size_t i = 0; i < v.size(); ++i)
				operator[](i) = v[i];
		}
		vector& operator=(const vector& v)
		{
			if (this != &v) {
				vector_traits<X>::free(pv);
				pv = vector_traits<X>::alloc(v.size());
				for (size_t i = 0; i < v.size(); ++i)
					operator[](i) = v[i];
			}

			return *this;
		}
		~vector()
		{
			vector_traits<X>::free(pv);
		}

		typename vector_traits<X>::vector_type* operator&()
		{
			return pv;
		}

		size_t size() const
		{
			return pv->size;
		}
		size_t stride() const
		{
			return pv->stride;
		}
		bool owner() const
		{
			return pv->owner != 0;
		}

		X operator[](size_t i) const
		{
			return vector_traits<X>::get(pv, i);
		}
		X& operator[](size_t i)
		{
			return pv->data[i*(pv->stride)];
		}
	};

} // gsl

#ifdef _DEBUG
#include <cassert>

template<class X>
inline void gsl_test_vector()
{
	{
		gsl::vector<double> v(10);
		assert (v.size() == 10);
		assert (v.stride() == 1);
		assert (v.owner());

		auto v0(v);
		assert (v0.size() == 10);
		assert (v0.stride() == 1);
		assert (v0.owner());

		v = v0;
		assert (v.size() == 10);
		assert (v.stride() == 1);
		assert (v.owner());
	}
}


#endif // _DEBUG

