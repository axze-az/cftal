package sleef

import "math"

//

func rint(x float64) float64 {
  if (x < 0) { return float64(int(x - 0.5)); }
  return float64(int(x + 0.5));
}

func fabs(d float64) float64 {
  return math.Copysign(d, 1);
}

func mulsign(x, y float64) float64 {
  if (math.Signbit(y)) { return -x; }
  return x;
}

func sign(d float64) float64 {
  if (math.Signbit(d)) { return -1; }
  return 1;
}

func ternary(b bool, x, y float64) float64 {
  if (b) { return x; }
  return y;
}

func iternary(b bool, x, y int) int {
  if (b) { return x; }
  return y;
}

func upper(d float64) float64 {
  var l uint64;
  l = math.Float64bits(d);
  return math.Float64frombits(l & 0xfffffffff8000000);
}

func isnan(x float64) bool { return x != x; }
func isinf(x float64) bool { return x == math.Inf(1) || x == math.Inf(-1); }
func ispinf(x float64) bool { return x == math.Inf(1); }
func isminf(x float64) bool { return x == math.Inf(-1); }

func ilogbp1(d float64) int {
  var m bool;
  var q int;
  m = d < 4.9090934652977266E-91;
  d = ternary(m, 2.037035976334486E90 * d, d);
  q = int(math.Float64bits(d) >> 52) & 0x7ff;
  q = iternary(m, q - (300 + 0x3fe), q - 0x3fe);
  return q;
}

//

func Ldexp(x float64, q int) float64 {
  var u float64;
  var m int;

  m = q >> 31;
  m = (((m + q) >> 9) - m) << 7;
  q = q - (m << 2);
  u = math.Float64frombits((uint64)((int64(m + 0x3ff)) << 52));
  x = x * u * u * u * u;
  u = math.Float64frombits((uint64)((int64(q + 0x3ff)) << 52));
  return x * u;
}

func Ilogb(d float64) int {
  var e int;
  e = ilogbp1(fabs(d)) - 1;
  e = iternary(d == 0, -2147483648, e);
  e = iternary(isinf(d), 2147483647, e);
  return e;
}

func Sin(d float64) float64 {
  var q int;
  var u, s float64;

  u = d * 0.3183098861837906715377675267450287;
  if (u < 0) {
    q = (int)(u - 0.5);
  } else {
    q = (int)(u + 0.5);
  }

  d = float64(q) * (-.7853981554508209228515625*4) + d;
  d = float64(q) * (-.794662735614792836713604629039764404296875e-8*4) + d;
  d = float64(q) * (-.306161699786838294306516483068750264552437361480769e-16*4) + d;

  s = d * d;

  if ((q & 1) != 0) { d = -d; }

  u = -7.97255955009037868891952e-18;
  u = u * s + 2.81009972710863200091251e-15;
  u = u * s - 7.64712219118158833288484e-13;
  u = u * s + 1.60590430605664501629054e-10;
  u = u * s - 2.50521083763502045810755e-08;
  u = u * s + 2.75573192239198747630416e-06;
  u = u * s - 0.000198412698412696162806809;
  u = u * s + 0.00833333333333332974823815;
  u = u * s - 0.166666666666666657414808;

  u = u * d * s + d;

  return u;
}

func Cos(d float64) float64 {
  var q int;
  var u, s float64;

  q = 1 + 2*int(rint(d * 0.3183098861837906715377675267450287 - 0.5));

  d = float64(q) * (-.7853981554508209228515625*2) + d;
  d = float64(q) * (-.794662735614792836713604629039764404296875e-8*2) + d;
  d = float64(q) * (-.306161699786838294306516483068750264552437361480769e-16*2) + d;

  s = d * d;

  if ((q & 2) == 0) { d = -d; }

  u = -7.97255955009037868891952e-18;
  u = u * s + 2.81009972710863200091251e-15;
  u = u * s - 7.64712219118158833288484e-13;
  u = u * s + 1.60590430605664501629054e-10;
  u = u * s - 2.50521083763502045810755e-08;
  u = u * s + 2.75573192239198747630416e-06;
  u = u * s - 0.000198412698412696162806809;
  u = u * s + 0.00833333333333332974823815;
  u = u * s - 0.166666666666666657414808;
  u = u * d * s + d;

  return u;
}

