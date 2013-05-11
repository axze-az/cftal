#include <assert.h>
#include <math.h>

#if defined (__GNUC__) || defined (__INTEL_COMPILER) || defined (__clang__)
#define INLINE __attribute__((always_inline))
#else
#define INLINE inline
#endif

#include "nonnumber.h"

#ifdef ENABLE_SSE2
#include "helpersse2.h"
#endif

#ifdef ENABLE_AVX
#include "helperavx.h"
#endif

#ifdef ENABLE_AVX2
#include "helperavx2.h"
#endif

#ifdef ENABLE_FMA4
#include "helperfma4.h"
#endif

//

#include "dd.h"
#include "df.h"

//

#define PI4_A 0.78539816290140151978
#define PI4_B 4.9604678871439933374e-10
#define PI4_C 1.1258708853173288931e-18
#define PI4_D 1.7607799325916000908e-27

#define M_4_PI 1.273239544735162542821171882678754627704620361328125

#define L2U .69314718055966295651160180568695068359375
#define L2L .28235290563031577122588448175013436025525412068e-12
#define R_LN2 1.442695040888963407359924681001892137426645954152985934135449406931

//

#define PI4_Af 0.78515625f
#define PI4_Bf 0.00024187564849853515625f
#define PI4_Cf 3.7747668102383613586e-08f
#define PI4_Df 1.2816720341285448015e-12f

#define L2Uf 0.693145751953125f
#define L2Lf 1.428606765330187045e-06f
#define R_LN2f 1.442695040888963407359924681001892137426645954152985934135449406931f

//

vdouble xldexp(vdouble x, vint q) { return vldexp_vd_vd_vi(x, q); }

vint xilogb(vdouble d) {
  vdouble e = vcast_vd_vi(vsub_vi_vi_vi(vilogbp1_vi_vd(vabs_vd_vd(d)), vcast_vi_i(1)));
  e = vsel_vd_vm_vd_vd(veq_vm_vd_vd(d, vcast_vd_d(0)), vcast_vd_d(-2147483648.0), e);
  e = vsel_vd_vm_vd_vd(veq_vm_vd_vd(vabs_vd_vd(d), vcast_vd_d(INFINITY)), vcast_vd_d(2147483647), e);
  return vrint_vi_vd(e);
}

vdouble xsin(vdouble d) {
  vint q;
  vdouble u, s;

  q = vrint_vi_vd(vmul_vd_vd_vd(d, vcast_vd_d(M_1_PI)));

  u = vcast_vd_vi(q);
  d = vmla_vd_vd_vd_vd(u, vcast_vd_d(-PI4_A*4), d);
  d = vmla_vd_vd_vd_vd(u, vcast_vd_d(-PI4_B*4), d);
  d = vmla_vd_vd_vd_vd(u, vcast_vd_d(-PI4_C*4), d);
  d = vmla_vd_vd_vd_vd(u, vcast_vd_d(-PI4_D*4), d);

  s = vmul_vd_vd_vd(d, d);

  d = vsel_vd_vm_vd_vd(veq_vm_vi_vi(vand_vi_vi_vi(q, vcast_vi_i(1)), vcast_vi_i(1)), vneg_vd_vd(d), d);

  u = vcast_vd_d(-7.97255955009037868891952e-18);
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(2.81009972710863200091251e-15));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(-7.64712219118158833288484e-13));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(1.60590430605664501629054e-10));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(-2.50521083763502045810755e-08));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(2.75573192239198747630416e-06));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(-0.000198412698412696162806809));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(0.00833333333333332974823815));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(-0.166666666666666657414808));

  u = vmla_vd_vd_vd_vd(s, vmul_vd_vd_vd(u, d), d);

  return u;
}

vdouble xsin_u1(vdouble d) {
  vint q;
  vdouble u;
  vdouble2 s, t, x;

  q = vrint_vi_vd(vmul_vd_vd_vd(d, vcast_vd_d(M_1_PI)));
  u = vcast_vd_vi(q);

  s = ddadd2_vd2_vd_vd (d, vmul_vd_vd_vd(u, vcast_vd_d(-PI4_A*4)));
  s = ddadd2_vd2_vd2_vd(s, vmul_vd_vd_vd(u, vcast_vd_d(-PI4_B*4)));
  s = ddadd2_vd2_vd2_vd(s, vmul_vd_vd_vd(u, vcast_vd_d(-PI4_C*4)));
  s = ddadd2_vd2_vd2_vd(s, vmul_vd_vd_vd(u, vcast_vd_d(-PI4_D*4)));

  t = s;
  s = ddsqu_vd2_vd2(s);

  u = vcast_vd_d(2.72052416138529567917983e-15);
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(-7.6429259411395447190023e-13));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(1.60589370117277896211623e-10));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(-2.5052106814843123359368e-08));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(2.75573192104428224777379e-06));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(-0.000198412698412046454654947));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(0.00833333333333318056201922));

  x = ddadd_vd2_vd_vd2(vcast_vd_d(1), ddmul_vd2_vd2_vd2(ddadd_vd2_vd_vd(vcast_vd_d(-0.166666666666666657414808), vmul_vd_vd_vd(u, s.x)), s));

  x = ddmul_vd2_vd2_vd2(t, x);
  u = vadd_vd_vd_vd(x.x, x.y);

  u = vsel_vd_vm_vd_vd(veq_vm_vi_vi(vand_vi_vi_vi(q, vcast_vi_i(1)), vcast_vi_i(1)), vneg_vd_vd(u), u);

  return u;
}

vdouble xcos(vdouble d) {
  vint q;
  vdouble u, s;

  q = vrint_vi_vd(vmla_vd_vd_vd_vd(d, vcast_vd_d(M_1_PI), vcast_vd_d(-0.5)));
  q = vadd_vi_vi_vi(vadd_vi_vi_vi(q, q), vcast_vi_i(1));

  u = vcast_vd_vi(q);
  d = vmla_vd_vd_vd_vd(u, vcast_vd_d(-PI4_A*2), d);
  d = vmla_vd_vd_vd_vd(u, vcast_vd_d(-PI4_B*2), d);
  d = vmla_vd_vd_vd_vd(u, vcast_vd_d(-PI4_C*2), d);
  d = vmla_vd_vd_vd_vd(u, vcast_vd_d(-PI4_D*2), d);

  s = vmul_vd_vd_vd(d, d);

  d = vsel_vd_vm_vd_vd(veq_vm_vi_vi(vand_vi_vi_vi(q, vcast_vi_i(2)), vcast_vi_i(0)), vneg_vd_vd(d), d);

  u = vcast_vd_d(-7.97255955009037868891952e-18);
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(2.81009972710863200091251e-15));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(-7.64712219118158833288484e-13));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(1.60590430605664501629054e-10));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(-2.50521083763502045810755e-08));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(2.75573192239198747630416e-06));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(-0.000198412698412696162806809));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(0.00833333333333332974823815));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(-0.166666666666666657414808));

  u = vmla_vd_vd_vd_vd(s, vmul_vd_vd_vd(u, d), d);

  return u;
}

vdouble xcos_u1(vdouble d) {
  vint q;
  vdouble u;
  vdouble2 s, t, x;

  q = vrint_vi_vd(vmla_vd_vd_vd_vd(d, vcast_vd_d(M_1_PI), vcast_vd_d(-0.5)));
  q = vadd_vi_vi_vi(vadd_vi_vi_vi(q, q), vcast_vi_i(1));
  u = vcast_vd_vi(q);

  s = ddadd2_vd2_vd_vd (d, vmul_vd_vd_vd(u, vcast_vd_d(-PI4_A*2)));
  s = ddadd2_vd2_vd2_vd(s, vmul_vd_vd_vd(u, vcast_vd_d(-PI4_B*2)));
  s = ddadd2_vd2_vd2_vd(s, vmul_vd_vd_vd(u, vcast_vd_d(-PI4_C*2)));
  s = ddadd2_vd2_vd2_vd(s, vmul_vd_vd_vd(u, vcast_vd_d(-PI4_D*2)));

  t = s;
  s = ddsqu_vd2_vd2(s);

  s = ddnormalize_vd2_vd2(s);

  u = vcast_vd_d(2.72052416138529567917983e-15);
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(-7.6429259411395447190023e-13));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(1.60589370117277896211623e-10));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(-2.5052106814843123359368e-08));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(2.75573192104428224777379e-06));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(-0.000198412698412046454654947));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(0.00833333333333318056201922));

  x = ddadd_vd2_vd_vd2(vcast_vd_d(1), ddmul_vd2_vd2_vd2(ddadd_vd2_vd_vd(vcast_vd_d(-0.166666666666666657414808), vmul_vd_vd_vd(u, s.x)), s));

  x = ddmul_vd2_vd2_vd2(t, x);
  u = vadd_vd_vd_vd(x.x, x.y);

  u = vsel_vd_vm_vd_vd(veq_vm_vi_vi(vand_vi_vi_vi(q, vcast_vi_i(2)), vcast_vi_i(0)), vneg_vd_vd(u), u);

  return u;
}

vdouble2 xsincos(vdouble d) {
  vint q;
  vmask m;
  vdouble u, s, t, rx, ry;
  vdouble2 r;

  q = vrint_vi_vd(vmul_vd_vd_vd(d, vcast_vd_d(M_2_PI)));

  s = d;

  u = vcast_vd_vi(q);
  s = vmla_vd_vd_vd_vd(u, vcast_vd_d(-PI4_A*2), s);
  s = vmla_vd_vd_vd_vd(u, vcast_vd_d(-PI4_B*2), s);
  s = vmla_vd_vd_vd_vd(u, vcast_vd_d(-PI4_C*2), s);
  s = vmla_vd_vd_vd_vd(u, vcast_vd_d(-PI4_D*2), s);

  t = s;

  s = vmul_vd_vd_vd(s, s);

  u = vcast_vd_d(1.58938307283228937328511e-10);
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(-2.50506943502539773349318e-08));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(2.75573131776846360512547e-06));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(-0.000198412698278911770864914));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(0.0083333333333191845961746));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(-0.166666666666666130709393));
  u = vmul_vd_vd_vd(vmul_vd_vd_vd(u, s), t);

  rx = vadd_vd_vd_vd(t, u);

  u = vcast_vd_d(-1.13615350239097429531523e-11);
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(2.08757471207040055479366e-09));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(-2.75573144028847567498567e-07));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(2.48015872890001867311915e-05));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(-0.00138888888888714019282329));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(0.0416666666666665519592062));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(-0.5));

  ry = vmla_vd_vd_vd_vd(s, u, vcast_vd_d(1));

  m = veq_vm_vi_vi(vand_vi_vi_vi(q, vcast_vi_i(1)), vcast_vi_i(0));
  r.x = vsel_vd_vm_vd_vd(m, rx, ry);
  r.y = vsel_vd_vm_vd_vd(m, ry, rx);

  m = veq_vm_vi_vi(vand_vi_vi_vi(q, vcast_vi_i(2)), vcast_vi_i(2));
  r.x = vreinterpret_vd_vm(vxor_vm_vm_vm(vand_vm_vm_vm(m, vreinterpret_vm_vd(vcast_vd_d(-0.0))), vreinterpret_vm_vd(r.x)));

  m = veq_vm_vi_vi(vand_vi_vi_vi(vadd_vi_vi_vi(q, vcast_vi_i(1)), vcast_vi_i(2)), vcast_vi_i(2));
  r.y = vreinterpret_vd_vm(vxor_vm_vm_vm(vand_vm_vm_vm(m, vreinterpret_vm_vd(vcast_vd_d(-0.0))), vreinterpret_vm_vd(r.y)));

  m = visinf_vm_vd(d);
  r.x = vsel_vd_vm_vd_vd(m, vcast_vd_d(NAN), r.x);
  r.y = vsel_vd_vm_vd_vd(m, vcast_vd_d(NAN), r.y);

  return r;
}

