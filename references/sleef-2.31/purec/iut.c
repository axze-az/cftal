#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <math.h>

#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <signal.h>

#include "sleef.h"

int readln(int fd, char *buf, int cnt) {
  int i, rcnt = 0;

  if (cnt < 1) return -1;

  while(cnt >= 2) {
    i = read(fd, buf, 1);
    if (i != 1) return i;

    if (*buf == '\n') break;

    rcnt++;
    buf++;
    cnt--;
  }

  *++buf = '\0';
  rcnt++;
  return rcnt;
}

int startsWith(char *str, char *prefix) {
  return strncmp(str, prefix, strlen(prefix)) == 0;
}

double u2d(uint64_t u) {
  union {
    double f;
    uint64_t i;
  } tmp;
  tmp.i = u;
  return tmp.f;
}

uint64_t d2u(double d) {
  union {
    double f;
    uint64_t i;
  } tmp;
  tmp.f = d;
  return tmp.i;
}

float u2f(uint32_t u) {
  union {
    float f;
    uint32_t i;
  } tmp;
  tmp.i = u;
  return tmp.f;
}

uint32_t f2u(float d) {
  union {
    float f;
    uint32_t i;
  } tmp;
  tmp.f = d;
  return tmp.i;
}

#define BUFSIZE 1024

