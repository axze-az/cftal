#include "x86vec_test.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <iomanip>
#include <cstdlib>

namespace {
	struct _space8 {
	};
	static _space8 space8;

	std::ostream& operator<<(std::ostream& s, const _space8& t)
	{
		for (std::size_t i=0;i<8;++i)
			s.put(' ');
		return s;
	}

	class cvt_int {
		int _i;
		std::size_t _prec;
	public:
		cvt_int(int ii, std::size_t pr) : _i(ii), _prec(pr) {
		}
		int i() const {
			return _i;
		}
		std::size_t prec() const {
			return _prec;
		}
	};

	std::ostream& operator<<(std::ostream& s, const cvt_int& i)
	{
		if (i.i() < 0) {
			for (std::size_t j=0; j<i.prec();++j)
				s << '_';
		} else {
			char c(s.fill());
			s << std::setfill('0')
			  << std::setw(i.prec())<<i.i()
			  << std::setfill(c);
		}
		return s;
	}

	std::string make_file_name(const std::string& base,
				   const std::string& func,
				   int i=-2, int prec=-2)
	{
		std::stringstream s;
		s << base << '_' << func;
		if (i>-2) {
			s << '_' << cvt_int(i, prec);
		}
		s << ".cc";
		return s.str();
	}
}


std::ostream& x86vec::test::operator<<(std::ostream& s, const idx& i)
{
	const std::size_t n=i.size();
	for (std::size_t j=0; j<n; ++j) {
		s << std::setw(2) << i[j];
		if (j!=n-1)
			s << ',';
	}
	return s;
}

bool x86vec::test::check_f64(const char* msg,
				__m128d v, const idx& i)
{
	union {
		double _d[2];
		__m128d _v;
	} t;
	_mm_store_pd(t._d, v);
	bool rc(check_val(t._d[0], i[0]) && check_val(t._d[1], i[1]));
	if (rc == false) {
		std::cerr << msg << "< " << i
			  << "> [ " << pr_v2d(v) << "] FAILED.\n";
	}
	return rc;
}

bool x86vec::test::check_f32(const char* msg,
			       __m128 v, const idx& i)
{
	union {
		float _f[4];
		__m128 _v;
	} t;
	_mm_store_ps(t._f, v);
	bool rc(true);
	for (int j=0;j<4;++j)
		rc &= check_val(t._f[j], i[j]);
	if (rc == false) {
		std::cout << msg << "< " << i
			  << "> [ " << pr_v4f(v) << " ] FAILED.\n";
	}
	return rc;
}

bool x86vec::test::check_u16(const char* msg,
			     __m128i v, const idx& i)
{
	union {
		uint16_t _u[8];
		__m128i _v;
	} t;
	_mm_store_si128(&t._v, v);
	bool rc(true);
	for (int j=0;j<8;++j) {
		rc &= check_val(t._u[j], i[j]);
	}
	if (rc == false) {
		std::cout << msg << "< " << i
			  << "> [ " << pr_v8u16(v) << " ] FAILED.\n";
	}
	return rc;
}

bool x86vec::test::check_u32(const char* msg,
			     __m128i v, const idx& i)
{
	union {
		uint32_t _u[4];
		__m128i _v;
	} t;
	_mm_store_si128(&t._v, v);
	bool rc(true);
	for (int j=0;j<4;++j)
		rc &= check_val(t._u[j], i[j]);
	if (rc == false) {
		std::cout << msg << "< " << i
			  << "> [ " << pr_v4u32(v) << " ] FAILED.\n";
	}
	return rc;
}

bool x86vec::test::check_u64(const char* msg,
			     __m128i v, const idx& i)
{
	union {
		uint64_t _u[2];
		__m128i _v;
	} t;
	_mm_store_si128(&t._v, v);
	bool rc(true);
	for (int j=0;j<2;++j)
		rc &= check_val(t._u[j], i[j]);
	if (rc == false) {
		std::cout << msg << "< " << i
			  << "> [ " << pr_v2u64(v) << " ] FAILED.\n";
	}
	return rc;
}

void x86vec::test::generate(const std::string& name_base)
{
	generate_f64(name_base);
	generate_u64(name_base);
	generate_f32(name_base);
	generate_u32(name_base);
	generate_u16(name_base);
}