func Tan(d float64) float64 {
  var q int;
  var u, s, x float64;

  q = int(rint(d * (2 * 0.3183098861837906715377675267450287)));

  x = float64(q) * (-.7853981554508209228515625*2) + d;
  x = float64(q) * (-.794662735614792836713604629039764404296875e-8*2) + x;
  x = float64(q) * (-.306161699786838294306516483068750264552437361480769e-16*2) + x;

  s = x * x;

  if ((q & 1) != 0) { x = -x; }

  u = 1.01419718511083373224408e-05;
  u = u * s - 2.59519791585924697698614e-05;
  u = u * s + 5.23388081915899855325186e-05;
  u = u * s - 3.05033014433946488225616e-05;
  u = u * s + 7.14707504084242744267497e-05;
  u = u * s + 8.09674518280159187045078e-05;
  u = u * s + 0.000244884931879331847054404;
  u = u * s + 0.000588505168743587154904506;
  u = u * s + 0.00145612788922812427978848;
  u = u * s + 0.00359208743836906619142924;
  u = u * s + 0.00886323944362401618113356;
  u = u * s + 0.0218694882853846389592078;
  u = u * s + 0.0539682539781298417636002;
  u = u * s + 0.133333333333125941821962;
  u = u * s + 0.333333333333334980164153;

  u = u * x * s + x;

  if ((q & 1) != 0) { u = 1.0 / u; }

  if (isinf(d)) { u = math.NaN(); }

  return u;
}

func Sincos(d float64) (rx, ry float64) {
  var q int;
  var u, s, t float64;

  q = int(rint(d * (2 * 0.3183098861837906715377675267450287)));

  s = d;

  s = s - float64(q) * (2 * .7853981554508209228515625);
  s = s - float64(q) * (2 * .794662735614792836713604629039764404296875e-8);
  s = s - float64(q) * (2 * .306161699786838294306516483068750264552437361480769e-16);

  t = s;

  s = s * s;

  u = 1.58938307283228937328511e-10;
  u = u * s - 2.50506943502539773349318e-08;
  u = u * s + 2.75573131776846360512547e-06;
  u = u * s - 0.000198412698278911770864914;
  u = u * s + 0.0083333333333191845961746;
  u = u * s - 0.166666666666666130709393;
  u = u * s * t;

  rx = t + u;

  u = -1.13615350239097429531523e-11;
  u = u * s + 2.08757471207040055479366e-09;
  u = u * s - 2.75573144028847567498567e-07;
  u = u * s + 2.48015872890001867311915e-05;
  u = u * s - 0.00138888888888714019282329;
  u = u * s + 0.0416666666666665519592062;
  u = u * s - 0.5;

  ry = u * s + 1;

  if ((q & 1) != 0) { s = ry; ry = rx; rx = s; }
  if ((q & 2) != 0) { rx = -rx; }
  if (((q+1) & 2) != 0) { ry = -ry; }

  if (isinf(d)) { rx = math.NaN(); ry = math.NaN(); }

  return rx, ry;
}

func Asin(d float64) float64 {
  return mulsign(atan2k(fabs(d), math.Sqrt((1+d)*(1-d))), d);
}

func Acos(d float64) float64 {
  return mulsign(atan2k(math.Sqrt((1+d)*(1-d)), fabs(d)), d) + ternary(d < 0, 3.1415926535897932384626433832795029, 0);
}

func Atan(s float64) float64 {
  var t, u float64;
  var q int;

  q = 0;

  if (s < 0) { s = -s; q = 2; }
  if (s > 1) { s = 1.0 / s; q |= 1; }

  t = s * s;

  u = -1.88796008463073496563746e-05;
  u = u * t + 0.000209850076645816976906797;
  u = u * t - 0.00110611831486672482563471;
  u = u * t + 0.00370026744188713119232403;
  u = u * t - 0.00889896195887655491740809;
  u = u * t + 0.016599329773529201970117;
  u = u * t - 0.0254517624932312641616861;
  u = u * t + 0.0337852580001353069993897;
  u = u * t - 0.0407629191276836500001934;
  u = u * t + 0.0466667150077840625632675;
  u = u * t - 0.0523674852303482457616113;
  u = u * t + 0.0587666392926673580854313;
  u = u * t - 0.0666573579361080525984562;
  u = u * t + 0.0769219538311769618355029;
  u = u * t - 0.090908995008245008229153;
  u = u * t + 0.111111105648261418443745;
  u = u * t - 0.14285714266771329383765;
  u = u * t + 0.199999999996591265594148;
  u = u * t - 0.333333333333311110369124;

  t = s + s * (t * u);

  if ((q & 1) != 0) { t = 1.570796326794896557998982 - t; }
  if ((q & 2) != 0) { t = -t; }

  return t;
}

