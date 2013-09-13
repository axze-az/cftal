#if !defined (__MATH_FUNC_F32_H__)
#define __MATH_FUNC_F32_H__ 1

#include <cftal/config.h>
#include <cftal/d_real.h>
#include <cftal/std_types.h>
#include <type_traits>
#include <limits>
#include <utility>

namespace cftal {
        namespace math {

                template <>
                struct func_traits<float, int32_t>
                        : public d_real_traits<float> {
                        typedef float vf_type;
                        typedef int32_t vi_type;
                        typedef bool vmf_type;
                        typedef bool vmi_type;
                        typedef uint32_t mask_type;
                        typedef union {
                                float _d;
                                uint32_t _u;
                        } ud_t;

                        static constexpr int32_t bias = 0x7e;
                        static constexpr int32_t e_max= 127;
                        static constexpr int32_t e_min= -126;
                        static constexpr int32_t bits=23;
                        static constexpr int32_t vec_len=1;

                        static constexpr double pinf() {
                                return std::numeric_limits<float>::infinity();
                        }
                        static constexpr double ninf() {
                                return -std::numeric_limits<double>::infinity();
                        }
                        static constexpr double nan() {
                                return std::numeric_limits<double>::quiet_NaN();
                        }
                        static
                        vmf_type vmi_to_vmf(const vmi_type& mi) {
                                return mi;
                        }
                        static
                        vmi_type vmf_to_vmi(const vmf_type& mf) {
                                return mf;
                        }
                        static
                        vi_type sel(const vmi_type& msk,
                                    const vi_type& t, const vi_type& f) {
                                return msk ? t : f;
                        }
                        static
                        vf_type sel(const vmf_type& msk,
                                    const vf_type& t, const vf_type& f) {
                                return msk ? t : f;
                        }
                        static
                        vf_type insert_exp(const vi_type& e) {
                                ud_t t;
                                t._u = uint64_t(e) << bits;
                                return t._d;
                        }
                        static
                        vi_type extract_exp(const vf_type& d) {
                                ud_t t;
                                t._d = d;
                                return (t._u >> bits) & 0x7FF;
                        }
                        static
                        vf_type cvt_i_to_f(const vi_type& i) {
                                return vf_type(i);
                        }
                        // including rounding to nearest.
                        static
                        vi_type cvt_f_to_i(const vf_type& f) {
                                return f < 0 ?
                                        (vi_type)(f - 0.5) :
                                        (vi_type)(f + 0.5);
                        }
                        // including rounding towards zero
                        static
                        vi_type cvt_rz_f_to_i(const vf_type& f) {
                                return (vi_type)f;
                        }

			static
			vi_type as_int(const vf_type& f) {
                                ud_t t;
                                t._d = f;
                                return t._u;
			}

			static
			vf_type as_float(const vi_type& i) {
                                ud_t t;
                                t._u = i;
                                return t._d;
			}
                };

                template <typename _T>
                class func<float, int32_t, _T> {
                        typedef typename _T::vf_type vf_type;
                        typedef typename _T::vi_type vi_type;
                        typedef typename _T::vmf_type vmf_type;
                        typedef typename _T::vmi_type vmi_type;

                public:
                        static vf_type pow2i(const vi_type& d);
                        static vf_type ldexp(const vf_type& vf,
                                             const vi_type& vi);
			static vf_type frexp(const vf_type& vf,
					     vi_type* vi);
                        static vi_type ilogbp1(const vf_type& vi);
                        static vi_type ilogb(const vf_type& vf);
                };
        }
}

template <typename _T>
inline
typename
cftal::math::func<float, cftal::int32_t, _T>::vf_type
cftal::math::func<float, cftal::int32_t, _T>::pow2i(const vi_type& vi)
{
        vi_type e(vi + vi_type(_T::bias));
        vf_type r(_T::insert_exp(e));
        vmi_type mi;
        vmf_type mf;
        mi= (vi < vi_type(_T::e_min));
        mf= _T::vmi_to_vmf(mi);
        r= _T::sel(mf, vf_type(0.0), r);
        mi= (vi > vi_type(_T::e_max));
        mf= _T::vmi_to_vmf(mi);
        vf_type inf(_T::pinf());
        r= _T::sel(mf, vf_type(inf), r);
        return r;
}

