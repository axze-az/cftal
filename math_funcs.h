#if !defined (__MATH_FUNCS_H__)
#define __MATH_FUNCS_H__ 1

namespace cftal {

	namespace impl {

		template <class _T>
		struct d_real_constants_dbl {
			static const unsigned MAX_FAC=32;
			static const _T inv_fac[MAX_FAC+1];
			static const _T m_ln2;
		};

	}
}

#define INV_FAC_00_HI 1.0000000000000000000000e+00
#define INV_FAC_00_LO 0.0000000000000000000000e+00
#define INV_FAC_01_HI 1.0000000000000000000000e+00
#define INV_FAC_01_LO 0.0000000000000000000000e+00
#define INV_FAC_02_HI 5.0000000000000000000000e-01
#define INV_FAC_02_LO 0.0000000000000000000000e+00
#define INV_FAC_03_HI 1.6666666666666665741481e-01
#define INV_FAC_03_LO 9.2518585385429706566156e-18
#define INV_FAC_04_HI 4.1666666666666664353702e-02
#define INV_FAC_04_LO 2.3129646346357426641539e-18
#define INV_FAC_05_HI 8.3333333333333332176851e-03
#define INV_FAC_05_LO 1.1564823173178713802252e-19
#define INV_FAC_06_HI 1.3888888888888889418943e-03
#define INV_FAC_06_LO -5.3005439543735770590566e-20
#define INV_FAC_07_HI 1.9841269841269841252632e-04
#define INV_FAC_07_LO 1.7209558293420705286779e-22
#define INV_FAC_08_HI 2.4801587301587301565790e-05
#define INV_FAC_08_LO 2.1511947866775881608473e-23
#define INV_FAC_09_HI 2.7557319223985892510951e-06
#define INV_FAC_09_LO -1.8583932740464720810392e-22
#define INV_FAC_10_HI 2.7557319223985888275786e-07
#define INV_FAC_10_LO 2.3767714622250297318518e-23
#define INV_FAC_11_HI 2.5052108385441720223866e-08
#define INV_FAC_11_LO -1.4488140709359119660293e-24
#define INV_FAC_12_HI 2.0876756987868100186555e-09
#define INV_FAC_12_LO -1.2073450591132599716911e-25
#define INV_FAC_13_HI 1.6059043836821613340863e-10
#define INV_FAC_13_LO 1.2585294588752098052117e-26
#define INV_FAC_14_HI 1.1470745597729724507297e-11
#define INV_FAC_14_LO 2.0655512752830745424540e-28
#define INV_FAC_15_HI 7.6471637318198164055138e-13
#define INV_FAC_15_LO 7.0387287773345300106125e-30
#define INV_FAC_16_HI 4.7794773323873852534462e-14
#define INV_FAC_16_LO 4.3992054858340812566328e-31
#define INV_FAC_17_HI 2.8114572543455205981105e-15
#define INV_FAC_17_LO 1.6508842730861432599403e-31
#define INV_FAC_18_HI 1.5619206968586225271148e-16
#define INV_FAC_18_LO 1.1910679660273754002389e-32
#define INV_FAC_19_HI 8.2206352466243294955370e-18
#define INV_FAC_19_LO 2.2141894119604265363725e-34
#define INV_FAC_20_HI 4.1103176233121648440650e-19
#define INV_FAC_20_LO 1.4412973378659527149817e-36
#define INV_FAC_21_HI 1.9572941063391262595198e-20
#define INV_FAC_21_LO -1.3643503830087908487197e-36
#define INV_FAC_22_HI 8.8967913924505740778892e-22
#define INV_FAC_22_LO -7.9114026148723762170263e-38
#define INV_FAC_23_HI 3.8681701706306841261487e-23
#define INV_FAC_23_LO -8.8431776554823422165616e-40
#define INV_FAC_24_HI 1.6117375710961183858953e-24
#define INV_FAC_24_LO -3.6846573564509766032865e-41
#define INV_FAC_25_HI 6.4469502843844735894989e-26
#define INV_FAC_25_LO -1.9330404233703468010728e-42
#define INV_FAC_26_HI 2.4795962632247975896123e-27
#define INV_FAC_26_LO -1.2953730964765228775764e-43
#define INV_FAC_27_HI 9.1836898637955460053942e-29
#define INV_FAC_27_LO 1.4303150396787318912725e-45
#define INV_FAC_28_HI 3.2798892370698377589766e-30
#define INV_FAC_28_LO 1.5117542744029878689714e-46
#define INV_FAC_29_HI 1.1309962886447715881757e-31
#define INV_FAC_29_LO 1.0498015412959506023854e-47
#define INV_FAC_30_HI 3.7699876288159053851494e-33
#define INV_FAC_30_LO 2.5870347832750323834849e-49