void x86vec::test::generate_f64(const std::string& name_base)
{
	std::string fname(name_base + "_f64.cc");
	std::ofstream f(fname.c_str(), std::ios::out | std::ios::trunc);
	if (!f)
		return;
	// select double
	f << "#include \"x86vec_test.h\"\n"
	  << "#include <iostream>\n"
	  << "bool x86vec::test::check_select_f64()\n"
	  << "{\n"
	  << space8 << "bool rc(true);\n"
	  << space8 << "__m128d a = load_f64(false);\n"
	  << space8 << "__m128d b = load_f64(true);\n"
	  << space8 << "__m128d r;\n"
	  << space8 << "idx id(-2,-2);\n\n";
	for (int i=0; i<2; ++i) {
		for (int j=0; j<2; ++j) {
			f << space8 << "r=select_f64<"
			  << idx(i,j) << ">(a,b);\n";
			f << space8 << "id.assign("
			  << idx(((i!=0) ? 0 : 2),
				 ((j!=0) ? 1 : 3))
			  << ");\n";
			f << space8
			  << "rc &= check_f64(\"select_f64\", r, id);\n";
		}
	}
	f << space8 << "return rc;\n"
	  << "}\n\n";

	// perm1 double
	f << "bool x86vec::test::check_perm1_f64()\n"
	  << "{\n"
	  << space8 << "bool rc(true);\n"
	  << space8 << "__m128d a = load_f64(false);\n"
	  << space8 << "__m128d r;\n"
	  << space8 << "idx id(-2,-2);\n\n";
	for (int i=-1; i<2; ++i) {
		for (int j=-1; j<2; ++j) {
			f << space8 << "r=perm_f64<"
			  << idx(i,j) << ">(a);\n";
			f << space8 << "id.assign("
			  << idx(i, j)
			  << ");\n";
			f << space8
			  << "rc &= check_f64(\"perm1_f64\", r, id);\n";
		}
	}
	f << space8 << "return rc;\n"
	  << "}\n\n";

	// perm2 double
	f << "bool x86vec::test::check_perm2_f64()\n"
	  << "{\n"
	  << space8 << "bool rc(true);\n"
	  << space8 << "__m128d a = load_f64(false);\n"
	  << space8 << "__m128d b = load_f64(true);\n"
	  << space8 << "__m128d r;\n"
	  << space8 << "idx id(-2,-2);\n\n";
	for (int i=-1; i<4; ++i) {
		for (int j=-1; j<4; ++j) {
			f << space8 << "r=perm_f64<"
			  << idx(i,j) << ">(a,b);\n";
			f << space8 << "id.assign("
			  << idx(i, j)
			  << ");\n";
			f << space8
			  << "rc &= check_f64(\"perm2_f64\", r, id);\n";
		}
	}
	f << space8 << "return rc;\n"
	  << "}\n\n";
}

void x86vec::test::generate_u64(const std::string& name_base)
{
	std::string fname(name_base + "_u64.cc");
	std::ofstream f(fname.c_str(), std::ios::out | std::ios::trunc);
	if (!f)
		return;
	// select u64
	f << "#include \"x86vec_test.h\"\n"
	  << "#include <iostream>\n"
	  << "bool x86vec::test::check_select_u64()\n"
	  << "{\n"
	  << space8 << "bool rc(true);\n"
	  << space8 << "__m128i a = load_u64(false);\n"
	  << space8 << "__m128i b = load_u64(true);\n"
	  << space8 << "__m128i r;\n"
	  << space8 << "idx id(-2,-2);\n\n";
	for (int i=0; i<2; ++i) {
		for (int j=0; j<2; ++j) {
			f << space8 << "r=select_u64<"
			  << idx(i,j) << ">(a,b);\n";
			f << space8 << "id.assign("
			  << idx(((i!=0) ? 0 : 2),
				 ((j!=0) ? 1 : 3))
			  << ");\n";
			f << space8
			  << "rc &= check_u64(\"select_u64\", r, id);\n";
		}
	}
	f << space8 << "return rc;\n"
	  << "}\n\n";

	// perm1 u64
	f << "bool x86vec::test::check_perm1_u64()\n"
	  << "{\n"
	  << space8 << "bool rc(true);\n"
	  << space8 << "__m128i a = load_u64(false);\n"
	  << space8 << "__m128i r;\n"
	  << space8 << "idx id(-2,-2);\n\n";
	for (int i=-1; i<2; ++i) {
		for (int j=-1; j<2; ++j) {
			f << space8 << "r=perm_u64<"
			  << idx(i,j) << ">(a);\n";
			f << space8 << "id.assign("
			  << idx(i, j)
			  << ");\n";
			f << space8
			  << "rc &= check_u64(\"perm1_u64\", r, id);\n";
		}
	}
	f << space8 << "return rc;\n"
	  << "}\n\n";

	// perm2 u64
	f << "bool x86vec::test::check_perm2_u64()\n"
	  << "{\n"
	  << space8 << "bool rc(true);\n"
	  << space8 << "__m128i a = load_u64(false);\n"
	  << space8 << "__m128i b = load_u64(true);\n"
	  << space8 << "__m128i r;\n"
	  << space8 << "idx id(-2,-2);\n\n";
	for (int i=-1; i<4; ++i) {
		for (int j=-1; j<4; ++j) {
			f << space8 << "r=perm_u64<"
			  << idx(i,j) << ">(a,b);\n";
			f << space8 << "id.assign("
			  << idx(i, j)
			  << ");\n";
			f << space8
			  << "rc &= check_u64(\"perm2_u64\", r, id);\n";
		}
	}
	f << space8 << "return rc;\n"
	  << "}\n\n";
}

