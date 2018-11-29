//
// Copyright Axel Zeuner 2010-2018. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "cftal/test/program.h"
#include <cstdlib>

cftal::test::pgm_args
cftal::test::parse(int argc, char** argv, std::size_t cnt)
{
    using std::string_view;
    pgm_args args(cnt);
    int non_option_arg=0;
    bool err=false;
    bool fast=false;

    args._data_dir=dirname(argv[0]);
    args._data_dir += "/../../test/data";


    for (int i=1; i<argc; ++i) {
        string_view ai(argv[i]);
        if (ai == "--speed") {
            args._speed_only= true;
        } else if (ai == "--fast") {
            fast = true;
        } else if (ai == "--cache") {
            args._use_cache=true;
        } else if (ai == "--mt") {
            args._mt = true;
        } else if (ai == "--no-mt") {
            args._mt = false;
        } else {
            if (ai[0] != '-') {
                args._data_dir=std::string(ai.data(), ai.length());
                ++non_option_arg;
            } else {
                err=true;
            }
        }
    }
    if (non_option_arg>1 || err) {
        std::cerr << argv[0]
                  << " [--fast] [--speed] [--[no-]mt] [--cache]\n"
                     "--fast  reduces the test count\n"
                     "--speed performs a speed test only\n"
                     "--mt    force multithreading\n"
                     "--no-mt disable multithreading\n"
                     "--cache use a file cache\n"
                  << std::flush;
        std::exit(3);
    }
    if (args._speed_only)
        args._cnt <<= 3;
    if (fast)
        args._cnt >>= 4;
    return args;
}