func Log(d float64) float64 {
  var x, x2, t, m float64;
  var e int;

  e = ilogbp1(d * 0.7071);
  m = Ldexp(d, -e);

  x = (m-1) / (m+1);
  x2 = x * x;

  t = 0.148197055177935105296783;
  t = t * x2 + 0.153108178020442575739679;
  t = t * x2 + 0.181837339521549679055568;
  t = t * x2 + 0.22222194152736701733275;
  t = t * x2 + 0.285714288030134544449368;
  t = t * x2 + 0.399999999989941956712869;
  t = t * x2 + 0.666666666666685503450651;
  t = t * x2 + 2;

  x = x * t + 0.693147180559945286226764 * float64(e);

  if (isinf(d)) { x = math.Inf(1); }
  if (d < 0) { x = math.NaN(); }
  if (d == 0) { x = math.Inf(-1); }

  return x;
}

func Exp(d float64) float64 {
  var q int;
  var s, u float64;

  q = int(rint(d * 1.442695040888963407359924681001892137426645954152985934135449406931));

  s = float64(q) * -.69314718055966295651160180568695068359375 + d;
  s = float64(q) * -.28235290563031577122588448175013436025525412068e-12 + s;

  u = 2.08860621107283687536341e-09;
  u = u * s + 2.51112930892876518610661e-08;
  u = u * s + 2.75573911234900471893338e-07;
  u = u * s + 2.75572362911928827629423e-06;
  u = u * s + 2.4801587159235472998791e-05;
  u = u * s + 0.000198412698960509205564975;
  u = u * s + 0.00138888888889774492207962;
  u = u * s + 0.00833333333331652721664984;
  u = u * s + 0.0416666666666665047591422;
  u = u * s + 0.166666666666666851703837;
  u = u * s + 0.5;

  u = s * s * u + s + 1;
  u = Ldexp(u, q);

  if (isminf(d)) { u = 0; }

  return u;
}

func atan2k(y, x float64) float64 {
  var s, t, u float64;
  var q int;

  q = 0;

  if (x < 0) { x = -x; q = -2; }
  if (y > x) { t = x; x = y; y = -t; q += 1; }

  s = y / x;
  t = s * s;

  u = -1.88796008463073496563746e-05;
  u = u * t + 0.000209850076645816976906797;
  u = u * t - 0.00110611831486672482563471;
  u = u * t + 0.00370026744188713119232403;
  u = u * t - 0.00889896195887655491740809;
  u = u * t + 0.016599329773529201970117;
  u = u * t - 0.0254517624932312641616861;
  u = u * t + 0.0337852580001353069993897;
  u = u * t - 0.0407629191276836500001934;
  u = u * t + 0.0466667150077840625632675;
  u = u * t - 0.0523674852303482457616113;
  u = u * t + 0.0587666392926673580854313;
  u = u * t - 0.0666573579361080525984562;
  u = u * t + 0.0769219538311769618355029;
  u = u * t - 0.090908995008245008229153;
  u = u * t + 0.111111105648261418443745;
  u = u * t - 0.14285714266771329383765;
  u = u * t + 0.199999999996591265594148;
  u = u * t - 0.333333333333311110369124;

  t = u * t * s + s;
  t = float64(q) * (3.1415926535897932384626433832795029/2) + t;

  return t;
}