int main(int argc, char **argv) {
  char buf[BUFSIZE];

  //fprintf(stderr, "IUT start\n");

  for(;;) {
    if (readln(STDIN_FILENO, buf, BUFSIZE-1) < 1) break;

    //fprintf(stderr, "iut: got %s\n", buf);

    if (startsWith(buf, "sin ")) {
      uint64_t u;
      sscanf(buf, "sin %lx", &u);
      u = d2u(xsin(u2d(u)));
      printf("%lx\n", u);
    } else if (startsWith(buf, "cos ")) {
      uint64_t u;
      sscanf(buf, "cos %lx", &u);
      u = d2u(xcos(u2d(u)));
      printf("%lx\n", u);
    } else if (startsWith(buf, "sincos ")) {
      uint64_t u;
      sscanf(buf, "sincos %lx", &u);
      double2 x = xsincos(u2d(u));
      printf("%lx %lx\n", d2u(x.x), d2u(x.y));
    } else if (startsWith(buf, "tan ")) {
      uint64_t u;
      sscanf(buf, "tan %lx", &u);
      u = d2u(xtan(u2d(u)));
      printf("%lx\n", u);
    } else if (startsWith(buf, "asin ")) {
      uint64_t u;
      sscanf(buf, "asin %lx", &u);
      u = d2u(xasin(u2d(u)));
      printf("%lx\n", u);
    } else if (startsWith(buf, "acos ")) {
      uint64_t u;
      sscanf(buf, "acos %lx", &u);
      u = d2u(xacos(u2d(u)));
      printf("%lx\n", u);
    } else if (startsWith(buf, "atan ")) {
      uint64_t u;
      sscanf(buf, "atan %lx", &u);
      u = d2u(xatan(u2d(u)));
      printf("%lx\n", u);
    } else if (startsWith(buf, "log ")) {
      uint64_t u;
      sscanf(buf, "log %lx", &u);
      u = d2u(xlog(u2d(u)));
      printf("%lx\n", u);
    } else if (startsWith(buf, "exp ")) {
      uint64_t u;
      sscanf(buf, "exp %lx", &u);
      u = d2u(xexp(u2d(u)));
      printf("%lx\n", u);
    } else if (startsWith(buf, "atan2 ")) {
      uint64_t u, v;
      sscanf(buf, "atan2 %lx %lx", &u, &v);
      u = d2u(xatan2(u2d(u), u2d(v)));
      printf("%lx\n", u);
    } else if (startsWith(buf, "pow ")) {
      uint64_t u, v;
      sscanf(buf, "pow %lx %lx", &u, &v);
      u = d2u(xpow(u2d(u), u2d(v)));
      printf("%lx\n", u);
    } else if (startsWith(buf, "sinh ")) {
      uint64_t u;
      sscanf(buf, "sinh %lx", &u);
      u = d2u(xsinh(u2d(u)));
      printf("%lx\n", u);
    } else if (startsWith(buf, "cosh ")) {
      uint64_t u;
      sscanf(buf, "cosh %lx", &u);
      u = d2u(xcosh(u2d(u)));
      printf("%lx\n", u);
    } else if (startsWith(buf, "tanh ")) {
      uint64_t u;
      sscanf(buf, "tanh %lx", &u);
      u = d2u(xtanh(u2d(u)));
      printf("%lx\n", u);
    } else if (startsWith(buf, "asinh ")) {
      uint64_t u;
      sscanf(buf, "asinh %lx", &u);
      u = d2u(xasinh(u2d(u)));
      printf("%lx\n", u);
    } else if (startsWith(buf, "acosh ")) {
      uint64_t u;
      sscanf(buf, "acosh %lx", &u);
      u = d2u(xacosh(u2d(u)));
      printf("%lx\n", u);
    } else if (startsWith(buf, "atanh ")) {
      uint64_t u;
      sscanf(buf, "atanh %lx", &u);
      u = d2u(xatanh(u2d(u)));
      printf("%lx\n", u);
    } else if (startsWith(buf, "fma ")) {
      uint64_t u, v, w;
      sscanf(buf, "fma %lx %lx %lx", &u, &v, &w);
      u = d2u(xfma(u2d(u), u2d(v), u2d(w)));
      printf("%lx\n", u);
    } else if (startsWith(buf, "sqrt ")) {
      uint64_t u;
      sscanf(buf, "sqrt %lx", &u);
      u = d2u(xsqrt(u2d(u)));
      printf("%lx\n", u);
    } else if (startsWith(buf, "cbrt ")) {
      uint64_t u;
      sscanf(buf, "cbrt %lx", &u);
      u = d2u(xcbrt(u2d(u)));
      printf("%lx\n", u);
    } else if (startsWith(buf, "exp2 ")) {
      uint64_t u;
      sscanf(buf, "exp2 %lx", &u);
      u = d2u(xexp2(u2d(u)));
      printf("%lx\n", u);
    } else if (startsWith(buf, "exp10 ")) {
      uint64_t u;
      sscanf(buf, "exp10 %lx", &u);
      u = d2u(xexp10(u2d(u)));
      printf("%lx\n", u);
    } else if (startsWith(buf, "expm1 ")) {
      uint64_t u;
      sscanf(buf, "expm1 %lx", &u);
      u = d2u(xexpm1(u2d(u)));
      printf("%lx\n", u);
    } else if (startsWith(buf, "log10 ")) {
      uint64_t u;
      sscanf(buf, "log10 %lx", &u);
      u = d2u(xlog10(u2d(u)));
      printf("%lx\n", u);
    } else if (startsWith(buf, "log1p ")) {
      uint64_t u;
      sscanf(buf, "log1p %lx", &u);
      u = d2u(xlog1p(u2d(u)));
      printf("%lx\n", u);
    } else if (startsWith(buf, "sinf ")) {
      uint32_t u;
      sscanf(buf, "sinf %x", &u);
      u = f2u(xsinf(u2f(u)));
      printf("%x\n", u);
    } else if (startsWith(buf, "cosf ")) {
      uint32_t u;
      sscanf(buf, "cosf %x", &u);
      u = f2u(xcosf(u2f(u)));
      printf("%x\n", u);
    } else if (startsWith(buf, "sincosf ")) {
      uint32_t u;
      sscanf(buf, "sincosf %x", &u);
      float2 x = xsincosf(u2f(u));
      printf("%x %x\n", f2u(x.x), f2u(x.y));
    } else if (startsWith(buf, "tanf ")) {
      uint32_t u;
      sscanf(buf, "tanf %x", &u);
      u = f2u(xtanf(u2f(u)));
      printf("%x\n", u);
    } else if (startsWith(buf, "asinf ")) {
      uint32_t u;
      sscanf(buf, "asinf %x", &u);
      u = f2u(xasinf(u2f(u)));
      printf("%x\n", u);
    } else if (startsWith(buf, "acosf ")) {
      uint32_t u;
      sscanf(buf, "acosf %x", &u);
      u = f2u(xacosf(u2f(u)));
      printf("%x\n", u);
    } else if (startsWith(buf, "atanf ")) {
      uint32_t u;
      sscanf(buf, "atanf %x", &u);
      u = f2u(xatanf(u2f(u)));
      printf("%x\n", u);
    } else if (startsWith(buf, "atan2f ")) {
      uint32_t u, v;
      sscanf(buf, "atan2f %x %x", &u, &v);
      u = f2u(xatan2f(u2f(u), u2f(v)));
      printf("%x\n", u);
    } else if (startsWith(buf, "logf ")) {
      uint32_t u;
      sscanf(buf, "logf %x", &u);
      u = f2u(xlogf(u2f(u)));
      printf("%x\n", u);
    } else if (startsWith(buf, "expf ")) {
      uint32_t u;
      sscanf(buf, "expf %x", &u);
      u = f2u(xexpf(u2f(u)));
      printf("%x\n", u);
    } else if (startsWith(buf, "cbrtf ")) {
      uint32_t u;
      sscanf(buf, "cbrtf %x", &u);
      u = f2u(xcbrtf(u2f(u)));
      printf("%x\n", u);
    } else {
      break;
    }

    fflush(stdout);
  }

  return 0;
}
