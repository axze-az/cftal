package main

import "fmt"
import "math"
import "./sleef"

func main() {
     for {
          var u0, u1 uint64;
	  var d0, d1 float64;
	  var s string;

     	  fmt.Scanf("%s", &s);

	  if (s == "sin") {
	     fmt.Scanf("%x", &u0);
	     d0 = math.Float64frombits(u0);
	     d1 = sleef.Sin(d0);
	     u1 = math.Float64bits(d1);
	     fmt.Printf("%x\n", u1);
	  } else if (s == "cos") {
	     fmt.Scanf("%x", &u0);
	     d0 = math.Float64frombits(u0);
	     d1 = sleef.Cos(d0);
	     u1 = math.Float64bits(d1);
	     fmt.Printf("%x\n", u1);
	  } else if (s == "tan") {
	     fmt.Scanf("%x", &u0);
	     d0 = math.Float64frombits(u0);
	     d1 = sleef.Tan(d0);
	     u1 = math.Float64bits(d1);
	     fmt.Printf("%x\n", u1);
	  } else if (s == "asin") {
	     fmt.Scanf("%x", &u0);
	     d0 = math.Float64frombits(u0);
	     d1 = sleef.Asin(d0);
	     u1 = math.Float64bits(d1);
	     fmt.Printf("%x\n", u1);
	  } else if (s == "acos") {
	     fmt.Scanf("%x", &u0);
	     d0 = math.Float64frombits(u0);
	     d1 = sleef.Acos(d0);
	     u1 = math.Float64bits(d1);
	     fmt.Printf("%x\n", u1);
	  } else if (s == "atan") {
	     fmt.Scanf("%x", &u0);
	     d0 = math.Float64frombits(u0);
	     d1 = sleef.Atan(d0);
	     u1 = math.Float64bits(d1);
	     fmt.Printf("%x\n", u1);
	  } else if (s == "log") {
	     fmt.Scanf("%x", &u0);
	     d0 = math.Float64frombits(u0);
	     d1 = sleef.Log(d0);
	     u1 = math.Float64bits(d1);
	     fmt.Printf("%x\n", u1);
	  } else if (s == "exp") {
	     fmt.Scanf("%x", &u0);
	     d0 = math.Float64frombits(u0);
	     d1 = sleef.Exp(d0);
	     u1 = math.Float64bits(d1);
	     fmt.Printf("%x\n", u1);
	  } else if (s == "sincos") {
	     fmt.Scanf("%x", &u0);
	     d0 = math.Float64frombits(u0);
	     d0, d1 = sleef.Sincos(d0);
	     u0 = math.Float64bits(d0);
	     u1 = math.Float64bits(d1);
	     fmt.Printf("%x %x\n", u0, u1);
	  } else if (s == "atan2") {
	     fmt.Scanf("%x %x", &u0, &u1);
	     d0 = math.Float64frombits(u0);
	     d1 = math.Float64frombits(u1);
	     d0 = sleef.Atan2(d0, d1);
	     u0 = math.Float64bits(d0);
	     fmt.Printf("%x\n", u0);
 	  } else if (s == "pow") {
	     fmt.Scanf("%x %x", &u0, &u1);
	     d0 = math.Float64frombits(u0);
	     d1 = math.Float64frombits(u1);
	     d0 = sleef.Pow(d0, d1);
	     u0 = math.Float64bits(d0);
	     fmt.Printf("%x\n", u0);
 	  } else if (s == "sinh") {
	     fmt.Scanf("%x", &u0);
	     d0 = math.Float64frombits(u0);
	     d1 = sleef.Sinh(d0);
	     u1 = math.Float64bits(d1);
	     fmt.Printf("%x\n", u1);
	  } else if (s == "cosh") {
	     fmt.Scanf("%x", &u0);
	     d0 = math.Float64frombits(u0);
	     d1 = sleef.Cosh(d0);
	     u1 = math.Float64bits(d1);
	     fmt.Printf("%x\n", u1);
	  } else if (s == "tanh") {
	     fmt.Scanf("%x", &u0);
	     d0 = math.Float64frombits(u0);
	     d1 = sleef.Tanh(d0);
	     u1 = math.Float64bits(d1);
	     fmt.Printf("%x\n", u1);
	  } else if (s == "asinh") {
	     fmt.Scanf("%x", &u0);
	     d0 = math.Float64frombits(u0);
	     d1 = sleef.Asinh(d0);
	     u1 = math.Float64bits(d1);
	     fmt.Printf("%x\n", u1);
	  } else if (s == "acosh") {
	     fmt.Scanf("%x", &u0);
	     d0 = math.Float64frombits(u0);
	     d1 = sleef.Acosh(d0);
	     u1 = math.Float64bits(d1);
	     fmt.Printf("%x\n", u1);
	  } else if (s == "atanh") {
	     fmt.Scanf("%x", &u0);
	     d0 = math.Float64frombits(u0);
	     d1 = sleef.Atanh(d0);
	     u1 = math.Float64bits(d1);
	     fmt.Printf("%x\n", u1);
	  } else if (s == "sqrt") {
	     fmt.Scanf("%x", &u0);
	     d0 = math.Float64frombits(u0);
	     d1 = sleef.Sqrt(d0);
	     u1 = math.Float64bits(d1);
	     fmt.Printf("%x\n", u1);
	  } else if (s == "cbrt") {
	     fmt.Scanf("%x", &u0);
	     d0 = math.Float64frombits(u0);
	     d1 = sleef.Cbrt(d0);
	     u1 = math.Float64bits(d1);
	     fmt.Printf("%x\n", u1);
	  } else if (s == "exp2") {
	     fmt.Scanf("%x", &u0);
	     d0 = math.Float64frombits(u0);
	     d1 = sleef.Exp2(d0);
	     u1 = math.Float64bits(d1);
	     fmt.Printf("%x\n", u1);
	  } else if (s == "exp10") {
	     fmt.Scanf("%x", &u0);
	     d0 = math.Float64frombits(u0);
	     d1 = sleef.Exp10(d0);
	     u1 = math.Float64bits(d1);
	     fmt.Printf("%x\n", u1);
	  } else if (s == "expm1") {
	     fmt.Scanf("%x", &u0);
	     d0 = math.Float64frombits(u0);
	     d1 = sleef.Expm1(d0);
	     u1 = math.Float64bits(d1);
	     fmt.Printf("%x\n", u1);
	  } else if (s == "log10") {
	     fmt.Scanf("%x", &u0);
	     d0 = math.Float64frombits(u0);
	     d1 = sleef.Log10(d0);
	     u1 = math.Float64bits(d1);
	     fmt.Printf("%x\n", u1);
	  } else if (s == "log1p") {
	     fmt.Scanf("%x", &u0);
	     d0 = math.Float64frombits(u0);
	     d1 = sleef.Log1p(d0);
	     u1 = math.Float64bits(d1);
	     fmt.Printf("%x\n", u1);
	  } else {
	    break;
	  }
     }
}