func Atan2(y, x float64) float64 {
  var r float64;

  r = atan2k(fabs(y), x);

  r = mulsign(r, x);
  if (isinf(x) || x == 0) {
    r = (3.1415926535897932384626433832795029/2);
    r -= ternary(isinf(x), sign(x) * (3.1415926535897932384626433832795029/2), 0);
  }

  if (isinf(y)          ) {
    r = (3.1415926535897932384626433832795029/2);
    r -= ternary(isinf(x), sign(x) * (3.1415926535897932384626433832795029/4), 0);
  }

  if (                    y == 0) {
    r = ternary(math.Signbit(x), 3.1415926535897932384626433832795029, 0);
  }

  return ternary(isnan(x) || isnan(y), math.NaN(), mulsign(r, y));
}

//

type double2 struct { x, y float64 }

  func dd(x, y float64) double2 {
    var r double2;
    r.x = x; r.y = y;
    return r;
  }

func normalize_d(t double2) double2 {
  var s double2;

  s.x = t.x + t.y;
  s.y = t.x - s.x + t.y;

  return s;
}

func scale_d(d double2, s float64) double2 {
  var r double2;

  r.x = d.x * s;
  r.y = d.y * s;

  return r;
}

func add2_ss(x, y float64) double2 {
  var r double2;
  var v float64;

  r.x = x + y;
  v = r.x - x;
  r.y = (x - (r.x - v)) + (y - v);

  return r;
}

func add_ds(x double2, y float64) double2 {
  var r double2;

  r.x = x.x + y;
  r.y = x.x - r.x + y + x.y;

  return r;
}

func add2_ds(x double2, y float64) double2 {
  var r double2;
  var v float64;

  r.x  = x.x + y;
  v = r.x - x.x;
  r.y = (x.x - (r.x - v)) + (y - v);
  r.y += x.y;

  return r;
}

func add_sd(x float64, y double2) double2 {
  var r double2;

  r.x = x + y.x;
  r.y = x - r.x + y.x + y.y;

  return r;
}

func add_dd(x, y double2) double2 {
  var r double2;

  r.x = x.x + y.x;
  r.y = x.x - r.x + y.x + x.y + y.y;

  return r;
}

func add2_dd(x, y double2) double2 {
  var r double2;
  var v float64;

  r.x  = x.x + y.x;
  v = r.x - x.x;
  r.y = (x.x - (r.x - v)) + (y.x - v);
  r.y += x.y + y.y;

  return r;
}

func div_dd(n, d double2) double2 {
  var t, dh, dl, th, tl, nhh, nhl, u float64;
  var q double2;

  t = 1.0 / d.x;
  dh  = upper(d.x); dl  = d.x - dh;
  th  = upper(t  ); tl  = t   - th;
  nhh = upper(n.x); nhl = n.x - nhh;

  q.x = n.x * t;

  u = -q.x + nhh * th + nhh * tl + nhl * th + nhl * tl +
    q.x * (1 - dh * th - dh * tl - dl * th - dl * tl);

  q.y = t * (n.y - q.x * d.y) + u;

  return q;
}

func mul_ss(x, y float64) double2 {
  var xh, xl, yh, yl float64;
  var r double2;

  xh = upper(x); xl = x - xh;
  yh = upper(y); yl = y - yh;

  r.x = x * y;
  r.y = xh * yh - r.x + xl * yh + xh * yl + xl * yl;

  return r;
}

func mul_ds(x double2, y float64) double2 {
  var xh, xl, yh, yl float64;
  var r double2;

  xh = upper(x.x); xl = x.x - xh;
  yh = upper(y  ); yl = y   - yh;

  r.x = x.x * y;
  r.y = xh * yh - r.x + xl * yh + xh * yl + xl * yl + x.y * y;

  return r;
}

func mul_dd(x, y double2) double2 {
  var xh, xl, yh, yl float64;
  var r double2;

  xh = upper(x.x); xl = x.x - xh;
  yh = upper(y.x); yl = y.x - yh;

  r.x = x.x * y.x;
  r.y = xh * yh - r.x + xl * yh + xh * yl + xl * yl + x.x * y.y + x.y * y.x;

  return r;
}

func squ_d(x double2) double2 {
  var xh, xl float64;
  var r double2;

  xh = upper(x.x); xl = x.x - xh;

  r.x = x.x * x.x;
  r.y = xh * xh - r.x + (xh + xh) * xl + xl * xl + x.x * (x.y + x.y);

  return r;
}