void x86vec::test::generate_f32(const std::string& name_base)
{
	std::string fname(make_file_name(name_base, "sel_f32"));
	std::ofstream f(fname.c_str(), std::ios::out | std::ios::trunc);
	if (!f)
		return;
	// select float
	f << "#include \"x86vec_test.h\"\n\n"
	  << "bool x86vec::test::check_select_f32()\n"
	  << "{\n"
	  << space8 << "bool rc(true);\n"
	  << space8 << "__m128 a = load_f32(false);\n"
	  << space8 << "__m128 b = load_f32(true);\n"
	  << space8 << "__m128 r;\n"
	  << space8 << "idx id(-2,-2);\n\n";
	for (int i=0; i<2; ++i) {
		for (int j=0; j<2; ++j) {
			for (int k=0; k<2;++k) {
				for (int l=0; l<2; ++l) {
					f << space8 << "r=select_f32<"
					  << idx(i, j, k, l) << ">(a,b);\n";
					f << space8 << "id.assign("
					  << idx(((i!=0) ? 0 : 4),
						 ((j!=0) ? 1 : 5),
						 ((k!=0) ? 2 : 6),
						 ((l!=0) ? 3 : 7))
					  << ");\n";
					f << space8
					  << "rc &= "
					  << "check_f32(\"select_f32\", r, id);\n";				}
			}
		}
	}
	f << space8 << "return rc;\n"
	  << "}\n\n";
	f.close();

	for (int i=-1; i<4; ++i) {
		fname = make_file_name(name_base, "perm1_f32", i, 1);
		f.open(fname.c_str(), std::ios::out | std::ios::trunc);
		// perm1 float
		f << "#include \"x86vec_test.h\"\n\n"
		  << "bool x86vec::test::check_perm1_f32_" << cvt_int(i,1)
		  << "()\n"
		  << "{\n"
		  << space8 << "bool rc(true);\n"
		  << space8 << "__m128 a = load_f32(false);\n"
		  << space8 << "__m128 r;\n"
		  << space8 << "idx id(-2,-2);\n\n";
		for (int j=-1; j<4; ++j) {
			for (int k=-1; k<4;++k) {
				for (int l=-1; l<4; ++l) {
					f << space8 << "r=perm_f32<"
					  << idx(i, j, k, l) << ">(a);\n";
					f << space8 << "id.assign("
					  << idx(i, j, k, l)
					  << ");\n";
					f << space8
					  << "rc &= "
					  << "check_f32(\"perm1_f32\", r, id);\n";
				}
			}
		}
		f << space8 << "return rc;\n"
		  << "}\n\n";
		f.close();
	}

	// perm2 float
	for (int i=-1; i<8; ++i) {
		fname = make_file_name(name_base, "perm2_f32", i, 1);
		f.open(fname.c_str(), std::ios::out | std::ios::trunc);
		f << "#include \"x86vec_test.h\"\n\n"
		  << "bool x86vec::test::check_perm2_f32_"<< cvt_int(i, 1)
		  << "()\n"
		  << "{\n"
		  << space8 << "bool rc(true);\n"
		  << space8 << "__m128 a = load_f32(false);\n"
		  << space8 << "__m128 b = load_f32(true);\n"
		  << space8 << "__m128 r;\n"
		  << space8 << "idx id(-2,-2);\n\n";
		for (int j=-1; j<8; ++j) {
			for (int k=-1; k<8;++k) {
				for (int l=-1; l<8; ++l) {
					f << space8 << "r=perm_f32<"
					  << idx(i, j, k, l) << ">(a,b);\n";
					f << space8 << "id.assign("
					  << idx(i, j, k, l)
					  << ");\n";
					f << space8
					  << "rc &= "
					  << "check_f32(\"perm1_f32\", r, id);\n";
				}
			}
		}
		f << space8 << "return rc;\n"
		  << "}\n\n";
		f.close();
	}
	fname = make_file_name(name_base, "perm_f32");
	f.open(fname.c_str(), std::ios::out | std::ios::trunc);
	// perm1 float
	f << "#include \"x86vec_test.h\"\n\n"
	  << "bool x86vec::test::check_perm1_f32()\n"
	  << "{\n"
	  << space8 << "bool rc(true);\n";
	for (int i=-1; i<4; ++i) {
		f << space8 << "rc &= check_perm1_f32_"
		  << cvt_int(i,1)
		  << "();\n";
	}
	f << space8 << "return rc;\n"
	  << "}\n\n";
	f << "//#include \"x86vec_test.h\"\n\n"
	  << "bool x86vec::test::check_perm2_f32()\n"
	  << "{\n"
	  << space8 << "bool rc(true);\n";
	for (int i=-1; i<8; ++i) {
		f << space8 << "rc &= check_perm2_f32_"
		  << cvt_int(i,1)
		  << "();\n";
	}
	f << space8 << "return rc;\n"
	  << "}\n\n";
}