vdouble2 xsincos_u1(vdouble d) {
  vint q;
  vmask m;
  vdouble u, rx, ry;
  vdouble2 r, s, t, x;

  q = vrint_vi_vd(vmul_vd_vd_vd(d, vcast_vd_d(2 * M_1_PI)));
  u = vcast_vd_vi(q);

  s = ddadd2_vd2_vd_vd (d, vmul_vd_vd_vd(u, vcast_vd_d(-PI4_A*2)));
  s = ddadd2_vd2_vd2_vd(s, vmul_vd_vd_vd(u, vcast_vd_d(-PI4_B*2)));
  s = ddadd2_vd2_vd2_vd(s, vmul_vd_vd_vd(u, vcast_vd_d(-PI4_C*2)));
  s = ddadd2_vd2_vd2_vd(s, vmul_vd_vd_vd(u, vcast_vd_d(-PI4_D*2)));

  t = s;

  s = ddsqu_vd2_vd2(s);
  s.x = vadd_vd_vd_vd(s.x, s.y);

  u = vcast_vd_d(1.58938307283228937328511e-10);
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(-2.50506943502539773349318e-08));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(2.75573131776846360512547e-06));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(-0.000198412698278911770864914));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(0.0083333333333191845961746));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(-0.166666666666666130709393));

  u = vmul_vd_vd_vd(u, vmul_vd_vd_vd(s.x, t.x));

  x = ddadd_vd2_vd2_vd(t, u);
  rx = vadd_vd_vd_vd(x.x, x.y);

  u = vcast_vd_d(-1.13615350239097429531523e-11);
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(2.08757471207040055479366e-09));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(-2.75573144028847567498567e-07));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(2.48015872890001867311915e-05));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(-0.00138888888888714019282329));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(0.0416666666666665519592062));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(-0.5));

  x = ddadd_vd2_vd_vd2(vcast_vd_d(1), ddmul_vd2_vd_vd(s.x, u));
  ry = vadd_vd_vd_vd(x.x, x.y);

  m = veq_vm_vi_vi(vand_vi_vi_vi(q, vcast_vi_i(1)), vcast_vi_i(0));
  r.x = vsel_vd_vm_vd_vd(m, rx, ry);
  r.y = vsel_vd_vm_vd_vd(m, ry, rx);

  m = veq_vm_vi_vi(vand_vi_vi_vi(q, vcast_vi_i(2)), vcast_vi_i(2));
  r.x = vreinterpret_vd_vm(vxor_vm_vm_vm(vand_vm_vm_vm(m, vreinterpret_vm_vd(vcast_vd_d(-0.0))), vreinterpret_vm_vd(r.x)));

  m = veq_vm_vi_vi(vand_vi_vi_vi(vadd_vi_vi_vi(q, vcast_vi_i(1)), vcast_vi_i(2)), vcast_vi_i(2));
  r.y = vreinterpret_vd_vm(vxor_vm_vm_vm(vand_vm_vm_vm(m, vreinterpret_vm_vd(vcast_vd_d(-0.0))), vreinterpret_vm_vd(r.y)));

  m = visinf_vm_vd(d);
  r.x = vsel_vd_vm_vd_vd(m, vcast_vd_d(NAN), r.x);
  r.y = vsel_vd_vm_vd_vd(m, vcast_vd_d(NAN), r.y);

  return r;
}

vdouble xtan(vdouble d) {
  vint q;
  vdouble u, s, x;
  vmask m;

  q = vrint_vi_vd(vmul_vd_vd_vd(d, vcast_vd_d(M_2_PI)));

  u = vcast_vd_vi(q);
  x = vmla_vd_vd_vd_vd(u, vcast_vd_d(-PI4_A*2), d);
  x = vmla_vd_vd_vd_vd(u, vcast_vd_d(-PI4_B*2), x);
  x = vmla_vd_vd_vd_vd(u, vcast_vd_d(-PI4_C*2), x);
  x = vmla_vd_vd_vd_vd(u, vcast_vd_d(-PI4_D*2), x);

  s = vmul_vd_vd_vd(x, x);

  m = veq_vm_vi_vi(vand_vi_vi_vi(q, vcast_vi_i(1)), vcast_vi_i(1));
  x = vsel_vd_vm_vd_vd(m, vneg_vd_vd(x), x);

  u = vcast_vd_d(1.01419718511083373224408e-05);
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(-2.59519791585924697698614e-05));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(5.23388081915899855325186e-05));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(-3.05033014433946488225616e-05));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(7.14707504084242744267497e-05));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(8.09674518280159187045078e-05));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(0.000244884931879331847054404));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(0.000588505168743587154904506));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(0.00145612788922812427978848));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(0.00359208743836906619142924));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(0.00886323944362401618113356));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(0.0218694882853846389592078));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(0.0539682539781298417636002));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(0.133333333333125941821962));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(0.333333333333334980164153));

  u = vmla_vd_vd_vd_vd(s, vmul_vd_vd_vd(u, x), x);

  u = vsel_vd_vm_vd_vd(m, vrec_vd_vd(u), u);

  u = vsel_vd_vm_vd_vd(visinf_vm_vd(d), vcast_vd_d(NAN), u);

  return u;
}

vdouble xtan_u1(vdouble d) {
  vint q;
  vdouble u;
  vdouble2 s, t, x;
  vmask m;

  q = vrint_vi_vd(vmul_vd_vd_vd(d, vcast_vd_d(M_2_PI)));
  u = vcast_vd_vi(q);

  s = ddadd2_vd2_vd_vd (d, vmul_vd_vd_vd(u, vcast_vd_d(-PI4_A*2)));
  s = ddadd2_vd2_vd2_vd(s, vmul_vd_vd_vd(u, vcast_vd_d(-PI4_B*2)));
  s = ddadd2_vd2_vd2_vd(s, vmul_vd_vd_vd(u, vcast_vd_d(-PI4_C*2)));
  s = ddadd2_vd2_vd2_vd(s, vmul_vd_vd_vd(u, vcast_vd_d(-PI4_D*2)));

  m = veq_vm_vi_vi(vand_vi_vi_vi(q, vcast_vi_i(1)), vcast_vi_i(1));
  s = vsel_vd2_vm_vd2_vd2(m, ddneg_vd2_vd2(s), s);

  t = s;
  s = ddsqu_vd2_vd2(s);
  s = ddnormalize_vd2_vd2(s);

  u = vcast_vd_d(1.01419718511083373224408e-05);
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(-2.59519791585924697698614e-05));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(5.23388081915899855325186e-05));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(-3.05033014433946488225616e-05));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(7.14707504084242744267497e-05));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(8.09674518280159187045078e-05));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(0.000244884931879331847054404));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(0.000588505168743587154904506));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(0.00145612788922812427978848));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(0.00359208743836906619142924));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(0.00886323944362401618113356));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(0.0218694882853846389592078));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(0.0539682539781298417636002));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(0.133333333333125941821962));

  x = ddadd_vd2_vd_vd2(vcast_vd_d(1), ddmul_vd2_vd2_vd2(ddadd_vd2_vd_vd(vcast_vd_d(0.333333333333334980164153), vmul_vd_vd_vd(u, s.x)), s));
  x = ddmul_vd2_vd2_vd2(t, x);

  x = vsel_vd2_vm_vd2_vd2(m, ddrec_vd2_vd2(ddnormalize_vd2_vd2(x)), x);

  u = vadd_vd_vd_vd(x.x, x.y);

  //u = vsel_vd_vm_vd_vd(visinf_vm_vd(d), vcast_vd_d(NAN), u);

  return u;
}

static INLINE vdouble atan2k(vdouble y, vdouble x) {
  vdouble s, t, u;
  vint q;
  vmask p;

  q = vsel_vi_vd_vd_vi_vi(x, vcast_vd_d(0), vcast_vi_i(-2), vcast_vi_i(0));
  x = vabs_vd_vd(x);

  q = vsel_vi_vd_vd_vi_vi(x, y, vadd_vi_vi_vi(q, vcast_vi_i(1)), q);
  p = vlt_vm_vd_vd(x, y);
  s = vsel_vd_vm_vd_vd(p, vneg_vd_vd(x), y);
  t = vmax_vd_vd_vd(x, y);

  s = vdiv_vd_vd_vd(s, t);
  t = vmul_vd_vd_vd(s, s);

  u = vcast_vd_d(-1.88796008463073496563746e-05);
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(0.000209850076645816976906797));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(-0.00110611831486672482563471));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(0.00370026744188713119232403));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(-0.00889896195887655491740809));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(0.016599329773529201970117));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(-0.0254517624932312641616861));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(0.0337852580001353069993897));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(-0.0407629191276836500001934));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(0.0466667150077840625632675));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(-0.0523674852303482457616113));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(0.0587666392926673580854313));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(-0.0666573579361080525984562));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(0.0769219538311769618355029));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(-0.090908995008245008229153));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(0.111111105648261418443745));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(-0.14285714266771329383765));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(0.199999999996591265594148));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(-0.333333333333311110369124));

  t = vmla_vd_vd_vd_vd(s, vmul_vd_vd_vd(t, u), s);
  t = vmla_vd_vd_vd_vd(vcast_vd_vi(q), vcast_vd_d(M_PI/2), t);

  return t;
}

static INLINE vdouble2 atan2k_u1(vdouble2 y, vdouble2 x) {
  vdouble u;
  vdouble2 s, t;
  vint q;
  vmask p;

  q = vsel_vi_vd_vd_vi_vi(x.x, vcast_vd_d(0), vcast_vi_i(-2), vcast_vi_i(0));
  p = vlt_vm_vd_vd(x.x, vcast_vd_d(0));
  x = vsel_vd2_vm_vd2_vd2(p, ddneg_vd2_vd2(x), x);

  q = vsel_vi_vd_vd_vi_vi(x.x, y.x, vadd_vi_vi_vi(q, vcast_vi_i(1)), q);
  p = vlt_vm_vd_vd(x.x, y.x);
  s = vsel_vd2_vm_vd2_vd2(p, ddneg_vd2_vd2(x), y);
  t = vsel_vd2_vm_vd2_vd2(p, y, x);

  s = dddiv_vd2_vd2_vd2(s, t);
  t = ddsqu_vd2_vd2(s);
  t = ddnormalize_vd2_vd2(t);

  u = vcast_vd_d(1.06298484191448746607415e-05);
  u = vmla_vd_vd_vd_vd(u, t.x, vcast_vd_d(-0.000125620649967286867384336));
  u = vmla_vd_vd_vd_vd(u, t.x, vcast_vd_d(0.00070557664296393412389774));
  u = vmla_vd_vd_vd_vd(u, t.x, vcast_vd_d(-0.00251865614498713360352999));
  u = vmla_vd_vd_vd_vd(u, t.x, vcast_vd_d(0.00646262899036991172313504));
  u = vmla_vd_vd_vd_vd(u, t.x, vcast_vd_d(-0.0128281333663399031014274));
  u = vmla_vd_vd_vd_vd(u, t.x, vcast_vd_d(0.0208024799924145797902497));
  u = vmla_vd_vd_vd_vd(u, t.x, vcast_vd_d(-0.0289002344784740315686289));
  u = vmla_vd_vd_vd_vd(u, t.x, vcast_vd_d(0.0359785005035104590853656));
  u = vmla_vd_vd_vd_vd(u, t.x, vcast_vd_d(-0.041848579703592507506027));
  u = vmla_vd_vd_vd_vd(u, t.x, vcast_vd_d(0.0470843011653283988193763));
  u = vmla_vd_vd_vd_vd(u, t.x, vcast_vd_d(-0.0524914210588448421068719));
  u = vmla_vd_vd_vd_vd(u, t.x, vcast_vd_d(0.0587946590969581003860434));
  u = vmla_vd_vd_vd_vd(u, t.x, vcast_vd_d(-0.0666620884778795497194182));
  u = vmla_vd_vd_vd_vd(u, t.x, vcast_vd_d(0.0769225330296203768654095));
  u = vmla_vd_vd_vd_vd(u, t.x, vcast_vd_d(-0.0909090442773387574781907));
  u = vmla_vd_vd_vd_vd(u, t.x, vcast_vd_d(0.111111108376896236538123));
  u = vmla_vd_vd_vd_vd(u, t.x, vcast_vd_d(-0.142857142756268568062339));
  u = vmla_vd_vd_vd_vd(u, t.x, vcast_vd_d(0.199999999997977351284817));
  u = vmla_vd_vd_vd_vd(u, t.x, vcast_vd_d(-0.333333333333317605173818));

  t = ddmul_vd2_vd2_vd(t, u);
  t = ddnormalize_vd2_vd2(t);
  t = ddmul_vd2_vd2_vd2(s, ddadd_vd2_vd_vd2(vcast_vd_d(1), t));
  t = ddadd2_vd2_vd2_vd2(ddmul_vd2_vd2_vd(vcast_vd2_d_d(1.570796326794896557998982, 6.12323399573676603586882e-17), vcast_vd_vi(q)), t);

  return t;
}

vdouble xatan2(vdouble y, vdouble x) {
  vdouble r = atan2k(vabs_vd_vd(y), x);

  r = vmulsign_vd_vd_vd(r, x);
  r = vsel_vd_vm_vd_vd(vor_vm_vm_vm(visinf_vm_vd(x), veq_vm_vd_vd(x, vcast_vd_d(0))), vsub_vd_vd_vd(vcast_vd_d(M_PI/2), visinf2(x, vmulsign_vd_vd_vd(vcast_vd_d(M_PI/2), x))), r);
  r = vsel_vd_vm_vd_vd(visinf_vm_vd(y), vsub_vd_vd_vd(vcast_vd_d(M_PI/2), visinf2(x, vmulsign_vd_vd_vd(vcast_vd_d(M_PI/4), x))), r);
  r = vsel_vd_vm_vd_vd(veq_vm_vd_vd(y, vcast_vd_d(0)), vsel_vd_vm_vd_vd(veq_vm_vd_vd(vsign_vd_vd(x), vcast_vd_d(-1.0)), vcast_vd_d(M_PI), vcast_vd_d(0)), r);

  return vsel_vd_vm_vd_vd(vor_vm_vm_vm(visnan_vm_vd(x), visnan_vm_vd(y)), vcast_vd_d(NAN), vmulsign_vd_vd_vd(r, y));
}