func rec_s(d float64) double2 {
  var t, dh, dl, th, tl float64;
  var q double2;

  t = 1.0 / d;
  dh = upper(d); dl = d - dh;
  th = upper(t); tl = t - th;

  q.x = t;
  q.y = t * (1 - dh * th - dh * tl - dl * th - dl * tl);

  return q;
}

func sqrt_d(d double2) double2 {
  var t float64;

  t = math.Sqrt(d.x + d.y);
  return scale_d(mul_dd(add2_dd(d, mul_ss(t, t)), rec_s(t)), 0.5);
}

func logk(d float64) double2 {
  var x, x2 double2;
  var m, t float64;
  var e int;

  e = ilogbp1(d * 0.7071);
  m = Ldexp(d, -e);

  x = div_dd(add2_ss(-1, m), add2_ss(1, m));
  x2 = squ_d(x);

  t = 0.134601987501262130076155;
  t = t * x2.x + 0.132248509032032670243288;
  t = t * x2.x + 0.153883458318096079652524;
  t = t * x2.x + 0.181817427573705403298686;
  t = t * x2.x + 0.222222231326187414840781;
  t = t * x2.x + 0.285714285651261412873718;
  t = t * x2.x + 0.400000000000222439910458;
  t = t * x2.x + 0.666666666666666371239645;

  return add2_dd(mul_ds(dd(0.693147180559945286226764, 2.319046813846299558417771e-17), float64(e)),
		 add2_dd(scale_d(x, 2), mul_ds(mul_dd(x2, x), t)));
}

func expk(d double2) float64 {
  var q int;
  var s, t double2;
  var u float64;

  q = int(rint((d.x + d.y) * 1.442695040888963407359924681001892137426645954152985934135449406931));

  s = add2_ds(d, float64(q) * -.69314718055966295651160180568695068359375);
  s = add2_ds(s, float64(q) * -.28235290563031577122588448175013436025525412068e-12);

  s = normalize_d(s);

  u = 2.51069683420950419527139e-08;
  u = u * s.x + 2.76286166770270649116855e-07;
  u = u * s.x + 2.75572496725023574143864e-06;
  u = u * s.x + 2.48014973989819794114153e-05;
  u = u * s.x + 0.000198412698809069797676111;
  u = u * s.x + 0.0013888888939977128960529;
  u = u * s.x + 0.00833333333332371417601081;
  u = u * s.x + 0.0416666666665409524128449;
  u = u * s.x + 0.166666666666666740681535;
  u = u * s.x + 0.500000000000000999200722;

  t = add_dd(s, mul_ds(squ_d(s), u));

  t = add_sd(1, t);

  return Ldexp(t.x + t.y, q);
}

func Pow(x, y float64) float64 {
  var yisint, yisodd bool;
  var result, efx float64;

  yisint = float64(int(y)) == y;
  yisodd = (1 & int(y)) != 0 && yisint;

  result = expk(mul_ds(logk(fabs(x)), y));

  result = ternary(isnan(result), math.Inf(1), result);
  result *=  ternary(x >= 0, 1, ternary(!yisint, math.NaN(), ternary(yisodd, -1, 1)));

  efx = mulsign(fabs(x) - 1, y);
  if (isinf(y)) { result = ternary(efx < 0, 0.0, ternary(efx == 0, 1.0, math.Inf(1))); }
  if (isinf(x) || x == 0) { result = ternary(yisodd, sign(x), 1) * (ternary(ternary(x == 0, -y, y) < 0, 0, math.Inf(1))); }
  if (isnan(x) || isnan(y)) { result = math.NaN(); }
  if (y == 0 || x == 1) { result = 1; }

  return result;
}