void x86vec::test::generate_u32(const std::string& name_base)
{
	std::string fname(make_file_name(name_base, "sel_u32"));
	std::ofstream f(fname.c_str(), std::ios::out | std::ios::trunc);
	if (!f)
		return;
	// select u32
	f << "#include \"x86vec_test.h\"\n\n"
	  << "bool x86vec::test::check_select_u32()\n"
	  << "{\n"
	  << space8 << "bool rc(true);\n"
	  << space8 << "__m128i a = load_u32(false);\n"
	  << space8 << "__m128i b = load_u32(true);\n"
	  << space8 << "__m128i r;\n"
	  << space8 << "idx id(-2,-2);\n\n";
	for (int i=0; i<2; ++i) {
		for (int j=0; j<2; ++j) {
			for (int k=0; k<2;++k) {
				for (int l=0; l<2; ++l) {
					f << space8 << "r=select_u32<"
					  << idx(i, j, k, l) << ">(a,b);\n";
					f << space8 << "id.assign("
					  << idx(((i!=0) ? 0 : 4),
						 ((j!=0) ? 1 : 5),
						 ((k!=0) ? 2 : 6),
						 ((l!=0) ? 3 : 7))
					  << ");\n";
					f << space8
					  << "rc &= "
					  << "check_u32(\"select_u32\", r, id);\n";				}
			}
		}
	}
	f << space8 << "return rc;\n"
	  << "}\n\n";
	f.close();

	for (int i=-1; i<4; ++i) {
		fname = make_file_name(name_base, "perm1_u32", i, 1);
		f.open(fname.c_str(), std::ios::out | std::ios::trunc);
		// perm1 u32
		f << "#include \"x86vec_test.h\"\n\n"
		  << "bool x86vec::test::check_perm1_u32_" << cvt_int(i,1)
		  << "()\n"
		  << "{\n"
		  << space8 << "bool rc(true);\n"
		  << space8 << "__m128i a = load_u32(false);\n"
		  << space8 << "__m128i r;\n"
		  << space8 << "idx id(-2,-2);\n\n";
		for (int j=-1; j<4; ++j) {
			for (int k=-1; k<4;++k) {
				for (int l=-1; l<4; ++l) {
					f << space8 << "r=perm_u32<"
					  << idx(i, j, k, l) << ">(a);\n";
					f << space8 << "id.assign("
					  << idx(i, j, k, l)
					  << ");\n";
					f << space8
					  << "rc &= "
					  << "check_u32(\"perm1_u32\", r, id);\n";
				}
			}
		}
		f << space8 << "return rc;\n"
		  << "}\n\n";
		f.close();
	}

	// perm2 u32
	for (int i=-1; i<8; ++i) {
		fname = make_file_name(name_base, "perm2_u32", i, 1);
		f.open(fname.c_str(), std::ios::out | std::ios::trunc);
		f << "#include \"x86vec_test.h\"\n\n"
		  << "bool x86vec::test::check_perm2_u32_" << cvt_int(i, 1)
		  << "()\n"
		  << "{\n"
		  << space8 << "bool rc(true);\n"
		  << space8 << "__m128i a = load_u32(false);\n"
		  << space8 << "__m128i b = load_u32(true);\n"
		  << space8 << "__m128i r;\n"
		  << space8 << "idx id(-2,-2);\n\n";
		for (int j=-1; j<8; ++j) {
			for (int k=-1; k<8;++k) {
				for (int l=-1; l<8; ++l) {
					f << space8 << "r=perm_u32<"
					  << idx(i, j, k, l) << ">(a,b);\n";
					f << space8 << "id.assign("
					  << idx(i, j, k, l)
					  << ");\n";
					f << space8
					  << "rc &= "
					  << "check_u32(\"perm1_u32\", r, id);\n";
				}
			}
		}
		f << space8 << "return rc;\n"
		  << "}\n\n";
		f.close();
	}
	fname = make_file_name(name_base, "perm_u32");
	f.open(fname.c_str(), std::ios::out | std::ios::trunc);
	// perm1 u32
	f << "#include \"x86vec_test.h\"\n\n"
	  << "bool x86vec::test::check_perm1_u32()\n"
	  << "{\n"
	  << space8 << "bool rc(true);\n";
	for (int i=-1; i<4; ++i) {
		f << space8 << "rc &= check_perm1_u32_"
		  << cvt_int(i,1)
		  << "();\n";
	}
	f << space8 << "return rc;\n"
	  << "}\n\n";
	f << "//#include \"x86vec_test.h\"\n\n"
	  << "bool x86vec::test::check_perm2_u32()\n"
	  << "{\n"
	  << space8 << "bool rc(true);\n";
	for (int i=-1; i<8; ++i) {
		f << space8 << "rc &= check_perm2_u32_"
		  << cvt_int(i,1)
		  << "();\n";
	}
	f << space8 << "return rc;\n"
	  << "}\n\n";
}