vdouble xatan2_u1(vdouble y, vdouble x) {
  vdouble2 d = atan2k_u1(vcast_vd2_vd_vd(vabs_vd_vd(y), vcast_vd_d(0)), vcast_vd2_vd_vd(x, vcast_vd_d(0)));
  vdouble r = vadd_vd_vd_vd(d.x, d.y);

  r = vmulsign_vd_vd_vd(r, x);
  r = vsel_vd_vm_vd_vd(vor_vm_vm_vm(visinf_vm_vd(x), veq_vm_vd_vd(x, vcast_vd_d(0))), vsub_vd_vd_vd(vcast_vd_d(M_PI/2), visinf2(x, vmulsign_vd_vd_vd(vcast_vd_d(M_PI/2), x))), r);
  r = vsel_vd_vm_vd_vd(visinf_vm_vd(y), vsub_vd_vd_vd(vcast_vd_d(M_PI/2), visinf2(x, vmulsign_vd_vd_vd(vcast_vd_d(M_PI/4), x))), r);
  r = vsel_vd_vm_vd_vd(veq_vm_vd_vd(y, vcast_vd_d(0)), vsel_vd_vm_vd_vd(veq_vm_vd_vd(vsign_vd_vd(x), vcast_vd_d(-1.0)), vcast_vd_d(M_PI), vcast_vd_d(0)), r);

  return vsel_vd_vm_vd_vd(vor_vm_vm_vm(visnan_vm_vd(x), visnan_vm_vd(y)), vcast_vd_d(NAN), vmulsign_vd_vd_vd(r, y));
}

vdouble xasin(vdouble d) {
  vdouble x, y;
  x = vadd_vd_vd_vd(vcast_vd_d(1), d);
  y = vsub_vd_vd_vd(vcast_vd_d(1), d);
  x = vmul_vd_vd_vd(x, y);
  x = vsqrt_vd_vd(x);
  x = vsel_vd_vm_vd_vd(visnan_vm_vd(x), vcast_vd_d(NAN), atan2k(vabs_vd_vd(d), x));
  return vmulsign_vd_vd_vd(x, d);
}

vdouble xasin_u1(vdouble d) {
  vdouble2 d2 = atan2k_u1(vcast_vd2_vd_vd(vabs_vd_vd(d), vcast_vd_d(0)), ddsqrt_vd2_vd2(ddmul_vd2_vd2_vd2(ddadd_vd2_vd_vd(vcast_vd_d(1), d), ddsub_vd2_vd_vd(vcast_vd_d(1), d))));
  vdouble r = vadd_vd_vd_vd(d2.x, d2.y);
  r = vsel_vd_vm_vd_vd(veq_vm_vd_vd(vabs_vd_vd(d), vcast_vd_d(1)), vcast_vd_d(1.570796326794896557998982), r);
  return vmulsign_vd_vd_vd(r, d);
}

vdouble xacos(vdouble d) {
  vdouble x, y;
  x = vadd_vd_vd_vd(vcast_vd_d(1), d);
  y = vsub_vd_vd_vd(vcast_vd_d(1), d);
  x = vmul_vd_vd_vd(x, y);
  x = vsqrt_vd_vd(x);
  x = vmulsign_vd_vd_vd(atan2k(x, vabs_vd_vd(d)), d);
  y = (vdouble)vand_vm_vm_vm(vlt_vm_vd_vd(d, vcast_vd_d(0)), (vmask)vcast_vd_d(M_PI));
  x = vadd_vd_vd_vd(x, y);
  return x;
}

vdouble xacos_u1(vdouble d) {
  vdouble2 d2 = atan2k_u1(ddsqrt_vd2_vd2(ddmul_vd2_vd2_vd2(ddadd_vd2_vd_vd(vcast_vd_d(1), d), ddsub_vd2_vd_vd(vcast_vd_d(1), d))), vcast_vd2_vd_vd(vabs_vd_vd(d), vcast_vd_d(0)));
  d2 = ddscale_vd2_vd2_vd(d2, vmulsign_vd_vd_vd(vcast_vd_d(1), d));

  vmask m;
  m = vneq_vm_vd_vd(vabs_vd_vd(d), vcast_vd_d(1));
  d2.x = (vdouble)vand_vm_vm_vm(m, (vmask)d2.x);
  d2.y = (vdouble)vand_vm_vm_vm(m, (vmask)d2.y);
  m = vlt_vm_vd_vd(d, vcast_vd_d(0));
  d2 = vsel_vd2_vm_vd2_vd2(m, ddadd_vd2_vd2_vd2(vcast_vd2_d_d(3.141592653589793116, 1.2246467991473532072e-16), d2), d2);

  return vadd_vd_vd_vd(d2.x, d2.y);
}

vdouble xatan_u1(vdouble d) {
  vdouble2 d2 = atan2k_u1(vcast_vd2_vd_vd(vabs_vd_vd(d), vcast_vd_d(0)), vcast_vd2_d_d(1, 0));
  vdouble r = vadd_vd_vd_vd(d2.x, d2.y);
  r = vsel_vd_vm_vd_vd(visinf_vm_vd(d), vcast_vd_d(1.570796326794896557998982), r);
  return vmulsign_vd_vd_vd(r, d);
}

vdouble xatan(vdouble s) {
  vdouble t, u;
  vint q;

  q = vsel_vi_vd_vd_vi_vi(s, vcast_vd_d(0), vcast_vi_i(2), vcast_vi_i(0));
  s = vabs_vd_vd(s);

  q = vsel_vi_vd_vd_vi_vi(vcast_vd_d(1), s, vadd_vi_vi_vi(q, vcast_vi_i(1)), q);
  s = vsel_vd_vm_vd_vd(vlt_vm_vd_vd(vcast_vd_d(1), s), vdiv_vd_vd_vd(vcast_vd_d(1), s), s);

  t = vmul_vd_vd_vd(s, s);

  u = vcast_vd_d(-1.88796008463073496563746e-05);
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(0.000209850076645816976906797));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(-0.00110611831486672482563471));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(0.00370026744188713119232403));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(-0.00889896195887655491740809));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(0.016599329773529201970117));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(-0.0254517624932312641616861));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(0.0337852580001353069993897));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(-0.0407629191276836500001934));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(0.0466667150077840625632675));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(-0.0523674852303482457616113));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(0.0587666392926673580854313));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(-0.0666573579361080525984562));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(0.0769219538311769618355029));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(-0.090908995008245008229153));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(0.111111105648261418443745));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(-0.14285714266771329383765));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(0.199999999996591265594148));
  u = vmla_vd_vd_vd_vd(u, t, vcast_vd_d(-0.333333333333311110369124));

  t = vmla_vd_vd_vd_vd(s, vmul_vd_vd_vd(t, u), s);

  t = vsel_vd_vm_vd_vd(veq_vm_vi_vi(vand_vi_vi_vi(q, vcast_vi_i(1)), vcast_vi_i(1)), vsub_vd_vd_vd(vcast_vd_d(M_PI/2), t), t);
  t = vsel_vd_vm_vd_vd(veq_vm_vi_vi(vand_vi_vi_vi(q, vcast_vi_i(2)), vcast_vi_i(2)), vneg_vd_vd(t), t);

  return t;
}

vdouble xlog(vdouble d) {
  vdouble x, x2;
  vdouble t, m;
  vint e;

  e = vilogbp1_vi_vd(vmul_vd_vd_vd(d, vcast_vd_d(0.7071)));
  m = vldexp_vd_vd_vi(d, vsub_vi_vi_vi(vcast_vi_i(0), e));

  x = vdiv_vd_vd_vd(vadd_vd_vd_vd(vcast_vd_d(-1), m), vadd_vd_vd_vd(vcast_vd_d(1), m));
  x2 = vmul_vd_vd_vd(x, x);

  t = vcast_vd_d(0.148197055177935105296783);
  t = vmla_vd_vd_vd_vd(t, x2, vcast_vd_d(0.153108178020442575739679));
  t = vmla_vd_vd_vd_vd(t, x2, vcast_vd_d(0.181837339521549679055568));
  t = vmla_vd_vd_vd_vd(t, x2, vcast_vd_d(0.22222194152736701733275));
  t = vmla_vd_vd_vd_vd(t, x2, vcast_vd_d(0.285714288030134544449368));
  t = vmla_vd_vd_vd_vd(t, x2, vcast_vd_d(0.399999999989941956712869));
  t = vmla_vd_vd_vd_vd(t, x2, vcast_vd_d(0.666666666666685503450651));
  t = vmla_vd_vd_vd_vd(t, x2, vcast_vd_d(2));

  x = vmla_vd_vd_vd_vd(x, t, vmul_vd_vd_vd(vcast_vd_d(0.693147180559945286226764), vcast_vd_vi(e)));

  x = vsel_vd_vm_vd_vd(vispinf_vm_vd(d), vcast_vd_d(INFINITY), x);
  x = vsel_vd_vm_vd_vd(vgt_vm_vd_vd(vcast_vd_d(0), d), vcast_vd_d(NAN), x);
  x = vsel_vd_vm_vd_vd(veq_vm_vd_vd(d, vcast_vd_d(0)), vcast_vd_d(-INFINITY), x);

  return x;
}

vdouble xexp(vdouble d) {
  vint q = vrint_vi_vd(vmul_vd_vd_vd(d, vcast_vd_d(R_LN2)));
  vdouble s, u;

  s = vmla_vd_vd_vd_vd(vcast_vd_vi(q), vcast_vd_d(-L2U), d);
  s = vmla_vd_vd_vd_vd(vcast_vd_vi(q), vcast_vd_d(-L2L), s);

  u = vcast_vd_d(2.08860621107283687536341e-09);
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(2.51112930892876518610661e-08));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(2.75573911234900471893338e-07));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(2.75572362911928827629423e-06));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(2.4801587159235472998791e-05));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(0.000198412698960509205564975));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(0.00138888888889774492207962));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(0.00833333333331652721664984));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(0.0416666666666665047591422));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(0.166666666666666851703837));
  u = vmla_vd_vd_vd_vd(u, s, vcast_vd_d(0.5));

  u = vadd_vd_vd_vd(vcast_vd_d(1), vmla_vd_vd_vd_vd(vmul_vd_vd_vd(s, s), u, s));

  u = vldexp_vd_vd_vi(u, q);

  u = vsel_vd_vm_vd_vd(visminf_vm_vd(d), vcast_vd_d(0), u);

  return u;
}

static INLINE vdouble2 logk(vdouble d) {
  vdouble2 x, x2;
  vdouble t, m;
  vint e;

  e = vilogbp1_vi_vd(vmul_vd_vd_vd(d, vcast_vd_d(0.7071)));
  m = vldexp_vd_vd_vi(d, vsub_vi_vi_vi(vcast_vi_i(0), e));

  x = dddiv_vd2_vd2_vd2(ddadd2_vd2_vd_vd(vcast_vd_d(-1), m), ddadd2_vd2_vd_vd(vcast_vd_d(1), m));
  x2 = ddsqu_vd2_vd2(x);
  x2 = ddnormalize_vd2_vd2(x2);

  t = vcast_vd_d(0.134601987501262130076155);
  t = vmla_vd_vd_vd_vd(t, x2.x, vcast_vd_d(0.132248509032032670243288));
  t = vmla_vd_vd_vd_vd(t, x2.x, vcast_vd_d(0.153883458318096079652524));
  t = vmla_vd_vd_vd_vd(t, x2.x, vcast_vd_d(0.181817427573705403298686));
  t = vmla_vd_vd_vd_vd(t, x2.x, vcast_vd_d(0.222222231326187414840781));
  t = vmla_vd_vd_vd_vd(t, x2.x, vcast_vd_d(0.285714285651261412873718));
  t = vmla_vd_vd_vd_vd(t, x2.x, vcast_vd_d(0.400000000000222439910458));
  t = vmla_vd_vd_vd_vd(t, x2.x, vcast_vd_d(0.666666666666666371239645));

  return ddadd2_vd2_vd2_vd2(ddmul_vd2_vd2_vd(vcast_vd2_vd_vd(vcast_vd_d(0.693147180559945286226764), vcast_vd_d(2.319046813846299558417771e-17)),
		       vcast_vd_vi(e)),
		ddadd2_vd2_vd2_vd2(ddscale_vd2_vd2_vd(x, vcast_vd_d(2)), ddmul_vd2_vd2_vd(ddmul_vd2_vd2_vd2(x2, x), t)));
}

vdouble xlog_u1(vdouble d) {
  vdouble2 s = logk(d);
  vdouble x = vadd_vd_vd_vd(s.x, s.y);

  x = vsel_vd_vm_vd_vd(vispinf_vm_vd(d), vcast_vd_d(INFINITY), x);
  x = vsel_vd_vm_vd_vd(vgt_vm_vd_vd(vcast_vd_d(0), d), vcast_vd_d(NAN), x);
  x = vsel_vd_vm_vd_vd(veq_vm_vd_vd(d, vcast_vd_d(0)), vcast_vd_d(-INFINITY), x);

  return x;
}