template <typename _T>
inline
typename cftal::math::func<float, cftal::int32_t, _T>::vf_type
cftal::math::func<float, cftal::int32_t, _T>::ldexp(const vf_type& vd,
						    const vi_type& ve)
{
        vi_type q= ve;
        vi_type m = q >> 31;
        m = (((m + q) >> 6) - m) << 4;
        q = q - (m << 2);

        m += 127;
        m = max(vi_type(0), m);
        m = min(vi_type(0xff), m);

        vf_type fm = _T::insert_exp(m);
        vf_type r = vd * fm * fm * fm * fm;
        q += 0x7f;
        // q = max(vi_type(0), q);
        // q = min(vi_type(0x7ff), q);
        vf_type fq = _T::insert_exp(q);
        return r * fq;
}

template <typename _T>
inline
typename cftal::math::func<float, cftal::int32_t, _T>::vf_type
cftal::math::func<float, cftal::int32_t, _T>::frexp(const vf_type& vd,
                                                     vi_type* ve)
{
	// normal numbers:
	vi_type i(_T::as_int(vd));

	vi_type value_head(i & vi_type(0x7fffffff));

	vi_type is_inf_nan_zero((value_head >= 0x7f800000) |
				(value_head==vi_type(0)));
	vi_type is_denom(value_head < 0x008000000);

	// exponent:
	vi_type e((value_head >> 23) - vi_type(126));

	// denormals
	// const vf_type two54=1.80143985094819840000e+16f;
	// multiply with 2^25
	const vf_type two25(0x1.p25f);
	vf_type vden(two25 * vd);
	vi_type iden(_T::as_int(vden));
	vi_type value_head_den(iden & vi_type(0x7fffffff));
	vi_type eden((value_head_den>>23) - vi_type(126 +25));

	// select denom/normal
	e = _T::sel(is_denom, eden, e);
	i = _T::sel(is_denom, iden, i);
	// insert exponent
	i = (i & vi_type(0x807fffff)) | vi_type(0x7e<<23);
	// interpret as float
	vf_type frc(_T::as_float(i));
	// inf, nan, zero
	vmf_type f_inz(_T::vmi_to_vmf(is_inf_nan_zero));
	e= _T::sel(is_inf_nan_zero, vi_type(0), e);
	frc = _T::sel(f_inz, vd, frc);

	if (ve != nullptr)
		*ve= e;
	return frc;
}

template <typename _T>
inline
typename cftal::math::func<float, cftal::int32_t, _T>::vi_type
cftal::math::func<float, cftal::int32_t, _T>::ilogbp1(const vf_type& vd)
{
        vmf_type mf= vd < 5.421010862427522E-20f;
        vf_type d = _T::sel(mf, 1.8446744073709552E19f * vd, vd);
        vi_type q = _T::extract_exp(d);
        vmi_type mi= _T::vmf_to_vmi(mf);
        vi_type qs = _T::sel(mi, vi_type(64 + 0x7e), vi_type(0x7e));
        return q - qs;
}

template <typename _T>
inline
typename cftal::math::func<float, cftal::int32_t, _T>::vi_type
cftal::math::func<float, cftal::int32_t, _T>::ilogb(const vf_type& d)
{
        vi_type e(ilogbp1(abs(d) -1));
        vmf_type mf= d == 0.0f;
        vmi_type mi= _T::vmf_to_vmi(mf);
        e = _T::sel(mi, vi_type(-2147483648), e);
        mf = isinf(d);
        mi = _T::vmf_to_vmi(mf);
        e = _T::sel(mi, vi_type(2147483647), e);
        return e;
}

// Local Variables:
// mode: c++
// end:
#endif