func expk2(d double2) double2 {
  var q int;
  var s, t double2;
  var u float64;

  q = int(rint((d.x + d.y) * 1.442695040888963407359924681001892137426645954152985934135449406931));

  s = add2_ds(d, float64(q) * -.69314718055966295651160180568695068359375);
  s = add2_ds(s, float64(q) * -.28235290563031577122588448175013436025525412068e-12);

  s = normalize_d(s);

  u = 2.51069683420950419527139e-08;
  u = u * s.x + 2.76286166770270649116855e-07;
  u = u * s.x + 2.75572496725023574143864e-06;
  u = u * s.x + 2.48014973989819794114153e-05;
  u = u * s.x + 0.000198412698809069797676111;
  u = u * s.x + 0.0013888888939977128960529;
  u = u * s.x + 0.00833333333332371417601081;
  u = u * s.x + 0.0416666666665409524128449;
  u = u * s.x + 0.166666666666666740681535;
  u = u * s.x + 0.500000000000000999200722;

  t = add_dd(s, mul_ds(squ_d(s), u));

  t = add_sd(1, t);
  return dd(Ldexp(t.x, q), Ldexp(t.y, q));
}

func Sinh(x float64) float64 {
  var y float64;
  var d double2;

  y = fabs(x);
  d = expk2(dd(y, 0));
  d = add2_dd(d, div_dd(dd(-1, 0), d));
  y = (d.x + d.y) * 0.5;

  y = ternary(isinf(x) || isnan(y), math.Inf(1), y);
  y = mulsign(y, x);
  y = ternary(isnan(x), math.NaN(), y);

  return y;
}

func Cosh(x float64) float64 {
  var y float64;
  var d double2;

  d = expk2(dd(x, 0));
  d = add2_dd(d, div_dd(dd(1, 0), d));
  y = (d.x + d.y) * 0.5;

  y = ternary(isinf(x) || isnan(y), math.Inf(1), y);
  y = ternary(isnan(x), math.NaN(), y);

  return y;
}

func Tanh(x float64) float64 {
  var y float64;
  var d, e double2;

  y = fabs(x);
  d = expk2(dd(y, 0));
  e = div_dd(dd(1, 0), d);
  d = div_dd(add2_dd(d, scale_d(e, -1)), add2_dd(d, e));
  y = d.x + d.y;

  y = ternary(isinf(x) || isnan(y), 1.0, y);
  y = mulsign(y, x);
  y = ternary(isnan(x), math.NaN(), y);

  return y;
}

func logk2(d double2) double2 {
  var x, x2, m double2;
  var t float64;
  var e int;

  d = normalize_d(d);
  e = ilogbp1(d.x * 0.7071);
  m = scale_d(d, Ldexp(1, -e));

  x = div_dd(add2_ds(m, -1), add2_ds(m, 1));
  x2 = squ_d(x);

  t = 0.134601987501262130076155;
  t = t * x2.x + 0.132248509032032670243288;
  t = t * x2.x + 0.153883458318096079652524;
  t = t * x2.x + 0.181817427573705403298686;
  t = t * x2.x + 0.222222231326187414840781;
  t = t * x2.x + 0.285714285651261412873718;
  t = t * x2.x + 0.400000000000222439910458;
  t = t * x2.x + 0.666666666666666371239645;

  return add2_dd(mul_ds(dd(0.693147180559945286226764, 2.319046813846299558417771e-17), float64(e)),
		 add2_dd(scale_d(x, 2), mul_ds(mul_dd(x2, x), t)));
}

func Asinh(x float64) float64 {
  var y float64;
  var d double2;

  y = fabs(x);
  d = logk2(add2_ds(sqrt_d(add2_ds(mul_ss(y, y),  1)), y));
  y = d.x + d.y;

  y = ternary(isinf(x) || isnan(y), math.Inf(1), y);
  y = mulsign(y, x);
  y = ternary(isnan(x), math.NaN(), y);

  return y;
}

func Acosh(x float64) float64 {
  var y float64;
  var d double2;

  d = logk2(add2_ds(sqrt_d(add2_ds(mul_ss(x, x), -1)), x));
  y = d.x + d.y;

  y = ternary(isinf(x) || isnan(y), math.Inf(1), y);
  y = ternary(x == 1.0, 0.0, y);
  y = ternary(x < 1.0, math.NaN(), y);
  y = ternary(isnan(x), math.NaN(), y);

  return y;
}

func Atanh(x float64) float64 {
  var y float64;
  var d double2;

  y = fabs(x);
  d = logk2(div_dd(add2_ss(1, y), add2_ss(1, -y)));
  y = ternary(y > 1.0, math.NaN(), ternary(y == 1.0, math.Inf(1), (d.x + d.y) * 0.5));

  y = ternary(isinf(x) || isnan(y), math.NaN(), y);
  y = mulsign(y, x);
  y = ternary(isnan(x), math.NaN(), y);

  return y;
}