static INLINE vdouble expk(vdouble2 d) {
  vdouble u = vmul_vd_vd_vd(vadd_vd_vd_vd(d.x, d.y), vcast_vd_d(R_LN2));
  vint q = vrint_vi_vd(u);
  vdouble2 s, t;

  s = ddadd2_vd2_vd2_vd(d, vmul_vd_vd_vd(vcast_vd_vi(q), vcast_vd_d(-L2U)));
  s = ddadd2_vd2_vd2_vd(s, vmul_vd_vd_vd(vcast_vd_vi(q), vcast_vd_d(-L2L)));

  q = vrint_vi_vd(vmin_vd_vd_vd(vmax_vd_vd_vd(vcast_vd_d(-2047.49), u), vcast_vd_d(2047.49)));

  s = ddnormalize_vd2_vd2(s);

  u = vcast_vd_d(2.51069683420950419527139e-08);
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(2.76286166770270649116855e-07));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(2.75572496725023574143864e-06));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(2.48014973989819794114153e-05));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(0.000198412698809069797676111));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(0.0013888888939977128960529));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(0.00833333333332371417601081));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(0.0416666666665409524128449));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(0.166666666666666740681535));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(0.500000000000000999200722));

  t = ddadd_vd2_vd2_vd2(s, ddmul_vd2_vd2_vd(ddsqu_vd2_vd2(s), u));

  t = ddadd_vd2_vd_vd2(vcast_vd_d(1), t);
  u = vadd_vd_vd_vd(t.x, t.y);
  u = vldexp_vd_vd_vi(u, q);

  return u;
}

vdouble xpow(vdouble x, vdouble y) {
#if 1
  vmask yisint = veq_vm_vd_vd(vcast_vd_vi(vrint_vi_vd(y)), y);
  vmask yisodd = vand_vm_vm_vm(veq_vm_vi_vi(vand_vi_vi_vi(vrint_vi_vd(y), vcast_vi_i(1)), vcast_vi_i(1)), yisint);

  vdouble result = expk(ddmul_vd2_vd2_vd(logk(vabs_vd_vd(x)), y));

  //result = vsel_vd_vm_vd_vd(visnan_vm_vd(result), vcast_vd_d(INFINITY), result);

  result = vmul_vd_vd_vd(result,
		vsel_vd_vm_vd_vd(vgt_vm_vd_vd(x, vcast_vd_d(0)),
		     vcast_vd_d(1),
		     vsel_vd_vm_vd_vd(yisint,
			  vsel_vd_vm_vd_vd(yisodd,
			       vcast_vd_d(-1),
			       vcast_vd_d(1)),
			  vcast_vd_d(NAN))));

  vdouble efx = vreinterpret_vd_vm(vxor_vm_vm_vm(vreinterpret_vm_vd(vsub_vd_vd_vd(vabs_vd_vd(x), vcast_vd_d(1))), vsignbit_vm_vd(y)));

  result = vsel_vd_vm_vd_vd(visinf_vm_vd(y),
		vsel_vd_vm_vd_vd(vlt_vm_vd_vd(efx, vcast_vd_d(0)),
		     vcast_vd_d(0),
		     vsel_vd_vm_vd_vd(veq_vm_vd_vd(efx, vcast_vd_d(0)),
			  vcast_vd_d(1.0),
			  vcast_vd_d(INFINITY))),
		result);

  result = vsel_vd_vm_vd_vd(vor_vm_vm_vm(visinf_vm_vd(x), veq_vm_vd_vd(x, vcast_vd_d(0))),
		vmul_vd_vd_vd(vsel_vd_vm_vd_vd(yisodd, vsign_vd_vd(x), vcast_vd_d(1)),
		     vsel_vd_vm_vd_vd(vlt_vm_vd_vd(vsel_vd_vm_vd_vd(veq_vm_vd_vd(x, vcast_vd_d(0)), vneg_vd_vd(y), y), vcast_vd_d(0)),
			  vcast_vd_d(0),
			  vcast_vd_d(INFINITY))),
		result);

  result = vsel_vd_vm_vd_vd(vor_vm_vm_vm(visnan_vm_vd(x), visnan_vm_vd(y)), vcast_vd_d(NAN), result);

  result = vsel_vd_vm_vd_vd(vor_vm_vm_vm(veq_vm_vd_vd(y, vcast_vd_d(0)), veq_vm_vd_vd(x, vcast_vd_d(1))), vcast_vd_d(1), result);

  return result;
#else
  return expk(ddmul_vd2_vd2_vd(logk(x), y));
#endif
}

static INLINE vdouble2 expk2(vdouble2 d) {
  vdouble u = vmul_vd_vd_vd(vadd_vd_vd_vd(d.x, d.y), vcast_vd_d(R_LN2));
  vint q = vrint_vi_vd(u);
  vdouble2 s, t;

  s = ddadd2_vd2_vd2_vd(d, vmul_vd_vd_vd(vcast_vd_vi(q), vcast_vd_d(-L2U)));
  s = ddadd2_vd2_vd2_vd(s, vmul_vd_vd_vd(vcast_vd_vi(q), vcast_vd_d(-L2L)));

  q = vrint_vi_vd(vmin_vd_vd_vd(vmax_vd_vd_vd(vcast_vd_d(-2047.49), u), vcast_vd_d(2047.49)));

  s = ddnormalize_vd2_vd2(s);

  u = vcast_vd_d(2.51069683420950419527139e-08);
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(2.76286166770270649116855e-07));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(2.75572496725023574143864e-06));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(2.48014973989819794114153e-05));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(0.000198412698809069797676111));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(0.0013888888939977128960529));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(0.00833333333332371417601081));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(0.0416666666665409524128449));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(0.166666666666666740681535));
  u = vmla_vd_vd_vd_vd(u, s.x, vcast_vd_d(0.500000000000000999200722));

  t = ddadd_vd2_vd2_vd2(s, ddmul_vd2_vd2_vd(ddsqu_vd2_vd2(s), u));

  t = ddadd_vd2_vd_vd2(vcast_vd_d(1), t);

  return vcast_vd2_vd_vd(vldexp_vd_vd_vi(t.x, q), vldexp_vd_vd_vi(t.y, q));
}

vdouble xsinh(vdouble x) {
  vdouble y = vabs_vd_vd(x);
  vdouble2 d = expk2(vcast_vd2_vd_vd(y, vcast_vd_d(0)));
  d = ddadd2_vd2_vd2_vd2(d, dddiv_vd2_vd2_vd2(vcast_vd2_vd_vd(vcast_vd_d(-1), vcast_vd_d(0)), d));
  y = vmul_vd_vd_vd(vadd_vd_vd_vd(d.x, d.y), vcast_vd_d(0.5));

  y = vsel_vd_vm_vd_vd(vor_vm_vm_vm(visinf_vm_vd(x), visnan_vm_vd(y)), vcast_vd_d(INFINITY), y);
  y = vmulsign_vd_vd_vd(y, x);
  y = vsel_vd_vm_vd_vd(visnan_vm_vd(x), vcast_vd_d(NAN), y);

  return y;
}

vdouble xcosh(vdouble x) {
  vdouble2 d = expk2(vcast_vd2_vd_vd(x, vcast_vd_d(0)));
  d = ddadd2_vd2_vd2_vd2(d, dddiv_vd2_vd2_vd2(vcast_vd2_vd_vd(vcast_vd_d(1), vcast_vd_d(0)), d));
  vdouble y = vmul_vd_vd_vd(vadd_vd_vd_vd(d.x, d.y), vcast_vd_d(0.5));

  y = vsel_vd_vm_vd_vd(vor_vm_vm_vm(visinf_vm_vd(x), visnan_vm_vd(y)), vcast_vd_d(INFINITY), y);
  y = vsel_vd_vm_vd_vd(visnan_vm_vd(x), vcast_vd_d(NAN), y);

  return y;
}

vdouble xtanh(vdouble x) {
  vdouble y = vabs_vd_vd(x);
  vdouble2 d = expk2(vcast_vd2_vd_vd(y, vcast_vd_d(0)));
  vdouble2 e = dddiv_vd2_vd2_vd2(vcast_vd2_vd_vd(vcast_vd_d(1), vcast_vd_d(0)), d);
  d = dddiv_vd2_vd2_vd2(ddadd2_vd2_vd2_vd2(d, ddscale_vd2_vd2_vd(e, vcast_vd_d(-1))), ddadd2_vd2_vd2_vd2(d, e));
  y = vadd_vd_vd_vd(d.x, d.y);

  y = vsel_vd_vm_vd_vd(vor_vm_vm_vm(visinf_vm_vd(x), visnan_vm_vd(y)), vcast_vd_d(1.0), y);
  y = vmulsign_vd_vd_vd(y, x);
  y = vsel_vd_vm_vd_vd(visnan_vm_vd(x), vcast_vd_d(NAN), y);

  return y;
}

static INLINE vdouble2 logk2(vdouble2 d) {
  vdouble2 x, x2, m;
  vdouble t;
  vint e;

  d = ddnormalize_vd2_vd2(d);
  e = vilogbp1_vi_vd(vmul_vd_vd_vd(d.x, vcast_vd_d(0.7071)));
  m = ddscale_vd2_vd2_vd(d, vldexp_vd_vd_vi(vcast_vd_d(1), vsub_vi_vi_vi(vcast_vi_i(0), e)));

  x = dddiv_vd2_vd2_vd2(ddadd2_vd2_vd2_vd(m, vcast_vd_d(-1)), ddadd2_vd2_vd2_vd(m, vcast_vd_d(1)));
  x2 = ddsqu_vd2_vd2(x);
  x2 = ddnormalize_vd2_vd2(x2);

  t = vcast_vd_d(0.134601987501262130076155);
  t = vmla_vd_vd_vd_vd(t, x2.x, vcast_vd_d(0.132248509032032670243288));
  t = vmla_vd_vd_vd_vd(t, x2.x, vcast_vd_d(0.153883458318096079652524));
  t = vmla_vd_vd_vd_vd(t, x2.x, vcast_vd_d(0.181817427573705403298686));
  t = vmla_vd_vd_vd_vd(t, x2.x, vcast_vd_d(0.222222231326187414840781));
  t = vmla_vd_vd_vd_vd(t, x2.x, vcast_vd_d(0.285714285651261412873718));
  t = vmla_vd_vd_vd_vd(t, x2.x, vcast_vd_d(0.400000000000222439910458));
  t = vmla_vd_vd_vd_vd(t, x2.x, vcast_vd_d(0.666666666666666371239645));

  return ddadd2_vd2_vd2_vd2(ddmul_vd2_vd2_vd(vcast_vd2_vd_vd(vcast_vd_d(0.693147180559945286226764), vcast_vd_d(2.319046813846299558417771e-17)),
		       vcast_vd_vi(e)),
		ddadd2_vd2_vd2_vd2(ddscale_vd2_vd2_vd(x, vcast_vd_d(2)), ddmul_vd2_vd2_vd(ddmul_vd2_vd2_vd2(x2, x), t)));
}

vdouble xasinh(vdouble x) {
  vdouble y = vabs_vd_vd(x);
  vdouble2 d = logk2(ddadd2_vd2_vd2_vd(ddsqrt_vd2_vd2(ddadd2_vd2_vd2_vd(ddmul_vd2_vd_vd(y, y),  vcast_vd_d(1))), y));
  y = vadd_vd_vd_vd(d.x, d.y);

  y = vsel_vd_vm_vd_vd(vor_vm_vm_vm(visinf_vm_vd(x), visnan_vm_vd(y)), vcast_vd_d(INFINITY), y);
  y = vmulsign_vd_vd_vd(y, x);
  y = vsel_vd_vm_vd_vd(visnan_vm_vd(x), vcast_vd_d(NAN), y);

  return y;
}

vdouble xacosh(vdouble x) {
  vdouble2 d = logk2(ddadd2_vd2_vd2_vd(ddsqrt_vd2_vd2(ddadd2_vd2_vd2_vd(ddmul_vd2_vd_vd(x, x), vcast_vd_d(-1))), x));
  vdouble y = vadd_vd_vd_vd(d.x, d.y);

  y = vsel_vd_vm_vd_vd(vor_vm_vm_vm(visinf_vm_vd(x), visnan_vm_vd(y)), vcast_vd_d(INFINITY), y);
  y = vsel_vd_vm_vd_vd(veq_vm_vd_vd(x, vcast_vd_d(1.0)), vcast_vd_d(0.0), y);
  y = vsel_vd_vm_vd_vd(vlt_vm_vd_vd(x, vcast_vd_d(1.0)), vcast_vd_d(NAN), y);
  y = vsel_vd_vm_vd_vd(visnan_vm_vd(x), vcast_vd_d(NAN), y);

  return y;
}

vdouble xatanh(vdouble x) {
  vdouble y = vabs_vd_vd(x);
  vdouble2 d = logk2(dddiv_vd2_vd2_vd2(ddadd2_vd2_vd_vd(vcast_vd_d(1), y), ddadd2_vd2_vd_vd(vcast_vd_d(1), vneg_vd_vd(y))));
  y = vsel_vd_vm_vd_vd(vgt_vm_vd_vd(y, vcast_vd_d(1.0)), vcast_vd_d(NAN), vsel_vd_vm_vd_vd(veq_vm_vd_vd(y, vcast_vd_d(1.0)), vcast_vd_d(INFINITY), vmul_vd_vd_vd(vadd_vd_vd_vd(d.x, d.y), vcast_vd_d(0.5))));

  y = vsel_vd_vm_vd_vd(vor_vm_vm_vm(visinf_vm_vd(x), visnan_vm_vd(y)), vcast_vd_d(NAN), y);
  y = vmulsign_vd_vd_vd(y, x);
  y = vsel_vd_vm_vd_vd(visnan_vm_vd(x), vcast_vd_d(NAN), y);

  return y;
}

