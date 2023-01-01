//
// Copyright (C) 2010-2023 Axel Zeuner
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
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
//
#include "cftal/test/program.h"
#include <cstdlib>
#include <thread>

cftal::test::pgm_args::pgm_args(std::size_t c)
    : _speed_only(false),
      _mt(std::thread::hardware_concurrency()),
      _use_cache(false), _fast(false),
      _slow(false),
      _data_dir("../test/data/"),
      _cnt(c)
{
}

std::ostream&
cftal::test::operator<<(std::ostream& s, const pgm_args& ags)
{
    s << '(';
    if (ags._mt>0) {
	s << "mt=" << ags._mt;
    } else {
	s << "st";
    }
    s << (ags._speed_only ? ", speed only" : "")
      << (ags._fast ? ", fast" : "" )
      << (ags._slow ? ", slow" : "" )
      << ')';
    return s;
}

cftal::test::pgm_args
cftal::test::parse(int argc, char** argv, std::size_t cnt)
{
    using std::string_view;
    pgm_args args(cnt);
    int non_option_arg=0;
    bool err=false;

    args._data_dir=dirname(argv[0]);
    args._data_dir += "/../../test/data";

    for (int i=1; i<argc; ++i) {
        string_view argi(argv[i]);
        string_view::size_type eq_pos=argi.find('=');
        string_view ai(argi.substr(0, eq_pos));
        if (argi == "--speed") {
            args._speed_only= true;
        } else if (argi == "--fast") {
            args._fast = true;
            args._slow = false;
        } else if (argi == "--slow") {
            args._slow = true;
            args._fast = false;
        } else if (argi == "--cache") {
            args._use_cache=true;
        } else if (ai == "--mt") {
            if (argi.length()>eq_pos) {
                string_view pl=argi.substr(eq_pos+1);
                std::istringstream is(std::string(pl.data(), pl.length()));
                uint32_t tc=0;
                is >> tc;
                if (is.fail() || !is.eof()) {
                    err=true;
                } else {
                    args._mt=tc;
                }
            } // else use default value
        } else if (argi == "--no-mt") {
            args._mt = 0;
        } else {
            if (argi[0] != '-') {
                args._data_dir=std::string(ai.data(), ai.length());
                ++non_option_arg;
            } else {
                err=true;
            }
        }
    }
    if (non_option_arg>1 || err) {
        std::cerr << argv[0]
                  << " [--fast|--slow] [--speed] [--[no-]mt] [--cache]\n"
                     "--fast   reduces the test count\n"
                     "--slow   increases the test count\n"
                     "--speed  performs a speed test only\n"
                     "--mt[=X] force multithreading with X threads\n"
                     "--no-mt  disable multithreading\n"
                     "--cache  use a file cache\n"
                  << std::flush;
        std::exit(3);
    }
    if (args._speed_only)
        args._cnt <<= 3;
    if (args._slow)
        args._cnt <<= 3;
    if (args._fast)
        args._cnt >>= 4;
    return args;
}