template <class _T>
const _T 
cftal::impl::d_real_constants_dbl<_T>::inv_fac[MAX_FAC+1]= {
	_T(INV_FAC_00_HI, INV_FAC_00_LO),
	_T(INV_FAC_01_HI, INV_FAC_01_LO),
	_T(INV_FAC_02_HI, INV_FAC_02_LO),
	_T(INV_FAC_03_HI, INV_FAC_03_LO),
	_T(INV_FAC_04_HI, INV_FAC_04_LO),
	_T(INV_FAC_05_HI, INV_FAC_05_LO),
	_T(INV_FAC_06_HI, INV_FAC_06_LO),
	_T(INV_FAC_07_HI, INV_FAC_07_LO),
	_T(INV_FAC_08_HI, INV_FAC_08_LO),
	_T(INV_FAC_09_HI, INV_FAC_09_LO),
	_T(INV_FAC_10_HI, INV_FAC_10_LO),

	_T(INV_FAC_10_HI, INV_FAC_10_LO),
	_T(INV_FAC_11_HI, INV_FAC_11_LO),
	_T(INV_FAC_12_HI, INV_FAC_12_LO),
	_T(INV_FAC_13_HI, INV_FAC_13_LO),
	_T(INV_FAC_14_HI, INV_FAC_14_LO),
	_T(INV_FAC_15_HI, INV_FAC_15_LO),
	_T(INV_FAC_16_HI, INV_FAC_16_LO),
	_T(INV_FAC_17_HI, INV_FAC_17_LO),
	_T(INV_FAC_18_HI, INV_FAC_18_LO),
	_T(INV_FAC_19_HI, INV_FAC_19_LO),
	_T(INV_FAC_20_HI, INV_FAC_20_LO),

	_T(INV_FAC_20_HI, INV_FAC_20_LO),
	_T(INV_FAC_21_HI, INV_FAC_21_LO),
	_T(INV_FAC_22_HI, INV_FAC_22_LO),
	_T(INV_FAC_23_HI, INV_FAC_23_LO),
	_T(INV_FAC_24_HI, INV_FAC_24_LO),
	_T(INV_FAC_25_HI, INV_FAC_25_LO),
	_T(INV_FAC_26_HI, INV_FAC_26_LO),
	_T(INV_FAC_27_HI, INV_FAC_27_LO),
	_T(INV_FAC_28_HI, INV_FAC_28_LO),
	_T(INV_FAC_29_HI, INV_FAC_29_LO),
	_T(INV_FAC_30_HI, INV_FAC_30_LO)
};

template <class _T>
const _T 
cftal::impl::d_real_constants_dbl<_T>::m_ln2(
	6.931471805599452862e-01,
	2.319046813846299558e-17
);

#undef INV_FAC_00_HI
#undef INV_FAC_00_LO
#undef INV_FAC_01_HI
#undef INV_FAC_01_LO
#undef INV_FAC_02_HI
#undef INV_FAC_02_LO
#undef INV_FAC_03_HI
#undef INV_FAC_03_LO
#undef INV_FAC_04_HI
#undef INV_FAC_04_LO
#undef INV_FAC_05_HI
#undef INV_FAC_05_LO
#undef INV_FAC_06_HI
#undef INV_FAC_06_LO
#undef INV_FAC_07_HI
#undef INV_FAC_07_LO
#undef INV_FAC_08_HI
#undef INV_FAC_08_LO
#undef INV_FAC_09_HI
#undef INV_FAC_09_LO
#undef INV_FAC_10_HI
#undef INV_FAC_10_LO
#undef INV_FAC_11_HI
#undef INV_FAC_11_LO
#undef INV_FAC_12_HI
#undef INV_FAC_12_LO
#undef INV_FAC_13_HI
#undef INV_FAC_13_LO
#undef INV_FAC_14_HI
#undef INV_FAC_14_LO
#undef INV_FAC_15_HI
#undef INV_FAC_15_LO
#undef INV_FAC_16_HI
#undef INV_FAC_16_LO
#undef INV_FAC_17_HI
#undef INV_FAC_17_LO
#undef INV_FAC_18_HI
#undef INV_FAC_18_LO
#undef INV_FAC_19_HI
#undef INV_FAC_19_LO
#undef INV_FAC_20_HI
#undef INV_FAC_20_LO
#undef INV_FAC_21_HI
#undef INV_FAC_21_LO
#undef INV_FAC_22_HI
#undef INV_FAC_22_LO
#undef INV_FAC_23_HI
#undef INV_FAC_23_LO
#undef INV_FAC_24_HI
#undef INV_FAC_24_LO
#undef INV_FAC_25_HI
#undef INV_FAC_25_LO
#undef INV_FAC_26_HI
#undef INV_FAC_26_LO
#undef INV_FAC_27_HI
#undef INV_FAC_27_LO
#undef INV_FAC_28_HI
#undef INV_FAC_28_LO
#undef INV_FAC_29_HI
#undef INV_FAC_29_LO
#undef INV_FAC_30_HI
#undef INV_FAC_30_LO

// Local Variables:
// mode: c++
// end:
#endif