vdouble xcbrt(vdouble d) {
  vdouble x, y, q = vcast_vd_d(1.0);
  vint e, qu, re;
  vdouble t;

  e = vilogbp1_vi_vd(vabs_vd_vd(d));
  d = vldexp_vd_vd_vi(d, vsub_vi_vi_vi(vcast_vi_i(0), e));

  t = vadd_vd_vd_vd(vcast_vd_vi(e), vcast_vd_d(6144));
  qu = vtruncate_vi_vd(vdiv_vd_vd_vd(t, vcast_vd_d(3)));
  re = vtruncate_vi_vd(vsub_vd_vd_vd(t, vmul_vd_vd_vd(vcast_vd_vi(qu), vcast_vd_d(3))));

  q = vsel_vd_vm_vd_vd(veq_vm_vi_vi(re, vcast_vi_i(1)), vcast_vd_d(1.2599210498948731647672106), q);
  q = vsel_vd_vm_vd_vd(veq_vm_vi_vi(re, vcast_vi_i(2)), vcast_vd_d(1.5874010519681994747517056), q);
  q = vldexp_vd_vd_vi(q, vsub_vi_vi_vi(qu, vcast_vi_i(2048)));

  q = vmulsign_vd_vd_vd(q, d);

  d = vabs_vd_vd(d);

  x = vcast_vd_d(-0.640245898480692909870982);
  x = vmla_vd_vd_vd_vd(x, d, vcast_vd_d(2.96155103020039511818595));
  x = vmla_vd_vd_vd_vd(x, d, vcast_vd_d(-5.73353060922947843636166));
  x = vmla_vd_vd_vd_vd(x, d, vcast_vd_d(6.03990368989458747961407));
  x = vmla_vd_vd_vd_vd(x, d, vcast_vd_d(-3.85841935510444988821632));
  x = vmla_vd_vd_vd_vd(x, d, vcast_vd_d(2.2307275302496609725722));

  y = vmul_vd_vd_vd(x, x); y = vmul_vd_vd_vd(y, y); x = vsub_vd_vd_vd(x, vmul_vd_vd_vd(vmlapn_vd_vd_vd_vd(d, y, x), vcast_vd_d(1.0 / 3.0)));
  y = vmul_vd_vd_vd(vmul_vd_vd_vd(d, x), x);
  y = vmul_vd_vd_vd(vsub_vd_vd_vd(y, vmul_vd_vd_vd(vmul_vd_vd_vd(vcast_vd_d(2.0 / 3.0), y), vmla_vd_vd_vd_vd(y, x, vcast_vd_d(-1.0)))), q);

  return y;
}

vdouble xcbrt_u1(vdouble d) {
  vdouble x, y, z, t;
  vdouble2 q2 = vcast_vd2_d_d(1, 0), u, v;
  vint e, qu, re;

  e = vilogbp1_vi_vd(vabs_vd_vd(d));
  d = vldexp_vd_vd_vi(d, vsub_vi_vi_vi(vcast_vi_i(0), e));

  t = vadd_vd_vd_vd(vcast_vd_vi(e), vcast_vd_d(6144));
  qu = vtruncate_vi_vd(vdiv_vd_vd_vd(t, vcast_vd_d(3)));
  re = vtruncate_vi_vd(vsub_vd_vd_vd(t, vmul_vd_vd_vd(vcast_vd_vi(qu), vcast_vd_d(3))));

  q2 = vsel_vd2_vm_vd2_vd2(veq_vm_vi_vi(re, vcast_vi_i(1)), vcast_vd2_d_d(1.2599210498948731907, -2.5899333753005069177e-17), q2);
  q2 = vsel_vd2_vm_vd2_vd2(veq_vm_vi_vi(re, vcast_vi_i(2)), vcast_vd2_d_d(1.5874010519681995834, -1.0869008194197822986e-16), q2);

  q2.x = vmulsign_vd_vd_vd(q2.x, d); q2.y = vmulsign_vd_vd_vd(q2.y, d);
  d = vabs_vd_vd(d);

  x = vcast_vd_d(-0.640245898480692909870982);
  x = vmla_vd_vd_vd_vd(x, d, vcast_vd_d(2.96155103020039511818595));
  x = vmla_vd_vd_vd_vd(x, d, vcast_vd_d(-5.73353060922947843636166));
  x = vmla_vd_vd_vd_vd(x, d, vcast_vd_d(6.03990368989458747961407));
  x = vmla_vd_vd_vd_vd(x, d, vcast_vd_d(-3.85841935510444988821632));
  x = vmla_vd_vd_vd_vd(x, d, vcast_vd_d(2.2307275302496609725722));

  y = vmul_vd_vd_vd(x, x); y = vmul_vd_vd_vd(y, y); x = vsub_vd_vd_vd(x, vmul_vd_vd_vd(vmlapn_vd_vd_vd_vd(d, y, x), vcast_vd_d(1.0 / 3.0)));

  z = x;

  u = ddmul_vd2_vd_vd(x, x);
  u = ddmul_vd2_vd2_vd2(u, u);
  u = ddmul_vd2_vd2_vd(u, d);
  u = ddadd2_vd2_vd2_vd(u, vneg_vd_vd(x));
  y = vadd_vd_vd_vd(u.x, u.y);

  y = vmul_vd_vd_vd(vmul_vd_vd_vd(vcast_vd_d(-2.0 / 3.0), y), z);
  v = ddadd2_vd2_vd2_vd(ddmul_vd2_vd_vd(z, z), y);
  v = ddmul_vd2_vd2_vd(v, d);
  v = ddmul_vd2_vd2_vd2(v, q2);
  z = vldexp_vd_vd_vi(vadd_vd_vd_vd(v.x, v.y), vsub_vi_vi_vi(qu, vcast_vi_i(2048)));

  z = vsel_vd_vm_vd_vd(visinf_vm_vd(d), vmulsign_vd_vd_vd(vcast_vd_d(INFINITY), q2.x), z);
  z = vsel_vd_vm_vd_vd(veq_vm_vd_vd(d, vcast_vd_d(0)), vmulsign_vd_vd_vd(vcast_vd_d(0), q2.x), z);

  return z;
}

vdouble xexp2(vdouble a) {
  vdouble u = expk(ddmul_vd2_vd2_vd(vcast_vd2_vd_vd(vcast_vd_d(0.69314718055994528623), vcast_vd_d(2.3190468138462995584e-17)), a));
  u = vsel_vd_vm_vd_vd(vispinf_vm_vd(a), vcast_vd_d(INFINITY), u);
  u = vsel_vd_vm_vd_vd(visminf_vm_vd(a), vcast_vd_d(0), u);
  return u;
}

vdouble xexp10(vdouble a) {
  vdouble u = expk(ddmul_vd2_vd2_vd(vcast_vd2_vd_vd(vcast_vd_d(2.3025850929940459011), vcast_vd_d(-2.1707562233822493508e-16)), a));
  u = vsel_vd_vm_vd_vd(vispinf_vm_vd(a), vcast_vd_d(INFINITY), u);
  u = vsel_vd_vm_vd_vd(visminf_vm_vd(a), vcast_vd_d(0), u);
  return u;
}

vdouble xexpm1(vdouble a) {
  vdouble2 d = ddadd2_vd2_vd2_vd(expk2(vcast_vd2_vd_vd(a, vcast_vd_d(0))), vcast_vd_d(-1.0));
  vdouble x = vadd_vd_vd_vd(d.x, d.y);
  x = vsel_vd_vm_vd_vd(vispinf_vm_vd(a), vcast_vd_d(INFINITY), x);
  x = vsel_vd_vm_vd_vd(visminf_vm_vd(a), vcast_vd_d(-1), x);
  return x;
}

vdouble xlog10(vdouble a) {
  vdouble2 d = ddmul_vd2_vd2_vd2(logk(a), vcast_vd2_vd_vd(vcast_vd_d(0.43429448190325176116), vcast_vd_d(6.6494347733425473126e-17)));
  vdouble x = vadd_vd_vd_vd(d.x, d.y);

  x = vsel_vd_vm_vd_vd(vispinf_vm_vd(a), vcast_vd_d(INFINITY), x);
  x = vsel_vd_vm_vd_vd(vgt_vm_vd_vd(vcast_vd_d(0), a), vcast_vd_d(NAN), x);
  x = vsel_vd_vm_vd_vd(veq_vm_vd_vd(a, vcast_vd_d(0)), vcast_vd_d(-INFINITY), x);

  return x;
}

vdouble xlog1p(vdouble a) {
  vdouble2 d = logk2(ddadd2_vd2_vd_vd(a, vcast_vd_d(1)));
  vdouble x = vadd_vd_vd_vd(d.x, d.y);

  x = vsel_vd_vm_vd_vd(vispinf_vm_vd(a), vcast_vd_d(INFINITY), x);
  x = vsel_vd_vm_vd_vd(vgt_vm_vd_vd(vcast_vd_d(-1), a), vcast_vd_d(NAN), x);
  x = vsel_vd_vm_vd_vd(veq_vm_vd_vd(a, vcast_vd_d(-1)), vcast_vd_d(-INFINITY), x);

  return x;
}

//

static INLINE vfloat vsel_vf_vm_vf_vf(vmask mask, vfloat x, vfloat y) {
  return (vfloat)vor_vm_vm_vm(vand_vm_vm_vm(mask, (vmask)x), vandnot_vm_vm_vm(mask, (vmask)y));
}

static INLINE vint2 vsel_vi2_vf_vf_vi2_vi2(vfloat f0, vfloat f1, vint2 x, vint2 y) {
  vint2 m2 = vcast_vi2_vm(vlt_vm_vf_vf(f0, f1));
  return vor_vi2_vi2_vi2(vand_vi2_vi2_vi2(m2, x), vandnot_vi2_vi2_vi2(m2, y));
}

static INLINE vmask vsignbit_vm_vf(vfloat f) {
  return vand_vm_vm_vm((vmask)f, (vmask)vcast_vf_f(-0.0f));
}

static INLINE vfloat vmulsign_vf_vf_vf(vfloat x, vfloat y) {
  return (vfloat)vxor_vm_vm_vm((vmask)x, vsignbit_vm_vf(y));
}

static INLINE vfloat vsign_vf_vf(vfloat f) {
  return (vfloat)vor_vm_vm_vm((vmask)vcast_vf_f(1.0f), vand_vm_vm_vm((vmask)vcast_vf_f(-0.0f), (vmask)f));
}

static INLINE vmask visinf_vm_vf(vfloat d) { return veq_vm_vf_vf(vabs_vf_vf(d), vcast_vf_f(INFINITYf)); }
static INLINE vmask vispinf_vm_vf(vfloat d) { return veq_vm_vf_vf(d, vcast_vf_f(INFINITYf)); }
static INLINE vmask visminf_vm_vf(vfloat d) { return veq_vm_vf_vf(d, vcast_vf_f(-INFINITYf)); }
static INLINE vmask visnan_vm_vf(vfloat d) { return vneq_vm_vf_vf(d, d); }
static INLINE vfloat visinf2_vf_vf_vm(vfloat d, vfloat m) { return (vfloat)vand_vm_vm_vm(visinf_vm_vf(d), vor_vm_vm_vm(vsignbit_vm_vf(d), (vmask)m)); }
static INLINE vfloat visinff(vfloat d) { return visinf2_vf_vf_vm(d, vcast_vf_f(1.0f)); }

static INLINE vint2 vilogbp1_vi2_vf(vfloat d) {
  vmask m = vlt_vm_vf_vf(d, vcast_vf_f(5.421010862427522E-20f));
  d = vsel_vf_vm_vf_vf(m, vmul_vf_vf_vf(vcast_vf_f(1.8446744073709552E19f), d), d);
  vint2 q = vand_vi2_vi2_vi2(vsrl_vi2_vi2_i(vcast_vi2_vm(vreinterpret_vm_vf(d)), 23), vcast_vi2_i(0xff));
  q = vsub_vi2_vi2_vi2(q, vsel_vi2_vm_vi2_vi2(m, vcast_vi2_i(64 + 0x7e), vcast_vi2_i(0x7e)));
  return q;
}

static INLINE vfloat vldexp_vf_vf_vi2(vfloat x, vint2 q) {
  vfloat u;
  vint2 m = vsra_vi2_vi2_i(q, 31);
  m = vsll_vi2_vi2_i(vsub_vi2_vi2_vi2(vsra_vi2_vi2_i(vadd_vi2_vi2_vi2(m, q), 6), m), 4);
  q = vsub_vi2_vi2_vi2(q, vsll_vi2_vi2_i(m, 2));
  m = vadd_vi2_vi2_vi2(m, vcast_vi2_i(0x7f));
  m = vand_vi2_vi2_vi2(vgt_vi2_vi2_vi2(m, vcast_vi2_i(0)), m);
  vint2 n = vgt_vi2_vi2_vi2(m, vcast_vi2_i(0xff));
  m = vor_vi2_vi2_vi2(vandnot_vi2_vi2_vi2(n, m), vand_vi2_vi2_vi2(n, vcast_vi2_i(0xff)));
  u = vreinterpret_vf_vm(vcast_vm_vi2(vsll_vi2_vi2_i(m, 23)));
  x = vmul_vf_vf_vf(vmul_vf_vf_vf(vmul_vf_vf_vf(vmul_vf_vf_vf(x, u), u), u), u);
  u = vreinterpret_vf_vm(vcast_vm_vi2(vsll_vi2_vi2_i(vadd_vi2_vi2_vi2(q, vcast_vi2_i(0x7f)), 23)));
  return vmul_vf_vf_vf(x, u);
}