void x86vec::test::generate_u16(const std::string& name_base)
{
	std::string fname(make_file_name(name_base, "sel_u16"));
	std::ofstream f(fname.c_str(), std::ios::out | std::ios::trunc);
	if (!f)
		return;
	// select u16
	f << "#include \"x86vec_test.h\"\n\n"
	  << "bool x86vec::test::check_select_u16()\n"
	  << "{\n"
	  << space8 << "bool rc(true);\n"
	  << space8 << "__m128i a = load_u16(false);\n"
	  << space8 << "__m128i b = load_u16(true);\n"
	  << space8 << "__m128i r;\n"
	  << space8 << "idx id(-2,-2);\n\n";
	for (int i0=0; i0<2; ++i0) {
		for (int i1=0; i1<2; ++i1) {
			for (int i2=0; i2<2;++i2) {
				for (int i3=0; i3<2; ++i3) {
					for (int i4=0; i4<2; ++i4) {
						for (int i5=0; i5<2; ++i5) {
							for (int i6=0; i6<2;++i6) {
								for (int i7=0; i7<2; ++i7) {
									f << space8 << "r=select_u16<"
									  << idx(i0, i1, i2, i3, i4, i5, i6, i7) << ">(a,b);\n";
									f << space8 << "id.assign("
									  << idx((i0 !=0) ? 0 : 8,
										 (i1 !=0) ? 1 : 9,
										 (i2 !=0) ? 2 : 10,
										 (i3 !=0) ? 3 : 11,
										 (i4 !=0) ? 4 : 12,
										 (i5 !=0) ? 5 : 13,
										 (i6 !=0) ? 6 : 14,
										 (i7 !=0) ? 7 : 15)
									  << ");\n";
									f << space8
									  << "rc &= "
									  << "check_u16(\"select_u16\", r, id);\n";
								}
							}
						}
					}
				}
			}
		}
	}
	f << space8 << "return rc;\n"
	  << "}\n\n";
	f.close();

	const int TEST_CASES = 768;
	// perm1 u16
	for (int i0=-1; i0<8; ++i0) {
		fname = make_file_name(name_base, "perm1_u16", i0, 1);
		f.open(fname.c_str(), std::ios::out | std::ios::trunc);
		f << "#include \"x86vec_test.h\"\n\n"
		  << "bool x86vec::test::check_perm1_u16_" << cvt_int(i0,1)
		  <<"()\n"
		  << "{\n"
		  << space8 << "bool rc(true);\n"
		  << space8 << "__m128i a = load_u16(false);\n"
		  << space8 << "__m128i r;\n"
		  << space8 << "idx id(-2,-2);\n\n";
		const unsigned int n1=8+1;
		for (int i=0;i<TEST_CASES; ++i) {
			int i1, i2, i3, i4, i5, i6, i7;
			i1= ((uint32_t(std::rand()) >> 8)% n1) -1;
			i2= ((uint32_t(std::rand()) >> 8)% n1) -1;
			i3= ((uint32_t(std::rand()) >> 8)% n1) -1;
			i4= ((uint32_t(std::rand()) >> 8)% n1) -1;
			i5= ((uint32_t(std::rand()) >> 8)% n1) -1;
			i6= ((uint32_t(std::rand()) >> 8)% n1) -1;
			i7= ((uint32_t(std::rand()) >> 8)% n1) -1;
			f << space8 << "r=perm_u16<"
			  << idx(i0, i1, i2, i3, i4, i5, i6, i7) << ">(a);\n";
			f << space8 << "id.assign("
			  << idx(i0, i1, i2, i3, i4, i5, i6, i7)
			  << ");\n";
			f << space8
			  << "rc &= "
			  << "check_u16(\"perm1_u16\", r, id);\n";
		}
		f << space8 << "return rc;\n"
		  << "}\n\n";
		f.close();
	}

	// perm2 u16
	for (int i0=-1; i0<16;++i0) {
		fname = make_file_name(name_base, "perm2_u16", i0, 2);
		f.open(fname.c_str(), std::ios::out | std::ios::trunc);
		f << "#include \"x86vec_test.h\"\n\n"
		  << "bool x86vec::test::check_perm2_u16_" << cvt_int(i0,2)
		  << "()\n"
		  << "{\n"
		  << space8 << "bool rc(true);\n"
		  << space8 << "__m128i a = load_u16(false);\n"
		  << space8 << "__m128i b = load_u16(true);\n"
		  << space8 << "__m128i r;\n"
		  << space8 << "idx id(-2,-2);\n\n";
		const unsigned int n2=16+1;
		for (int i=0;i<TEST_CASES; ++i) {
			int i1, i2, i3, i4, i5, i6, i7;
			i1= ((uint32_t(std::rand()) >> 8)% n2) -1;
			i2= ((uint32_t(std::rand()) >> 8)% n2) -1;
			i3= ((uint32_t(std::rand()) >> 8)% n2) -1;
			i4= ((uint32_t(std::rand()) >> 8)% n2) -1;
			i5= ((uint32_t(std::rand()) >> 8)% n2) -1;
			i6= ((uint32_t(std::rand()) >> 8)% n2) -1;
			i7= ((uint32_t(std::rand()) >> 8)% n2) -1;
			f << space8 << "r=perm_u16<"
			  << idx(i0, i1, i2, i3, i4, i5, i6, i7)
			  << ">(a,b);\n";
			f << space8 << "id.assign("
			  << idx(i0, i1, i2, i3, i4, i5, i6, i7)
			  << ");\n";
			f << space8
			  << "rc &= "
			  << "check_u16(\"perm2_u16\", r, id);\n";
		}
		f << space8 << "return rc;\n"
		  << "}\n\n";
		f.close();
	}
	fname = make_file_name(name_base, "perm_u16");
	f.open(fname.c_str(), std::ios::out | std::ios::trunc);
	// perm1 u16
	f << "#include \"x86vec_test.h\"\n\n"
	  << "bool x86vec::test::check_perm1_u16()\n"
	  << "{\n"
	  << space8 << "bool rc(true);\n";
	for (int i=-1; i<8; ++i) {
		f << space8 << "rc &= check_perm1_u16_"
		  << cvt_int(i,1)
		  << "();\n";
	}
	f << space8 << "return rc;\n"
	  << "}\n\n";
	f << "//#include \"x86vec_test.h\"\n\n"
	  << "bool x86vec::test::check_perm2_u16()\n"
	  << "{\n"
	  << space8 << "bool rc(true);\n";
	for (int i=-1; i<16; ++i) {
		f << space8 << "rc &= check_perm2_u16_"
		  << cvt_int(i,2)
		  << "();\n";
	}
	f << space8 << "return rc;\n"
	  << "}\n\n";
}
