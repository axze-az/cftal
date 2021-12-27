// 
// Copyright (C) 2010-2021 Axel Zeuner
// 
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA  
//
#include <iostream>
#include <iomanip>
#include <cftal/config.h>
#include <cftal/x86/intrin.h>
#include <cftal/as.h>

namespace cftal {
    namespace test {
        void
        div_su8();
        
        float
        raw_div_x8(float a, float b);
        
        void
        div_su16();

        float
        raw_div_x16(float a, float b);

        float 
        raw_div(float a, float b);        
        
    }    
}

float
cftal::test::raw_div_x8(float a, float b)
{
#if !defined(__SSE__)
    int32_t x = cftal::as<int32_t>(b);
    x = 0x7EEEEEEE - x;
    float rcp = cftal::as<float>(x);

    for (int i=0; i<2; ++i) {
        float r= 1.0f - rcp * b;
        rcp = rcp + rcp*r;
    }
    float q = rcp * a;
#else
    __m128 vb=_mm_set_ss(b);
    __m128 vrcp=_mm_rcp_ss(vb);
    float rcp=_mm_cvtss_f32(vrcp);
    float q = rcp * a;
#endif    
    return q;
}

float
cftal::test::raw_div_x16(float a, float b)
{
#if !defined(__SSE__)
    int32_t x = cftal::as<int32_t>(b);
    x = 0x7EEEEEEE - x;
    float rcp = cftal::as<float>(x);
    const int _M=3;
#else
    __m128 vb=_mm_set_ss(b);
    __m128 vrcp=_mm_rcp_ss(vb);
    float rcp=_mm_cvtss_f32(vrcp);
    const int _M=1;
#endif    
    for (int i=0; i<_M; ++i) {
        float r= 1.0f - rcp * b;
        rcp = rcp + rcp*r;
    }
    float q = rcp * a;
    return q;
}


float
cftal::test::raw_div(float a, float b)
{
#if !defined(__SSE__)
    int32_t x = cftal::as<int32_t>(b);
    x = 0x7EEEEEEE - x;
    float rcp = cftal::as<float>(x);
    const int _M=3;
#else
    __m128 vb=_mm_set_ss(b);
    __m128 vrcp=_mm_rcp_ss(vb);
    float rcp=_mm_cvtss_f32(vrcp);
    const int _M=1;
#endif    
    for (int i=0; i<_M; ++i) {
        float r= 1.0f - rcp * b;
        rcp = rcp + rcp*r;
    }
    float q = rcp * a;
    const int _N=0;
    for (int i=0; i<_N; ++i) {
        float r= a - b* q;
        q = q + r * rcp;
    }    
    return q;
}


void
cftal::test::div_su8()
{
    std::cout << "checking unsigned 8 bit division" << std::endl;
    for (uint32_t u=0; u < 256; ++u) {
        for (uint32_t v=1; v<256; ++v) {
            uint32_t q=u/v;
            
            const auto offs=0.5f;
            
            auto fu=float(u) + offs;
            auto fv=float(v);
            auto fq=raw_div_x8(fu, fv);
            uint32_t qa=uint32_t(fq);
            
            if (q != qa) {
                std::cout << std::setw(8) << u
                          << std::setw(8) << v
                          << std::setw(8) << q
                          << std::setw(8) << qa
                          << std::setw(8) << int(qa) - int (q)
                          << std::endl;
            }   
        }
    }   
    
    std::cout << "checking signed 8 bit division" << std::endl;
    for (int32_t u=-128; u < 128; ++u) {
        for (int32_t v=-128; v<128; ++v) {
            if (v==0)
                continue;
            int32_t q=u/v;
            
            const auto poffs=0.5f;
            const auto noffs=-poffs;
            auto fu=float(u);
            auto o=fu < 0.0f ? noffs : poffs;
            fu += o;
            auto fv=float(v);
            auto fq=raw_div_x8(fu, fv);
            int32_t qa=int32_t(fq);
            
            if (q != qa) {
                std::cout << std::setw(8) << u
                          << std::setw(8) << v
                          << std::setw(8) << q
                          << std::setw(8) << qa
                          << std::setw(8) << int(qa) - int (q)
                          << std::endl;
            }   
        }
    }   
}


void
cftal::test::div_su16()
{
    std::cout << "checking unsigned 16 bit division" << std::endl;
    for (uint32_t u=0; u < 65356; ++u) {
        for (uint32_t v=1; v<65536; ++v) {
            uint32_t q=u/v;
            
            const auto offs=0.5f;
            
            auto fu=float(u) + offs;
            auto fv=float(v);
            auto fq=raw_div_x16(fu, fv);
            uint32_t qa=uint32_t(fq);
            
            if (q != qa) {
                std::cout << std::setw(8) << u
                          << std::setw(8) << v
                          << std::setw(8) << q
                          << std::setw(8) << qa
                          << std::setw(8) << int(qa) - int (q)
                          << std::endl;
            }   
        }
    }   

    std::cout << "checking signed 16 bit division" << std::endl;
    for (int32_t u=-32768; u < 32768; ++u) {
        for (int32_t v=-32768; v<32768; ++v) {
            if (v==0)
                continue;
            int32_t q=u/v;
            
            const auto poffs=0.5f;
            const auto noffs=-poffs;
            auto fu=float(u);
            auto o= fu < 0.0f ? noffs : poffs;
            fu += o;
            auto fv=float(v);
            auto fq=raw_div_x16(fu, fv);
            int32_t qa=int32_t(fq);
            
            if (q != qa) {
                std::cout << std::setw(8) << u
                          << std::setw(8) << v
                          << std::setw(8) << q
                          << std::setw(8) << qa
                          << std::setw(8) << int(qa) - int (q)
                          << std::endl;
            }   
        }
    }   
}


int main(int argc, char** argv)
{
    cftal::test::div_su8();
    cftal::test::div_su16();
    return 0;
}