vfloat xldexpf(vfloat x, vint2 q) { return vldexp_vf_vf_vi2(x, q); }

vfloat xsinf(vfloat d) {
  vint2 q;
  vfloat u, s;

  q = vrint_vi2_vf(vmul_vf_vf_vf(d, vcast_vf_f((float)M_1_PI)));

  u = vcast_vf_vi2(q);
  d = vmla_vf_vf_vf_vf(u, vcast_vf_f(-PI4_Af*4), d);
  d = vmla_vf_vf_vf_vf(u, vcast_vf_f(-PI4_Bf*4), d);
  d = vmla_vf_vf_vf_vf(u, vcast_vf_f(-PI4_Cf*4), d);
  d = vmla_vf_vf_vf_vf(u, vcast_vf_f(-PI4_Df*4), d);

  s = vmul_vf_vf_vf(d, d);

  d = vsel_vf_vm_vf_vf(veq_vm_vi2_vi2(vand_vi2_vi2_vi2(q, vcast_vi2_i(1)), vcast_vi2_i(1)), vneg_vf_vf(d), d);

  u = vcast_vf_f(2.6083159809786593541503e-06f);
  u = vmla_vf_vf_vf_vf(u, s, vcast_vf_f(-0.0001981069071916863322258f));
  u = vmla_vf_vf_vf_vf(u, s, vcast_vf_f(0.00833307858556509017944336f));
  u = vmla_vf_vf_vf_vf(u, s, vcast_vf_f(-0.166666597127914428710938f));

  u = vmla_vf_vf_vf_vf(s, vmul_vf_vf_vf(u, d), d);

  u = vsel_vf_vm_vf_vf(visinf_vm_vf(d), vcast_vf_f(NAN), u);

  return u;
}

vfloat xcosf(vfloat d) {
  vint2 q;
  vfloat u, s;

  q = vrint_vi2_vf(vsub_vf_vf_vf(vmul_vf_vf_vf(d, vcast_vf_f((float)M_1_PI)), vcast_vf_f(0.5f)));
  q = vadd_vi2_vi2_vi2(vadd_vi2_vi2_vi2(q, q), vcast_vi2_i(1));

  u = vcast_vf_vi2(q);
  d = vmla_vf_vf_vf_vf(u, vcast_vf_f(-PI4_Af*2), d);
  d = vmla_vf_vf_vf_vf(u, vcast_vf_f(-PI4_Bf*2), d);
  d = vmla_vf_vf_vf_vf(u, vcast_vf_f(-PI4_Cf*2), d);
  d = vmla_vf_vf_vf_vf(u, vcast_vf_f(-PI4_Df*2), d);

  s = vmul_vf_vf_vf(d, d);

  d = vsel_vf_vm_vf_vf(veq_vm_vi2_vi2(vand_vi2_vi2_vi2(q, vcast_vi2_i(2)), vcast_vi2_i(2)), d, vneg_vf_vf(d));

  u = vcast_vf_f(2.6083159809786593541503e-06f);
  u = vmla_vf_vf_vf_vf(u, s, vcast_vf_f(-0.0001981069071916863322258f));
  u = vmla_vf_vf_vf_vf(u, s, vcast_vf_f(0.00833307858556509017944336f));
  u = vmla_vf_vf_vf_vf(u, s, vcast_vf_f(-0.166666597127914428710938f));

  u = vmla_vf_vf_vf_vf(s, vmul_vf_vf_vf(u, d), d);

  u = vsel_vf_vm_vf_vf(visinf_vm_vf(d), vcast_vf_f(NAN), u);

  return u;
}

vfloat2 xsincosf(vfloat d) {
  vint2 q;
  vmask m;
  vfloat u, s, t, rx, ry;
  vfloat2 r;

  q = vrint_vi2_vf(vmul_vf_vf_vf(d, vcast_vf_f((float)M_2_PI)));

  s = d;

  u = vcast_vf_vi2(q);
  s = vmla_vf_vf_vf_vf(u, vcast_vf_f(-PI4_Af*2), s);
  s = vmla_vf_vf_vf_vf(u, vcast_vf_f(-PI4_Bf*2), s);
  s = vmla_vf_vf_vf_vf(u, vcast_vf_f(-PI4_Cf*2), s);
  s = vmla_vf_vf_vf_vf(u, vcast_vf_f(-PI4_Df*2), s);

  t = s;

  s = vmul_vf_vf_vf(s, s);

  u = vcast_vf_f(-0.000195169282960705459117889f);
  u = vmla_vf_vf_vf_vf(u, s, vcast_vf_f(0.00833215750753879547119141f));
  u = vmla_vf_vf_vf_vf(u, s, vcast_vf_f(-0.166666537523269653320312f));
  u = vmul_vf_vf_vf(vmul_vf_vf_vf(u, s), t);

  rx = vadd_vf_vf_vf(t, u);

  u = vcast_vf_f(-2.71811842367242206819355e-07f);
  u = vmla_vf_vf_vf_vf(u, s, vcast_vf_f(2.47990446951007470488548e-05f));
  u = vmla_vf_vf_vf_vf(u, s, vcast_vf_f(-0.00138888787478208541870117f));
  u = vmla_vf_vf_vf_vf(u, s, vcast_vf_f(0.0416666641831398010253906f));
  u = vmla_vf_vf_vf_vf(u, s, vcast_vf_f(-0.5));

  ry = vmla_vf_vf_vf_vf(s, u, vcast_vf_f(1));

  m = veq_vm_vi2_vi2(vand_vi2_vi2_vi2(q, vcast_vi2_i(1)), vcast_vi2_i(0));
  r.x = vsel_vf_vm_vf_vf(m, rx, ry);
  r.y = vsel_vf_vm_vf_vf(m, ry, rx);

  m = veq_vm_vi2_vi2(vand_vi2_vi2_vi2(q, vcast_vi2_i(2)), vcast_vi2_i(2));
  r.x = vreinterpret_vf_vm(vxor_vm_vm_vm(vand_vm_vm_vm(m, vreinterpret_vm_vf(vcast_vf_f(-0.0))), vreinterpret_vm_vf(r.x)));

  m = veq_vm_vi2_vi2(vand_vi2_vi2_vi2(vadd_vi2_vi2_vi2(q, vcast_vi2_i(1)), vcast_vi2_i(2)), vcast_vi2_i(2));
  r.y = vreinterpret_vf_vm(vxor_vm_vm_vm(vand_vm_vm_vm(m, vreinterpret_vm_vf(vcast_vf_f(-0.0))), vreinterpret_vm_vf(r.y)));

  m = visinf_vm_vf(d);
  r.x = vsel_vf_vm_vf_vf(m, vcast_vf_f(NAN), r.x);
  r.y = vsel_vf_vm_vf_vf(m, vcast_vf_f(NAN), r.y);

  return r;
}

vfloat xtanf(vfloat d) {
  vint2 q;
  vmask m;
  vfloat u, s, x;

  q = vrint_vi2_vf(vmul_vf_vf_vf(d, vcast_vf_f((float)(2 * M_1_PI))));

  x = d;

  u = vcast_vf_vi2(q);
  x = vmla_vf_vf_vf_vf(u, vcast_vf_f(-PI4_Af*2), x);
  x = vmla_vf_vf_vf_vf(u, vcast_vf_f(-PI4_Bf*2), x);
  x = vmla_vf_vf_vf_vf(u, vcast_vf_f(-PI4_Cf*2), x);
  x = vmla_vf_vf_vf_vf(u, vcast_vf_f(-PI4_Df*2), x);

  s = vmul_vf_vf_vf(x, x);

  m = veq_vm_vi2_vi2(vand_vi2_vi2_vi2(q, vcast_vi2_i(1)), vcast_vi2_i(1));
  x = vsel_vf_vm_vf_vf(m, vneg_vf_vf(x), x);

  u = vcast_vf_f(0.00927245803177356719970703f);
  u = vmla_vf_vf_vf_vf(u, s, vcast_vf_f(0.00331984995864331722259521f));
  u = vmla_vf_vf_vf_vf(u, s, vcast_vf_f(0.0242998078465461730957031f));
  u = vmla_vf_vf_vf_vf(u, s, vcast_vf_f(0.0534495301544666290283203f));
  u = vmla_vf_vf_vf_vf(u, s, vcast_vf_f(0.133383005857467651367188f));
  u = vmla_vf_vf_vf_vf(u, s, vcast_vf_f(0.333331853151321411132812f));

  u = vmla_vf_vf_vf_vf(s, vmul_vf_vf_vf(u, x), x);

  u = vsel_vf_vm_vf_vf(m, vrec_vf_vf(u), u);

  u = vsel_vf_vm_vf_vf(visinf_vm_vf(d), vcast_vf_f(NANf), u);

  return u;
}

vfloat xatanf(vfloat s) {
  vfloat t, u;
  vint2 q;

  q = vsel_vi2_vf_vf_vi2_vi2(s, vcast_vf_f(0.0f), vcast_vi2_i(2), vcast_vi2_i(0));
  s = vabs_vf_vf(s);

  q = vsel_vi2_vf_vf_vi2_vi2(vcast_vf_f(1.0f), s, vadd_vi2_vi2_vi2(q, vcast_vi2_i(1)), q);
  s = vsel_vf_vm_vf_vf(vlt_vm_vf_vf(vcast_vf_f(1.0f), s), vdiv_vf_vf_vf(vcast_vf_f(1.0f), s), s);

  t = vmul_vf_vf_vf(s, s);

  u = vcast_vf_f(0.00282363896258175373077393f);
  u = vmla_vf_vf_vf_vf(u, t, vcast_vf_f(-0.0159569028764963150024414f));
  u = vmla_vf_vf_vf_vf(u, t, vcast_vf_f(0.0425049886107444763183594f));
  u = vmla_vf_vf_vf_vf(u, t, vcast_vf_f(-0.0748900920152664184570312f));
  u = vmla_vf_vf_vf_vf(u, t, vcast_vf_f(0.106347933411598205566406f));
  u = vmla_vf_vf_vf_vf(u, t, vcast_vf_f(-0.142027363181114196777344f));
  u = vmla_vf_vf_vf_vf(u, t, vcast_vf_f(0.199926957488059997558594f));
  u = vmla_vf_vf_vf_vf(u, t, vcast_vf_f(-0.333331018686294555664062f));

  t = vmla_vf_vf_vf_vf(s, vmul_vf_vf_vf(t, u), s);

  t = vsel_vf_vm_vf_vf(veq_vm_vi2_vi2(vand_vi2_vi2_vi2(q, vcast_vi2_i(1)), vcast_vi2_i(1)), vsub_vf_vf_vf(vcast_vf_f((float)(M_PI/2)), t), t);
  t = vsel_vf_vm_vf_vf(veq_vm_vi2_vi2(vand_vi2_vi2_vi2(q, vcast_vi2_i(2)), vcast_vi2_i(2)), vneg_vf_vf(t), t);

  return t;
}

static INLINE vfloat atan2kf(vfloat y, vfloat x) {
  vfloat s, t, u;
  vint2 q;
  vmask p;

  q = vsel_vi2_vf_vf_vi2_vi2(x, vcast_vf_f(0.0f), vcast_vi2_i(-2), vcast_vi2_i(0));
  x = vabs_vf_vf(x);

  q = vsel_vi2_vf_vf_vi2_vi2(x, y, vadd_vi2_vi2_vi2(q, vcast_vi2_i(1)), q);
  p = vlt_vm_vf_vf(x, y);
  s = vsel_vf_vm_vf_vf(p, vneg_vf_vf(x), y);
  t = vmax_vf_vf_vf(x, y);

  s = vdiv_vf_vf_vf(s, t);
  t = vmul_vf_vf_vf(s, s);

  u = vcast_vf_f(0.00282363896258175373077393f);
  u = vmla_vf_vf_vf_vf(u, t, vcast_vf_f(-0.0159569028764963150024414f));
  u = vmla_vf_vf_vf_vf(u, t, vcast_vf_f(0.0425049886107444763183594f));
  u = vmla_vf_vf_vf_vf(u, t, vcast_vf_f(-0.0748900920152664184570312f));
  u = vmla_vf_vf_vf_vf(u, t, vcast_vf_f(0.106347933411598205566406f));
  u = vmla_vf_vf_vf_vf(u, t, vcast_vf_f(-0.142027363181114196777344f));
  u = vmla_vf_vf_vf_vf(u, t, vcast_vf_f(0.199926957488059997558594f));
  u = vmla_vf_vf_vf_vf(u, t, vcast_vf_f(-0.333331018686294555664062f));

  t = vmla_vf_vf_vf_vf(s, vmul_vf_vf_vf(t, u), s);
  t = vmla_vf_vf_vf_vf(vcast_vf_vi2(q), vcast_vf_f((float)(M_PI/2)), t);

  return t;
}