func Fma(x, y, z float64) float64 {
  var xh, xl, yh, yl, h, l, h2, l2, v float64;

  xh = math.Float64frombits((math.Float64bits(x) + 0x4000000) & 0xfffffffff8000000);
  xl = x - xh;
  yh = math.Float64frombits((math.Float64bits(y) + 0x4000000) & 0xfffffffff8000000);
  yl = y - yh;

  h = x * y;
  l = xh * yh - h + xl * yh + xh * yl + xl * yl;

  h2 = h + z;
  v = h2 - h;
  l2 = (h - (h2 - v)) + (z - v) + l;

  return h2 + l2;
}

func Sqrt(d float64) float64 {
  var q, x float64;

  q = 1;

  if (d < 8.636168555094445E-78) {
    d *= 1.157920892373162E77;
    q = 2.9387358770557188E-39;
  }

  // http://en.wikipedia.org/wiki/Fast_inverse_square_root
  x = math.Float64frombits(0x5fe6ec85e7de30da - (math.Float64bits(d + 1e-320) >> 1));

  x = x * (1.5 - 0.5 * d * x * x);
  x = x * (1.5 - 0.5 * d * x * x);
  x = x * (1.5 - 0.5 * d * x * x);

  // You can change xfma to fma if fma is correctly implemented
  x = Fma(d * x, d * x, -d) * (x * -0.5) + d * x;

  return ternary(d == math.Inf(1), math.Inf(1), x * q);
}

func Cbrt(d float64) float64 {
  var x, y, q float64;
  var e, r int;

  q = 1.0;

  e = ilogbp1(d);
  d = Ldexp(d, -e);
  r = (e + 6144) % 3;
  q = ternary(r == 1, 1.2599210498948731647672106, q);
  q = ternary(r == 2, 1.5874010519681994747517056, q);
  q = Ldexp(q, (e + 6144) / 3 - 2048);

  q = mulsign(q, d);
  d = fabs(d);

  x = -0.640245898480692909870982;
  x = x * d + 2.96155103020039511818595;
  x = x * d + -5.73353060922947843636166;
  x = x * d + 6.03990368989458747961407;
  x = x * d + -3.85841935510444988821632;
  x = x * d + 2.2307275302496609725722;

  y = x * x; y = y * y; x -= (d * y - x) * (1.0 / 3.0);
  y = d * x * x;
  y = (y - (2.0 / 3.0) * y * (y * x - 1)) * q;

  return y;
}

func Exp2(a float64) float64 {
  var u float64;
  u = expk(mul_ds(dd(0.69314718055994528623, 2.3190468138462995584e-17), a));
  if (ispinf(a)) { u = math.Inf(1); }
  if (isminf(a)) { u = 0; }
  return u;
}

func Exp10(a float64) float64 {
  var u float64;
  u = expk(mul_ds(dd(2.3025850929940459011, -2.1707562233822493508e-16), a));
  if (ispinf(a)) { u = math.Inf(1); }
  if (isminf(a)) { u = 0; }
  return u;
}

func Expm1(a float64) float64 {
  var d double2;
  var x float64;

  d = add2_ds(expk2(dd(a, 0)), -1.0);
  x = d.x + d.y;
  if (ispinf(a)) { x = math.Inf(1); }
  if (isminf(a)) { x = -1; }
  return x;
}

func Log10(a float64) float64 {
  var d double2;
  var x float64;

  d = mul_dd(logk(a), dd(0.43429448190325176116, 6.6494347733425473126e-17));
  x = d.x + d.y;

  if (isinf(a)) { x = math.Inf(1); }
  if (a < 0) { x = math.NaN(); }
  if (a == 0) { x = -math.Inf(1); }

  return x;
}

func Log1p(a float64) float64 {
  var d double2;
  var x float64;

  d = logk2(add2_ss(a, 1));
  x = d.x + d.y;

  if (isinf(a)) { x = math.Inf(1); }
  if (a < -1) { x = math.NaN(); }
  if (a == -1) { x = -math.Inf(1); }

  return x;
}