vfloat xatan2f(vfloat y, vfloat x) {
  vfloat r = atan2kf(vabs_vf_vf(y), x);

  r = vmulsign_vf_vf_vf(r, x);
  r = vsel_vf_vm_vf_vf(vor_vm_vm_vm(visinf_vm_vf(x), veq_vm_vf_vf(x, vcast_vf_f(0.0f))), vsub_vf_vf_vf(vcast_vf_f((float)(M_PI/2)), visinf2_vf_vf_vm(x, vmulsign_vf_vf_vf(vcast_vf_f((float)(M_PI/2)), x))), r);
  r = vsel_vf_vm_vf_vf(visinf_vm_vf(y), vsub_vf_vf_vf(vcast_vf_f((float)(M_PI/2)), visinf2_vf_vf_vm(x, vmulsign_vf_vf_vf(vcast_vf_f((float)(M_PI/4)), x))), r);
  r = vsel_vf_vm_vf_vf(veq_vm_vf_vf(y, vcast_vf_f(0.0f)), vsel_vf_vm_vf_vf(veq_vm_vf_vf(vsign_vf_vf(x), vcast_vf_f(-1.0f)), vcast_vf_f((float)M_PI), vcast_vf_f(0.0f)), r);

  return vsel_vf_vm_vf_vf(vor_vm_vm_vm(visnan_vm_vf(x), visnan_vm_vf(y)), vcast_vf_f(NANf), vmulsign_vf_vf_vf(r, y));
}

vfloat xasinf(vfloat d) {
  vfloat x, y;
  x = vadd_vf_vf_vf(vcast_vf_f(1.0f), d);
  y = vsub_vf_vf_vf(vcast_vf_f(1.0f), d);
  x = vmul_vf_vf_vf(x, y);
  x = vsqrt_vf_vf(x);
  x = vsel_vf_vm_vf_vf(visnan_vm_vf(x), vcast_vf_f(NANf), atan2kf(vabs_vf_vf(d), x));
  return vmulsign_vf_vf_vf(x, d);
}

vfloat xacosf(vfloat d) {
  vfloat x, y;
  x = vadd_vf_vf_vf(vcast_vf_f(1.0f), d);
  y = vsub_vf_vf_vf(vcast_vf_f(1.0f), d);
  x = vmul_vf_vf_vf(x, y);
  x = vsqrt_vf_vf(x);
  x = vmulsign_vf_vf_vf(atan2kf(x, vabs_vf_vf(d)), d);
  y = (vfloat)vand_vm_vm_vm(vlt_vm_vf_vf(d, vcast_vf_f(0.0f)), (vmask)vcast_vf_f((float)M_PI));
  x = vadd_vf_vf_vf(x, y);
  return x;
}

vfloat xlogf(vfloat d) {
  vfloat x, x2, t, m;
  vint2 e;

  e = vilogbp1_vi2_vf(vmul_vf_vf_vf(d, vcast_vf_f(0.7071f)));
  m = vldexp_vf_vf_vi2(d, vsub_vi2_vi2_vi2(vcast_vi2_i(0), e));

  x = vdiv_vf_vf_vf(vadd_vf_vf_vf(vcast_vf_f(-1.0f), m), vadd_vf_vf_vf(vcast_vf_f(1.0f), m));
  x2 = vmul_vf_vf_vf(x, x);

  t = vcast_vf_f(0.2371599674224853515625f);
  t = vmla_vf_vf_vf_vf(t, x2, vcast_vf_f(0.285279005765914916992188f));
  t = vmla_vf_vf_vf_vf(t, x2, vcast_vf_f(0.400005519390106201171875f));
  t = vmla_vf_vf_vf_vf(t, x2, vcast_vf_f(0.666666567325592041015625f));
  t = vmla_vf_vf_vf_vf(t, x2, vcast_vf_f(2.0f));

  x = vmla_vf_vf_vf_vf(x, t, vmul_vf_vf_vf(vcast_vf_f(0.693147180559945286226764f), vcast_vf_vi2(e)));

  x = vsel_vf_vm_vf_vf(vispinf_vm_vf(d), vcast_vf_f(INFINITYf), x);
  x = vsel_vf_vm_vf_vf(vgt_vm_vf_vf(vcast_vf_f(0), d), vcast_vf_f(NANf), x);
  x = vsel_vf_vm_vf_vf(veq_vm_vf_vf(d, vcast_vf_f(0)), vcast_vf_f(-INFINITYf), x);

  return x;
}

vfloat xexpf(vfloat d) {
  vint2 q = vrint_vi2_vf(vmul_vf_vf_vf(d, vcast_vf_f(R_LN2f)));
  vfloat s, u;

  s = vmla_vf_vf_vf_vf(vcast_vf_vi2(q), vcast_vf_f(-L2Uf), d);
  s = vmla_vf_vf_vf_vf(vcast_vf_vi2(q), vcast_vf_f(-L2Lf), s);

  u = vcast_vf_f(0.00136324646882712841033936f);
  u = vmla_vf_vf_vf_vf(u, s, vcast_vf_f(0.00836596917361021041870117f));
  u = vmla_vf_vf_vf_vf(u, s, vcast_vf_f(0.0416710823774337768554688f));
  u = vmla_vf_vf_vf_vf(u, s, vcast_vf_f(0.166665524244308471679688f));
  u = vmla_vf_vf_vf_vf(u, s, vcast_vf_f(0.499999850988388061523438f));

  u = vadd_vf_vf_vf(vcast_vf_f(1.0f), vmla_vf_vf_vf_vf(vmul_vf_vf_vf(s, s), u, s));

  u = vldexp_vf_vf_vi2(u, q);

  u = vsel_vf_vm_vf_vf(visminf_vm_vf(d), vcast_vf_f(0.0f), u);

  return u;
}

vfloat xcbrtf(vfloat d) {
  vfloat x, y, q = vcast_vf_f(1.0), t;
  vint2 e, qu, re;

  e = vilogbp1_vi2_vf(vabs_vf_vf(d));
  d = vldexp_vf_vf_vi2(d, vsub_vi2_vi2_vi2(vcast_vi2_i(0), e));

  t = vadd_vf_vf_vf(vcast_vf_vi2(e), vcast_vf_f(6144));
  qu = vtruncate_vi2_vf(vdiv_vf_vf_vf(t, vcast_vf_f(3)));
  re = vtruncate_vi2_vf(vsub_vf_vf_vf(t, vmul_vf_vf_vf(vcast_vf_vi2(qu), vcast_vf_f(3))));

  q = vsel_vf_vm_vf_vf(veq_vm_vi2_vi2(re, vcast_vi2_i(1)), vcast_vf_f(1.2599210498948731647672106f), q);
  q = vsel_vf_vm_vf_vf(veq_vm_vi2_vi2(re, vcast_vi2_i(2)), vcast_vf_f(1.5874010519681994747517056f), q);
  q = vldexp_vf_vf_vi2(q, vsub_vi2_vi2_vi2(qu, vcast_vi2_i(2048)));

  q = vmulsign_vf_vf_vf(q, d);
  d = vabs_vf_vf(d);

  x = vcast_vf_f(-0.601564466953277587890625f);
  x = vmla_vf_vf_vf_vf(x, d, vcast_vf_f(2.8208892345428466796875f));
  x = vmla_vf_vf_vf_vf(x, d, vcast_vf_f(-5.532182216644287109375f));
  x = vmla_vf_vf_vf_vf(x, d, vcast_vf_f(5.898262500762939453125f));
  x = vmla_vf_vf_vf_vf(x, d, vcast_vf_f(-3.8095417022705078125f));
  x = vmla_vf_vf_vf_vf(x, d, vcast_vf_f(2.2241256237030029296875f));

  y = vmul_vf_vf_vf(vmul_vf_vf_vf(d, x), x);
  y = vmul_vf_vf_vf(vsub_vf_vf_vf(y, vmul_vf_vf_vf(vmul_vf_vf_vf(vcast_vf_f(2.0f / 3.0f), y), vmla_vf_vf_vf_vf(y, x, vcast_vf_f(-1.0f)))), q);

  return y;
}

static INLINE vfloat2 logkf(vfloat d) {
  vfloat2 x, x2;
  vfloat t, m;
  vint2 e;

  e = vilogbp1_vi2_vf(vmul_vf_vf_vf(d, vcast_vf_f(0.7071f)));
  m = vldexp_vf_vf_vi2(d, vsub_vi2_vi2_vi2(vcast_vi2_i(0), e));

  x = dfdiv_vf2_vf2_vf2(dfadd2_vf2_vf_vf(vcast_vf_f(-1), m), dfadd2_vf2_vf_vf(vcast_vf_f(1), m));
  x2 = dfsqu_vf2_vf2(x);
  x2 = dfnormalize_vf2_vf2(x2);

  t = vcast_vf_f(0.2371599674224853515625f);
  t = vmla_vf_vf_vf_vf(t, x2.x, vcast_vf_f(0.285279005765914916992188f));
  t = vmla_vf_vf_vf_vf(t, x2.x, vcast_vf_f(0.400005519390106201171875f));
  t = vmla_vf_vf_vf_vf(t, x2.x, vcast_vf_f(0.666666567325592041015625f));

  return dfadd2_vf2_vf2_vf2(dfmul_vf2_vf2_vf(vcast_vf2_vf_vf(vcast_vf_f(0.69314718246459960938f), vcast_vf_f(-1.904654323148236017e-09f)),
		       vcast_vf_vi2(e)),
		dfadd2_vf2_vf2_vf2(dfscale_vf2_vf2_vf(x, vcast_vf_f(2)), dfmul_vf2_vf2_vf(dfmul_vf2_vf2_vf2(x2, x), t)));
}

static INLINE vfloat expkf(vfloat2 d) {
  vfloat u = vmul_vf_vf_vf(vadd_vf_vf_vf(d.x, d.y), vcast_vf_f(R_LN2f));
  vint2 q = vrint_vi2_vf(u);
  vfloat2 s, t;

  s = dfadd2_vf2_vf2_vf(d, vmul_vf_vf_vf(vcast_vf_vi2(q), vcast_vf_f(-L2Uf)));
  s = dfadd2_vf2_vf2_vf(s, vmul_vf_vf_vf(vcast_vf_vi2(q), vcast_vf_f(-L2Lf)));

  s = dfnormalize_vf2_vf2(s);

  u = vcast_vf_f(0.00136324646882712841033936f);
  u = vmla_vf_vf_vf_vf(u, s.x, vcast_vf_f(0.00836596917361021041870117f));
  u = vmla_vf_vf_vf_vf(u, s.x, vcast_vf_f(0.0416710823774337768554688f));
  u = vmla_vf_vf_vf_vf(u, s.x, vcast_vf_f(0.166665524244308471679688f));
  u = vmla_vf_vf_vf_vf(u, s.x, vcast_vf_f(0.499999850988388061523438f));

  t = dfadd_vf2_vf2_vf2(s, dfmul_vf2_vf2_vf(dfsqu_vf2_vf2(s), u));

  t = dfadd_vf2_vf_vf2(vcast_vf_f(1), t);
  u = vadd_vf_vf_vf(t.x, t.y);
  u = vldexp_vf_vf_vi2(u, q);

  return u;
}

vfloat xpowf(vfloat x, vfloat y) {
#if 1
  vmask yisint = veq_vm_vf_vf(vcast_vf_vi2(vrint_vi2_vf(y)), y);
  vmask yisodf = vand_vm_vm_vm(veq_vm_vi2_vi2(vand_vi2_vi2_vi2(vrint_vi2_vf(y), vcast_vi2_i(1)), vcast_vi2_i(1)), yisint);

  vfloat result = expkf(dfmul_vf2_vf2_vf(logkf(vabs_vf_vf(x)), y));

  //result = vsel_vf_vm_vf_vf(visnan_vm_vf(result), vcast_vf_f(INFINITYf), result);

  result = vmul_vf_vf_vf(result,
		vsel_vf_vm_vf_vf(vgt_vm_vf_vf(x, vcast_vf_f(0)),
		     vcast_vf_f(1),
		     vsel_vf_vm_vf_vf(yisint,
			  vsel_vf_vm_vf_vf(yisodf,
			       vcast_vf_f(-1),
			       vcast_vf_f(1)),
			  vcast_vf_f(NANf))));

  vfloat efx = vreinterpret_vf_vm(vxor_vm_vm_vm(vreinterpret_vm_vf(vsub_vf_vf_vf(vabs_vf_vf(x), vcast_vf_f(1))), vsignbit_vm_vf(y)));

  result = vsel_vf_vm_vf_vf(visinf_vm_vf(y),
		vsel_vf_vm_vf_vf(vlt_vm_vf_vf(efx, vcast_vf_f(0)),
		     vcast_vf_f(0),
		     vsel_vf_vm_vf_vf(veq_vm_vf_vf(efx, vcast_vf_f(0)),
			  vcast_vf_f(1.0),
			  vcast_vf_f(INFINITYf))),
		result);

  result = vsel_vf_vm_vf_vf(vor_vm_vm_vm(visinf_vm_vf(x), veq_vm_vf_vf(x, vcast_vf_f(0))),
		vmul_vf_vf_vf(vsel_vf_vm_vf_vf(yisodf, vsign_vf_vf(x), vcast_vf_f(1)),
		     vsel_vf_vm_vf_vf(vlt_vm_vf_vf(vsel_vf_vm_vf_vf(veq_vm_vf_vf(x, vcast_vf_f(0)), vneg_vf_vf(y), y), vcast_vf_f(0)),
			  vcast_vf_f(0),
			  vcast_vf_f(INFINITYf))),
		result);

  result = vsel_vf_vm_vf_vf(vor_vm_vm_vm(visnan_vm_vf(x), visnan_vm_vf(y)), vcast_vf_f(NANf), result);

  result = vsel_vf_vm_vf_vf(vor_vm_vm_vm(veq_vm_vf_vf(y, vcast_vf_f(0)), veq_vm_vf_vf(x, vcast_vf_f(1))), vcast_vf_f(1), result);

  return result;
#else
  return expkf(dfmul_vf2_vf2_vf(logkf(x), y));
#endif
}

static INLINE vfloat2 expk2f(vfloat2 d) {
  vfloat u = vmul_vf_vf_vf(vadd_vf_vf_vf(d.x, d.y), vcast_vf_f(R_LN2f));
  vint2 q = vrint_vi2_vf(u);
  vfloat2 s, t;

  s = dfadd2_vf2_vf2_vf(d, vmul_vf_vf_vf(vcast_vf_vi2(q), vcast_vf_f(-L2Uf)));
  s = dfadd2_vf2_vf2_vf(s, vmul_vf_vf_vf(vcast_vf_vi2(q), vcast_vf_f(-L2Lf)));

  q = vrint_vi2_vf(vmin_vf_vf_vf(vmax_vf_vf_vf(vcast_vf_f(-2047.49), u), vcast_vf_f(2047.49)));

  s = dfnormalize_vf2_vf2(s);

  u = vcast_vf_f(0.00136324646882712841033936f);
  u = vmla_vf_vf_vf_vf(u, s.x, vcast_vf_f(0.00836596917361021041870117f));
  u = vmla_vf_vf_vf_vf(u, s.x, vcast_vf_f(0.0416710823774337768554688f));
  u = vmla_vf_vf_vf_vf(u, s.x, vcast_vf_f(0.166665524244308471679688f));
  u = vmla_vf_vf_vf_vf(u, s.x, vcast_vf_f(0.499999850988388061523438f));

  t = dfadd_vf2_vf2_vf2(s, dfmul_vf2_vf2_vf(dfsqu_vf2_vf2(s), u));

  t = dfadd_vf2_vf_vf2(vcast_vf_f(1), t);

  return vcast_vf2_vf_vf(vldexp_vf_vf_vi2(t.x, q), vldexp_vf_vf_vi2(t.y, q));
}

vfloat xsinhf(vfloat x) {
  vfloat y = vabs_vf_vf(x);
  vfloat2 d = expk2f(vcast_vf2_vf_vf(y, vcast_vf_f(0)));
  d = dfadd2_vf2_vf2_vf2(d, dfdiv_vf2_vf2_vf2(vcast_vf2_vf_vf(vcast_vf_f(-1), vcast_vf_f(0)), d));
  y = vmul_vf_vf_vf(vadd_vf_vf_vf(d.x, d.y), vcast_vf_f(0.5));

  y = vsel_vf_vm_vf_vf(vor_vm_vm_vm(visinf_vm_vf(x), visnan_vm_vf(y)), vcast_vf_f(INFINITYf), y);
  y = vmulsign_vf_vf_vf(y, x);
  y = vsel_vf_vm_vf_vf(visnan_vm_vf(x), vcast_vf_f(NANf), y);

  return y;
}

vfloat xcoshf(vfloat x) {
  vfloat2 d = expk2f(vcast_vf2_vf_vf(x, vcast_vf_f(0)));
  d = dfadd2_vf2_vf2_vf2(d, dfdiv_vf2_vf2_vf2(vcast_vf2_vf_vf(vcast_vf_f(1), vcast_vf_f(0)), d));
  vfloat y = vmul_vf_vf_vf(vadd_vf_vf_vf(d.x, d.y), vcast_vf_f(0.5));

  y = vsel_vf_vm_vf_vf(vor_vm_vm_vm(visinf_vm_vf(x), visnan_vm_vf(y)), vcast_vf_f(INFINITYf), y);
  y = vsel_vf_vm_vf_vf(visnan_vm_vf(x), vcast_vf_f(NANf), y);

  return y;
}

vfloat xtanhf(vfloat x) {
  vfloat y = vabs_vf_vf(x);
  vfloat2 d = expk2f(vcast_vf2_vf_vf(y, vcast_vf_f(0)));
  vfloat2 e = dfdiv_vf2_vf2_vf2(vcast_vf2_vf_vf(vcast_vf_f(1), vcast_vf_f(0)), d);
  d = dfdiv_vf2_vf2_vf2(dfadd2_vf2_vf2_vf2(d, dfscale_vf2_vf2_vf(e, vcast_vf_f(-1))), dfadd2_vf2_vf2_vf2(d, e));
  y = vadd_vf_vf_vf(d.x, d.y);

  y = vsel_vf_vm_vf_vf(vor_vm_vm_vm(visinf_vm_vf(x), visnan_vm_vf(y)), vcast_vf_f(1.0), y);
  y = vmulsign_vf_vf_vf(y, x);
  y = vsel_vf_vm_vf_vf(visnan_vm_vf(x), vcast_vf_f(NANf), y);

  return y;
}

static INLINE vfloat2 logk2f(vfloat2 d) {
  vfloat2 x, x2, m;
  vfloat t;
  vint2 e;

  d = dfnormalize_vf2_vf2(d);
  e = vilogbp1_vi2_vf(vmul_vf_vf_vf(d.x, vcast_vf_f(0.7071)));
  m = dfscale_vf2_vf2_vf(d, vldexp_vf_vf_vi2(vcast_vf_f(1), vsub_vi2_vi2_vi2(vcast_vi2_i(0), e)));

  x = dfdiv_vf2_vf2_vf2(dfadd2_vf2_vf2_vf(m, vcast_vf_f(-1)), dfadd2_vf2_vf2_vf(m, vcast_vf_f(1)));
  x2 = dfsqu_vf2_vf2(x);
  x2 = dfnormalize_vf2_vf2(x2);

  t = vcast_vf_f(0.2371599674224853515625f);
  t = vmla_vf_vf_vf_vf(t, x2.x, vcast_vf_f(0.285279005765914916992188f));
  t = vmla_vf_vf_vf_vf(t, x2.x, vcast_vf_f(0.400005519390106201171875f));
  t = vmla_vf_vf_vf_vf(t, x2.x, vcast_vf_f(0.666666567325592041015625f));

  return dfadd2_vf2_vf2_vf2(dfmul_vf2_vf2_vf(vcast_vf2_vf_vf(vcast_vf_f(0.69314718246459960938f), vcast_vf_f(-1.904654323148236017e-09f)),
		       vcast_vf_vi2(e)),
		dfadd2_vf2_vf2_vf2(dfscale_vf2_vf2_vf(x, vcast_vf_f(2)), dfmul_vf2_vf2_vf(dfmul_vf2_vf2_vf2(x2, x), t)));
}

vfloat xasinhf(vfloat x) {
  vfloat y = vabs_vf_vf(x);
  vfloat2 d = logk2f(dfadd2_vf2_vf2_vf(dfsqrt_vf2_vf2(dfadd2_vf2_vf2_vf(dfmul_vf2_vf_vf(y, y),  vcast_vf_f(1))), y));
  y = vadd_vf_vf_vf(d.x, d.y);

  y = vsel_vf_vm_vf_vf(vor_vm_vm_vm(visinf_vm_vf(x), visnan_vm_vf(y)), vcast_vf_f(INFINITYf), y);
  y = vmulsign_vf_vf_vf(y, x);
  y = vsel_vf_vm_vf_vf(visnan_vm_vf(x), vcast_vf_f(NANf), y);

  return y;
}

vfloat xacoshf(vfloat x) {
  vfloat2 d = logk2f(dfadd2_vf2_vf2_vf(dfsqrt_vf2_vf2(dfadd2_vf2_vf2_vf(dfmul_vf2_vf_vf(x, x), vcast_vf_f(-1))), x));
  vfloat y = vadd_vf_vf_vf(d.x, d.y);

  y = vsel_vf_vm_vf_vf(vor_vm_vm_vm(visinf_vm_vf(x), visnan_vm_vf(y)), vcast_vf_f(INFINITYf), y);
  y = vsel_vf_vm_vf_vf(veq_vm_vf_vf(x, vcast_vf_f(1.0)), vcast_vf_f(0.0), y);
  y = vsel_vf_vm_vf_vf(vlt_vm_vf_vf(x, vcast_vf_f(1.0)), vcast_vf_f(NANf), y);
  y = vsel_vf_vm_vf_vf(visnan_vm_vf(x), vcast_vf_f(NANf), y);

  return y;
}

vfloat xatanhf(vfloat x) {
  vfloat y = vabs_vf_vf(x);
  vfloat2 d = logk2f(dfdiv_vf2_vf2_vf2(dfadd2_vf2_vf_vf(vcast_vf_f(1), y), dfadd2_vf2_vf_vf(vcast_vf_f(1), vneg_vf_vf(y))));
  y = vsel_vf_vm_vf_vf(vgt_vm_vf_vf(y, vcast_vf_f(1.0)), vcast_vf_f(NANf), vsel_vf_vm_vf_vf(veq_vm_vf_vf(y, vcast_vf_f(1.0)), vcast_vf_f(INFINITYf), vmul_vf_vf_vf(vadd_vf_vf_vf(d.x, d.y), vcast_vf_f(0.5))));

  y = vsel_vf_vm_vf_vf(vor_vm_vm_vm(visinf_vm_vf(x), visnan_vm_vf(y)), vcast_vf_f(NANf), y);
  y = vmulsign_vf_vf_vf(y, x);
  y = vsel_vf_vm_vf_vf(visnan_vm_vf(x), vcast_vf_f(NANf), y);

  return y;
}

vfloat xexp2f(vfloat a) {
  vfloat u = expkf(dfmul_vf2_vf2_vf(vcast_vf2_vf_vf(vcast_vf_f(0.69314718246459960938f), vcast_vf_f(-1.904654323148236017e-09f)), a));
  u = vsel_vf_vm_vf_vf(vispinf_vm_vf(a), vcast_vf_f(INFINITYf), u);
  u = vsel_vf_vm_vf_vf(visminf_vm_vf(a), vcast_vf_f(0), u);
  return u;
}

vfloat xexp10f(vfloat a) {
  vfloat u = expkf(dfmul_vf2_vf2_vf(vcast_vf2_vf_vf(vcast_vf_f(2.3025851249694824219f), vcast_vf_f(-3.1975436520781386207e-08f)), a));
  u = vsel_vf_vm_vf_vf(vispinf_vm_vf(a), vcast_vf_f(INFINITYf), u);
  u = vsel_vf_vm_vf_vf(visminf_vm_vf(a), vcast_vf_f(0), u);
  return u;
}

vfloat xexpm1f(vfloat a) {
  vfloat2 d = dfadd2_vf2_vf2_vf(expk2f(vcast_vf2_vf_vf(a, vcast_vf_f(0))), vcast_vf_f(-1.0));
  vfloat x = vadd_vf_vf_vf(d.x, d.y);
  x = vsel_vf_vm_vf_vf(vispinf_vm_vf(a), vcast_vf_f(INFINITYf), x);
  x = vsel_vf_vm_vf_vf(visminf_vm_vf(a), vcast_vf_f(-1), x);
  return x;
}

vfloat xlog10f(vfloat a) {
  vfloat2 d = dfmul_vf2_vf2_vf2(logkf(a), vcast_vf2_vf_vf(vcast_vf_f(0.43429449200630187988f), vcast_vf_f(-1.0103050118726031315e-08f)));
  vfloat x = vadd_vf_vf_vf(d.x, d.y);

  x = vsel_vf_vm_vf_vf(vispinf_vm_vf(a), vcast_vf_f(INFINITYf), x);
  x = vsel_vf_vm_vf_vf(vgt_vm_vf_vf(vcast_vf_f(0), a), vcast_vf_f(NANf), x);
  x = vsel_vf_vm_vf_vf(veq_vm_vf_vf(a, vcast_vf_f(0)), vcast_vf_f(-INFINITYf), x);

  return x;
}

vfloat xlog1pf(vfloat a) {
  vfloat2 d = logk2f(dfadd2_vf2_vf_vf(a, vcast_vf_f(1)));
  vfloat x = vadd_vf_vf_vf(d.x, d.y);

  x = vsel_vf_vm_vf_vf(vispinf_vm_vf(a), vcast_vf_f(INFINITYf), x);
  x = vsel_vf_vm_vf_vf(vgt_vm_vf_vf(vcast_vf_f(-1), a), vcast_vf_f(NANf), x);
  x = vsel_vf_vm_vf_vf(veq_vm_vf_vf(a, vcast_vf_f(-1)), vcast_vf_f(-INFINITYf), x);

  return x;
}
